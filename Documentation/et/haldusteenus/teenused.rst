..  IVXV collector service management interface user guide

Service management
===================

The service management page opens from the menu option ``Teenused``.


Service summary
----------------

The service summary displays an overview of all registered services
by status. The number of services in each status is displayed after each status:

#. Not installed – the service is not installed;

#. Installed – the service is installed and the trust root configuration and
   the collector service technical configuration have been applied to it. The
   election configuration has not been applied to the service;

#. Configured – all configurations have been applied to the service and it is operational;

#. Failure – a failure has been detected in the service operation;

#. Removed – the service has been removed from the collector service composition.


Service list
-------------

The service list displays all services registered in the management service.
The following information is displayed for each service:

In the service management view, the subservice list is displayed, sorted
by service identifier:

#. Service identifier;

#. Service subnet;

#. Service type;

#. Service status;

If the management service has detected missing configurations or an error condition
for a subservice, the corresponding information is displayed below the service.
Only one message is displayed per service at a time.

Clicking on a service entry in the list opens a table with more detailed information below the entry:

#. Number of consecutive errors detected by the service health check
   (only for services in ``configured`` or ``failure`` status);

#. Time of the last service health check execution
   (only for services in ``configured`` or ``failure`` status);

#. Version of the technical configuration applied to the service;

#. Version of the election configuration applied to the service;

#. Service IP address and port;

#. Service TLS certificate checksum (SHA256);

#. Checksum of the key corresponding to the service TLS certificate (SHA256);

#. Checksum of the shared encryption secret for Mobile-ID/Smart-ID/Web eID support services
   (SHA256);
