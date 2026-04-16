..  IVXV collector service management service description

IVXV Configuration in the Election Organization Process
-------------------------------------------------------

To use IVXV in the context of an election, the system and its associated
applications must be configured so that it is possible to receive votes from
voters and handle them in accordance with the integrity, confidentiality, and
availability requirements set for the system. This technical document provides
an overview of the most important configuration operations and is intended to
supplement the compliance with procedural rules described in the electronic
voting handbook.

Data Required for Configuration Preparation
********************************************

Election general parameters
  The election general parameters define the unique identifier of the election
  for use by all associated components, the number of questions and their
  identifiers, the start and end time of the voting period, and the vote
  verification settings. The specification of election general parameters
  is covered in this document.

Initial voter list
  The initial voter list is a file in a customized format, whose format and
  associated protocols are defined in the document "IVXV Protocols". For
  Estonian national elections, the initial voter list comes from the Population
  Register.

Choices list
  The choices list is a JSON format file, whose format and associated
  protocols are defined in the document "IVXV Protocols". For Estonian national
  elections, the choices list comes from the election information system.

Districts list
  The districts list is a JSON format file, whose format and associated
  protocols are defined in the document "IVXV Protocols". For Estonian national
  elections, the districts list comes from the election information system.

Application trust root
  The application trust root defines the certification hierarchies based on
  which IVXV applications verify digital signatures. For Estonian national
  elections, the composition of the trust root is determined by the National
  Electoral Service. The format of the application trust root is covered in
  chapter :numref:`ivxv-rakendused`.

Collector service trust root
  The collector service trust root defines the certification hierarchies based
  on which IVXV collector service components verify digital signatures. For
  Estonian national elections, the composition of the trust root is determined
  by the National Electoral Service. The format and associated protocols of the
  collector service trust root are covered in chapter :numref:`kogumisteenus`.

Collector service technical configuration
  The collector service technical configuration describes the IVXV
  microservice settings and the distribution of instances. For Estonian
  national elections, the collector service provider is found by the National
  Electoral Service. The technical configuration is agreed upon between the
  election owner and the collector service provider. The technical
  configuration is covered in chapter :numref:`kt-technical`.

Collector service keys and certificates
  The collector service microservices communicate with each other via the TLS
  protocol. The corresponding certificates must be exported to the Voter
  Application and the Verification Application. The creation of keys related
  to the collector service is covered in chapter :numref:`kt-krypto`.

Vote encryption key specification
  The algorithm used for the vote encryption key and associated technical
  parameters are fixed before generating the vote encryption key. The key
  specification is covered in chapter :numref:`key-groupgen`.

Activities Before the Voting Period
***********************************

Before the start of the voting period, the following activities are performed
based on the preceding data:

#. :numref:`app-install`
#. :numref:`app-trust`
#. :numref:`key-groupgen`
#. :numref:`key-init`
#. :numref:`key-testkey`
#. :numref:`kt-trust`
#. :numref:`kt-technical`
#. :numref:`kt-election`
#. Loading the districts list into the Collector Service
#. Loading the choices list into the Collector Service
#. Loading the voter list (initial) into the Collector Service
#. :numref:`kt-management`
#. :numref:`valijarakendus`
#. :numref:`kontroll`

Voting Period Activities
************************

#. Loading voter lists (changes) into the Collector Service

Activities After the Voting Period
**********************************

E-ballot box processing
^^^^^^^^^^^^^^^^^^^^^^^

#. :numref:`processor-check`
#. :numref:`processor-squash`
#. :numref:`processor-revoke`
#. :numref:`processor-anonymize`

Vote mixing
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

#. :numref:`mix-install`
#. :numref:`mix-mix`
#. :numref:`mix-verify`

Determining the voting result and data audit
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

#. :numref:`key-decrypt`
#. :numref:`auditor-convert`
#. :numref:`auditor-mix`
#. :numref:`auditor-decrypt`
