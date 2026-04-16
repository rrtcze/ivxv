..  IVXV collector service administration guide

Appendices
==========

.. _utiliidid:

Utilities
---------

Overview and help text of collector service management command-line utilities.

.. contents:: .
   :local:
   :depth: 1


Data Store Utilities
^^^^^^^^^^^^^^^^^^^^

.. include:: utiliitide-abiteave/ivxv-create-data-dirs.inc

.. include:: utiliitide-abiteave/ivxv-db-reset.inc

.. include:: utiliitide-abiteave/ivxv-db-dump.inc


Service State Utilities
^^^^^^^^^^^^^^^^^^^^^^^^

.. include:: utiliitide-abiteave/ivxv-status.inc

.. include:: utiliitide-abiteave/ivxv-service.inc


Event Log Utilities
^^^^^^^^^^^^^^^^^^^^

.. include:: utiliitide-abiteave/ivxv-eventlog-dump.inc


User Management Utilities
^^^^^^^^^^^^^^^^^^^^^^^^^^

.. include:: utiliitide-abiteave/ivxv-users-list.inc


Configuration Utilities
^^^^^^^^^^^^^^^^^^^^^^^^

.. include:: utiliitide-abiteave/ivxv-collector-init.inc

.. include:: utiliitide-abiteave/ivxv-cmd-load.inc

.. include:: utiliitide-abiteave/ivxv-config-validate.inc

.. include:: utiliitide-abiteave/ivxv-config-apply.inc

Applying settings to managed services is possible once the collector service
technical settings have been loaded into the management service.

Configuration application order:

#. Technical settings together with trust root settings.

   #. Installing service software;

   #. Creating management service access to the managed service account;

   #. Applying service logging settings;

   #. Removing management service access to the service host root account
      (only if there are no more unconfigured services on the service machine);

   #. Applying trust root to the service;

   #. Applying technical settings to the service;

#. Choices list;

#. District list;

#. Voter lists;

The log collection service differs from other managed services:

#. The log collection service is configured before other services to ensure
   the earliest possible log collection.

#. No other settings besides log collection service settings are applied to the
   log collection services (the log collection service does not need trust root
   settings, collector service technical settings, or election settings).

Applying election lists (choices and voter lists) means transferring the list
to the storage service through the service that serves the corresponding list.

For example, the choices list is applied to only one (randomly selected)
choices service, which transfers the list to the storage service. Through the
storage service, the list is available to all other choices services.

.. include:: utiliitide-abiteave/ivxv-voter-list-download.inc

.. include:: utiliitide-abiteave/ivxv-secret-load.inc

.. include:: utiliitide-abiteave/ivxv-copy-log-to-logmon.inc

.. include:: utiliitide-abiteave/ivxv-update-packages.inc

.. include:: utiliitide-abiteave/ivxv-backup-crontab.inc


Data Export and Backup Utilities
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. include:: utiliitide-abiteave/ivxv-export-votes.inc

.. include:: utiliitide-abiteave/ivxv-backup.inc

.. include:: utiliitide-abiteave/ivxv-generate-processor-input.inc

.. include:: utiliitide-abiteave/ivxv-voterstats.inc

.. include:: utiliitide-abiteave/ivxv-voting-sessions.inc


Daemons
^^^^^^^^

.. include:: utiliitide-abiteave/ivxv-agent-daemon.inc


Internal Utilities
^^^^^^^^^^^^^^^^^^^

.. attention::

   Internal utilities are used by the management daemon for managing
   sub-services and generally do not need to be run separately.

.. include:: utiliitide-abiteave/ivxv-admin-helper.inc

.. include:: utiliitide-abiteave/ivxv-admin-sudo.inc


Configuration Files
--------------------

.. _ivxv-logcollector.conf:

Log Collection Service Configuration File
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. literalinclude:: ../../../common/collector/config/rsyslog-logcollector.conf
   :name: /etc/rsyslog.d/ivxv-logcollector.conf
   :language: text
   :linenos:


Additional Settings
--------------------

.. _configure-ssh-idcard-auth:

SSH User Authentication Using ID Card
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

It is possible to authenticate to the SSH service using an ID card public key,
using the PKCS#11-capable SSH client ``kitty.exe`` (http://kitty.9bis.net/).

