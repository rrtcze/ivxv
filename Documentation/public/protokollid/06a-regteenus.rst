..  IVXV registration service

====================================
Registration of an Electronic Vote
====================================

For successful vote storage, the IVXV protocol provides for registering the
vote with an external registration service provider and making the
registration proof available to the voter application. The registration service
operates on the basis of the RFC3161 timestamp protocol. The protocol has been
extended such that the collection service can provide its own signature to the
timestamp request, which makes possible a later comparative extract from the
registration service. The presence of an independent registration service
reduces the risk of votes being "lost" by the collection service.

Registration Service
====================

The registration service is a service through which the collection service
registers all votes received from voters. After the end of the voting period,
the collection service delivers the stored votes to the processor, and the
registration service delivers the registered votes to the processor.

The registration service helps ensure the integrity of the e-ballot box. We
assume that the collection service has no ability to forge digital signatures
and thereby create additional votes or alter already stored votes. The risk
remains that the collection service may not deliver all stored votes to the
processor. To mitigate the risk of selective delivery of votes, the IVXV
protocol uses an additional registration service where the collection service
registers each stored vote. The voter has the protocol-compliant ability to
verify correct registration -- the registration service's digitally signed
confirmation of the registration of a specific vote is also presented to the
specific voter.

Registration Service in the Protocol
--------------------------------

The collection service sends to the registration service an order signed by it
(hereinafter ORDER), which contains the vote identifier and the hash of the
signed vote::

  ORDER = Sign_K(V_id, Hash(VOTE))

The registration service stores the ORDER for later issuance and responds to
the collection service with a registration confirmation signed by it
(hereinafter CONFIRMATION), which signs the original ORDER and the time of
issuance of the CONFIRMATION::

  CONFIRMATION = Sign_R(Hash(ORDER), t)

The collection service returns both the CONFIRMATION and the ORDER to the voter
application. The voter receives notification of successful vote storage only
upon successful verification of the CONFIRMATION and the underlying ORDER.

At the end of the voting period, the registration service delivers the ORDERs
made by the collection service to the processor.

The registration service must initially deliver to the processor at least the
list::

  (V_id, Hash(VOTE))

If the registration service delivers only the above-described list, then it
must later be able to provide the order corresponding to the requested element
of the list::

  (V_id, Hash(VOTE)), Sign_K(V_id, Hash(VOTE))


.. figure:: model/img/phase1.png

   Role of the registration service in voting


.. figure:: model/img/phase2.png

   Role of the registration service in vote verification


.. figure:: model/img/phase3.png

   Role of the registration service in vote handover


Registration Service Interfaces
------------------------------

The registration service has two interfaces:

#. the interface for receiving ORDERs and issuing CONFIRMATIONs;

#. the interface for issuing the list of CONFIRMATIONs issued based on ORDERs
   and the underlying ORDERs.

The functionality of the registration service is issuing CONFIRMATIONs to the
collection service, storing the issued CONFIRMATIONs and their underlying
ORDERs, and later delivering them to the processor.

If the registration service provides service to multiple different parties,
then it must be guaranteed that the ORDERs of the collection service related
to a specific election and the corresponding CONFIRMATIONs are verifiably
distinguishable by the voter application and the verification application
from the ORDERs of other parties and their corresponding CONFIRMATIONs.
Otherwise, a situation may arise where the collection service does register
the vote, but the information about it does not reach the processor.

The registration service must be able to deliver all ORDERs received from
the collection service.

Requirements of Parties for the Registration Service
----------------------------------------

Processor
````````

The processor's task includes, among other things, determining:

#. which of the votes delivered by the collection service will be counted, and

#. whether the collection service has failed to deliver any votes.

Discrepancies identified as a result of the processor's work must be resolved,
and here there are the following 3 cases:

#. The collection service delivers the signed vote together with the
   CONFIRMATION to the processor, the registration service delivers the
   collection service's ORDER on the basis of which the CONFIRMATION was
   issued to the processor -- there is no dispute; if the specific vote was
   the last one for the voter, it is sent for counting.

#. The collection service delivers the signed vote together with the
   CONFIRMATION to the processor, the registration service does not deliver
   anything about this vote to the processor. Since the CONFIRMATION is
   signed by the registration service, the fault is on the registration
   service's side. If the specific vote was the last one for the voter, it
   is sent for counting.

