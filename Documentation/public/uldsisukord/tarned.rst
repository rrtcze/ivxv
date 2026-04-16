..  IVXV dokumentatsiooni üldsisukord

Deliveries
==========

Changes in delivery 1.10.4 composition, differences compared to delivery 1.10.3
--------------------------------------------------------------------------------

Collection Service
~~~~~~~~~~~~~~~~~~

General changes

* Refinements to voter list change downloads

Registration Service
~~~~~~~~~~~~~~~~~~~~

* No changes

Verification Applications
~~~~~~~~~~~~~~~~~~~~~~~~~

Android

* No changes

iOS

* No changes

Mixnet
~~~~~~

* No changes

Processing Applications
~~~~~~~~~~~~~~~~~~~~~~~

General

* No changes

Key Application

* No changes

Processing Application

* No changes

Audit Application

* No changes

Voter Applications and Configuration Application
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

* No changes

Documentation
~~~~~~~~~~~~~

* Numbering review
* Key application configuration refinements
* Smart-ID protocol example refinements

Log Monitor
~~~~~~~~~~~

* No changes


Changes in delivery 1.10.3 composition, differences compared to delivery 1.10.2
--------------------------------------------------------------------------------

Collection Service
~~~~~~~~~~~~~~~~~~

General changes

* No changes

Registration Service
~~~~~~~~~~~~~~~~~~~~

* No changes

Verification Applications
~~~~~~~~~~~~~~~~~~~~~~~~~

Android

* No changes

iOS

* No changes

Mixnet
~~~~~~

* No changes

Processing Applications
~~~~~~~~~~~~~~~~~~~~~~~

General

* No changes

Key Application

* No changes

Processing Application

* No changes

Audit Application

* No changes

Voter Applications and Configuration Application
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

* No changes

Documentation
~~~~~~~~~~~~~

* Translation review
* Spelling review
* Documenting delivery 1.10.2 content

Log Monitor
~~~~~~~~~~~

* No changes


Changes in delivery 1.10.2 composition, differences compared to delivery 1.10.1
--------------------------------------------------------------------------------

Collection Service
~~~~~~~~~~~~~~~~~~

General changes

* Improvement of ZIP/BDOC file handling
* Dependency updates, JavaScript
* eID tool testing
* Memory leak fixes
* Smart-ID flow updates according to protocol
* List loading interval and strategy refinements
* Development and test environment improvements
* Minor fixes

Registration Service
~~~~~~~~~~~~~~~~~~~~

* No changes

Verification Applications
~~~~~~~~~~~~~~~~~~~~~~~~~

Android

* Application migration to the Chancellery of the Riigikogu store
* TargetSDK update
* Various bug fixes in the user interface
* Additional obfuscation
* Error message improvements

iOS

* Application migration to the Chancellery of the Riigikogu store
* Various bug fixes in the user interface
* Refinements to application backup
* Application lifecycle state machine refinements
* Error message improvements

Mixnet
~~~~~~

* No changes

Processing Applications
~~~~~~~~~~~~~~~~~~~~~~~

General

* Improvement of ZIP/BDOC file handling

Key Application

* Minor fixes

Processing Application

* Minor fixes

Audit Application

* Minor fixes

Voter Applications and Configuration Application
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

* Dependency updates, OpenSSL, PCRE
* UI library FLTK update
* Smart-ID flow update
* Testing with the latest ID card
* Compilation environment refinements

Documentation
~~~~~~~~~~~~~

* Translation review
* Spelling review
* Documenting delivery 1.10.2 content

Log Monitor
~~~~~~~~~~~

* Dependency updates, Python, JavaScript
* Web interface enhancements
* Adoption of query pooler ``pgbouncer``
* Web server configuration review based on security test results


Changes in delivery 1.10.1 composition, differences compared to delivery 1.10.0
--------------------------------------------------------------------------------

Collection Service
~~~~~~~~~~~~~~~~~~

General changes

* Support for updated SmartID certificate profile

Registration Service
~~~~~~~~~~~~~~~~~~~~

