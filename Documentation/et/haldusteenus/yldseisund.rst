..  IVXV collector service management interface user guide

General status
===============

The general status page opens from the menu option ``Üldseisund``.

Collector service general status
---------------------------------

The collector service general status view displays the following data:

#. Election identifier;

#. Collector service status;

#. Current voting phase;

#. Versions of configurations and lists applied to the collector service;

#. Summary of microservice statuses;

#. Status of collector service software packages;

#. Number of users registered in the collector service;

#. Number of commands loaded into the collector service.

To determine the collector service general status, the management service regularly
collects status data from subservices and maintains records of it.

.. note::

   Commands loaded into the collector service are divided into active and
   archived commands. Active commands are currently applied to the service.
   Archived commands have been loaded into the system but are not applied
   — for example, commands replaced by a newer version.
