..  IVXV collector service management interface user guide

Configuration application states
=================================

The configuration states monitoring page opens from the menu option ``Seadistused``.

The status is displayed for the following configurations:

* Trust root configuration;

* Technical configuration;

* Election configuration;

* Choices list;

* Districts list;

* Voter lists.

The status is not displayed for the following configurations:

* User permissions (applied immediately upon loading).

For configurations loaded into the management service, the following is displayed:

* Configuration application status;

* Active configuration version;

* Number of configuration application attempts;

* For configurations sent for application, the application log is also displayed.


Loading configurations into the collector service
---------------------------------------------------

To load the technical configuration and election configurations into the collector
service, there is a loading form at the bottom of the page. Only configuration
packages digitally signed by authorized users are allowed to be loaded. The order
of loading configurations is not important. Loading the election configuration is
a prerequisite for loading election lists.

.. note::

   The trust root configuration is loaded by the collector service administrator
   from the command line. The collector service management interface cannot be used
   before the trust root is loaded.