* No changes

Verification Applications
~~~~~~~~~~~~~~~~~~~~~~~~~

Android

* Refinements in vote verification, edge case review

iOS

* Refinements in vote verification, edge case review

Mixnet
~~~~~~

* No changes

Processing Applications
~~~~~~~~~~~~~~~~~~~~~~~

General

* No changes

Key Application

* No changes

Processing Application

* No changes

Audit Application

* No changes

Voter Applications and Configuration Application
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

* No changes

Documentation
~~~~~~~~~~~~~

* No changes

Log Monitor
~~~~~~~~~~~

* Minor fixes according to the changelog


Changes in delivery 1.10.0 composition, differences compared to delivery 1.9.10
--------------------------------------------------------------------------------

Collection Service
~~~~~~~~~~~~~~~~~~

General changes

* Functionality for removing invalid ballots in the collection service
* MODP and elliptic curve cryptography
* Various minor fixes according to the changelog

Registration Service
~~~~~~~~~~~~~~~~~~~~

* No changes

Verification Applications
~~~~~~~~~~~~~~~~~~~~~~~~~

Android

* Elliptic curve cryptography
* Accessibility improvements
* Refinements in vote verification, edge case review

iOS

* Elliptic curve cryptography
* Accessibility improvements
* Refinements in vote verification, edge case review

Mixnet
~~~~~~

* Elliptic curve cryptography

Processing Applications
~~~~~~~~~~~~~~~~~~~~~~~

General

* Elliptic curve cryptography
* Refinements in ballot box verification, edge case review

Key Application

* Elliptic curve cryptography
* Refinements in ballot box verification, edge case review

Processing Application

* Elliptic curve cryptography
* Refinements in ballot box verification, edge case review

Audit Application

* Elliptic curve cryptography
* Refinements in ballot box verification, edge case review

Voter Applications and Configuration Application
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

* Elliptic curve cryptography
* Proxy usage refactoring

Documentation
~~~~~~~~~~~~~

* Protocol document enhancements
* Log document creation

Log Monitor
~~~~~~~~~~~

* Minor fixes according to the changelog


Changes in delivery 1.9.10 composition, differences compared to delivery 1.9.4
--------------------------------------------------------------------------------

Collection Service
~~~~~~~~~~~~~~~~~~

General changes

* Various minor fixes according to the changelog

Registration Service
~~~~~~~~~~~~~~~~~~~~

* No changes

Verification Applications
~~~~~~~~~~~~~~~~~~~~~~~~~

Android

* FLAG_SECURE adoption
* Refinements in vote verification, edge case review

iOS

* Accessibility improvements
* Refinements in vote verification, edge case review

Mixnet
~~~~~~

* No changes

Processing Applications
~~~~~~~~~~~~~~~~~~~~~~~

General

* No changes

Key Application

* Edge case review for declaring cryptograms invalid


Processing Application

* Edge case review for declaring votes invalid

Audit Application

* No changes

Voter Applications and Configuration Application
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

* Windows, accessibility bug fixes

Documentation
~~~~~~~~~~~~~

* Harmonization of Estonian and English documentation
* Architecture document enhancements

Log Monitor
~~~~~~~~~~~

* Detection of voting fact transmission failures from logs
* Minor fixes according to the changelog


Changes in delivery 1.9.4 composition, differences compared to delivery 1.8.2
--------------------------------------------------------------------------------

Collection Service
~~~~~~~~~~~~~~~~~~

General changes

* Ubuntu 22.04 support
* Go version upgrade
* etcd version upgrade and configuration
* Dependency updates
* Addition of Web eID authentication method
* Addition of session status microservice
* Improving EHS statistics interface reliability
* Gradual end of elections
* Making session identifier mandatory
* ASiCe format refinement
* VIS support for detailed statistics
* SmartID support refinements
* Various minor fixes according to the changelog

Registration Service
~~~~~~~~~~~~~~~~~~~~

* No changes

Verification Applications
~~~~~~~~~~~~~~~~~~~~~~~~~

