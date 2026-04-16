..  IVXV arhitektuur

Collector Service
=============

According to the General Description [ÜK2016]_, the Collector Service is:

.. epigraph::

   The central component of the system, operated by the Collector. The service
   assists the Voter in composing an e-vote and registers it before storing it
   in the e-ballot box. The Collector Service uses external services
   (authentication, signing, registration). In addition to the Collector
   itself, the Collector Service has other administrators (Organizer, Client
   Support), for whom the Collector Service has separate management interfaces.

The Collector Service operates in online mode and at least the interfaces
towards the voter application and the verification application are open to
the internet. Therefore, the Collector Service processes requests from a
potentially untrusted source. Due to the security level required of the
software, and the requirements for high availability, scalability, layered
deployment, and extensibility, the collector service is further divided into
microservices providing one specific service each, which can be flexibly
deployed.

All collector service components are programmed in `Go
<https://golang.org>`_. Go has:

- static typing, which enables the detection of type errors before running
  the program;

- automatic memory management, which eliminates security vulnerabilities
  arising from faulty memory management in the application;

- an open source compiler;

- concurrency/parallelism, which allows the use of parallelism in
  multi-core systems.

The collector service generally uses JSON format for data transfer, except
in situations where external circumstances necessitate the use of another
data format (for example, the BDOC format is based on XML).

The Collector Service supports Riigikogu (Parliament) elections, local
government council elections, European Parliament elections, and referendums.

The collector service components take virtualization technologies into
account, and the collector service can be deployed both on a single virtual
hardware instance and on different instances per microservice. The collector
service components are deployable on the Ubuntu 22.04 LTS (Jammy Jellyfish)
operating system on a 64-bit architecture.

Data storage is implemented using a key-value database (etcd). For testing
purposes, data storage to the file system and to memory has also been
implemented, but these are not recommended for use in a production
environment. Additionally, the collector service has an interface for adding
new storage protocols. The final decision on the solution to use is made by
the collector service administrators when configuring the service.

Microservices
-------------

.. figure:: model/img/collector_microservices.png

   Collector service breakdown into microservices

The Collector Service is divided into core services and auxiliary services.
The core services - proxy service, choices service, voting service,
verification service, and storage service - are bounded to a single election
for the sake of architectural simplicity, but microservices of multiple
elections may run on the same hardware, within the same operating system
context. Additionally, auxiliary services may be used with the collector
service - an authentication service for voter identity verification and a
signing service to facilitate vote signing by the voter application.

Services can be deployed both separately and together in various
configurations, which makes a layered architecture possible. Based on
function, it is advisable to keep the Proxy and Storage Services separate
from the others.

The services use TLS as the transport protocol, connections are at
least server-side authenticated. The application layer protocol is JSON-RPC.

All services generate activity logs, which are stored both locally and
logged to a central log collector via the syslog protocol.

Proxy Service Function and Technical Interface
``````````````````````````````````````````````

The main function of the proxy service is to provide a single entry point
(port 443) for the Voter Application and the Verification Application. The
proxy service is a dispatcher service between other components, which allows
the collector service to be internally deployed as microservices while having
only a single entry point for the system. Additionally, in a replicated
deployment, it can perform the role of a load balancer.

The proxy service does not terminate the TLS connection but uses the TLS
*Server Name Indication* (SNI) extension to identify the destination.
Clients include the SNI extension in the TLS ``ClientHello`` message, where
they specify in plaintext which service they wish to communicate with: the
proxy service sees this, contacts an instance providing the corresponding
service, and begins relaying messages between the client and the service.
The proxy service DOES NOT terminate TLS and does not see the content of
messages. The proxy service has data about the locations (address:port) of
all other services and the service relays message exchange between all
parties.

The proxy service is a stateless component that can be horizontally
scaled.