For security reasons, password authentication to the management interface SSH
service should be disabled. To disable password authentication, set the parameter
``PasswordAuthentication`` to ``no`` in the configuration file
:file:`/etc/ssh/sshd_config`::

   # To disable tunneled clear text passwords, change to no here!
   PasswordAuthentication no

The location of the authorized users file (:file:`/etc/ssh/kasutajad`) must be
specified in the file :file:`/etc/ssh/sshd_config` using the parameter
``AuthorizedKeysFile``:

   ``AuthorizedKeysFile /etc/ssh/kasutajad``

.. important::

   To apply changes made in the configuration file ``/etc/ssh/sshd_config``,
   the SSH service must be restarted::

      # service ssh restart
      [ ok ] Restarting OpenBSD Secure Shell server: sshd.

Setting up a user to authenticate with an ID card authentication certificate
is done as follows:

#. Creating a user account:

   .. code-block:: shell-session

      # adduser --disabled-password kasutajanimi
      # usermod -a -G www-data kasutajanimi

#. Saving the user's ID card authentication certificate in PEM format
   to the file :file:`usercert.cer` (using the ID card management tool);

#. Extracting the user's public key from the certificate and saving it to the
   file :file:`userpubkey.pem`:

   .. code-block:: shell-session

      # openssl x509 -in usercert.cer -pubkey -noout > userpubkey.pem

#. Converting the public key to PKCS#8 format, adding the user identifier,
   and saving it to the SSH authorized users file
   :file:`/etc/ssh/kasutajad`:

   .. code-block:: shell-session

      # KEY=$(ssh-keygen -i -m PKCS8 -f userpubkey.pem)
      # echo "$KEY kasutaja@eesti.ee" >> /etc/ssh/kasutajad

#. Verifying that the added entry is in the format ``ssh-rsa PKCS8-key``
   user-identifier:

   .. code-block:: shell-session

      # tail -1 /etc/ssh/kasutajad
      ssh-rsa AAAAB3NzaC1yc2EAAAAELGuiTwAAAIEAxZf/TuSrGJEU1PlfkY9jJ33VOYVZ9Vao0Uiytlf8
      7HJu/78fCIB7m05J7ibpMhsZoZ4DElU7ve0VwbvdDS3srh1OhiQcUjpznTlx4rIM1vkHwadrHtmF+BNi
      DwbLbbdD5y3puGcLH+sLuwba6Vuc3aU0QuqzenYmY9pV7w9y0wc= kasutaja@eesti.ee


Data Store
-----------

Management service data is stored in the file system and in a database. Data
from external systems that has been transferred to the management service in
file form is stored in the file system. Data generated during the operation of
the management service is stored in the database.


Data Stored in the File System
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

*  :file:`/etc/ivxv/` — configuration and list files applied to and currently
   valid for the collector service;

*  :file:`/var/lib/ivxv/` — collector service management service data files;

*  :file:`/var/lib/ivxv/admin-ui-data/` — JSON files served for the management
   service web interface;

*  :file:`/var/lib/ivxv/admin-ui-data/status.json` — collector service status
   summary data;

*  :file:`/var/lib/ivxv/admin-ui-permissions/` — management service web interface
   user permissions (for the Apache web server);

*  :file:`/var/lib/ivxv/ballot-box/` — directory for storing the downloaded e-ballot box;

*  :file:`/var/lib/ivxv/commands/` — history of command files applied for
   managing the collector service;

*  :file:`/var/lib/ivxv/commands/<command-type>-<timestamp>.bdoc` —
   digitally signed command in ``ASiC-E`` format.

*  :file:`/var/lib/ivxv/commands/<command-type>-<timestamp>.json` —
   command status file in JSON format.

*  :file:`/var/lib/ivxv/db/` — management service database directory;

*  :file:`/var/lib/ivxv/db/ivxv-management.db` — management service database
   file;

*  :file:`/var/lib/ivxv/ivxv-management-events.log` — management service event
   log;

*  :file:`/var/lib/ivxv/service/` — other service-specific files
   (e.g., public key extracted from the registration key);

*  :file:`/var/lib/ivxv/upload/` — files loaded into the collector service
   through the web interface;

Data Stored in the Database
^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Data field name and description:

