..  IVXV collector service management interface user guide

List management
================

The list management page opens from the menu option ``Nimekirjad``.


Choices list
-------------

For the choices list, the list status and, if loaded, its version (the signer's
data along with the digital signature timestamp) are displayed.

The possible list statuses are:

#. Not loaded;

#. Loaded into the management service;

#. Applied to the collector service.


Voter lists
------------

For voter lists, the total number of lists, the number of lists per status,
and a listing of all lists registered in the collector service (version and status)
are displayed.

For the initial voter list, the list version is the signer's data along with the
digital signature timestamp; for a changelist, it is the download URL along with
the download timestamp.

The possible list statuses are:

#. Pending application;

#. Applied to the collector service;

#. Invalid;

#. Skipped.


Districts list
---------------

For the districts list, the list status and, if loaded, its version (the signer's
data along with the digital signature timestamp) are displayed.

The possible list statuses are:

#. Not loaded;

#. Loaded into the management service;

#. Applied to the collector service.


Loading lists into the collector service
-----------------------------------------

To load lists into the collector service, there is a loading form at the bottom of
the page. Only lists digitally signed by authorized users are allowed to be loaded.

.. note::

   The order of loading lists is not important. Election configurations must be
   loaded before loading lists.

.. important::

   The choices list can only be applied to the collector service once!
