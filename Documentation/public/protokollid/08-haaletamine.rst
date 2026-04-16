..  IVXV protocols

===================
Communication Protocols
===================

Interface
------

The collection service's voter-facing microservices communicate with the voter
application and the verification application via the JSON-RPC protocol.

:id: JSON-RPC request identifier
:method: RPC method
:params: Parameters of the specific RPC method

.. literalinclude:: ../../common/examples/json.rpc.method.query.json
   :language: json
   :linenos:

:error: Possible error information or ``null`` if no error
:id: JSON-RPC request identifier, must match the id used in the request
:result: Method-specific response data structure

.. literalinclude:: ../../common/examples/json.rpc.method.response.json
   :language: json
   :linenos:

During the first request exchange with any IVXV microservice, the communicating
application is issued a HEX-encoded unique session identifier (``result.SessionID``),
which the application uses in all subsequent requests to the collection service
(``params.SessionID``). The session identifier is used to associate RPC requests
related to voting into a single session. The association is informational and
its purpose is to simplify log analysis; decisions regarding vote district
affiliation and other substantive aspects are made based on digitally signed data.

TLS is used as the transport protocol. Encrypted channel termination takes
place in the specific microservice. To enable load balancing and flexible
deployment of microservices, the TLS-SNI extension is used, which allows
the proxy service to route the TLS stream to the correct microservice instance
without terminating it. The proxy service is typically available on port 443
of the collection service's external interface.

Obtaining the Choices List
----------------------------

Obtaining the choices list means the voter application's communication with the
choices service (SNI ``choices.ivxv.invalid``). Obtaining the choices list
requires voter authentication and determination of their district affiliation.

The voter application makes the request ``RPC.VoterChoices`` to obtain the lists.

:params.AuthMethod: Supported options are methods ``tls`` and ``ticket``.
:params.OS: Operating system on which the voter application is used.

Request ``RPC.VoterChoices`` for authentication with an ID card - authentication
takes place at the TLS protocol level during request processing using the ID
card's authentication certificate.

.. literalinclude:: ../../common/examples/id.rpc.voterchoices.query.json
   :language: json
   :linenos:

Request ``RPC.VoterChoices`` for authentication with Mobile-ID - to make the
request, the Mobile-ID mediation service (SNI ``mid.ivxv.invalid``) must first
be used to obtain a signed authentication token.

:params.AuthToken: A signed token obtained through the authentication service,
                   which contains the voter's unique identifier.

:params.SessionID: Since in the Mobile-ID case, there was an interaction to
                   obtain the authentication token before obtaining the list,
                   there is a session identifier that must be used.

.. literalinclude:: ../../common/examples/mid.rpc.voterchoices.query.json
   :language: json
   :linenos:

Request ``RPC.VoterChoices`` for authentication with Smart-ID - to make the
request, the Smart-ID mediation service (SNI ``smartid.ivxv.invalid``) must
first be used to obtain a signed authentication token.

:params.AuthToken: A signed token obtained through the authentication service,
                   which contains the voter's unique identifier.

:params.SessionID: Since in the Smart-ID case, there was an interaction to
                   obtain the authentication token before obtaining the list,
                   there is a session identifier that must be used.

.. literalinclude:: ../../common/examples/smartid.rpc.voterchoices.query.json
   :language: json
   :linenos:

Request ``RPC.VoterChoices`` for authentication with Web eID - to make the
request, the Web eID mediation service (SNI ``webeid.ivxv.invalid``) must
first be used to obtain a signed authentication token.

:params.AuthToken: A signed token obtained through the authentication service,
                   which contains the voter's unique identifier.

:params.SessionID: Since in the Web eID case, there was an interaction to
                   obtain the authentication token before obtaining the list,
                   there is a session identifier that must be used.

.. literalinclude:: ../../common/examples/webeid.rpc.voterchoices.query.json
   :language: json
   :linenos:

Response from the choices service to the request ``RPC.VoterChoices``.

:result.Choices: The voter's district affiliation identifier ``VoterDistrict``
:result.List: BASE64-encoded district choices list ``DistrictChoices``
:result.Voted: If the voter has already voted, then ``true``; otherwise
               this field is not present in the response.