Android

* TLS 1.3
* Abandoning certificate pinning
* Choices list verification

iOS

* TLS 1.3
* Choices list verification

Mixnet
~~~~~~

* No changes

Processing Applications
~~~~~~~~~~~~~~~~~~~~~~~

General

* Java 17

Key Application

* Proving correct decryption of invalid ballots


Processing Application

* Statistics calculation refinements
* Processing procedure auditing refinements

Audit Application

* Verifying correct decryption of invalid ballots
* Ballot verification refinements

Voter Applications and Configuration Application
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

* TLS 1.3
* Multiple PKCS11 token support
* Windows certificate detection improvements
* Expired certificate detection
* DLL loading error fixes
* Accessibility on macOS platform
* User interface changes
* Screenshot automation

Documentation
~~~~~~~~~~~~~

* Adding documentation related to Web eID authentication method
* Harmonization of Estonian and English documentation

Log Monitor
~~~~~~~~~~~

* Ubuntu 22.04 support
* Grafana version upgrade
* Statistics calculation refinements


Changes in delivery 1.8.2 composition, differences compared to delivery 1.8.1
--------------------------------------------------------------------------------

Collection Service
~~~~~~~~~~~~~~~~~~

General changes

* Voter list format change
* Addition of EHS/VIS X-Road interface CI
* EHS/VIS X-Road interface documentation refinements
* Minor bug fixes

Registration Service
~~~~~~~~~~~~~~~~~~~~

* No changes

Verification Applications
~~~~~~~~~~~~~~~~~~~~~~~~~

Android

* RSA removal
* Bug fixes

iOS

* No changes

Mixnet
~~~~~~

* No changes

Processing Applications
~~~~~~~~~~~~~~~~~~~~~~~

General

* Voter list format change

Key Application

* No changes

Processing Application

* Workflow consolidation

Audit Application

* No changes

Voter Applications and Configuration Application
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

* Minor bug fixes

Documentation
~~~~~~~~~~~~~

* Refinements related to software changes

Log Monitor
~~~~~~~~~~~

* No changes

Changes in delivery 1.8.1 composition, differences compared to delivery 1.7.7
--------------------------------------------------------------------------------

Collection Service
~~~~~~~~~~~~~~~~~~

General changes

* Addition of Smart-ID support
* Addition of EHS/VIS X-Road interface
* Ordering of voting facts
* Configurable SNI


Registration Service
~~~~~~~~~~~~~~~~~~~~

* No changes

Verification Applications
~~~~~~~~~~~~~~~~~~~~~~~~~

Android

* Smart-ID
* Refined cryptogram verification
* Configurable SNI

iOS

* Smart-ID
* Refined cryptogram verification
* Configurable SNI

Mixnet
~~~~~~

* No changes

Processing Applications
~~~~~~~~~~~~~~~~~~~~~~~

General

* Smart-ID

Key Application

* No changes

Processing Application

* Workflow consolidation, parameter refinements

Audit Application

* No changes

Voter Applications and Configuration Application
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

* SmartID
* Updated appearance

Documentation
~~~~~~~~~~~~~

* Refinements related to software changes - SmartID, etc.

Log Monitor
~~~~~~~~~~~

* SmartID

Changes in delivery 1.7.7 composition, differences compared to delivery 1.7.6
--------------------------------------------------------------------------------

Collection Service
~~~~~~~~~~~~~~~~~~

General changes

* No changes

Management Service

* No changes

IVXV Microservices

* No changes

Registration Service
~~~~~~~~~~~~~~~~~~~~

* No changes

Verification Applications
~~~~~~~~~~~~~~~~~~~~~~~~~

Android

* No changes

iOS

* No changes

Mixnet
~~~~~~

* Changes related to selective flushing of the entropy source

Processing Applications
~~~~~~~~~~~~~~~~~~~~~~~

General

* No changes

Key Application

* No changes

Processing Application

* No changes

Audit Application

* No changes

Voter Applications and Configuration Application
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

* No changes

Documentation
~~~~~~~~~~~~~