Proxy Service Implementation
'''''''''''''''''''''''''''

The proxy service implementation uses the open-source HAProxy server, which
is a widely used software load balancer and proxy. Since the proxy service is
the first point of contact for connections coming from the public internet,
it is reasonable to use software whose reliability has already been proven.

Although HAProxy is often used in HTTP mode where it analyzes traffic, in
the proxy service role it operates in TCP mode and does not see inside the
encrypted TLS channel being proxied.

An HAProxy configuration file is generated from the IVXV configuration,
which contains the locations of other services, and the task of relaying
connections is handled by the latter. Additionally, HAProxy can be configured
to limit connection rates based on source address or some other identifier.
However, this remains the task of the system administrator.

Although HAProxy is capable of performing the load balancer role itself, it
can also be deployed behind other, potentially hardware-based load balancers,
where it will only perform the task of proxying based on SNI.

HAProxy source code is public and under a suitable license, and is packaged
in the official repository of the collector service base platform (see
:ref:`tehnoloogiad`).

Choices Service Function and Technical Interface
```````````````````````````````````````````````

The main function of the choices service is to relay choices lists to the
Voter Application. Information about the authenticated voter reaches the
Choices Service, and the Choices Service delivers the choices list
corresponding to the voter's district from the Storage Service to the Voter
Application.

The Choices Service is a stateless component that can be horizontally
scaled.

Verification Service Function and Technical Interface
``````````````````````````````````````````````````

The main function of the verification service is to process verification
requests and deliver the verifiable vote from the Storage Service to the
Verification Application.

The Verification Service is a stateless component that can be horizontally
scaled.

Voting Service Function and Technical Interface
````````````````````````````````````````````

The main function of the voting service is to process voting requests. The
Voting Service verifies the incoming vote, registers it with the
Registration Service, and stores it in the Storage Service.

The Voting Service is a stateless component that can be horizontally
scaled.

Storage Service Function and Technical Interface
`````````````````````````````````````````````

The main function of the storage service is the long-term storage of choices
and voter lists, as well as votes.

For horizontal scaling of the storage service, a storage technology that
supports distributed storage is used.

Storage Service Implementation
'''''''''''''''''''''''''''''

The Storage Service is not aware of the IVXV protocol or the specifics of
the stored data, but is a general-purpose key-value database for storing
binary data. All knowledge about the structure of stored data and the key
hierarchy is in the other services that use the Storage Service, which
behave as so-called "smart" clients.

This approach allows any widely used key-value database to be used as the
Storage Service without much effort: the only tasks are converting the IVXV
configuration to a format suitable for the database and starting the
service. The database software must only support storing and reading by key,
listing by key prefix, and an atomic compare-and-swap operation.

The Storage Service is a significant determinant of the collector service's
operating speed, which is why the hardware providing this service affects the
performance of the entire system and should be dimensioned according to the
database being used.

Currently, the only production-grade Storage Service implementation uses the
distributed key-value database etcd. In this case, the etcd authors'
`hardware recommendations
<https://coreos.com/etcd/docs/latest/op-guide/hardware.html>`_ should be
followed.

Authentication Service Function and Technical Interface
``````````````````````````````````````````````````

The main function of the authentication service is voter identity
verification. The authentication service is needed, for example, in the case
of Mobile-ID authentication.

Web eID Auxiliary Service Implementation
''''''''''''''''''''''''''''''

The IVXV includes a Web eID auxiliary service that implements the
Authentication Service for using ID cards within the Web eID framework.

Upon successful Web eID identity verification, the auxiliary service issues
a ticket to the Voter Application, which can be used to confirm the voter's
identity to other services. Each ticket can only be used to vote once.

Web eID does not provide a signing service; vote signing takes place locally
on the Voter's device, analogous to classic ID card
authentication/signing.

The Web eID auxiliary service is a stateless component. Thanks to this, the
Web eID auxiliary service can be horizontally scaled.


Signing Service Function and Technical Interface
``````````````````````````````````````````````

The function of the signing service is to support the Voter Application in
vote signing. The signing service is needed, for example, in the case of
Mobile-ID signing.

Mobile-ID Auxiliary Service Implementation
''''''''''''''''''''''''''''''''''''''''

The IVXV includes a Mobile-ID auxiliary service that acts as both the
Authentication Service and the Signing Service for Mobile-ID. The Voter
Application sends IVXV requests to the Mobile-ID auxiliary service, which
converts them to Mobile-ID requests and forwards them to the Mobile-ID
service provider.

Upon successful Mobile-ID identity verification, the auxiliary service
issues a ticket to the Voter Application, which can be used to confirm the
voter's identity to other services. Each ticket can only be used to vote
once.

For signing, the Voter Application sends only the hash of the vote to be
signed to the Mobile-ID auxiliary service and uses the signature received in
response in the same way as a signature created with an ID card.

The Mobile-ID auxiliary service does contain state about ongoing
authentication sessions, but is otherwise a stateless component. Thanks to
this, the Mobile-ID auxiliary service can be horizontally scaled.

Smart-ID Auxiliary Service Implementation
'''''''''''''''''''''''''''''''''''''''