.. literalinclude:: ../../common/examples/id.rpc.voterchoices.response.json
   :language: json
   :linenos:

Possible error messages for the request ``RPC.VoterChoices``.

:BAD_CERTIFICATE: Error with the voter's identity certificate.
:BAD_REQUEST: Invalid request.
:INELIGIBLE_VOTER: The voter does not have the right to vote.
:INTERNAL_SERVER_ERROR: Internal server error.
:UNAUTHENTICATED: Unauthenticated request.
:VOTER_TOO_YOUNG: The voter is too young.
:VOTING_END: The voting period has ended.


Sending the Signed Vote for Storage
-------------------------------------------

Sending the signed vote for storage means the voter application's communication
with the voting service (SNI ``voting.ivxv.invalid``).

The voter application makes the request ``RPC.Vote`` to send the signed vote
for storage.

:params.AuthMethod: Supported options are methods ``tls`` and ``ticket``.
:params.Choices: The voter's district affiliation identifier ``VoterDistrict``
                 that was in effect at the time of obtaining the choices list.
                 Correct use of this parameter allows the collection service to
                 warn the voter if their district affiliation has changed
                 compared to the start of voting.
:params.OS: Operating system on which the voter application is used.
:params.Type: Format of the signed vote. Currently the only supported value
              is ``bdoc``.
:params.Vote: BASE64-encoded vote ``SignedVote`` in the previously defined
              format (:ref:`signed-vote`).

Request ``RPC.Vote`` for authentication with an ID card.

.. literalinclude:: ../../common/examples/id.rpc.vote.query.json
   :language: json
   :linenos:

Request ``RPC.Vote`` for authentication with Mobile-ID.

.. literalinclude:: ../../common/examples/mid.rpc.vote.query.json
   :language: json
   :linenos:

Request ``RPC.Vote`` for authentication with Smart-ID.

.. literalinclude:: ../../common/examples/smartid.rpc.vote.query.json
   :language: json
   :linenos:

Request ``RPC.Vote`` for authentication with Web eID.

.. literalinclude:: ../../common/examples/webeid.rpc.vote.query.json
   :language: json
   :linenos:

Response from the voting service to the request ``RPC.Vote``.

:result.Qualification.ocsp:
:result.Qualification.tspreg:
    Additional proofs obtained by the collection service for qualifying and
    correctly registering the vote ``SignedVote`` (:ref:`signed-vote`) created
    by the voter application. The composition of the response depends on the
    specific configuration of the collection service; in this case, standard
    OCSP protocol is used for verifying the validity of the voter's signing
    certificate, and a PKIX timestamp protocol-based registration service is
    used both for fixing the time of voting and for registering the electronic
    vote in an independent external service. Both the OCSP response and the
    PKIX format timestamp with the supplements necessary for the registration
    service are forwarded to the voter application for verification.
:result.TestVote: If the vote was submitted before the start of voting and
                  was counted as a test vote, then ``true``; otherwise this
                  field is not present in the response. The voter application
                  displays a corresponding warning to the voter in the case
                  of a test vote.
:result.VoteID: The vote identifier in the storage service, based on which
                the verification application can later request the vote for
                analysis.

.. literalinclude:: ../../common/examples/id.rpc.vote.response.json
   :language: json
   :linenos:

Possible error messages for the request ``RPC.Vote``.

:BAD_CERTIFICATE: Error with the voter's identity or signing certificate.
:BAD_REQUEST: Invalid request.
:IDENTITY_MISMATCH: The personal identification codes of the identity and
                    signing certificates do not match.
:INELIGIBLE_VOTER: The voter does not have the right to vote.
:INTERNAL_SERVER_ERROR: Internal server error.
:OUTDATED_CHOICES: The voter's district affiliation has changed since
                   obtaining the list.
:UNAUTHENTICATED: Unauthenticated request.
:VOTER_TOO_YOUNG: The voter is too young.
:VOTING_END: The voting period has ended.


Voting with Mobile-ID
------------------------

Using Mobile-ID as a signing and authentication tool requires the use of
a helper service interfacing with the Mobile-ID service (SNI
``mid.ivxv.invalid``) to obtain an authentication token before obtaining
the choices list and for signing the vote before storage.