* Changes related to mixnet changes

Log Monitor
~~~~~~~~~~~

* No changes


Changes in delivery 1.7.6 composition, differences compared to delivery 1.6.0
--------------------------------------------------------------------------------

Collection Service
~~~~~~~~~~~~~~~~~~

General changes

* Changes related to managing input lists in VIS3
* Changes related to Ubuntu 20.04 support
* Minor changes/bug fixes according to the `changelog` file

Management Service

* Minor changes/bug fixes according to the `changelog` file

IVXV Microservices

* Minor changes/bug fixes according to the `changelog` file

Registration Service
~~~~~~~~~~~~~~~~~~~~

* No changes

Verification Applications
~~~~~~~~~~~~~~~~~~~~~~~~~

Android

* Changes related to migration to API version 28
* Outdated application detection

iOS

* Changes related to migration to iOS version 12
* Outdated application detection

Mixnet
~~~~~~

* Changes related to Ubuntu 20.04 support

Processing Applications
~~~~~~~~~~~~~~~~~~~~~~~

General

* Changes related to managing input lists in VIS3

Key Application

* No changes

Processing Application

* Processing workflow optimization

Audit Application

* No changes

Voter Applications and Configuration Application
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

* M1 processor type support on macOS platform
* FLTK, OpenSSL and other base library version upgrades
* Outdated application detection

Documentation
~~~~~~~~~~~~~

* Changes related to configuration and terminology changes

Log Monitor
~~~~~~~~~~~

* Included in the delivery




Changes in delivery 1.6.0 composition, differences compared to delivery 1.5.0
--------------------------------------------------------------------------------

Collection Service
~~~~~~~~~~~~~~~~~~

General changes

* Mobile-ID REST service support
* Minor changes/bug fixes according to the `changelog` file

Management Service

* Minor changes/bug fixes according to the `changelog` file

IVXV Microservices

* Minor changes/bug fixes according to the `changelog` file

Registration Service
~~~~~~~~~~~~~~~~~~~~

* No changes

Verification Applications
~~~~~~~~~~~~~~~~~~~~~~~~~

Android

* No changes

iOS

* No changes

Mixnet
~~~~~~

* Adoption of Java version 11
* Verificatum version upgrade

Processing Applications
~~~~~~~~~~~~~~~~~~~~~~~

General

* Adoption of Java version 11

Key Application

* New format for RSA key serialization

Processing Application

* No changes

Audit Application

* No changes

Voter Applications and Configuration Application
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

* Mobile-ID REST service support

Documentation
~~~~~~~~~~~~~

* Mobile-ID REST service support

Log Monitor
~~~~~~~~~~~

* Removed from delivery due to license expiration



Changes in delivery 1.5.0 composition, differences compared to delivery 1.4.1
--------------------------------------------------------------------------------

Collection Service
~~~~~~~~~~~~~~~~~~

General changes

* Logging of all requests
* etcd from Debian buster repository, to obtain the latest golang-google-rpc
* Minor changes/bug fixes according to the `changelog` file

Management Service

* Minor changes/bug fixes according to the `changelog` file

IVXV Microservices

* Minor changes/bug fixes according to the `changelog` file

Registration Service
~~~~~~~~~~~~~~~~~~~~

* No changes

Verification Applications
~~~~~~~~~~~~~~~~~~~~~~~~~

Android

* Changes related to code review and error handling improvements

iOS

* No changes

Mixnet
~~~~~~

* Changes related to mixing 300K votes

Processing Applications
~~~~~~~~~~~~~~~~~~~~~~~

General

* Using election identifier as a common prefix

Key Application

* Changes related to code review

Processing Application

* Changes related to processing 300K votes

Audit Application

* Progress bar
* Changes related to processing 300K votes

Voter Applications and Configuration Application
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

* MSAA support refinement
* Using system PIN dialogs on Windows platform

Documentation
~~~~~~~~~~~~~

* Addition of IVXV auditor guide
* Addition of change documents to the delivery


Log Monitor
~~~~~~~~~~~

