# IVXV Configuration Distribution Flow

## What this document covers

This document explains how configuration gets from the central management server
to the individual collector service hosts in the IVXV Internet Voting system. It
is intended for system engineers who are familiar with Linux administration but
may not know the IVXV internals in depth.

## Background

IVXV is composed of multiple **microservices** (voting, verification, choices,
storage, proxy, etc.) that run on separate hosts. A central **management service**
(also called collector-admin) coordinates them all. Each microservice is a Go
binary managed by systemd.

All configuration in IVXV is packaged in **signed BDOC containers** — digitally
signed archives that contain YAML files. This ensures that only authorized
personnel can change the system configuration. The trust chain starts with a
**trust root** config that defines whose signatures are accepted.

## The push model

IVXV uses a **push model**: the management service copies config files to service
hosts over SSH. Services never fetch their own config. This means:

- The management host needs SSH access to every service host.
- Config changes are applied by running a CLI tool on the management host.
- Services read config from local files on disk — they have no network config
  endpoint.

## Config types

There are five types of configuration, applied in this fixed order:

| # | Type         | What it contains                                        | Which services receive it       |
|---|--------------|---------------------------------------------------------|---------------------------------|
| 1 | `technical`  | Network topology, TLS settings, storage addresses, etc. | All services                    |
| 2 | `election`   | Election ID, voting period, questions, rate limits       | Services that handle votes      |
| 3 | `choices`    | Candidate/choice lists for the ballot                   | `choices` service only          |
| 4 | `districts`  | Electoral district definitions                          | `choices` service only          |
| 5 | `voters`     | Voter registry (can have multiple changesets)            | `voting` service only           |

Types 1–2 are core configs. Types 3–5 are lists that are loaded after the core
services are running.

## Step-by-step: what happens when you apply config

### Step 1 — Upload config to the management service

An authorized operator uploads a signed BDOC container using the management web
interface or CLI. The management service validates the signature, extracts
metadata, and stores the file locally. At this point nothing has changed on the
service hosts yet.

### Step 2 — Run `ivxv-config-apply`

The operator (or the management daemon automatically) runs:

```
ivxv-config-apply [--type=<type>] [<service-id> ...]
```

This tool reads the management database to find out which configs have been
uploaded and which services still need them. It then processes services in
dependency order:

1. **Log collectors** first (so logging works before anything else starts)
2. **Regular services** (voting, verification, choices, storage, etc.)
3. **Proxy (HAProxy)** last (so backends are ready before the proxy routes to them)

### Step 3 — For each service: copy, set permissions, notify

For every service that needs an update, the tool does the following over SSH:

```
┌─ Management host ─────────────────────────────────────────────────────┐
│                                                                       │
│  1. SCP the .bdoc file ──────────────►  /etc/ivxv/<type>.bdoc         │
│                                         (on the service host)         │
│                                                                       │
│  2. SSH: chmod 0640 /etc/ivxv/<type>.bdoc                             │
│     (readable by the service account, not world-readable)             │
│                                                                       │
│  3. For list configs (choices/districts/voters) only:                 │
│     SSH: ivxv-choiceimp / ivxv-districtimp / ivxv-voterimp            │
│     (tells the running service to reload the list without restart)    │
│                                                                       │
│  4. SSH: systemctl restart ivxv-<type>@<service-id>                   │
│     (service restarts and reads the new config from /etc/ivxv/)       │
│                                                                       │
└───────────────────────────────────────────────────────────────────────┘
```

### Step 4 — The service reads config on startup

When a Go service starts (or restarts), it reads three files from well-known
paths on the local filesystem:

| File                        | Contents                           |
|-----------------------------|------------------------------------|
| `/etc/ivxv/trust.bdoc`     | Trust root (whose signatures to accept) |
| `/etc/ivxv/technical.bdoc` | Network topology, TLS, storage     |
| `/etc/ivxv/election.bdoc`  | Election parameters                |

The service:

1. Opens each BDOC container
2. Verifies the digital signature against the trust root
3. Parses the YAML configuration inside
4. Begins serving requests with the new configuration

If signature verification fails, the service refuses to start.

### Step 5 — Result is reported back

After each service is configured, `ivxv-config-apply` records the result
(success/failure and config version) in the management database. The operator
can see the status in the management web interface.

## File locations summary

| Host             | Path                              | Purpose                              |
|------------------|-----------------------------------|--------------------------------------|
| Management host  | `active_config_files_path/`       | Uploaded BDOC containers (source)    |
| Management host  | Management database               | Tracks config versions per service   |
| Service host     | `/etc/ivxv/trust.bdoc`            | Trust root config                    |
| Service host     | `/etc/ivxv/technical.bdoc`        | Technical config                     |
| Service host     | `/etc/ivxv/election.bdoc`         | Election config                      |
| Service host     | `/etc/ivxv/choices.bdoc`          | Choices list                         |
| Service host     | `/etc/ivxv/districts.bdoc`        | Districts list                       |
| Service host     | `/etc/ivxv/voters<NNNN>.zip`      | Voter list changesets                |

## Key source files

If you need to trace the implementation:

| File | Role |
|------|------|
| `collector-admin/ivxv_admin/cli_utils/config_utils/config_apply.py` | Orchestrates the entire apply process |
| `collector-admin/ivxv_admin/service/service.py` — `copy_cfg_to_service()` | SCP + permissions + notify for a single service |
| `collector-admin/ivxv_admin/service/service.py` — `apply_tech_cfg()` | Technical config apply (install + trust + tech + restart) |
| `collector-admin/ivxv_admin/service/service.py` — `apply_election_cfg()` | Election config apply (copy + enable systemd + restart) |
| `common/collector/command/command.go` — `New()` | Go service startup: parses CLI flags, loads configs |
| `common/collector/conf/conf.go` — `New()` | Opens BDOC containers, verifies signatures, parses YAML |

## Troubleshooting tips

- **Service won't start after config apply?** Check that `/etc/ivxv/trust.bdoc`
  exists and that the election/technical configs are signed by a key the trust
  root recognizes.
- **Config apply fails with SSH errors?** Verify that the management host has SSH
  key access to the service host's `ivxv-admin` account.
- **Lists not updating?** List changes (choices/voters/districts) use importer
  tools (`ivxv-choiceimp`, etc.) that run on the service host. Check the service
  logs for import errors.
- **Want to apply config to just one service?** Pass the service ID:
  `ivxv-config-apply <service-id>`