Obtaining the Authentication Token
**************************

The voter application makes the request ``RPC.Authenticate`` to initiate
Mobile-ID authentication.

:params.OS: Operating system on which the voter application is used.
:params.IDCode: Personal identification code of the Mobile-ID user.
:params.PhoneNo: Phone number of the Mobile-ID user.

.. literalinclude:: ../../common/examples/mid.rpc.authenticate.query.json
   :language: json
   :linenos:

:result.Challenge: Hash from which to compute the Mobile-ID verification code
                   for display in the voter application
:result.SessionCode: Mobile-ID session identifier for subsequent poll requests

.. literalinclude:: ../../common/examples/mid.rpc.authenticate.response.json
   :language: json
   :linenos:

Possible error messages for the request ``RPC.Authenticate``.

:BAD_REQUEST: Invalid request.
:INTERNAL_SERVER_ERROR: Internal server error.
:VOTING_END: The voting period has ended.

The voter application makes the request ``RPC.AuthenticateStatus`` to check
the status of the authentication process.

:params.OS: Operating system on which the voter application is used.
:params.SessionCode: Authentication session identifier

.. literalinclude:: ../../common/examples/mid.rpc.authenticatestatus.query.json
   :language: json
   :linenos:


:result.AuthToken: Authentication token for presenting to other IVXV services,
                   or ``null`` if request processing is still ongoing.
:result.GivenName: The voter's given name upon successful authentication
:result.PersonalCode: The voter's personal identification code upon successful
                      authentication
:result.Status: Request status - ``POLL`` indicates the need to repeat the
                request, ``OK`` indicates successful authentication. Other
                response fields contain information only when the value is
                ``OK``.
:result.Surname: The voter's surname upon successful authentication


.. literalinclude:: ../../common/examples/mid.rpc.authenticatestatus.response.json
   :language: json
   :linenos:

.. literalinclude:: ../../common/examples/mid.rpc.authenticatestatus2.response.json
   :language: json
   :linenos:

Possible error messages for the request ``RPC.AuthenticateStatus``.

:BAD_REQUEST: Invalid request.
:INTERNAL_SERVER_ERROR: Internal server error.
:MID_BAD_CERTIFICATE: Error with the voter's Mobile-ID identity certificate.
:MID_NOT_USER: The phone number does not belong to a Mobile-ID client.
:MID_OPERATOR: Problem with the voter's mobile phone SIM card, which requires
               contacting the mobile operator to resolve.
:MID_ABSENT: The voter's mobile phone is not reachable.
:MID_CANCELED: The voter cancelled the Mobile-ID session.
:MID_EXPIRED: The Mobile-ID session has expired.
:MID_GENERAL: Error in the Mobile-ID service operation.
:VOTING_END: The voting period has ended.


Vote Signing
*********************

The voter application makes the request ``RPC.GetCertificate`` to obtain the
signing certificate.

:params.AuthMethod: Only the authentication method ``ticket`` is supported.
:params.AuthToken: Mobile-ID authentication token.
:params.OS: Operating system on which the voter application is used.
:params.PhoneNo: Phone number of the vote signer

.. literalinclude:: ../../common/examples/mid.rpc.getcertificate.query.json
   :language: json
   :linenos:


:result.Certificate: Signing certificate in X509 format

.. literalinclude:: ../../common/examples/mid.rpc.getcertificate.response.json
   :language: json
   :linenos:

Possible error messages for the request ``RPC.GetCertificate``.

:BAD_REQUEST: Invalid request.
:INTERNAL_SERVER_ERROR: Internal server error.
:MID_BAD_CERTIFICATE: Error with the voter's Mobile-ID signing certificate.
:MID_GENERAL: Error in the Mobile-ID service operation.
:MID_NOT_USER: The phone number does not belong to a Mobile-ID client.
:VOTING_END: The voting period has ended.


The voter application makes the request ``RPC.Sign`` to initiate vote signing.
The voter application computes the Mobile-ID verification code from the value
of the ``Hash`` data field.

