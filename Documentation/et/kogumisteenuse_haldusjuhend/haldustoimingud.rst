..  IVXV collector service administration guide

System Administrative Operations
=================================

.. _kogumisteenuse-oleku-jälgimine:

Monitoring Collector Service Status
------------------------------------

Collector service status data is registered in the management service database.
The utility :ref:`ivxv-status` is used to display the status.

The following data is displayed in the status:

* Election ID, phase, start and end time;

* Configuration loaded into the management service:

   * Configuration package versions;

   * Choices list and district list versions;

   * Voter list versions and states;

* Service list with applied configuration versions, service state
  and the time of its last detection;

* External service states;

* Management service data store statistics.

Depending on the state of the collector service, the status display utility
may omit some data blocks (if they are not relevant for the current state).
For full data output, see the help text for the :ref:`ivxv-status` utility.

Microservice status monitoring and registration of status and possible error
information in the management service database is handled by the management
service :ref:`agent daemon <ivxv-agent-daemon>`.

Downloading voter change lists from the Election Information System is done
using the :ref:`ivxv-voter-list-download` utility, which is launched by the
`cron` service at 15-minute intervals.

The utility :ref:`ivxv-eventlog-dump` is used to display the collector service
management service event log.

.. important::

   The management service provides the necessary information in the sub-service
   status data for restoring the service to working order. This may be:

   #. Information about missing settings (configuration files, keys, etc.). This
      is displayed until the service is provided with all settings required for
      startup.

   #. Error message — the error output of the sub-service management tools
      (configuration verification tool, service management tool) about a
      non-working service.


.. _korralduste-valideerimine:

Command Validation
------------------

Command file validation allows verifying that commands comply with formatting
requirements and detecting faulty or inconsistent commands.

Validation is performed using the command :ref:`ivxv-config-validate`.

Example of validating election settings::

   $ ivxv-config-validate --election=valimise-seadistus-TEST2017.asice


Consistency Validation of Commands
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Consistency validation is performed in two cases:

#. When multiple commands are given for validation at the same time;

#. When loading a command, if a significant command requiring consistency with
   the command being loaded has already been loaded into the management service.

Consistency validation checks for commands:

#. When validating election settings and/or lists (choices, district, or
   voter) simultaneously, the consistency of election identifiers is checked.

#. When validating multiple voter lists simultaneously, the following checks
   are performed:

   * Correct ordering of lists;

   *  In a change list, the following are checked:

      #. Duplicate addition and removal of a voter;

      #. Removal of a voter after their addition with the same change list.

      #. Removal of a voter from a district to which they have not been added;

#. When validating district and choices lists simultaneously, the following
   checks are performed:

   * Each election district must have at least one choice defined;

   * Each choice must be associated with an existing election district.

#. When validating district lists and voter lists simultaneously, the following
   checks are performed:

   * Each election precinct must have at least one voter;

   * Each person entered in the election list must be associated with an
     existing district;

#. When validating voter list(s) and district lists, the existence of the
   district assigned to the voter is checked in the district list.

If the election settings specify the administrative unit EHAK code assigned
to a voter residing abroad (parameter ``voterforeignehak``), the election
settings must also be included when validating the compliance of choices, voter,
and district lists, and the following additional checks are performed during
settings validation:

#. When validating the consistency of the voter list and district list, it is
   verified that the district list contains the district assigned to the voter
   in the administrative unit specified by the parameter.


.. _korralduste-laadimine-rakendamine:

Loading and Applying Commands
-----------------------------

Collector service commands are prepared as signed command packages that
describe the user identifier (*Common Name* i.e., CN field from the ID card)
and a list of roles.

Depending on the command, one or two commands must be used for application.
For commands concerning the management service, loading them into the management
service is sufficient. Commands concerning sub-services (such as configuration
packages) must be applied to the managed services after loading into the
management service.

Loading commands into the management service is done using the :ref:`ivxv-cmd-load`
command. During loading, :ref:`command validation <korralduste-valideerimine>` is
also performed; a faulty or inconsistent command will not be loaded.

Example of applying a choices list command:

.. include:: genereeritud-failid/haldusteenus-laadi_valikute_nimekiri.inc

.. seealso::

   * Help text for the :ref:`ivxv-cmd-load` command;

   * Description of command roles and the guide for preparing commands are
     available in the document ``IVXV Configuration
     Guide``.


Detecting Service Instance State
---------------------------------

The utility :ref:`ivxv-service` is used to detect the state of a microservice
instance, allowing direct querying of the service state (the utility
:ref:`ivxv-status` displays the state buffered in the database).

Example of a service state query:

.. include:: genereeritud-failid/mikroteenuse_seisundi_tuvastamine.inc


.. _teenuse-taaskäivitamine:

Service (Re)start
------------------

The utility :ref:`ivxv-service` is used for starting and restarting
microservices.

Example of restarting a service:

.. include:: genereeritud-failid/mikroteenuse_kaivitamine.inc

.. note::

   Whether the procedure is called starting or restarting depends on the state
   of the service process. Technically, these are similar procedures where
   first it is ensured that the service is stopped (stopping it if necessary)
   and then an attempt is made to start it with the currently valid settings.


.. _teenuse-seiskamine:

Stopping a Service
-------------------

The utility :ref:`ivxv-service` is used for stopping microservices.

Example of stopping a service:

.. include:: genereeritud-failid/mikroteenuse_seiskamine.inc


.. _teenuse-asendamine:

Replacing a Service Instance
-----------------------------

Replacing a service instance consists of removing one microservice instance
(see :ref:`teenuse-eemaldamine`) and adding another microservice instance with
the same function (see :ref:`teenuse-lisamine`).


.. _teenuse-lisamine:

Adding a Service Instance
--------------------------

To add a service instance, the server hosting the service must be prepared if
necessary (see :ref:`taristu-paigaldamine`), and a new technical configuration
containing the service instance to be added must be applied.

.. important::

   The identifier of the instance to be added must not match any other
   instance identifier, including those of previously removed instances.


.. _teenuse-eemaldamine:

Removing a Service Instance
-----------------------------

To remove a service instance:

#. Stop the service instance (see :ref:`teenuse-seiskamine`);

#. Prevent the service instance from being restarted (see below);

#. Apply a new technical configuration that no longer contains the instance to be removed.

.. important::

   When removing a service instance from the collector service, the complete
   elimination of the removed instance is important.

   Service instances use certificates issued by a specific certificate
   authority (CA) to prove trust to each other, but do not use the same
   method to revoke trust of a removed instance (due to the excessive
   complexity of implementing such a procedure).

   Therefore, it is important to ensure that a service instance removed from
   the collector service is completely removed from the system before applying
   the new configuration. Otherwise, there is a risk that the removed instance
   continues to operate and disrupts the collector service.

To prevent a service instance from being restarted during service removal,
the corresponding service software package must be removed from the service
host:

* Removing the choices service package:

   .. code-block:: text

      $ apt purge ivxv-choices

* Removing the Mobile-ID support service package:

   .. code-block:: shell-session

      $ apt purge ivxv-mid

* Removing the Smart-ID support service package:

   .. code-block:: shell-session

      $ apt purge ivxv-smartid

* Removing the Web eID support service package:

   .. code-block:: shell-session

      $ apt purge ivxv-webeid

* Removing the Session status support service package:

   .. code-block:: shell-session

      $ apt purge ivxv-sessionstatus

* Removing the proxy service package:

   .. code-block:: shell-session

      $ apt purge haproxy

* Removing the storage service package:

   .. code-block:: shell-session

      $ apt purge etcd-server

* Removing the verification service package:

   .. code-block:: shell-session

      $ apt purge ivxv-verification

* Removing the voting service package:

   .. code-block:: shell-session

      $ apt purge ivxv-voting


User Management
----------------

Initial user descriptions are defined in the trust root configuration; subsequent
management is done using the corresponding commands.

User management commands are applied using the :ref:`ivxv-cmd-load` command (see
:ref:`korralduste-laadimine-rakendamine`).

Example of applying a user permission command:

.. include:: genereeritud-failid/kasutaja_lisamine.inc

.. attention::

   Removing already added users from the system is not possible. Instead of
   removing a user, the user's role should be set to "user without permissions".

.. seealso::

   * Description of user roles and the guide for preparing authorization
     commands are available in the document ``IVXV Configuration Guide``.

   * Applying commands is described in section
     :ref:`korralduste-laadimine-rakendamine`.


Applying Software Updates
--------------------------

Software updates are divided into two categories from the collector service
perspective: operating system updates and collector service updates.

Installing new versions of operating system packages is not covered in the
collector service documentation. The system administrator must ensure that
up-to-date security updates are applied to the operating systems used by the
collector service;

Installing new versions of collector service software packages is done as follows:

#. Updated software packages are copied to the management service directory
   :file:`/etc/ivxv/debs` (preferably with root privileges);

#. The management service software is updated with root privileges using the
   command :command:`dpkg -i /etc/ivxv/debs/ivxv-common_1.0_all.deb
   /etv/ivxv/debs/ivxv-admin_1.0_amd64.deb` (the actual version number
   differs from the version used in this example);

#. Updating managed service software is done with the management service
   user ``ivxv-admin`` privileges using the command :ref:`ivxv-update-packages`.


Backup
------

Backup covers three types of data:

#. Management service settings;