* ``collector/state`` — collector service state;

* ``config/election`` — authorized user data of the person who digitally signed
  the election settings applied to the collector service in the format ``<CN> <timestamp>``;

* ``config/technical`` — authorized user data of the person who digitally signed
  the technical settings applied to the collector service in the format ``<CN> <timestamp>``;

* ``config/trust`` — authorized user data of the person who digitally signed
  the trust root settings applied to the collector service in the format ``<CN> <timestamp>``;

* ``election/election-id`` — election identifier;

* ``election/electionstart`` — election start time;

* ``election/electionstop`` — election end time;

* ``election/servicestart`` — collector service start time;

* ``election/servicestop`` — collector service stop time;

* ``host/<hostname>/state`` — service host state;

* ``list/choices`` — authorized user data of the person who digitally signed
  the choices list loaded into the management service in the format ``<CN> <timestamp>``;

* ``list/choices-loaded`` — authorized user data of the person who digitally
  signed the choices list loaded into the choices services in the format ``<CN>
  <timestamp>``;

* ``list/districts`` — authorized user data of the person who digitally signed
  the district list loaded into the choices services in the format ``<CN>
  <timestamp>``;

* ``list/districts-loaded`` — authorized user data of the person who digitally
  signed the district list loaded into the choices services in the format ``<CN>
  <timestamp>``;

* ``list/voters0000`` — authorized user data of the person who digitally signed
  the initial voter list loaded into the management service in the format ``<CN> <timestamp>``;

* ``list/voters<list-number>`` (``list-number >= 01``) — timestamp of the
  download time of the voter change list loaded into the management service;

* ``list/voters<list-number>-state`` — state of the voter list loaded into the
  choices services.

  Possible values:

  1. ``PENDING`` — loaded into the management service;

  2. ``APPLIED`` — applied to the choices service;

  3. ``INVALID`` — the list is marked as faulty and awaits the administrator's
     decision on skipping (only for change lists);

  4. ``SKIPPED`` — the list has been skipped (only for change lists).

* ``logmonitor/address`` — monitoring service address or network name;

* ``logmonitor/last-data`` — time of the last statistics file retrieval from
  the monitoring service;

* ``user/<idcode>`` — management service user name and roles in the format
  ``<surname,name> <role>[,<role>]``;

* ``service/<service-id>/service-type`` — Service type;

* ``service/<service-id>/technical-conf-version`` — Version of the technical
  configuration applied to the service;

* ``service/<service-id>/election-conf-version`` — Version of the election
  configuration applied to the service;

* ``service/<service-id>/network`` — Service subnet name;

* ``service/<service-id>/state`` — Service state;

* ``service/<service-id>/ping-errors`` — Number of consecutive errors in
  service liveness checks;

* ``service/<service-id>/last-data`` — Time of the last service status retrieval;

* ``service/<service-id>/ip-address`` — Service IP address;

* ``service/<service-id>/bg_info`` — Service background information as a string
  (e.g., error message generated during a liveness check);

* ``service/<service-id>/backup-times`` — Backup service automatic backup
  times;

* ``service/<service-id>/mid-token-key`` — Mobile-ID/Smart-ID/Web eID support
  service identity token key file checksum (SHA256);

* ``service/<service-id>/tls-cert`` — Service TLS certificate file
  checksum (SHA256);

* ``service/<service-id>/tls-key`` — Service TLS certificate key file
  checksum (SHA256);

* ``service/<service-id>/tspreg-key`` — Voting service time-stamping service
  signing key file checksum (SHA256);

Symbols used:

* ``<command-type>`` — command type:

   #. ``trust`` — trust root settings;

   #. ``technical`` — collector service settings;

   #. ``election`` — election settings;

* ``<CN>`` — ID card CN field in the format ``SURNAME,FIRSTNAME,PERSONALCODE``;

* ``<config-type>`` is the configuration type. The trust root configuration is
  ``trust``, the election configuration is ``election``, and the collector
  service technical configuration is ``tech``;

* ``<hostname>`` — service host name;

* ``<list-number>`` — two-digit sequence number of the election list; the first
  list is numbered 01.

* ``<service-id>`` — service identifier from the collector service settings;

* ``<timestamp>`` is a timestamp in ISO-8601 format.


