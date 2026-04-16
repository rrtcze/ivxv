..  IVXV collector service management interface user guide

Overview
========

Management interface functionality
-----------------------------------

The management interface is the web-based user interface of the collector service
management service and has the following functions:

* Presenting an overview of the collector service status and history:

   * General overview;

   * Service status;

   * Status of prepared lists;

   * General statistics;

   * Collector service management event log;

* Loading commands into the collector service;

* User management;

* Downloading extracts:

  * Downloading detailed voting statistics;

  * Downloading the voting sessions list;

  * Downloading the e-ballot box.


Access to the management interface
-----------------------------------

The collector service management interface is accessible using a web browser. The
``URL`` required to access the management interface is provided to users by the IVXV system administrator.

Only authorized users who have authenticated themselves with an ID card can access
the management interface. The set of functions available to a user depends on
the user's permissions.


User interface overview
------------------------

At the top of the page is the page header, which contains the name of the management
interface and an icon for viewing the logged-in user's details.

On the left side of the page is the menu bar, which can be used to navigate between subpages.

.. note::

   The user interface also scales to low-resolution screens; in that case,
   the menu section is hidden from the default view and can be opened from the page header.


Preparing and loading configurations, lists, and permissions
-------------------------------------------------------------

Through the user interface, it is possible to load collector service configurations,
choices lists and voter lists, and user permissions into the system.

These data must be formatted as digitally signed commands.
The preparation of configuration packages is described in the document ``IVXV
configuration preparation guide``.

Configuration packages loaded into the system can be downloaded by clicking
on the configuration package version information in the user interface.