#. Collector service e-ballot box;

#. Collected logs.

Backup creation is performed on the management service machine using the
:ref:`ivxv-backup` utility; backup copies are stored in the backup server
directory :file:`/var/backups/ivxv`.


Backing Up Management Service Settings
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

The following management service settings data is backed up:

#. :file:`etc/` — software packages loaded into the management service and
   currently valid configuration files;

#. :file:`admin-ui-permissions/` — management service user interface access
   permissions;

#. :file:`commands/` — all command files loaded into the management service.

Management service backup is performed in the management service; the data to
be backed up is copied to the backup server.

.. hint::

   For more efficient backup and recovery of management service data, it is
   recommended to use a dynamic snapshot dump of the management service virtual
   machine.

No procedure for restoring management service settings from a backup is provided
in the collector service.

Example of creating a management service settings backup::

   $ ivxv-backup management-conf


Backing Up the Collector Service E-Ballot Box
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Backing up the collector service e-ballot box involves creating an e-ballot box
from the votes collected in the storage service and copying it to the backup
service. Restoration of backed up data occurs during the e-ballot box export
after voting, where the e-ballot box to be processed is assembled from the
votes in the storage service and the votes saved in backup copies.

The e-ballot box backup is performed by the management service. The backup copy
is created in the storage service and copied to the backup server.

The backup copy has the same format as the e-ballot box output by the collector
service (ZIP64).

The backup data volume can be calculated using the following method:
``number of votes * 12.1 kB * compression factor``.

For example, the size of one hundred thousand votes, where the compression
factor is 0.4 = 472 MB.

Example of creating an e-ballot box backup::

   $ ivxv-backup ballot-box


Backing Up Logs
^^^^^^^^^^^^^^^^

Backing up log files collected by the log collection services involves copying
log files :file:`/var/log/ivxv/ivxv-YYYY-MM-DD-HH.log` to the backup server.
Log backup is performed by the management service.

No procedure for restoring logs from a backup is provided in the collector
service.

Example of creating a backup of logs collected by the log collection service::

   $ ivxv-backup log


.. _konsolideeritud-e-valimiskasti-koostamine:

Composing the Consolidated E-Ballot Box
-----------------------------------------

The consolidated e-ballot box is composed from votes collected in the storage
service and e-ballot boxes backed up to the backup service. The consolidation
process consists of the following steps:

#. Votes collected in the storage service are backed up to the backup service.
   As a result, all collected e-ballot boxes are stored in the backup service;

#. The consolidated e-ballot box is composed in the backup service;

#. The consolidated e-ballot box is copied to the management service.

Example of composing the consolidated e-ballot box:

.. include:: genereeritud-failid/e-valimiskasti_koostamine.inc


Composing the Processing Application Input Base
-------------------------------------------------

The processing application input base is a set of input files required for
vote processing, generated from data stored in the collector service. The
set composition is as follows:

#. District list;

#. Voter lists;

#. E-ballot box with collected votes;

#. Registration request validation data;

#. Processing application settings.

The output is a ZIP container containing the following files:

#. Digitally signed district list
   :file:`<election-id>.districts.json.asice`;

#. Voter list signing key public key
   :file:`voterfile.pub.key`;

#. Voter lists
   :file:`<changeset_no>.<election-id>.voters.utf`;

#. Voter list signatures
   :file:`<changeset_no>.<election-id>.voters.sig`;

#. Voter list skip commands
   :file:`<changeset_no>.<election-id>.voters-skip.yaml.asice`;

#. Registration request verification public key
   :file:`ts.key`;

#. Processing application settings template for e-ballot box verification
   :file:`<election-id>.processor.yaml`.

The processing application input base is composed using the
:ref:`ivxv-generate-processor-input` utility. Example:

.. include:: genereeritud-failid/töötlemisrakenduse_sisendi_koostamine.inc

Exporting Voting Statistics
----------------------------

Voting statistics are compiled in the voting service and consist of two parts:
general statistics (total number of voters) and detailed statistics. General
statistics are copied to the management service and exported to the Election
Information System at 15-minute intervals. Detailed statistics are compiled
and exported to the Election Information System manually.

Importing and exporting voting statistics is performed on the management service
machine using the :ref:`ivxv-voterstats` utility. Automatic importing and
exporting of general statistics is implemented using the cron service and
described in the file :file:`/etc/cron.d/ivxv-admin`.


Composing Voting Session Extracts
-----------------------------------

The voting and vote verification session extract is in CSV format and is
compiled in the log monitoring service.

The extract can be compiled in anonymized form, where users' personal
identification codes and IP addresses are replaced with anonymous values.

It is possible to choose whether to output all voting sessions or only sessions
with vote verification.

:ref:`ivxv-voting-sessions`