* Changes/bug fixes according to the `changelog` file




Changes in delivery 1.4.1 composition, differences compared to delivery 1.4.0
--------------------------------------------------------------------------------

Collection Service
~~~~~~~~~~~~~~~~~~

General changes

* Minor changes/bug fixes according to the `changelog` file

Management Service

* Minor changes/bug fixes according to the `changelog` file

IVXV Microservices

* Minor changes/bug fixes according to the `changelog` file

Registration Service
~~~~~~~~~~~~~~~~~~~~

* No changes

Verification Applications
~~~~~~~~~~~~~~~~~~~~~~~~~

Android

* No changes

iOS

* No changes

Mixnet
~~~~~~

* No changes

Processing Applications
~~~~~~~~~~~~~~~~~~~~~~~

General

* No changes

Key Application

* Change in *init* tool output files
* Change in *init* tool SN and CN parameters
* Change in *testkey* tool input parameters
* Display of used card numbers in *decrypt* tool

Processing Application

* No changes

Audit Application

* No changes

Voter Applications and Configuration Application
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

* MSAA support refinement

Documentation
~~~~~~~~~~~~~

* IVXV protocols - addition of registration protocol
* IVXV configuration guide - comprehensive updates and
  harmonization with the handbook.
* IVXV voter application - comprehensive updates.
* IVXV mixnet - document incorporated into the configuration guide, removed.
* IVXV registration service - document incorporated into the protocol specification, removed.

Log Monitor
~~~~~~~~~~~

* Minor changes/bug fixes according to the `changelog` file

Changes in delivery 1.4.0 composition, differences compared to delivery 1.3.0
--------------------------------------------------------------------------------

Collection Service
~~~~~~~~~~~~~~~~~~

General changes

* Automatic retry of OCSP and timestamp requests according to
  configuration
* Support for BDOC-TS signature containers
* Support for empty voter lists

Management Service

* Minor changes/bug fixes according to the `changelog` file

IVXV Microservices

* Minor changes/bug fixes according to the `changelog` file

Registration Service
~~~~~~~~~~~~~~~~~~~~
* No changes

Verification Applications
~~~~~~~~~~~~~~~~~~~~~~~~~

Android

* TLS 1.2 support for API versions < 19
* Replacing the help info view with the system browser
* Automatic text truncation for buttons when text overflows the screen

iOS

* No changes

Mixnet
~~~~~~

* No changes

Processing Applications
~~~~~~~~~~~~~~~~~~~~~~~

General

* Precinct number uniqueness requirement refinements
* Empty voter list support
* Support for certificates with encoding errors in applications

Key Application

* Removed LOG4 and LOG5

Processing Application

* Removed PDF format voter list from *revoke* phase

Audit Application

* No changes

Voter Applications and Configuration Application
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

* macOS 10.11 support
* 32bit Linux support
* UPX version update
* Pinpad card reader reliability improvement (Win)
* ID card communication error fixes (Win7/ECC)
* Both PEM and DER format data import (Configurator)
* Added configuration validation capability (Configurator)
* Fixed behavior with oversized configurations (Configurator)

Documentation
~~~~~~~~~~~~~

* Documentation update to reflect changes and incorporate DEMO2018
  feedback

Log Monitor
~~~~~~~~~~~

* Addition of MTA dependency
* CSV log export refinements, addition of start and end times
* Log analysis optimization for multi-core hardware
* Minor changes/bug fixes according to the `changelog` file

Changes in delivery 1.3.0 composition, differences compared to delivery 1.2.0
--------------------------------------------------------------------------------

Collection Service
~~~~~~~~~~~~~~~~~~

General changes

* Adoption of Ubuntu 18.04 LTS (Bionic Beaver)
* Description of crash recovery procedures

Management Service

* Fixed tools for obtaining service status information
* Minor changes/bug fixes according to the `changelog` file

IVXV Microservices

* Adoption of golang language version 1.9
* Support for the updated Estonian ID card profile (PNOEE)
* Minor changes/bug fixes according to the `changelog` file