:params.AuthMethod: Only the authentication method ``ticket`` is supported.
:params.AuthToken: Mobile-ID authentication token.
:params.Hash: BASE64-encoded hash of the electronic vote
:params.HashType: Name of the hash function for transmission to the Mobile-ID
                  service, either ``SHA256``, ``SHA384``, or ``SHA512``
:params.OS: Operating system on which the voter application is used.
:params.PhoneNo: Phone number of the vote signer

.. literalinclude:: ../../common/examples/mid.rpc.sign.query.json
   :language: json
   :linenos:

:result.SessionCode: Mobile-ID session identifier for subsequent poll requests.

.. literalinclude:: ../../common/examples/mid.rpc.sign.response.json
   :language: json
   :linenos:

Possible error messages for the request ``RPC.Sign``.

:BAD_REQUEST: Invalid request.
:INTERNAL_SERVER_ERROR: Internal server error.
:VOTING_END: The voting period has ended.


The voter application makes the request ``RPC.SignStatus`` to check the
status of the signing process.

:params.OS: Operating system on which the voter application is used.
:params.SessionCode: Mobile-ID session identifier

.. literalinclude:: ../../common/examples/mid.rpc.signstatus.query.json
   :language: json
   :linenos:

:result.Signature: If the response ``Status`` field is ``OK``, a BASE-64
                    encoded PKCS1 format signature; otherwise ``null``.
:result.Algorithm: If the response ``Status`` field is ``OK``, the signature
                   algorithm returned by the Mobile-ID service. Possible values
                   are ``SHA256WithECEncryption``, ``SHA256WithRSAEncryption``,
                   ``SHA384WithECEncryption``, ``SHA384WithRSAEncryption``,
                   ``SHA512WithECEncryption``, and ``SHA512WithRSAEncryption``.
:result.Status: Request status - ``POLL`` indicates the need to repeat the
                request, ``OK`` indicates successful signing. Other response
                fields contain information only when the value is ``OK``.

.. literalinclude:: ../../common/examples/mid.rpc.signstatus.response.json
   :language: json
   :linenos:

.. literalinclude:: ../../common/examples/mid.rpc.signstatus2.response.json
   :language: json
   :linenos:

Possible error messages for the request ``RPC.SignStatus``.

:BAD_REQUEST: Invalid request.
:INTERNAL_SERVER_ERROR: Internal server error.
:MID_ABSENT: The voter's mobile phone is not reachable.
:MID_BAD_CERTIFICATE: Error with the voter's Mobile-ID signing certificate.
:MID_OPERATOR: Problem with the voter's mobile phone SIM card, which requires
               contacting the mobile operator to resolve.
:MID_CANCELED: The voter cancelled the Mobile-ID session.
:MID_EXPIRED: The Mobile-ID session has expired.
:MID_GENERAL: Error in the Mobile-ID service operation.
:VOTING_END: The voting period has ended.


Voting with Smart-ID
------------------------

Using Smart-ID as a signing and authentication tool requires the use of
a helper service interfacing with the Smart-ID service (SNI
``smartid.ivxv.invalid``) to obtain an authentication token before obtaining
the choices list and for signing the vote before storage.


Obtaining the Authentication Token
**************************

The voter application makes the request ``RPC.Challenge`` to obtain the
Smart-ID verification code.

:params.OS: Operating system on which the voter application is used.

.. literalinclude:: ../../common/examples/smartid.rpc.challenge.query.json
   :language: json
   :linenos:

:result.Challenge: Hash from which to compute the Smart-ID verification code
                   for display in the voter application
:result.XSmartIDAuth: Request cookie, storing the hash of the Smart-ID
                      verification code, its lifetime timestamp, and session
                      identifier

.. literalinclude:: ../../common/examples/smartid.rpc.challenge.response.json
   :language: json
   :linenos:

Possible error messages for the request ``RPC.Authenticate``.

:BAD_REQUEST: Invalid request.
:INTERNAL_SERVER_ERROR: Internal server error.
:VOTING_END: The voting period has ended.

The voter application makes the request ``RPC.Authenticate`` to initiate
Smart-ID authentication.

:params.OS: Operating system on which the voter application is used.
:params.XSmartIDAuth: Request cookie, storing the hash of the Smart-ID
                      verification code, its lifetime timestamp, and session
                      identifier