The IVXV includes a Smart-ID auxiliary service that acts as both the
Authentication Service and the Signing Service for Smart-ID. The Voter
Application sends IVXV requests to the Smart-ID auxiliary service, which
converts them to Smart-ID requests and forwards them to the Smart-ID
service provider.

Upon successful Smart-ID identity verification, the auxiliary service
issues a ticket to the Voter Application, which can be used to confirm the
voter's identity to other services. Each ticket can only be used to vote
once.

For signing, the Voter Application sends only the hash of the vote to be
signed to the Smart-ID auxiliary service and uses the signature received in
response in the same way as a signature created with an ID card.

The Smart-ID auxiliary service does contain state about ongoing
authentication sessions, but is otherwise a stateless component. Thanks to
this, the Smart-ID auxiliary service can be horizontally scaled.


Voting Facts Queue Service
``````````````````````````

The main function of the voting facts queue service is to forward voting
facts to the Election Information System via the X-Road auxiliary service.

Collector Service Microservice Deployment
``````````````````````````````````````

The collector service microservices have minimal dependencies on external
packages. The required dependencies are:

#. SSH server for performing administrative tasks (used by the management
   service for managing microservices).

#. rsyslog for collecting logs to log collection services.

The collector service microservices are packaged in deb format and can also
be deployed as Docker-like containers.

External Services and Extensibility
--------------------------------

.. figure:: model/img/collector_extension.png

   Collector service extension modules and external services

The collector service microservices use extension modules to implement
different mechanisms for voter identification, digital signature verification
and qualification, including vote registration. Extension modules may use
external services to enable their implementation. For the extensibility of
microservices, a Go API is defined, based on which additional modules can be
implemented. Currently, the following modules are implemented:

- Authentication with TLS certificate (ID card);

- Authentication with Authentication Service ticket (Mobile-ID, Smart-ID, Web eID);

- BDOC verification;

- Validity confirmation service OCSP;

- Timestamping service RFC 3161;

- Registration service OCSP;

- Registration service RFC 3161.

The Registration Service plays a central role in the IVXV cryptographic
protocol, also participating in long-term vote storage.

Registration Service Function
````````````````````````````

The main function of the Registration Service is to accept signed
registration requests from the Voting Service, confirm them with its own
signed response, and retain them for later auditing at least until the end
of the voting period.

For resolving potential discrepancies arising during auditing, it is
important that

- the Registration Service is able to prove that every confirmation it
  issued was preceded by a registration request from the Storage Service;

- the Storage Service is able to prove that for every vote it stored, there
  is a Registration Service confirmation.

A sufficient protocol for achieving this level of proof is one where both
parties have a key pair for signing, requests and responses are signed, and
each party maintains a registry of the other party's messages. Such a
protocol is implementable, for example, with an OCSP-based Registration
Service. However, there may be cases where, for example, signing
registration requests is not possible with standard means (RFC 3161-based
registration). In such cases, the necessary evidence for the registration
service must be provided through other organizational-technical means.

The Registration Service currently has two different implementations:

#. The OCSP interface assumes the use of an OCSP-based timestamping service
   deployed in Estonia, where the nonce of the signed OCSP request is the
   hash of the vote placed by the Voting Service. The request is signed
   using standard OCSP means;

#. The RFC 3161 interface, where as a non-standard solution, the nonce of
   the timestamp request is the hash of the vote signed by the Voting
   Service.