#. The registration service delivers the collection service's ORDER to the
   processor, the collection service does not deliver a vote with the
   corresponding hash to the processor. Since the ORDER is signed by the
   collection service, the fault is on the collection service's side and
   the given vote must be located.

Voter
`````````

For the voter, the risk is that the collection service may "forget" their
vote. Seeing a proper CONFIRMATION gives the voter confidence that an external
party guarantees the delivery of their vote to the processor. For this
confidence, it is important that:

#. the CONFIRMATION is signed by the registration service;

#. the original ORDER contained in the CONFIRMATION is signed by the
   collection service;

#. trust that the registration service is able to remember the fact of
   issuing the CONFIRMATION;

#. trust that the registration service is able to prove the propriety of
   issuing the CONFIRMATION to the processor;

#. trust that the collection service is unable to obtain an alternative
   false confirmation that verifies in the voter application but does not
   reach the processor.

Collection Service
`````````````````

For the collection service, the risk is that the views of CONFIRMATIONs
delivered by the registration service and stored votes differ. The signature
given by the collection service to the ORDER is the collection service's
guarantee that no fictitious CONFIRMATIONs that the collection service has
not actually requested can originate from the registration service.

The collection service stores all registration service responses. Since they
are signed, the additional information is relevant only when the collection
service claims that a certain ORDER was not issued, although the registration
service has presented ``(v_id, Hash(VOTE))``. In such a case, the registration
service can present the entire collection service's ORDER (or at least its
signed component).

Registration Service
````````````````````

The registration service is interested in being able to prove the correctness
of its activities in dispute situations where the collection service fails to
deliver something. It is important to ensure:

#. ORDERs issued by the collection service within a specific election are
   verifiably distinguishable from ORDERs submitted by other clients.

#. The collection service cannot claim that it did not submit already
   submitted ORDERs.

Implementation of the Registration Service within the RFC 3161 Protocol Framework
--------------------------------------------------------------------

PKIX is a timestamping protocol where a trusted third party (Time-Stamp
Authority, TSA) confirms with its signature the existence of data at a
specific point in time. The protocol consists of one request and response.

Timestamp request::

  TimeStampReq ::= SEQUENCE  {
    version               INTEGER  { v1(1) },
    messageImprint        MessageImprint,
      --a hash algorithm OID and the hash value of the data to be
      --time-stamped
    reqPolicy             TSAPolicyId              OPTIONAL,
    nonce                 INTEGER                  OPTIONAL,
    certReq               BOOLEAN                  DEFAULT FALSE,
    extensions            [0] IMPLICIT Extensions  OPTIONAL  }

The data to be timestamped is presented to the service as a hash within the
``messageImprint``. The ``TimeStampReq`` does not contain the requester's
signature.

TSA response to the timestamp request::

  TimeStampResp ::= SEQUENCE  {
    status                PKIStatusInfo,
    timeStampToken        TimeStampToken           OPTIONAL  }

  TimeStampToken ::= ContentInfo
    -- contentType is id-signedData ([CMS])
    -- content is SignedData ([CMS])

  TSTInfo ::= SEQUENCE  {
    version               INTEGER  { v1(1) },
    policy                TSAPolicyId,
    messageImprint        MessageImprint,
      -- MUST have the same value as the similar field in
      -- TimeStampReq
    serialNumber          INTEGER,
      -- Time-Stamping users MUST be ready to accommodate integers
      -- up to 160 bits.
    genTime               GeneralizedTime,
    accuracy              Accuracy                 OPTIONAL,
    ordering              BOOLEAN                  DEFAULT FALSE,
    nonce                 INTEGER                  OPTIONAL,
      -- MUST be present if the similar field was present
      -- in TimeStampReq.  In that case it MUST have the same value.
    tsa                   [0] GeneralName          OPTIONAL,
    extensions            [1] IMPLICIT Extensions  OPTIONAL }


The ``TimeStampResp`` is a digitally signed container by the TSA, which
contains the ``messageImprint`` field received as part of the request and the
nonce.

