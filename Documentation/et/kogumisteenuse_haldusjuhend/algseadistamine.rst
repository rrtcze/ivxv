..  IVXV collector service administration guide

Initial Setup
=============

Initial system setup means installing and configuring the system for the
elections being conducted.

.. _nouded-platvormile:

Platform Requirements
---------------------

The collector service runs on the platform ``Ubuntu 20.04 LTS (Focal Fossa)``.

Mapping External Services
--------------------------

During the mapping of external services supported by the collector service and
used in the elections being conducted (Mobile-ID, Smart-ID, OCSP, etc.), a list
of external services and the data required for data exchange with them (network
address, port, etc.) is compiled.

External service data serves as input when composing the collector service
technical settings (:ref:`seadistuste_koostamine`).

As a result of mapping external services, the collector service provider has a
list of external services used by the collector service together with the
parameters required for using the services.


Preparing Support Services
---------------------------

Support services for the collector service are:

#. Technical monitoring service;

#. Log monitoring service;

#. Backup service.

Preparing Technical Monitoring
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. important::

   The collector service provider must perform technical hardware monitoring
   for the hardware allocated for the collector service operation.

The technical monitoring service is a monitoring and alerting system based on
`Zabbix <http://www.zabbix.com/>`_ software. The Zabbix server is installed and
configured independently by the collector service provider.

Technical monitoring may also include collector service software components as
described in section ":ref:`etcd-zabbix`".

For monitoring to function, persons responsible for monitoring must be designated
and their direct notification by the monitoring program about detected
anomalies must be ensured.

In addition to standard technical monitoring (service machine
CPU/disk usage, etc.), the collector service management service performs
sub-service monitoring and notifies the technical monitoring server of detected
anomalies.

.. todo::

   Add technical monitoring notification support to the management service!

As a result of preparing technical monitoring, the collector service provider
has a technical monitoring server with monitoring software installed and
where persons responsible for technical monitoring and their notification
methods are defined.


Preparing Log Monitoring
^^^^^^^^^^^^^^^^^^^^^^^^^

The log monitoring service consists of an rsyslog log server with analysis and
visualization software (Log Monitor, `Grafana <https://grafana.com/>`_).

Preparing log monitoring and integrating it with the collector service is
described in the document ``IVXV Activity Log
Monitoring Solution``.

As a result of preparing log monitoring, the collector service provider has a
log monitoring server with log monitoring software installed and where persons
with access to log monitoring data are defined.


Preparing Backup
^^^^^^^^^^^^^^^^^

The backup service is a backup server installed and configured by the collector
service provider, which is responsible for preserving backup copies created by
the collector service's internal backup server.

As a result of preparing backup, the collector service provider has a backup
server capable of backing up data through the collector service backup interface.


.. _seadistuste_koostamine:

Composing Collector Service Settings
--------------------------------------

Collector service settings consist of three separate parts:

#. **Trust root settings** contain data for verifying the signatures of
   settings (including the trust root itself) and the list of collector service
   administrator authorizations.

#. **Collector service technical settings** define the technical parameters of
   the collector service, the services used for conducting the election, as well
   as the sub-services that are part of the collector service.

#. **Election settings** define the settings for a single election.

The preparation of settings is described in the document IVXV-JSK-\* "IVXV
Electronic Voting Information System Configuration Guide". Settings to be
applied to the collector service must be packaged in an ASiC-E container and
signed by an authorized user.

As a result of composing collector service settings, the collector service
provider has the configuration packages needed for configuring the collector
service. All settings are signed by person(s) whose authorizations are described
in the trust root settings or whose authorizations are defined using separate
commands.


.. _taristu-paigaldamine:

Installing Collector Service Infrastructure
---------------------------------------------

The collector service infrastructure is allocated for providing the service
according to the prepared settings (:ref:`seadistuste_koostamine`).

In each service machine:

#. the hostname must be configured (file :file:`/etc/hostname`);

#. the SSH service must be installed (software package ``openssh-server``);

#. the technical monitoring service agent must be installed
   (software package ``zabbix-agent``);

#. the correct time must be ensured
   (for example, using the time service ``ntp``).