:params.Identifier: Personal identification code of the Smart-ID user.

.. literalinclude:: ../../common/examples/smartid.rpc.authenticate.query.json
   :language: json
   :linenos:

:result.SessionCode: Smart-ID session identifier for subsequent poll requests

.. literalinclude:: ../../common/examples/smartid.rpc.authenticate.response.json
   :language: json
   :linenos:

Possible error messages for the request ``RPC.Authenticate``.

:BAD_REQUEST: Invalid request.
:INTERNAL_SERVER_ERROR: Internal server error.
:VOTING_END: The voting period has ended.

The voter application makes the request ``RPC.AuthenticateStatus`` to check
the status of the authentication process.

:params.OS: Operating system on which the voter application is used.
:params.XSmartIDAuth: Request cookie, storing the hash of the Smart-ID
                      verification code, its lifetime timestamp, and session
                      identifier
:params.SessionCode: Authentication session identifier

.. literalinclude:: ../../common/examples/smartid.rpc.authenticatestatus.query.json
   :language: json
   :linenos:


:result.AuthToken: Authentication token for presenting to other IVXV services,
                   or ``null`` if request processing is still ongoing.
:result.DataToken: The voter's Smart-ID document number, or ``null`` if
                   request processing is still ongoing.
:result.GivenName: The voter's given name upon successful authentication
:result.PersonalCode: The voter's personal identification code upon successful
                      authentication
:result.Status: Request status - ``POLL`` indicates the need to repeat the
                request, ``OK`` indicates successful authentication. Other
                response fields contain information only when the value is
                ``OK``.
:result.Surname: The voter's surname upon successful authentication


.. literalinclude:: ../../common/examples/smartid.rpc.authenticatestatus.response.json
   :language: json
   :linenos:

.. literalinclude:: ../../common/examples/smartid.rpc.authenticatestatus2.response.json
   :language: json
   :linenos:

Possible error messages for the request ``RPC.AuthenticateStatus``.

:BAD_REQUEST: Invalid request.
:INTERNAL_SERVER_ERROR: Internal server error.
:SMARTID_BAD_CERTIFICATE: Error with the voter's Smart-ID identity certificate.
:SMARTID_VERIFICATION: The voter selected the wrong verification code.
:SMARTID_ACCOUNT: Error with the voter's Smart-ID account.
:SMARTID_CANCELED: The voter cancelled the Smart-ID session.
:SMARTID_EXPIRED: The Smart-ID session has expired.
:SMARTID_GENERAL: Error in the Smart-ID service operation.
:VOTING_END: The voting period has ended.


Vote Signing
*********************

The voter application makes the request ``RPC.GetCertificateChoice`` to choose
the signing certificate.

:params.AuthMethod: Only the authentication method ``ticket`` is supported.
:params.AuthToken: Smart-ID authentication token.
:params.DataToken: The voter's Smart-ID document number.
:params.OS: Operating system on which the voter application is used.

.. literalinclude:: ../../common/examples/smartid.rpc.getcertificatechoice.query.json
   :language: json
   :linenos:

:result.SessionCode: Smart-ID session identifier for subsequent poll requests

.. literalinclude:: ../../common/examples/smartid.rpc.getcertificatechoice.response.json
   :language: json
   :linenos:

The voter application makes the request ``RPC.GetCertificateChoiceStatus`` to
check the status of the signing certificate.


:params.OS: Operating system on which the voter application is used.
:params.SessionCode: Authentication session identifier

.. literalinclude:: ../../common/examples/smartid.rpc.getcertificatechoicestatus.query.json
   :language: json
   :linenos:

:result.Certificate: Signing certificate in X509 format
:result.Status: Request status - ``POLL`` indicates the need to repeat the
                request, ``OK`` indicates successful authentication. Other
                response fields contain information only when the value is
                ``OK``.

.. literalinclude:: ../../common/examples/smartid.rpc.getcertificatechoicestatus.response.json
   :language: json
   :linenos:

.. literalinclude:: ../../common/examples/smartid.rpc.getcertificatechoicestatus2.response.json
   :language: json
   :linenos:

Possible error messages for the request ``RPC.GetCertificateChoiceStatus``.

