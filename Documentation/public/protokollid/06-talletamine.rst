..  IVXV protocols

====================================================
Qualifying an Electronic Vote for Storage
====================================================

Qualified Vote
=====================

As a result of the voter application's work, a double envelope is sent to the
collection service for storage, which contains the voter's expression of will
in encrypted form, the voter's signature on the encrypted expression of will
in an agreed signature and container format, and the voter's signing
certificate in X509 format.

For successful vote storage, the IVXV protocol provides for registering the
vote with an external registration service provider and making the
registration proof available to the voter application. The election organizer
may prescribe additional steps for qualifying the vote beyond registration --
for example, obtaining a validity confirmation for the certificate that signed
the vote.

All qualifying elements obtained by the collection service that determine the
vote's status in subsequent processing stages must be presented to the voter
application and, upon request, also to the verification application, to ensure
that the voter can learn in a timely manner about the possibility of correct
processing of their vote.

OCSP Validity Confirmation
---------------------

OCSP (*Online Certificate Status Protocol*) is a standard protocol for
querying the validity information of X509 certificates. The collection service
may use this protocol to determine the validity of the certificate that signed
the vote. The OCSP response states that the certificate was valid at the time
of the query, but does not associate the OCSP response with a specific
signature.

RFC3161 Timestamp
-----------------

Using the RFC3161 timestamp protocol, a confirmation is obtained from a trust
service provider that a certain set of data existed before a certain point in
time. In the BDOC-TS context, the ``SignatureValue`` element of the signature
is timestamped in its canonicalized form. A classical OCSP response together
with an RFC 3161 format timestamp qualifies a BDOC-TS signature.

Storage
====================================================

Storing an electronic vote in the collection service means:

#. receiving the vote from the voter application and verifying the voter's
   signature;

#. possible qualification of the vote -- for example, proving the validity of
   the certificate at a time close to the signing of the vote;

#. registering the vote in an independent registration service;

#. mediating the vote-qualifying elements to the voter application.

Different combinations of signature formats and vote-qualifying services may
create different IVXV profiles. Within this specific document, the IVXV
profile is:

#. The signed vote format is BDOC-TS;

#. The validity confirmation protocol is standard OCSP;

#. The RFC3161 timestamp used for BDOC-TS qualification is also used as the
   registration proof.