#. name resolution must be configured to allow resolving the addresses of all
   service machines;

#. the Estonian locale with UTF-8 encoding support ``et_EE.UTF-8`` must be
   configured (either the ``locales`` package with the named locale configured,
   or the ``locales-all`` package, which installs all supported locales).

.. note::

   The name resolution used by each service machine must ensure that the
   names of hosts used for communication resolve correctly.

   Situations where a hostname resolves to multiple addresses or to an
   address unreachable by other hosts must be avoided.

   The following example describes a possible situation in the file
   :file:`/etc/hosts`, where after operating system installation, the hostname
   ``ivxv123`` is assigned to two interfaces. With such a configuration, a
   situation may arise where a service configured to accept connections on the
   address ``ivxv123`` starts listening on the local interface ``127.0.0.1``
   and is not accessible to other services through the public interface
   ``192.168.10.1``.

   .. code-block:: text

      # /etc/hosts
      127.0.0.1     ivxv123
      192.168.10.1  ivxv123

A list must be compiled from the hosts allocated for the collector service
infrastructure, containing the subnet location of the host, host name,
IP address, SSH server public key, and services planned for the host.

Example of the collector service infrastructure list:

.. code-block:: text

   Valimiste infrastruktuuri andmed

     Alamvõrk: zone1

        IP-aadress: 172.16.238.10
        Hostinimi: admin
        SSH-serveri avalik võti:
          ecdsa-sha2-nistp256 AAAAE2VjZHNhLX...SgtbbE= root@admin

        IP-aadress: 172.16.238.41
        Hostinimi: ivxv1
        SSH-serveri avalik võti:
          ecdsa-sha2-nistp256 AAAAE2VjZHNhLX...mN8ul0= root@ivxv1

     Alamvõrk: zone2

        IP-aadress: 172.16.100.63
        Hostinimi: ivxv2
        SSH-serveri avalik võti:
          ecdsa-sha2-nistp256 AAAE2VjZHNhLXN...rtWT7A= root@ivxv2

Hosts belonging to the collector service infrastructure must be added to
technical monitoring.

As a result of installing the collector service infrastructure, the collector
service provider has a documented platform for installing the collector service
in the designated configuration. All (virtual) machines in the infrastructure
are accessible by the technical monitoring service and no problems have been
detected in their state.


Creating Network Access
------------------------

The existence of network access according to the settings is required for
installing and configuring the collector service.


System Administrators and Users
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

#. From the collector service system administrators' computers to the management
   service (protocol SSH, port 22);

#. From the management service users' computers to the management service
   (protocol HTTPS, port 443);

#. From the collector service system administrators' computers to the log
   monitoring service (protocol SSH, port 22);

#. From the log monitoring users' computers to the log monitoring service
   (protocol HTTPS, port 443).


Inter-Service Communication
^^^^^^^^^^^^^^^^^^^^^^^^^^^^

#. From the management service to all microservices
   (protocol SSH, port 22);

#. From the management service to the log monitoring service
   (protocol SSH, port 22);

#. From all microservice hosts to all log collection services
   (protocol RELP, port 20514);

#. From all microservice hosts to all external log collection services
   (including the log monitoring service)
   (protocol RELP, port 20514);

#. From all microservice hosts to the log monitoring service
   (protocol SSH, port 22);

#. From all log collection service hosts to the log monitoring service
   (protocol SSH, port 22);

#. From the proxy service to other microservices except the storage service
   (protocol TLS, port according to technical settings);

#. From the choices service to storage services
   (protocol TLS, port according to technical settings);

#. From the voting service to storage services
   (protocol TLS, port according to technical settings);

#. From the verification service to storage services
   (protocol TLS, port according to technical settings);

#. From the storage service to other storage services
   (protocol TLS, port according to technical settings);

#. From the Mobile-ID support service to the external Mobile-ID service
   (protocol HTTP(S), port according to technical settings);

#. From the Smart-ID support service to the external Smart-ID service
   (protocol HTTP(S), port according to technical settings);

#. From other microservices to the Session status support service
   (protocol RPC, port according to technical settings);

#. From the voting service to the external qualification service
   (protocol HTTP(S), port according to technical settings);