:BAD_REQUEST: Invalid request.
:INTERNAL_SERVER_ERROR: Internal server error.
:SMARTID_BAD_CERTIFICATE: Error with the voter's Smart-ID signing certificate.
:SMARTID_GENERAL: Error in the Smart-ID service operation.
:VOTING_END: The voting period has ended.


The voter application makes the request ``RPC.Sign`` to initiate vote signing.
The voter application computes the Smart-ID verification code from the value
of the ``Hash`` data field.

:params.AuthMethod: Only the authentication method ``ticket`` is supported.
:params.AuthToken: Smart-ID authentication token.
:params.Hash: BASE64-encoded hash of the electronic vote
:params.HashType: Name of the hash function for transmission to the Smart-ID
                  service, either ``SHA256``, ``SHA384``, or ``SHA512``
:params.OS: Operating system on which the voter application is used.
:params.DataToken: The voter's Smart-ID document number.

.. literalinclude:: ../../common/examples/smartid.rpc.sign.query.json
   :language: json
   :linenos:

:result.SessionCode: Smart-ID session identifier for subsequent poll requests.

.. literalinclude:: ../../common/examples/smartid.rpc.sign.response.json
   :language: json
   :linenos:

Possible error messages for the request ``RPC.Sign``.

:BAD_REQUEST: Invalid request.
:INTERNAL_SERVER_ERROR: Internal server error.
:VOTING_END: The voting period has ended.


The voter application makes the request ``RPC.SignStatus`` to check the status
of the signing process.

:params.OS: Operating system on which the voter application is used.
:params.SessionCode: Smart-ID session identifier

.. literalinclude:: ../../common/examples/smartid.rpc.signstatus.query.json
   :language: json
   :linenos:

:result.Signature: If the response ``Status`` field is ``OK``, a BASE-64
                    encoded signature; otherwise ``null``.
:result.Algorithm: If the response ``Status`` field is ``OK``, the signature
                   algorithm returned by the Smart-ID service. Possible values
                   are ``sha256WithRSAEncryption``, ``sha384WithRSAEncryption``,
                   and ``sha512WithRSAEncryption``.
:result.Status: Request status - ``POLL`` indicates the need to repeat the
                request, ``OK`` indicates successful signing. Other response
                fields contain information only when the value is ``OK``.

.. literalinclude:: ../../common/examples/smartid.rpc.signstatus.response.json
   :language: json
   :linenos:

.. literalinclude:: ../../common/examples/smartid.rpc.signstatus2.response.json
   :language: json
   :linenos:

Possible error messages for the request ``RPC.SignStatus``.

:BAD_REQUEST: Invalid request.
:INTERNAL_SERVER_ERROR: Internal server error.
:SMARTID_BAD_CERTIFICATE: Error with the voter's Smart-ID identity certificate.
:SMARTID_VERIFICATION: The voter selected the wrong verification code.
:SMARTID_ACCOUNT: Error with the voter's Smart-ID account.
:SMARTID_CANCELED: The voter cancelled the Smart-ID session.
:SMARTID_EXPIRED: The Smart-ID session has expired.
:SMARTID_GENERAL: Error in the Smart-ID service operation.
:VOTING_END: The voting period has ended.

Voting with Web eID
------------------------

Using Web eID as an authentication tool requires the use of a helper service
interfacing with the Web eID service (SNI ``webeid.ivxv.invalid``) to obtain
an authentication token before obtaining the choices list.


Obtaining the Authentication Token
**************************

The voter application makes the request ``RPC.Challenge`` to initiate Web eID
authentication.

:params.OS: Operating system on which the voter application is used.

.. literalinclude:: ../../common/examples/webeid.rpc.challenge.query.json
   :language: json
   :linenos:

:result.Challenge: Base64 encoded hash, the decoded value of which the voter
                   application must use to create the authentication token
                   signature.
:params.SessionID: Session identifier.
:params.Bearer:    Cookie used by the server to verify the hash.

.. literalinclude:: ../../common/examples/webeid.rpc.challenge.response.json
   :language: json
   :linenos:

Possible error messages for the request ``RPC.Challenge``.