Adding Collector Service Extension Modules
`````````````````````````````````````

The collector service API defines six types of extension modules:

#. identity verification (Go package ``ivxv.ee/auth``, e.g., ``tls``);

#. deriving the voter identifier from the authenticated person's certificate
   (Go package ``ivxv.ee/identity``, e.g., ``serialnumber``);

#. deriving age from the voter identifier (Go package ``ivxv.ee/age``, e.g.,
   ``estpic``);

#. signed container verification (Go package ``ivxv.ee/container``,
   e.g., ``bdoc``);

#. signature qualification (Go package ``ivxv.ee/q11n``, e.g., ``tspreg``);

#. data storage protocol (Go package ``ivxv.ee/storage``, e.g., ``etcd``).

To add a new module, a module identifier and a subpackage with the module
implementation must be added to the module package. During the initialization
of the subpackage, the ``Register`` function of the module package must be
called to register the module.

To use a new module, its identifier must be added to the configuration under
the corresponding module type's settings along with the submodule settings.
The extension module receives the configuration block referenced by its
identifier, which it processes internally.

Module packages and the interfaces required from their modules are described
in more detail in the corresponding source code files. Also, at least one
implementation exists for each module, which can be used as a reference.


Monitoring
-----------

.. figure:: model/img/monitoring.png

   Monitoring solution

Logging
````````

The log generated by each microservice is defined systematically, based on
the protocol description and the service delivery state diagram.
At minimum, the following are logged:

* the fact of receiving each request and the start of processing;

* handover of processing to an external component;

* return of the processing sequence to the component;

* the end of request processing and the result;

* additionally, the passing of significant stages in the process state model.

The following principles are followed for logging:

* The rsyslog service is used for logging, which records the moment of
  writing the log entry with millisecond precision;

* At the start of each session, the system generates a unique identifier,
  which the client application uses when making requests to the central
  system;

* All log entries belonging to one session contain the same session
  identifier;

* A log entry is uniquely identifiable;

* For each logged message, it is possible to uniquely identify the point of
  origin of the message in the monitored system using a unique identifier;

* The log entry is in JSON format; for automated monitoring, machine
  readability is primary and human readability is secondary;

* Information going into the log is sanitized (urlencode) and a length limit
  is applied (a limit per entire log entry and also per parameter);

* Information originating from outside the system perimeter is logged only
  in sanitized form and only up to a specified length.

Since logging is done via rsyslog, it is possible to use the Guardtime module
to ensure log integrity.


General Statistics
`````````````````

The following statistics are monitored using a static web interface:

* successfully collected votes/number of voters;

* distribution of voters by gender, age group, operating system, and
  authentication method;

* successfully verified votes/number of voters;

* repeat voting statistics;

* distribution of voters by country based on IP address.


Detailed Statistics
````````````````

Detailed statistics are aggregated from logs using the SCCEIV log analyzer,
which analyzes the application activity log against a predefined profile and
enables session/error-type-based analysis.

Detailed statistics are available via an HTTPS interface.


.. _kogumisteenuse-haldus:

Management
------

The management of the collector service is done using digitally signed
configuration packages.

The Collector Service provides two interfaces for loading configuration
packages:

* Command line interface – the application verifies the signature, validates
  the format, consistency, and suitability of the commands with respect to
  the collector service state. The command is applied using a separate
  utility.

* Web interface – the web interface forwards the configuration package to
  the command line interface and returns information about the loading
  result to the user. Upon successful loading, the configuration package
  is also automatically applied using the same principles.

The functions of the web interface are:

* Monitoring the status of collector service microservices;

* Managing election lists;

* Displaying statistics about the progress of e-voting;

* Managing management service users;

* Displaying the collector service management log.

All commands given to the application are retained - including those that were
not applied. Faulty (non-validating) commands are not retained.

The collector service management service performs the following activities
automatically:

#. Loading voter list changes from the Election Information System;

#. Collecting voting statistics from the voting service and exporting them
   to the Election Information System;

#. Backing up stored votes, logs, and configurations to the backup service.


