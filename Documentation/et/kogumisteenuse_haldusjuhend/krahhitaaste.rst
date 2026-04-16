..  IVXV collector service administration guide

Crash Recovery
==============

The collector service is designed so that a crash of the service or its
components does not result in data loss, or the loss is minimal.


Prerequisites for Successful Crash Recovery
-------------------------------------------

High-Availability Configuration
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

The main prerequisite for successful crash recovery is deploying the collector
service with a high-availability configuration that specifies the use of at
least three storage service instances. Additionally, it is useful to allocate
infrastructure for installing an additional set of microservice instances for
faster crash resolution.


Using a Log Collector
^^^^^^^^^^^^^^^^^^^^^

The collector service configuration must describe the log collection service,
so that logs produced by microservices can be collected in a simple manner. It
is recommended to use multiple log collectors in different physical locations
to minimize the possibility of losing log entries.


Using a Backup Service
^^^^^^^^^^^^^^^^^^^^^^

The collector service configuration must describe the backup service and
automatic backup times with sufficient frequency. It is also recommended to
make backup copies of the backup service itself.

Automatic backup ensures the preservation of e-ballot box copies in case of a
:ref:`complete storage service crash <talletusteenuste-täielik-krahh>`.

.. note::

   The backup service should be installed physically separate from other
   collector service instances, so that possible emergencies (such as fire)
   do not affect both the backup service and other services simultaneously.

The backup service is designed for creating automatic backups of collector
service data in one location and making them available for operations that use
backup copies (such as vote counting).

.. note::

   The collector service provider should consider the possibility of making
   additional backup copies of the backup service to ensure the preservation
   of backed up data even in case of a backup service crash.

Preparedness for a Crash
^^^^^^^^^^^^^^^^^^^^^^^^^

A collector service crash affects all e-voting components; particular attention
must be paid to name resolution of voter applications and verification
applications, as well as the certificates required for trusting TLS
connections.

For successful voting, it must be ensured that name servers contain
up-to-date information about the voting system entry points throughout the
entire voting period — then voter applications and verification applications
can resolve names correctly according to changing conditions.

#. When a crash is detected, one of the first actions should be to remove
   the crashed service from name resolution, so that applications can no
   longer connect to it.
#. When services are restored after a crash, as the last step, the addresses
   of the new services should be made resolvable in name resolution according
   to the definitions in the applications.

If new microservices are added to the collector service (presumably after a
crash), the trustworthiness of the added services must be ensured in the
applications.

When planning the service, certificates/keys should also be created for
possible replacement services (choices, mid, voting). These keys should be
packaged into the voter application, so that after a crash there is no need
to distribute a new application. If certificates are created under a single
CA, it is sufficient to package the corresponding CA certificate into the
voter application. For verification applications, specific service
certificates must always be specified in the settings, but changing
verification application settings does not require redistributing the
verification applications.

Recovering Services from a Crash
---------------------------------


Microservice Instance Crash Without Data Loss
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

A microservice instance crash without data loss can occur with services that
do not handle data storage (choices service, voting service, verification
service, or Mobile-ID support service). In such a situation, it is sufficient
to either restart the service instance (if possible) or replace the service
instance with a new one.

.. seealso::

   * :ref:`teenuse-taaskäivitamine`

   * :ref:`teenuse-asendamine`

   * :ref:`recovery-stateless`

Log Collection Service Instance Crash
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

A log collection service crash can occur with or without log data corruption.

A crash without log data corruption means a situation where the rsyslog service
is stopped and therefore does not accept log entries from services, and the
saved log files are not corrupted. In such a situation, it is sufficient to
restart the service instance.

A log collection service crash with log data corruption requires replacing the
service instance with a new one.

While log data corruption always involves log data loss, a crash without
corruption should also be considered for this possibility. Logs are forwarded
over the RELP protocol, which is quite reliable, but despite this, log
forwarding may be interrupted in a situation where the rsyslog instance on the
host of the log-generating service has been restarted while the log collector
rsyslog instance was not running.

.. seealso::

   * :ref:`teenuse-taaskäivitamine`

   * :ref:`teenuse-asendamine`

   * `RELP - The Reliable Event Logging Protocol
     <https://www.rsyslog.com/doc/relp.html>`_

   * :ref:`recovery-logcollection`

Backup Service Instance Crash
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

A backup service instance crash means corruption of data backed up to the
backup service. To recover the service, the backup service must be reinstalled
and the backed up data restored. Data restoration to the backup server can also
occur after the end of vote collection, but before vote counting.

.. note::

   Backup procedures are controlled from the management service and therefore
   the backup service cannot be started or stopped.

.. seealso::

   * :ref:`recovery-backupservice`

Storage Service Instance Crash
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

When a single storage service instance crashes, it is sufficient to replace
the instance with a new one.

Storage services can only be added and removed when there are at least a
quorum of operational storage service instances in the cluster. The quorum size
is N/2+1 rounded down, where N is the configured number of instances (for
example, with three configured instances, the quorum size is two).

If fewer than a quorum of storage service instances remain, a new installation
must be performed on all instances (see
:ref:`talletusteenuste-täielik-krahh`).

Quorum-related limitations of the storage service:

#. The number of storage service instances can never be reduced to one;

#. When removing storage service instances, the quorum must be maintained.

   Example: if 6 storage service instances are configured (quorum=4), then
   three instances cannot be removed at once (3 would remain, quorum=2),
   because the set of configured instances would then be smaller than the
   original quorum. First, one must be removed (5 instances remain, quorum=3)
   and only then can the remaining two be removed.

.. seealso::

   * :ref:`teenuse-taaskäivitamine`

   * :ref:`teenuse-asendamine`

   * :ref:`recovery-storageservice`

.. _talletusteenuste-täielik-krahh:

Complete Storage Service Crash, i.e., Complete Collector Service Replacement
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

When completely replacing the storage services, a new technical configuration
must be prepared that meets the following conditions:

* does not contain any old storage services;

* all new storage services are listed in the ``storage.conf.bootstrap``
  parameter list.

.. important::

   When completely replacing storage services, the following must be considered:

   * votes collected before the replacement are preserved in backup copies
     made to backup servers;

   * votes collected between the backup creation and the crash will be lost;

   * choices, district, and voter lists must be re-applied to the services.

.. seealso::

   * :ref:`recovery-fullstorage`