:BAD_REQUEST: Invalid request.
:INTERNAL_SERVER_ERROR: Internal server error.
:VOTING_END: The voting period has ended.

The voter application makes the request ``RPC.Token`` to validate the
authentication token.

:params.OS:        Operating system on which the voter application is used.
:params.SessionID: Session identifier.
:params.Token:     Web eID authentication token.
:params.Bearer:    Cookie used by the server to verify the hash.

.. literalinclude:: ../../common/examples/webeid.rpc.token.query.json
   :language: json
   :linenos:

:result.AuthToken: Authentication token for presenting to other IVXV services
:result.GivenName: The voter's given name upon successful authentication
:result.PersonalCode: The voter's personal identification code upon successful
                      authentication
:result.Status: Request status - ``OK`` indicates successful authentication.
                Other response fields contain information only when the
                value is ``OK``.
:result.Surname: The voter's surname upon successful authentication


.. literalinclude:: ../../common/examples/webeid.rpc.token.response.json
   :language: json
   :linenos:

Possible error messages for the request ``RPC.Token``.

:BAD_REQUEST: Invalid request.
:INTERNAL_SERVER_ERROR: Internal server error.
:BAD_CERTIFICATE: Error with the voter's Web eID identity certificate.
:VOTING_END: The voting period has ended.

Vote Verification
-------------------

The verification application makes the request ``RPC.Verify`` to download the
signed vote and the proofs qualifying the vote from the collection service.

:params.OS: Operating system on which the verification application is used.
:params.VoteID: The vote identifier in the storage service, obtained from the
                voter application via a QR code.

.. literalinclude:: ../../common/examples/ver.rpc.verify.query.json
   :language: json
   :linenos:

:result.Qualification.ocsp:
:result.Qualification.tspreg:
    See the chapter on vote verification

:result.Type: Format of the signed vote. Currently the only supported value
              is ``bdoc``.
:result.Vote: BASE64-encoded vote ``SignedVote`` in the previously defined
              format (:ref:`signed-vote`).
:result.ChoicesList: District-based choices list in JSON format.

.. literalinclude:: ../../common/examples/ver.rpc.verify.response.json
   :language: json
   :linenos:

Possible error messages for the request ``RPC.Verify``.

:BAD_REQUEST: Invalid request.
:INTERNAL_SERVER_ERROR: Internal server error.
:VOTING_END: The voting period has ended.


E-Voting Running List
------------------------------

The helper service interfacing with the X-Road service (xroad-service) (SNI
``votesorder.ivxv.invalid``) is used to transmit information to the X-Road
security server.


Last Sequence Number
*******************
The X-Road service (xroad-service) makes the request ``RPC.VotesSeqNo`` to
obtain the last sequence number.

.. literalinclude:: ../../common/examples/votesorder.rpc.votesseqno.query.json
   :language: json
   :linenos:

:result.SeqNo:
    Last sequence number.

.. literalinclude:: ../../common/examples/votesorder.rpc.votesseqno.response.json
   :language: json
   :linenos:

Possible error messages for the request ``RPC.VotesSeqNo``.

:INTERNAL_SERVER_ERROR: Internal server error.
:VOTING_END: The voting period has ended.

E-Voting Batch
*******************
The X-Road service (xroad-service) makes the request ``RPC.Votes`` to obtain
the e-voting batch.

:params.VotesFrom: E-votes starting from this sequence number.
:params.BatchMaxSize: Size of the e-voting batch.

.. literalinclude:: ../../common/examples/votesorder.rpc.votes.query.json
   :language: json
   :linenos:

:result.batchRecords:
         List of e-votes
:result.batchRecords.seqNo:
         Vote sequence number
:result.batchRecords.idCode:
         Voter's personal identification code
:result.batchRecords.voterName:
         Voter's name
:result.batchRecords.kovCode:
         Local government EHAK code
:result.batchRecords.electoralDistrictNo:
         Electoral district number

.. literalinclude:: ../../common/examples/votesorder.rpc.votes.response.json
   :language: json
   :linenos:

Possible error messages for the request ``RPC.Votes``.

:BAD_REQUEST: Invalid request.
:INTERNAL_SERVER_ERROR: Internal server error.
:VOTING_END: The voting period has ended.