Management Service Components
`````````````````````````````

.. figure:: model/img/ms-management-service-components.png

   Collector service management service components

#. **Management web server** is an Apache server running under the system
   user ``www-data``, whose tasks are:

   #. Primary handling of HTTPS requests from users:

      #. Proving the trustworthiness of the management service (TLS certificate);

      #. Authenticating users;

   #. Serving pre-generated web pages and data files from the data store.

   #. Supplementing general background data query responses with logged-in
      user data (WSGI).

   #. Initial validation of uploaded commands and forwarding to the
      management daemon, and relaying the management daemon's responses to
      the client (WSGI).

#. **Management daemon** is a web server running under the user account
   ``ivxv-admin`` and listening on the local (``localhost``) interface,
   whose tasks are:

   #. Validating uploaded commands;

   #. Directly applying uploaded commands (user management);

   #. Saving uploaded commands for later application (for applying
      configuration and election lists to the service);

   #. Facilitating e-ballot box download.

#. **Agent daemon** is a daemon running under the user account
   ``ivxv-admin``, whose tasks are:

   #. Data collection and registration:

      #. Status of known microservices;

      #. Downloading activity monitoring statistics;

#. **Data store** is a directory in the file system where management service
   components store collected and generated data (see the detailed
   description in the appendices of the ``IVXV Collector Service Administration Guide``);

External components that the management service interacts with:

#. **Collector service sub-services** - installation, configuration, and
   status data collection is done via the agent daemon (SSH connection to
   the service machine);

#. **Monitoring server** - downloading general statistics data for display
   in the management service;

.. figure:: model/img/ms-upload-command.png

   Loading commands into the management service


Collector Service States
------------------------

The collector service state reflects the status of all sub-services of the
service, the status of the external services in use, and the overall status
derived from the above. The management service is responsible for determining
the overall status of the collector service.

The overall status states are:

#. **Not installed** - from the installation of the management service until
   all sub-services are installed;

#. **Installed** - all sub-services are installed, technical configurations
   and cryptographic keys necessary for the service to function have been
   applied to them. The election configuration has not been applied (but it
   may have been loaded into the management service);

#. **Configured** - the collector service is configured and operational,
   it is possible to conduct vote collection and export the e-ballot box.

#. **Partial failure** - the collector service is configured and partially
   operational, some sub-services are not operational, but this does not
   prevent the collector service from functioning.

#. **Failure** - a critical node of the collector service is not operational,
   proper service delivery is not possible.

.. figure:: model/img/ms-collector-status.png
   :scale: 50%

   Collector service state diagram. States by color: yellow -
   configuring, red - error, green - operational.


Collector Service Sub-Service States
`````````````````````````````````

.. figure:: model/img/ms-service-status.png
   :scale: 50%

   Sub-service state diagram as registered by the management service. States
   by color: yellow - configuring, red - error, green - operational.


Collector Service State Changes
````````````````````````````````

The collector service state is observable from the successful installation of
the management service; the initial state is **Not installed**.


Not Installed
''''''''''''

The trust anchor and technical configuration are being applied to the
collector service:

#. Loading configurations into the collector service;

#. Installing sub-services described in the technical configuration;

#. Applying the trust anchor and technical configurations to sub-services;

Upon successful application of configurations, the system's new state
becomes **Installed**.


Installed
'''''''''''

The collector service configurations have been applied to all sub-services;
election configurations have not been applied. The election configuration is
being loaded into the management service and applied to sub-services.

Upon successful application of the election configuration, the system's new
state becomes **Configured**.


Configured
'''''''''''

All collector service sub-services are configured and operational. The
management service has fresh status reports from all sub-services. It is
possible to conduct voting and export the e-ballot box.

If a failure is detected in the system, the system's new state becomes
**Partial failure**.

From the **Configured** state, the system never returns to the **Not
installed** or **Installed** states, even though when adding new
sub-services (while they are in the **not installed/installed** state), the
corresponding conditions would be met.


Partial Failure
'''''''''''

The system is configured and partially operational; some redundant parts of
the system are not operational, but this does not prevent the system from
functioning.

If the failure worsens to the point where the system is unable to provide
the service, the system's new state becomes **Failure**. After all failures
are resolved, the system's new state becomes **Configured**.


Failure
'''''

A failure has been detected in a configured system that prevents service
delivery.

When failures are resolved to the situation where the system can provide
the service, the system's new state becomes **Partial failure**.


Removed
''''''''''

The service has been removed from the configuration.


Voter List States in the Management Service
------------------------------------------

The state of a voter list can be:

#. **Pending application** - the list has been loaded into the management service;

#. **Applied** - the list has been applied to the collector service;

#. **Faulty** - the list has been marked as faulty, the management service
   will not load new voter list changes;

#. **Skipped** - the faulty list has been marked for skipping.

.. figure:: model/img/ms-voter-list-status.png

   Voter list state diagram

Transition processes:

#. Loading the list into the management service:

   The initial list is loaded by the collector service operator; the list
   state becomes **Pending application**;

   The change list is loaded by the management service. Depending on the
   validation result, the list state becomes either **Pending application**
   or **Faulty**;

#. **Applying to the collector service**: carried out by the management
   service with a list in **pending application** state. On success, the
   list state is set to **Applied**; on error, to **Faulty**;

#. **Skipping**: the operator assigns the state **Skipped** to a list with
   the state **Faulty**.
