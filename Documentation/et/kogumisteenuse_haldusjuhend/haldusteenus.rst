..  IVXV collector service administration guide

.. _haldusteenus:

Management Service
==================

The management service is a solution designed for managing the collector service. The
management service is installed on a separate machine, and through it, the collector
service is managed from installation to shutdown.

The management service functions are:

#. Managing collector service sub-services:

   #. Loading settings and election lists;

   #. Installing sub-services on prepared machines;

   #. Applying settings and lists to sub-services;

   #. Downloading voter list updates from the Election Information System;

#. Composing the e-ballot box for processing;

#. Monitoring general election statistics;

#. Downloading voter statistics;

#. Regular backup of the e-ballot box and logs;

#. Monitoring the state of the collector service;

The management service communicates with managed services over an `SSH
<https://en.wikipedia.org/wiki/Secure_Shell>`_ channel. Communication is always
initiated by the management service. Trust towards service machines is
established with the help of the system administrator after installing the
machines hosting the services.

After installing the machine hosting a service, the administrator creates
access for the management service to the root account of the service machine,
so that the management service can install the service software. After
installing the last service on a machine hosting services, the management
service removes access to the root account.


Management Service Composition
------------------------------

The management service user interface consists of two parts:

#. The main management functionality is implemented using :ref:`command-line
   utilities <utiliidid>`;

#. The graphical user interface is a web-based interface whose functionality
   is provided by command-line utilities.

   .. seealso::

      The graphical user interface user guide is available in the document
      ``IVXV Collector Service Management Interface User Guide``.

Additionally, the following daemon processes run:

#. A web server for the graphical user interface;

#. A management daemon for executing requests relayed by the web server;

#. An agent daemon for monitoring service states.
