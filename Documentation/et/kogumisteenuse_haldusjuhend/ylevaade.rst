..  IVXV collector service administration guide

Overview
========

Collector Service Overview
--------------------------

IVXV collector service is software designed for serving voters and collecting
votes during electronic voting.

The collector service consists of microservices and a management service for
administering them. The management service is command-line based. Some
functions have been extended with a web-based interface, which is described in
the document ``IVXV Collector Service Management Interface
User Guide``.

.. attention::

   The collector service is installed and configured separately for each
   election. A single collector service can serve only one election at a time.


Additional Materials
--------------------

This document uses concepts and definitions described in the document
``IVXV-ÜK-0.95 General Framework for Electronic Voting and Its
Use in Estonian National Elections``:

* Stages of e-voting;

* System parties and components.


Collector Service User Roles
-----------------------------

The following roles are used in the collector service:

#. **Collector service administrator** handles the technical management of the collector service;

#. **Election administrator** handles establishing election settings;

#. **Viewer** has access to status and statistical data provided through the management service;

A more detailed description of roles is available in the document ``IVXV
Electronic Voting Information System Configuration Guide``.


System Components
-----------------

Collector Service
^^^^^^^^^^^^^^^^^

**Management service** is the service for managing the collector service. Through the management service,
the collector service is managed and monitored from installation to shutdown.
See more in section :ref:`haldusteenus`.

**Log collector** is the collector service's internal log server that collects and stores
logs from all collector service sub-services. Logs collected by the log collector are
handed over to the organizer at the end of the elections.

**Internal backup** is the collector service's backup service that backs up data from all
sub-services and makes them available through a simple interface (file system directory)
to the external backup service.

**Sub-services** are services responsible for different aspects of the collector service.


.. _tugiteenused:

Support Services
^^^^^^^^^^^^^^^^

**Log monitoring** is a monitoring program designed for analyzing and monitoring
collector service logs.

**Technical monitoring** is a monitoring program designed for monitoring the
technical operation of the collector service.

**External backup** is an external backup service designed for storing data
backed up by the collector service's internal backup.


.. _välisteenused:

External Services
^^^^^^^^^^^^^^^^^

External services are services that depend on the requirements established for
the elections being conducted, with which the collector service is capable of
integrating. External services include the Registration Service, Time-Stamping
Service, Mobile-ID Service, Smart-ID Service, OCSP Service, etc.


Overview of Operations
----------------------

* Pre-voting stage:

   * :ref:`External services <välisteenused>` used by the collector service are
     documented;

   * Collector service :ref:`support services <tugiteenused>` are prepared;

   * Collector service settings are prepared (trust root, technical
     settings, and election settings);

   * Cryptographic keys and certificates required for service operation are
     generated;

   * Infrastructure required for running the collector service is prepared;

   * The management service is installed;

   * Settings are applied to the management service, based on which the management
     service installs and configures the collector service sub-services.

* Voting stage

   * Service operation is monitored;

   * Backups of the e-ballot box are created.

* Processing stage

   * Data collected in the collector service is exported:

      #. consolidated e-ballot box with collected votes.

* Counting stage

   * The collector service is not used during the counting stage;
