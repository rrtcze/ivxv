..  IVXV collector service management interface user guide

Management event log monitoring
================================

The collector service event log browsing page opens from the menu option
``Logiraamat``.

The log has the following fields:

#. ``Aeg`` - event registration time;

#. ``Teenus`` - service identifier;

#. ``Tase`` - log event level (``INFO`` or ``ERROR``);

#. ``Sündmus`` - event type identifier;

#. ``Kirjeldus`` - textual description of the event.

The log can be filtered and sorted by field value.

Log events
-----------

Collector service states:

:COLLECTOR_INIT:
   Collector service initialization (with command :command:`ivxv-collector-init`);

:COLLECTOR_RESET:
   Collector service configuration reset (loading trust root);

:COLLECTOR_STATE_CHANGE:
   Collector service state change;

Command loading:

:CMD_LOAD:
   Loading a command file into the management service;

:CMD_LOADED:
   Registration of a successfully loaded command file in the management service;

:CMD_REMOVED:
   Removal of a command file from the management service;

:VOTER_LIST_DOWNLOADED:
   Downloading a voter changelist;

:VOTER_LIST_DOWNLOAD_FAILED:
   Failed download of a voter changelist;

:VOTER_LIST_NOT_FOUND:
   The next voter changelist was not found in the Election Information System;

User permission changes:

:PERMISSION_SET:
   Assigning a permission to a user;

:PERMISSION_RESET:
   Resetting user permissions;

Voting period registration:

:SET_ELECTION_TIME:
   Registration of voting period start and end times;

Microservice management:

:SERVICE_REGISTER:
   Registering a service in the management service;

:SERVICE_CONFIG_APPLY:
   Applying configuration to a service;

:SERVICE_STATE_CHANGE:
   Service state change;

:SECRET_INSTALL:
   Loading a secret to a service.