It is in the interest of the registration service that the collection
service's request be signed. Since RFC 3161 does not support signed requests,
an alternative is to use an extension that enables the transmission of the
collection service's signature. This extension should also be returned by the
service as part of the timestamp. Since RFC 3161 does not unambiguously state
the requirement for mirroring extensions back, a realistic possibility is to
use the nonce of the timestamp request for extending the protocol. The nonce
is an ASN.1 INTEGER data type into which data of arbitrary structure can be
encoded, which makes the following scheme possible:

Before voting:

#. The collection service generates a signing key and certificate.

#. The collection service delivers the certificate to the organizer.

#. The collection service configures itself to use the TSA.

During voting:

#. The voter sends a vote for storage.

#. The collection service hashes the vote, signs the hash, and obtains a
   timestamp for the hash, using its signature on that hash as the nonce of
   the timestamp request TimeStampReq.

#. The TSA processes the timestamp request in accordance with RFC 3161
   requirements and issues a signed timestamp.

#. The collection service mediates the timestamp to the voter application,
   which performs the following checks:

   a) the timestamp is signed by the TSA,
   b) the timestamp contains a nonce,
   c) the timestamp contains the hash of their vote,
   d) the nonce is the collection service's signed hash of the voter's vote.

After voting:

#. The organizer provides the TSA with a time period and the collection
   service's certificate.

#. The TSA searches among all timestamp requests and responses of that time
   period for those that:

   a) have a nonce,
   b) the nonce decodes into the agreed data structure,
   c) the data structure verifies with the collection service's certificate.

#. The TSA delivers all found timestamp requests and timestamps.

#. The collection service delivers all timestamp requests, timestamps, and
   votes.

#. The processor analyzes the data according to the protocol.

#. The CONFIRMATION is signed by the registration service;

#. The original ORDER contained in the CONFIRMATION is signed by the
   collection service;

#. Trust that the registration service is able to remember the fact of
   issuing the CONFIRMATION;

#. Trust that the collection service is unable to obtain an alternative
   false confirmation that verifies in the voter application but does not
   reach the processor;

#. Trust that the registration service is able to prove the propriety of
   issuing the CONFIRMATION to the processor;

#. No fictitious CONFIRMATIONs that the collection service has not actually
   requested can originate from the registration service;

#. The collection service cannot claim that it did not submit already
   submitted ORDERs.

Nonce format::

  Signature ::= SEQUENCE {
    signingAlgorithm AlgorithmIdentifier,
    signature        ANY DEFINED BY signingAlgorithm
  }

  AlgorithmIdentifier ::= SEQUENCE {
    algorithm  OBJECT IDENTIFIER,
    parameters ANY DEFINED BY algorithm OPTIONAL
  }

The message is the DER encoding of TimeStampReq.messageImprint::

  MessageImprint ::= SEQUENCE {
    hashAlgorithm AlgorithmIdentifier,
    hashedMessage OCTET STRING
  }

When using RSA for signing, the value of the field
``Signature.signingAlgorithm.algorithm`` depends on the value of the message's
``hashAlgorithm`` field::

  pkcs-1 OBJECT IDENTIFIER ::= { iso(1) member-body(2) US(840) rsadsi(113549) pkcs(1) 1 }

  sha-1WithRSAEncryption   OBJECT IDENTIFIER  ::=  { pkcs-1  5 }
  sha224WithRSAEncryption  OBJECT IDENTIFIER  ::=  { pkcs-1 14 }
  sha256WithRSAEncryption  OBJECT IDENTIFIER  ::=  { pkcs-1 11 }
  sha384WithRSAEncryption  OBJECT IDENTIFIER  ::=  { pkcs-1 12 }
  sha512WithRSAEncryption  OBJECT IDENTIFIER  ::=  { pkcs-1 13 }

The field ``Signature.signingAlgorithm.parameters`` is absent or NULL.

The field ``Signature.signature`` is an OCTET STRING containing the RSA
signature on the message.

TSA Extract
-------------

The TSA extract of requests in TimeStampReq format submitted by the collection
service is presented as a ZIP file, where each request is saved in one file
that meets the following conditions:

* No folder structure; no file is located in a folder.
* File names are unique (no meaning is assigned to file names).

The delivered data set is:

  * Data file: `<datafilename>.zip`
  * Checksum file: `<datafilename>.zip.sha256sum.asice`

The content of the single-line checksum file is the HEX-encoded SHA256 hash
of the data file.