#. From the backup service to the management service
   (protocol SSH, port 22);

#. From the backup service to log collection services
   (protocol SSH, port 22);

#. From the backup service to storage services
   (protocol SSH, port 22);


Voter
^^^^^^

#. From the voter's device to the proxy service
   (protocol TLS, port according to technical settings, presumably 443).


Installing the Management Service
-----------------------------------

The management service is installed on the management service host.

To install the management service, **all** collector service software packages
must be copied to the management service machine directory :file:`/etc/ivxv/debs/`.
The management service is installed from these packages, and the management
service also uses these packages for installing sub-services.

Installing management service dependencies:

.. include:: genereeritud-failid/haldusteenuse_soltuvuste_paigaldamine.inc

Installing the management service:

.. include:: genereeritud-failid/haldusteenuse_paigaldamine.inc

.. important::

   Further use of the management service is done under the management service
   account. To do this, the administrator must create SSH access to the
   management service account ``ivxv-admin``. It is recommended to use
   ID card-based authentication (see :ref:`configure-ssh-idcard-auth`).

As a result of installing the management service, the collector service provider
has the interface required for managing the service.


Configuring the Management Service
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Some management service processes are executed at regular intervals using the
cron service. For these processes, possible error information is output to
standard outputs and cron forwards it via email to the account address of
the executor. Therefore, a mail server must be installed on the management
service machine and configured so that messages sent to all accounts on the
machine (e.g., ``root@localhost``) are forwarded to the service administrators.


Including Collector Service Infrastructure in Management
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

The management service uses the SSH protocol for managing the collector service.
For the management service to be able to trust other service hosts, the SSH
server keys of managed service hosts must be added to the management service.

Example of adding the SSH keys of host ``ivxv1`` to the management service's
trusted hosts::

   ivxv-admin@admin $ ssh-keyscan ivxv1 >> ~/.ssh/known_hosts
   # ivxv1:22 SSH-2.0-OpenSSH_8.2p1 Ubuntu-4ubuntu0.2
   # ivxv1:22 SSH-2.0-OpenSSH_8.2p1 Ubuntu-4ubuntu0.2
   # ivxv1:22 SSH-2.0-OpenSSH_8.2p1 Ubuntu-4ubuntu0.2

For the management service to be able to install software on service hosts,
SSH access must be created for the management service account ``ivxv-admin``
to the root account of the service hosts.

.. note::

   The management service needs root access for installing sub-service
   software. After successful installation on one host, the management
   service removes access to that host's root account.

The public key of the management service account SSH key pair is located in the
``ivxv-admin`` user's home directory in the file :file:`.ssh/id_ed25519.pub`
and is generated during the management service installation. If necessary, the
administrator may replace this key (but this must be done before the key is
transferred to the managed service machines).

On the service machine, the management service account SSH public key must be
placed in the file :file:`/root/.ssh/authorized_keys`. This file must be owned
by the root user and readable only by the root user (file permissions ``0600``).

As a result of including the collector service infrastructure in management, the
management service has trusted access to the root accounts of the service
machines belonging to the collector service infrastructure.


Connecting the Log Monitoring Solution with the Management Service
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

When using the log monitoring solution, the management service must have access
to the log monitoring solution to download collected statistics from there and,
if necessary, update the logs analyzed by the log monitoring solution.

For the management service to trust the log monitoring service, the SSH server
keys of the log monitoring service host (in this example named ``logmonitor``)
must be added to the management service::

   ivxv-admin@admin $ ssh-keyscan -t ecdsa logmonitor >> ~/.ssh/known_hosts

For the management service to access the log monitoring account, the management
service account SSH public key must be placed in the authorized keys file of the
log monitoring account ``logmon``
:file:`~logmon/.ssh/authorized_keys`. This file must be owned by the log monitor
user and readable only by that user (file permissions ``0600``).

As a result of connecting the log monitoring solution with the management
service, the activity log monitoring solution is accessible to the management
service, and the management service can load statistics data from the monitoring
solution and transfer up-to-date log data to the monitoring solution's data
store.


Replacing the Management Service Default Web Interface TLS Certificate
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