Registration Service
~~~~~~~~~~~~~~~~~~~~
* No changes

Verification Applications
~~~~~~~~~~~~~~~~~~~~~~~~~

Android

* ESTEID2018 certificate support
* Refined handling of public keys with faulty ASN1 encoding

iOS

* ESTEID2018 certificate support
* iPhone 10 X changes
* Using XCode 10 and iOS 12 SDK

Mixnet
~~~~~~

* Adoption of the Verificatum AGPL version

Processing Applications
~~~~~~~~~~~~~~~~~~~~~~~

Key Application

* No changes

Processing Application

* Added StatsTool for generating statistics files from the ballot box
* Added StatsDiffTool for comparing two statistics files
* ESTEID2018 certificate and profile support
* Using digidoc4j 2.1.0

Audit Application

* No changes

Voter Applications and Configuration Application
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

* Enabling candidate search in the voter application
* Displaying parties and candidates as folders in the voter application
* Migration of the voter application and configurator to JSON format settings
* ESTEID2018 certificate and profile support
* Win: IDEMIA minidriver support
* Linux/macOS: IDEMIA PKCS11 driver support
* macOS 10.14 support

Documentation
~~~~~~~~~~~~~

* Documentation update to reflect changes
* Addition of English architecture document and protocol specification

Log Monitor
~~~~~~~~~~~

* Adoption of Ubuntu 18.04 LTS (Bionic Beaver)
* Adopted Grafana 5.3.4
* Fixed age-based statistics generation and age group
  distribution
* CSV output from sessions

Changes in delivery 1.2.0 composition, differences compared to KOV2017 elections.
--------------------------------------------------------------------------------

Collection Service
~~~~~~~~~~~~~~~~~~

Management Service

* Added tool for removing faulty voter lists.
* Added tool for adding district/precinct lists.
* Added district-based statistics.
* Added backup service.
* Added tool for consolidating backed-up ballot boxes.
* Added tool for list consistency verification.
* Added capability to add election-specific prefixes to configuration files.
* Enhanced management interface with help information.
* Removed deprecated configuration parameter "stats.*"
* Fixed input file format validation and loading.

IVXV Microservices

* Updated etcd version.
* Added capability to configure etcd timeouts via environment variables.
* Added capability to modify cluster for crash recovery purposes.
* Fixed cluster behavior during leader change, retrying pending stores.
* TLS ciphers made configurable.
* Fixed BDOC profile identifying configuration field name.
* Added capability to configure Mobile-ID authentication to require both personal code and phone number.
* Added capability to limit repeat voting frequency.
* Added capability to support Windows line endings in configuration files.
* Improved BDOC XML canonicalization and parsing.
* Tightened DDS request format validations.
* Logging migrated to RELP protocol.
* Changed configuration file structure to distinguish Collector and Processor responsibilities.

Registration Service
~~~~~~~~~~~~~~~~~~~~
* No changes.

Verification Applications
~~~~~~~~~~~~~~~~~~~~~~~~~

Android

* Added instructions for verifying correspondence between published verification application and disclosed source code.

iOS

* No changes.

Mixnet
~~~~~~
* No changes.

Processing Applications
~~~~~~~~~~~~~~~~~~~~~~~
Key Application

* No changes.

Processing Application

* No changes.

Audit Application

* No changes.

Voter Applications and Configuration Application
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Linux and Mac – no platform-specific changes.
* Windows – fixed interfacing with Minidriver, adoption of mingw64.
* Added ID card ECC support.
* Configured Mobile-ID to require personal code and phone number when needed.
* Enhanced error codes.
* Adapted configurator to correspond with changes.
* Adapted BDOC XML templates

Documentation
~~~~~~~~~~~~~
* Documentation comprehensively updated in connection with changes

Log Monitor
~~~~~~~~~~~
* Abandoned CrateDB.
* Comprehensively adopted PostgreSQL.
* Adopted Grafana 5.0.1.
* Session validation fixes based on KOV2017 log analysis.
* Added statistics generation by districts.