.. _etcd-zabbix:

Monitoring Cluster State with Zabbix
--------------------------------------

The etcd cluster ensures system operation even in situations where a cluster
member loses functionality (crash, network connection loss, etc.). However, it
is important to monitor such events and identify their root cause. To detect
etcd crashes, the entry ``ivxv.ee/service/storage.EtcdTerminatedError`` should
be monitored in the storage service logs (``ivxv-YYYY-MM-DD-HH.log``).

Additionally, the etcd command-line client can be used to query the status of
cluster members. Since all client requests in the IVXV cluster are
authenticated, the command must be executed on one of the ``ivxv-storage``
service machines under the ``ivxv-storage`` user account (or root) privileges:

.. code-block:: shell-session

   # ivxv-storage@ivxv1:~$ env ETCDCTL_API=3 etcdctl \
         --cacert /var/lib/ivxv/service/storage@storage1.ivxv.ee/ca.pem \
         --cert /var/lib/ivxv/service/storage@storage1.ivxv.ee/tls.pem \
         --key /var/lib/ivxv/service/storage@storage1.ivxv.ee/tls.key \
         --endpoints ivxv1:2379,ivxv2:2379,ivxv3:2379 \
         endpoint status

   ivxv1:2379, 2d0df029f29770a4, 3.2.17, 25 kB, true, 12, 15
   ivxv2:2379, d4a9ae16c8557764, 3.2.17, 25 kB, false, 12, 15
   ivxv3:2379, e8914f4e0b89b80f, 3.2.17, 25 kB, false, 12, 15

The column meanings in the response are as follows:

 #. cluster member;
 #. cluster member identifier;
 #. etcd version;
 #. database size (max 8GB i.e., 8589934592);
 #. whether the specific cluster member is currently the leader;
 #. RAFT term (essentially the number of leader elections that have occurred);
 #. RAFT index — number of etcd write operations (including
    configuration changes).

An important parameter for monitoring is the RAFT term. A change in its value
indicates a leader change, which is usually associated with problems in cluster
operation — the existing leader does not respond quickly enough to cluster
member requests.

Command-line explanation:

 * ``env ETCDCTL_API=3``: we use etcd API version 3 (in Ubuntu version
   20.04 LTS, the ``etcdctl`` default API version is still 2);
 * ``--cacert``: we only trust servers whose certificate is issued by this CA;
 * ``--cert`` and ``--key``: we use the ivxv1 storage service certificate and
   key for client authentication;
 * ``--endpoints``: which servers to send the request to. Here, instead of
   listing all three, only one can be listed: in that case, the output will
   contain only one row. Useful, e.g., when Zabbix wants to query only that
   instance in each storage service;
 * ``endpoint status``: we query the status of the listed servers.


The output can also be requested in machine-readable JSON format
(parameter ``-w json``):

   .. code-block:: shell-session

      ivxv-storage@ivxv1:~$ env ETCDCTL_API=3 etcdctl \
          --cacert /var/lib/ivxv/service/storage@storage1.ivxv.ee/ca.pem \
          --cert /var/lib/ivxv/service/storage@storage1.ivxv.ee/tls.pem \
          --key /var/lib/ivxv/service/storage@storage1.ivxv.ee/tls.key \
          --endpoints ivxv1:2379,ivxv2:2379,ivxv3:2379 \
          endpoint status -w json

      [{"Endpoint":"ivxv1:2379","Status":{"header":{"cluster_id":1867986262344190226,"member_id":3246514969358332068,"revision":1,"raft_term":12},"version":"3.2.17","dbSize":24576,"leader":3246514969358332068,"raftIndex":15,"raftTerm":12}},
      {"Endpoint":"ivxv2:2379","Status":{"header":{"cluster_id":1867986262344190226,"member_id":15323970619978381156,"revision":1,"raft_term":12},"version":"3.2.17","dbSize":24576,"leader":3246514969358332068,"raftIndex":15,"raftTerm":12}},
      {"Endpoint":"ivxv3:2379","Status":{"header":{"cluster_id":1867986262344190226,"member_id":16758262885041944591,"revision":1,"raft_term":12},"version":"3.2.17","dbSize":24576,"leader":3246514969358332068,"raftIndex":15,"raftTerm":12}}]