During management service installation, a TLS certificate with a cryptographic
key and a strong Diffie-Hellman group file (see https://weakdh.org/) are
generated for the user interface web server. If necessary, the administrator can
replace them.

File locations:

* Web server TLS certificate key:
  :file:`/etc/ssl/private/ivxv-admin-default.key`

* Web server TLS certificate: :file:`/etc/ssl/certs/ivxv-admin-default.crt`

* Diffie-Hellman group file: :file:`/etc/ssl/dhparams.pem`

To apply replaced files, the web server must be restarted using the command
:command:`service apache2 restart` and the web interface must be verified to
be working.

As a result of replacing the management service default web interface TLS
certificate, the management service web interface uses a secure certificate.


Replacing the Management Service Default Authentication Certificate
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

During management service installation, a management service authentication
certificate with a cryptographic key is generated (the management service uses
this for authentication when exchanging information with the Election
Information System). If necessary, the administrator can replace them.

File locations:

* Authentication certificate key: :file:`/etc/ssl/private/ivxv-admin-client.key`

* Authentication certificate: :file:`/etc/ssl/certs/ivxv-admin-client.crt`

As a result of replacing the management service default authentication
certificate, the management service uses a secure certificate for
authenticating with the Election Information System.

Testing the authentication certificate:

.. code-block:: shell-session

   $ openssl s_client -connect vis-address:443 \
     -cert /etc/ssl/certs/ivxv-admin-client.crt \
     -key /etc/ssl/private/ivxv-admin-client.key


Resetting the Management Service
----------------------------------

Resetting the management service is done using the command
:ref:`ivxv-collector-init`. During this process, the management service data
directories are cleaned and the database is reset.


Applying Settings and Election Lists to the Collector Service
--------------------------------------------------------------

.. note::

   In this section and subsections, "configuration package" refers to both a
   file containing settings and an election list file signed by an authorized
   person.

The following configuration packages must be applied to the collector service:

#. Trust root — always loaded first;

#. Collector service technical settings — loaded before election settings;

#. Election settings — loaded before lists;

#. Choices list;

#. District list;

#. Initial voter list.

The following steps must be taken to apply the prepared configuration packages:

#. Transfer to the management service machine;

#. Loading into the management service;

#. Applying to sub-services.

.. hint::

   Preparation of configuration packages is described in section
   ":ref:`seadistuste_koostamine`".

.. attention::

   Loading trust root settings always involves resetting the collector service
   management service database!

As a result of applying settings and election lists to the collector service,
the collector service is configured to provide a proper vote collection service
during the designated period.


Transferring a Configuration Package to the Management Service Machine
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Transferring a configuration package to the management service machine is done
over the `SCP <https://en.wikipedia.org/wiki/Secure_copy>`_ protocol. The
configuration package must be accessible to the management service user account
``ivxv-admin``.

Example::

   $ scp seadistus.asice ivxv-admin@admin:
   seadistus.asice              100%   15KB  79.5KB/s   00:00

.. note::

   The collector service provider may also use other methods for transferring
   configuration packages, such as removable media.

As a result of transferring the configuration package, the package is on a data
carrier accessible by the management service.


Loading a Configuration Package into the Management Service
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

The configuration package is loaded into the management service using the
command :ref:`ivxv-cmd-load`. During this process, the management service
verifies the authorizations of the person who signed the configuration package
and validates the content and consistency of the settings. As a result of
loading, the configuration package is ready to be applied to the managed
services.

Example: Loading the trust root into the management service:

.. include:: genereeritud-failid/haldusteenus-laadi_usaldusjuure_seadistused.inc

As a result of loading the configuration package into the management service,
the management service is ready to apply the configuration package to the
sub-services. The configuration package version is displayed in the management
service status data.

.. seealso:: * :ref:`korralduste-valideerimine`


Applying Settings to Sub-Services
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Configuration packages loaded into the management service are applied to
managed services using the command :ref:`ivxv-config-apply`. Application is
possible after loading the technical settings, since the technical settings
provide the management service with data about the managed services.

During the settings application, the management service:

* Installs the service software being configured (when loading technical
  settings, if not previously installed);

* Transfers the configuration package to the managed service host file system;

* When loading election settings, enables and starts the service being configured.

.. note::

   The order of settings application is described in the help text section of
   the ivxv-config-apply utility (see :ref:`ivxv-config-apply`).

Example: Applying settings loaded into the management service to the managed
services::

   ivxv-admin@admin $ ivxv-config-apply
   INFO: Technical config is signed by ÕIGE,VALIK,44444444444 2017-06-07T12:05:44Z
   INFO: Service choices@choices1.ivxv.ee: Applying technical config
   SERVICE choices@choices1.ivxv.ee: Installing service to host "ivxv1"
   SERVICE choices@choices1.ivxv.ee: Querying state of the service software package "ivxv-choices"
   SERVICE choices@choices1.ivxv.ee: Copying software package files to service host
   SERVICE choices@choices1.ivxv.ee: Checking state of dpkg database in service host
   SERVICE choices@choices1.ivxv.ee: Installing dependencies for package "ivxv-common"
   Reading package lists...
   Building dependency tree...
   Reading state information...
   ...
   SERVICE voting@voting3.ivxv.ee: Set trust config file permissions in service host
   SERVICE voting@voting3.ivxv.ee: Trust root config successfully applied to service
   SERVICE voting@voting3.ivxv.ee: Applying technical config to service
   SERVICE voting@voting3.ivxv.ee: Copying technical config to service host
   SERVICE voting@voting3.ivxv.ee: Set technical config file permissions in service host
   SERVICE voting@voting3.ivxv.ee: Technical config successfully applied to service
   SERVICE voting@voting3.ivxv.ee: Registering technical config version "ÕIGE,VALIK,44444444444 2017-06-07T12:05:44Z" in management database
   SERVICE voting@voting3.ivxv.ee: Registering service state as "INSTALLED" in management database
   INFO: Service voting@voting3.ivxv.ee: technical config config applied successfully
   INFO: 15 configuration packages successfully applied

As a result of applying settings to sub-services, the managed services are
configured and their state is monitorable from the management service.

.. seealso:: * :ref:`korralduste-laadimine-rakendamine`


Applying Collector Service Cryptographic Keys
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

**Service cryptographic keys and TLS certificates** are applied using the
command :ref:`ivxv-secret-load`.

.. hint::

   The state of service cryptographic keys can be displayed using the command
   :command:`ivxv-status --service=<service-id>` (see :ref:`ivxv-status`)

Loading a key to a service:

.. code-block:: shell-session

   $ ivxv-secret-load --service=<teenuse-id> tls-key tls.key

Loading a certificate to a service:

.. code-block:: shell-session

   $ ivxv-secret-load --service=<teenuse-id> tls-cert tls.pem

.. important::

   Each service instance must have the key and certificate generated
   specifically for that instance applied!

**Applying the voting service time-stamp request signing key** is done using
the command :ref:`ivxv-secret-load`:

.. code-block:: shell-session

   $ ivxv-secret-load tsp-regkey tspreg.key

.. note::

   The voting service time-stamp request signing key only needs to be applied
   if the time-stamping service is used as a registration service (the value
   of the ``qualification/protocol`` field in the election settings is ``tspreg``).

**Applying the Mobile-ID/Smart-ID/Web eID identity token key** is done using
the command :ref:`ivxv-secret-load`:

.. code-block:: shell-session

   $ ivxv-secret-load mid-token-key mobid-shared-secret.key

.. note::

   The Mobile-ID/Smart-ID/Web eID identity token key only needs to be applied
   if the Mobile-ID/Smart-ID/Web eID support service is in use
   (the election settings contain the ``auth.ticket`` block).

As a result of applying collector service cryptographic keys, the communication
channels of managed services are equipped with the cryptographic keys required
for securing the channel, and the services also have cryptographic keys for
other important operations.


Verifying the Initial Setup Result
------------------------------------

As a result of the initial setup activities, the collector service is presumably
ready for conducting the election. The result can be verified by monitoring the
collector service status, which is described in the system administrative
operations section (:ref:`kogumisteenuse-oleku-jälgimine`).

The state of the collector service configured for conducting an election is
"Configured" (CONFIGURED). If the state is "Installed", the microservice states
and state background information should be checked.
