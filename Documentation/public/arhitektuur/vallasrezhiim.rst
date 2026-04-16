..  IVXV arhitektuur

Applications
==========


General Principles
-------------

All applications are command line interface applications packaged to work in a
Windows 10 (or newer) operating system environment. The component user
interfaces are monolingual. Components are delivered in Estonian, their
translation is possible using a translation file.

Applications are programmed in Java.

Applications communicating with external information systems use existing
interfaces/data structures to the maximum extent.

Applications receive their input from application settings and from files
indicated in the settings on the file system, and save their output to a
user-specified folder on the file system. Files may also be located on a RAM
disk.

Relevant applications support the ElGamal cryptosystem on integer residue
fields and the P-384 elliptic curve. The decryption proof is implemented
using a protocol based on Schnorr's zero-knowledge proof.

.. figure:: model/img/app_modules.png

   Application helper modules

The election interface is unified for applications, which enables the
implementation of different election types as modules. The digital signature
verification functionality is created using the
`digidoc4j <https://github.com/open-eid/digidoc4j>`_ library. The use of
helper modules is not separately shown in the following diagrams.

Application Configuration
```````````````````````

Applications are configured either with a digitally signed configuration
package or with command line switches. Command line switches do not support
entering hierarchically structured settings. Settings in the configuration
package are described in YAML:

.. code-block:: yaml

   check:
     ballotbox: votes.zip
     ballotbox_checksum: votes.zip.sha256sum.bdoc
     districts: TESTKOV2017.districts.json
     registrationlist: register.zip
     registrationlist_checksum: register.zip.sha256sum.bdoc
     tskey: ts.pub.key
     vlkey: test.gen.pub.key
     voterlists:
       -
         path: 00.TESTKOV2017.gen.voters
         signature: 00.TESTKOV2017.gen.voters.signature
       -
         path: 03.TESTKOV2017.gen.voters
         signature: 03.TESTKOV2017.gen.voters.signature
       -
         path: 06.TESTKOV2017.gen.voters
         signature: 06.TESTKOV2017.gen.voters.signature
       -
         path: 09.TESTKOV2017.gen.voters
         signature: 09.TESTKOV2017.gen.voters.signature
     election_start: 2017-05-01T12:00:00+03:00
     out: out-1
   squash:
     ballotbox: out-1/bb-1.json
     ballotbox_checksum: out-1/bb-1.json.sha256sum.bdoc
     districts: TESTKOV2017.districts.json
     out: out-2
   revoke:
     ballotbox: out-2/bb-2.json
     ballotbox_checksum: out-2/bb-2.json.sha256sum.bdoc
     districts: TESTKOV2017.districts.json
     revocationlists:
       - 12.TESTKOV2017.gen.revoke.json
       - 13.TESTKOV2017.gen.revoke.json
       - 14.TESTKOV2017.gen.revoke.json
       - 15.TESTKOV2017.gen.revoke.json
     out: out-3


Input Consistency Check
`````````````````````````````

All applications perform an input consistency check on the configuration
according to the configuration they use:

#. loading certificate configuration;

#. verifying the digital signature of the configuration;

#. verifying the districts list;

#. consistency check of the districts list;

#. loading the districts list;

#. verifying the choices list;

#. consistency check of the choices list;

#. loading the choices list;

#. verifying the voter lists;

#. consistency check of the voter lists;

#. loading the voter lists.


Key Application
-------------

.. figure:: model/img/key.png

   Key Application interfaces

The Key Application generates the vote encryption and vote decryption keys for
each election, and also performs vote counting and result output.

The Key Application uses the [DesmedtF89]_ threshold scheme, which is based on
a trusted dealer and applies Shamir's secret sharing, which is
information-theoretically secure for :math:`t < M` parties, where M is
the threshold.

Key shares are generated in volatile memory and stored on a smart card via
the PKCS15 interface.

The input of the Key Application for key generation is:

- Key pair identifier;

- ElGamal cryptosystem specification – integer residue field or P-384
  elliptic curve and key length;

- M-N threshold scheme specification, which must comply with the rule
  :math:`N >= 2 * M - 1`;

- N PKCS15-compatible smart cards;

The output of the Key Application for key generation is:

- Self-signed certificate;

- N key shares stored on smart cards;

- Detailed application activity log;

- Detailed application error log.

The input of the Key Application for vote counting is:

- Mixed votes;

- Key pair identifier;

- M key shares according to the threshold scheme specification.

The output of the Key Application for vote counting is:

- Signed voting result;

- List of invalid votes;

- Decryption proof (protocol based on Schnorr's zero-knowledge proof as
  referenced in the procurement documents);

- Detailed application activity log;

- Detailed application error log.

Processing Application
-----------------

The Processing Application verifies, revokes, and anonymizes votes collected
during the voting period according to Section 7.6 of the General Description.

The inputs of the Processing Application are:

- electronic votes stored by the collector service;

- timestamps issued by the registration service;

- voter lists;

- districts list;

- revocation lists;

- restoration lists.

The outputs of the Processing Application are:

- detailed application activity log;

- detailed application error log;

- list of e-voters in PDF format, according to the processing stage;

- list of e-voters in machine-readable format, according to the processing stage;

- anonymized votes.

In addition to previously defined interfaces and dependencies, the Processing
Application uses a third-party library for implementing the PDF output
functionality.

.. figure:: model/img/processing.png

   Processing Application interfaces

Complete Processing of Electronic Votes
`````````````````````````````````````

Complete processing of electronic votes is an activity during which the
Processing Application compares the set of votes stored by the Collector
Service with the set of votes stored by the registration service, checks the
compliance of stored votes with the election configuration, identifies the
votes to be counted, and anonymizes them for handover to the Key Application.

#. loading application settings;

#. verifying digital signatures of electronic votes;

#. verifying registration service confirmations;

#. verifying timestamps;

#. identifying the last valid vote for each voter;

#. outputting the initial list of e-voters in PDF format;

#. verifying revocation and restoration lists;

#. consistency check of revocation and restoration lists;

#. applying revocation and restoration lists;

#. compiling the list of votes to be mixed, separating cryptograms from
   digital signatures;

#. outputting the final list of e-voters in machine-readable format.


Generating the List of E-Voters
````````````````````````````````

#. loading application settings;

#. verifying digital signatures of electronic votes;

#. outputting the initial list of e-voters in PDF format.


Audit Application
--------------

.. figure:: model/img/audit.png

   Audit Application interfaces

The Audit Application (figure 9) mathematically verifies the correctness of
vote tallying and, when mixing is used, also the correctness of mixing.

The inputs of the Audit Application are;

- anonymized votes;

- mixed votes;

- Verificatum mixing proof;

- voting result.

The output of the Audit Application is the detailed application activity log,
which also contains an assessment of the overall success of the audit. If
necessary, a detailed application error log is also output.
