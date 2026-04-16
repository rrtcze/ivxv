..  IVXV protocols

================================================================================
Verification of an Electronic Vote Individually and as Part of the E-Ballot Box
================================================================================

An electronic vote is verified in the processing application, the collection
service, the voter application, and the verification application.

The most thorough verification of an electronic vote takes place as part of the
e-ballot box in the processing application, where the decision is made whether
to send a specific vote for counting or not. During these checks, the e-vote is
examined both individually and in relation to all other votes cast by the same
voter. Additionally, the e-ballot box is compared with the registration service
extract.

For each individual vote, a verification at a level analogous to the processing
application is performed in the voter application, where it is ensured that the
collection service has qualified the vote such that the checks performed in the
processing application will succeed. The verification application performs checks
equivalent to those of the voter application.

The collection service is additionally responsible for obtaining several
elements necessary for the final qualification of the vote and also performs
checks after obtaining them.


Components of the Final Electronic Vote
----------------------------------------

Elements available at the time of deciding whether a vote qualifies for
counting or not:

   #. the container containing the electronic vote - :ref:`entity-haale-konteiner`;

      #. the encrypted ballot - :ref:`entity-krypteeritud-sedel`;

      #. the voter's signature on the encrypted ballot - :ref:`entity-haale-signatuur`;

      #. the voter's digital signature on the encrypted ballot - :ref:`entity-haale-allkiri`;

      #. the voter's signing certificate - :ref:`entity-valija-sertifikaat`;

      #. the voter's personal identification code - :ref:`entity-valija-identiteet`;

   #. qualifying element - validity confirmation of the voter's certificate -
      :ref:`entity-kehtivuskinnitus`;

   #. qualifying element - timestamp on the signed encrypted ballot -
      :ref:`entity-ajatempel`;

   #. qualifying element - registration request container
      :ref:`entity-registreerimisparing-konteiner`;

      #. qualifying element - registration request for the signed encrypted
         ballot - :ref:`entity-registreerimisparing`;

   #. qualifying element - registration proof for the signed encrypted
      ballot - :ref:`entity-registreerimistoend`;

   #. proof of the voter's district affiliation at the time of voting -
      :ref:`entity-nimekirjatunnus`.


Elements available at the time of deciding how to count a vote:

   #. mixed encrypted ballot - :ref:`entity-miksitud-krypteeritud-sedel`;

   #. the voter's plaintext expression of will - :ref:`entity-tahteavaldus`;

   #. district affiliation identifier - :ref:`entity-ringkonnatunnus`;

   #. district-based choices list - :ref:`entity-ringkonna-valikutenimekiri`.


Additional elements:

   #. randomness used during encryption - :ref:`entity-juhuslikkus`; -
      created in the voter application during vote encryption and mediated
      only to the verification application.


.. _entity-tahteavaldus:

````````````````````
EXPRESSION OF WILL
````````````````````

The entity is created in the voter application and identified in the key
application. It is a byte sequence in UTF-8 encoding in EHS-specific format.

.. _check-tahteavaldus-correctness:

EXPRESSION OF WILL, format correctness
`````````````````````````````````````

Verification of the format correctness of the expression of will against this
specification.


.. _check-tahteavaldus-ringkonnatunnus-valikutenimekiri-consistency:

EXPRESSION OF WILL, DISTRICT IDENTIFIER, DISTRICT CHOICES LIST, consistency
```````````````````````````````````````````````````````````````````````````

Verification of the choice contained in the expression of will against the
district identifier and the choices list. The check succeeds if the identified
choice is available in the given district.

.. _check-tahteavaldus-ringkonna-valikutenimekiri-consistency:

EXPRESSION OF WILL, DISTRICT CHOICES LIST, consistency
```````````````````````````````````````````````````````

Verification of the choice contained in the expression of will against the
district-based choices list. The check succeeds if the identified choice is
available in the given district.


.. _entity-juhuslikkus:

```````````
RANDOMNESS
```````````

The entity is created in the voter application and also used in the verification
application. The entity is presented as a byte sequence in EHS-specific format
and must be compatible with the mathematical group determined by the public key
parameters.

.. _check-juhuslikkus-correctness:

RANDOMNESS, format correctness
````````````````````````````````

Verification of the format correctness of the randomness against this
specification.

.. _check-juhuslikkus-public-key-consistency:

RANDOMNESS, consistency with the public key
``````````````````````````````````````````

Verification of the consistency of the randomness with the public key. The
check succeeds if the randomness can be used as a scalar for computations
in the mathematical group determined by the public key parameters.

.. _entity-krypteeritud-sedel:

``````````````````
ENCRYPTED BALLOT
``````````````````

The entity is created in the voter application. It is a DER-encoded data
structure in EHS-specific format, whose verification is based on the EHS
public key, which among other things defines the mathematical group used
for encryption.

.. _check-krypteeritud-sedel-correctness:

ENCRYPTED BALLOT, format correctness
```````````````````````````````````

Verification of the format correctness of the encrypted ballot against this
specification.


.. _check-krypteeritud-sedel-public-key-consistency:

ENCRYPTED BALLOT, consistency with the public key
`````````````````````````````````````````````````

Verification of the consistency of the encrypted ballot with the public key.
The check succeeds if the components of the encrypted ballot can be used as
group members for computations in the mathematical group determined by the
public key parameters.

.. _check-krypteeritud-sedel-juhuslikkus-consistency:

ENCRYPTED BALLOT, RANDOMNESS, consistency
``````````````````````````````````````````

Verification of the consistency of the encrypted ballot with the randomness
based on the group parameters. The check succeeds if it can be shown that the
given randomness was used to compute the `uBlind` component of the encrypted
ballot according to the given group parameters.


.. _entity-valija-sertifikaat:

``````````````````
VOTER CERTIFICATE
``````````````````

The entity is assigned to the voter externally. It is a certificate in X.509
format, whose validity verification is based on root certificates and the
validity confirmation service provider belonging to the same public key
infrastructure.

.. _check-valija-sertifikaat-correctness:

VOTER CERTIFICATE, format correctness
```````````````````````````````````

Verification of the format correctness of the voter's certificate based on
the X.509 specification.

.. _check-valija-sertifikaat-consistency-protocol-settings:

VOTER CERTIFICATE, protocol-compliant consistency with election configuration
`````````````````````````````````````````````````````````````````````````

Verification of the protocol-compliant consistency of the voter's certificate
with the election configuration. The check succeeds if:

   #. The voter's certificate is valid based on the validity period contained
      in the certificate;

   #. The voter's certificate belongs to one of the certification hierarchies
      described in the election configuration.


.. _check-valija-sertifikaat-kehtivuskinnitus-consistency:

VOTER CERTIFICATE, VALIDITY CONFIRMATION, protocol-compliant consistency with election configuration
```````````````````````````````````````````````````````````````````````````````````````````````

Verification of the protocol-compliant consistency of the voter's certificate
and the validity confirmation with the election configuration. The check
succeeds if:

   #. The validity confirmation is correctly signed by a validity confirmation
      service provider that has the authority under the configuration to confirm
      the validity of the voter's certificate;

   #. The validity confirmation has been issued for the voter's certificate;

   #. The validity confirmation shows the OCSP status of the voter's
      certificate as 'Valid'.


.. _entity-valija-identiteet:

`````````````````
VOTER IDENTITY
`````````````````

The entity is assigned to the voter externally. It is a personal identification
code, whose verification is based on the VOTER CERTIFICATE.

.. _check-valija-identiteet-correctness:

VOTER IDENTITY, format correctness
``````````````````````````````````

Verification of the format correctness of the voter's identity based on the
Republic of Estonia personal identification code format.

.. _check-valija-identiteet-nimekirjatunnus-eligibility:

VOTER IDENTITY, LIST IDENTIFIER, voting right
``````````````````````````````````````````````

Verification of voting rights based on the voter's identity and the list
identifier. The check succeeds if the voter's identity is entered in the
voter list corresponding to the list identifier. In that case, a district
identifier is also assigned to the identity, which determines the
district-specific choices list.

.. _entity-haale-signatuur:

```````````````
VOTE SIGNATURE
```````````````

The entity is computed by the signing tool based on the hash of the ENCRYPTED
BALLOT provided as input by the voter application.

.. _check-haale-signatuur-correctness:

VOTE SIGNATURE, format correctness
````````````````````````````````````

Verification of the format correctness of the vote signature based on the
specific signing method.

.. _check-haale-signatuur-krypteeritud-sedel-valija-sertifikaat-consistency:

VOTE SIGNATURE, ENCRYPTED BALLOT, VOTER CERTIFICATE, consistency
``````````````````````````````````````````````````````````````````````

A check that succeeds if and only if it can be verified that the vote signature
was computed from the hash of the encrypted ballot using the private key
corresponding to the public key found in the voter's certificate.

.. _entity-haale-allkiri:

`````````````
VOTE DIGITAL SIGNATURE
`````````````

The entity is created in the voter application, placing the vote signature
into the signature format.

.. _check-haale-allkiri-correctness:

VOTE DIGITAL SIGNATURE, format correctness
``````````````````````````````````````````

Verification of the format correctness of the vote digital signature against
this specification.

.. _check-haale-allkiri-haale-signatuur-consistency:

VOTE DIGITAL SIGNATURE, VOTE SIGNATURE, consistency
`````````````````````````````````````````````````

Verification of the consistency of the vote digital signature and the vote
signature. The check succeeds if the given digital signature contains the
given signature.

.. _entity-haale-konteiner:

```````````````
VOTE CONTAINER
```````````````

The entity is created in the voter application by creating a format-compliant
container that contains, among other things, the encrypted ballot, the vote
digital signature, and the voter's certificate.

.. _check-haale-konteiner-correctness:

VOTE CONTAINER, format correctness
````````````````````````````````````

Verification of the format correctness of the vote container against this
specification.

.. _check-haale-konteiner-haale-allkiri-valija-sertifikaat-krypteeritud-sedel-consistency:

VOTE CONTAINER, VOTE DIGITAL SIGNATURE, VOTER CERTIFICATE, ENCRYPTED BALLOT, consistency
`````````````````````````````````````````````````````````````````````````````````````

Verification of the consistency of the vote container, vote digital signature,
voter certificate, and encrypted ballot. The check succeeds if the given
container contains the specific vote digital signature, voter certificate,
and encrypted ballot.

.. _entity-kehtivuskinnitus:

````````````````
VALIDITY CONFIRMATION
````````````````

The collection service is responsible for obtaining the entity. It is a
confirmation of the status of the voter's certificate in OCSP format.

.. _check-kehtivuskinnitus-correctness:

VALIDITY CONFIRMATION, format correctness
`````````````````````````````````````

Verification of the format correctness of the validity confirmation against
the OCSP specification.


.. _check-kehtivuskinnitus-ajatempel-order:

VALIDITY CONFIRMATION, TIMESTAMP, temporal order
``````````````````````````````````````````````

Verification of the temporal order of the validity confirmation and the
timestamp. The check succeeds if:

   #. the timestamp was not issued later than the validity confirmation;

   #. the time difference between the issuance of the timestamp and the
      validity confirmation is less than the time specified in the election
      configuration.


.. _entity-ajatempel:

`````````
TIMESTAMP
`````````

The collection service is responsible for obtaining the entity. It is a
timestamp in PKIX format.

.. _check-ajatempel-correctness:

TIMESTAMP, format correctness
``````````````````````````````

Verification of the format correctness of the timestamp against the PKIX
specification.


.. _check-ajatempel-consistency-protocol-settings:

TIMESTAMP, VOTE DIGITAL SIGNATURE, protocol-compliant consistency with election configuration
```````````````````````````````````````````````````````````````````````````````

Verification of the protocol-compliant consistency of the timestamp with the
election configuration. The check succeeds if:

   #. the timestamp is correctly signed by a timestamp service provider
      authorized in the election configuration;

   #. the timestamp was taken on the vote digital signature.

.. _entity-registreerimisparing:

````````````````````
REGISTRATION REQUEST
````````````````````

The entity is created in the collection service. The registration service
provider is responsible for storing the entity.

.. _check-registreerimisparing-correctness:

REGISTRATION REQUEST, format correctness
`````````````````````````````````````````

Verification of the format correctness of the registration request against
this specification.


.. _check-registreerimisparing-haale-allkiri-consistency:

REGISTRATION REQUEST, VOTE DIGITAL SIGNATURE, protocol-compliant consistency with election configuration
``````````````````````````````````````````````````````````````````````````````````````````````````````

Verification of the protocol-compliant consistency of the registration request
and the vote digital signature with the election configuration. The check
succeeds if:

   #. The registration request is composed for the vote digital signature;

   #. The registration request is correctly signed by the collection service
      referenced in the election configuration.


.. _check-registreerimisparing-registreerimistoend-consistency:

REGISTRATION REQUEST, REGISTRATION PROOF, consistency
```````````````````````````````````````````````````````````````````````

Verification of the protocol-compliant consistency of the registration request
and the registration proof with the election configuration. The check succeeds
if:

   #. The registration request is correctly signed by the collection service
      referenced in the election configuration.

   #. The registration proof is composed in response to the same registration
      request;

   #. The registration proof is correctly signed by the registration service
      referenced in the election configuration.


.. _entity-registreerimisparing-konteiner:

```````````````````````````````
REGISTRATION REQUEST CONTAINER
```````````````````````````````

The entity is created in the collection service. The registration service
provider is responsible for storing the entity.

.. _check-registreerimisparing-konteiner-correctness:

REGISTRATION REQUEST CONTAINER, format correctness
````````````````````````````````````````````````````

Verification of the format correctness of the registration request container
against this specification.


.. _check-registreerimisparing-konteiner-registreerimispäring-consistency:

REGISTRATION REQUEST CONTAINER, REGISTRATION REQUEST, protocol-compliant consistency with election configuration
````````````````````````````````````````````````````````````````````````````````````````````````````````````````

Verification of the protocol-compliant consistency of the registration request
container and the registration request with the election configuration. The
check succeeds if:

   #. The registration request container contains the registration request;

   #. The registration request is correctly signed by the collection service
      referenced in the election configuration.


.. _entity-registreerimistoend:

```````````````````
REGISTRATION PROOF
```````````````````

The collection service is responsible for obtaining the entity; the entity
is created by the registration service provider.

.. _check-registreerimistoend-correctness:

REGISTRATION PROOF, format correctness
````````````````````````````````````````

Verification of the format correctness of the registration proof against
this specification.


.. _check-registreerimistoend-haale-allkiri-consistency:

REGISTRATION PROOF, VOTE DIGITAL SIGNATURE, protocol-compliant consistency with election configuration
`````````````````````````````````````````````````````````````````````````````````````````

Verification of the protocol-compliant consistency of the registration proof
and the vote digital signature with the election configuration. The check
succeeds if:

   #. The registration proof is composed for the vote digital signature;

   #. The registration proof contains a registration request correctly signed
      by the collection service;

   #. The registration proof is correctly signed by the registration service
      referenced in the election configuration.


.. _entity-nimekirjatunnus:

```````````````
LIST IDENTIFIER
```````````````

The entity is created in the collection service and identifies one specific
version of the voter list.

.. _check-nimekirjatunnus-correctness:

LIST IDENTIFIER, format correctness
````````````````````````````````````

Verification of the format correctness of the list identifier against this
specification.

.. _check-nimekirjatunnus-consistency-protocol-settings:

LIST IDENTIFIER, protocol-compliant consistency with election configuration
`````````````````````````````````````````````````````````````````````

Verification of the protocol-compliant consistency of the list identifier
with the election configuration. The check succeeds if, based on the
amendment lists contained in the election configuration, it is possible to
compose the list corresponding to the list identifier.


.. _entity-miksitud-krypteeritud-sedel:

```````````````````````````
MIXED ENCRYPTED BALLOT
```````````````````````````

The entity is created in the mixing application. A mixed encrypted ballot is
essentially an encrypted ballot and the same checks apply as for an encrypted
ballot.

.. _check-miksitud-krypteeritud-sedel-correctness:

MIXED ENCRYPTED BALLOT, format correctness
````````````````````````````````````````````

Verification of the format correctness of the mixed encrypted ballot against
this specification.

.. _check-miksitud-krypteeritud-sedel-public-key-consistency:

MIXED ENCRYPTED BALLOT, consistency with the public key
``````````````````````````````````````````````````````

Verification of the consistency of the mixed encrypted ballot with the public
key. The check succeeds if the components of the mixed encrypted ballot can be
used as group members for computations in the mathematical group determined by
the public key parameters.


.. _entity-ringkonnatunnus:

```````````````
DISTRICT IDENTIFIER
```````````````

The entity is created in the processing application and refers to the
district-based choices list.

.. _check-ringkonnatunnus-correctness:

DISTRICT IDENTIFIER, format correctness
````````````````````````````````````

Verification of the format correctness of the district identifier against
this specification.

.. _entity-ringkonna-valikutenimekiri:

`````````````````````````````````
DISTRICT-BASED CHOICES LIST
`````````````````````````````````

The entity is assigned to the voter externally.

.. _check-ringkonna-valikutenimekiri-correctness:

DISTRICT-BASED CHOICES LIST, format correctness
``````````````````````````````````````````````````

Verification of the format correctness of the district-based choices list
against the VIS interface specification.

Checks in the Collection Service
--------------------------

The collection service handles each vote to be stored independently of other
votes. The task of the collection service is to store the vote throughout the
entire voting period and to obtain the elements necessary for the vote to
qualify during processing.

The collection service receives the following entities from the voter application:

   #. :ref:`entity-krypteeritud-sedel`

   #. :ref:`entity-valija-sertifikaat`

   #. :ref:`entity-valija-identiteet`

   #. :ref:`entity-haale-signatuur`

   #. :ref:`entity-haale-allkiri`

   #. :ref:`entity-haale-konteiner`

The collection service obtains the following entities from external services
during vote processing:

   #. :ref:`entity-kehtivuskinnitus`

   #. :ref:`entity-ajatempel`

   #. :ref:`entity-registreerimistoend`

The collection service identifies / creates the following entities itself:

   #. :ref:`entity-registreerimisparing`

   #. :ref:`entity-registreerimisparing-konteiner`

   #. :ref:`entity-nimekirjatunnus`

   #. :ref:`entity-ringkonnatunnus`

   #. :ref:`entity-ringkonna-valikutenimekiri`

The collection service does not directly interact with the following entities:

   #. :ref:`entity-tahteavaldus`

   #. :ref:`entity-juhuslikkus`

   #. :ref:`entity-miksitud-krypteeritud-sedel`

The collection service performs the following activities and checks:

   #. Receiving the vote storage request from the voter application

      #. :ref:`check-valija-sertifikaat-correctness`
      #. :ref:`check-valija-sertifikaat-consistency-protocol-settings`
      #. :ref:`check-valija-identiteet-correctness`
      #. :ref:`check-valija-identiteet-nimekirjatunnus-eligibility`
      #. :ref:`check-haale-signatuur-correctness`
      #. :ref:`check-haale-signatuur-krypteeritud-sedel-valija-sertifikaat-consistency`
      #. :ref:`check-haale-allkiri-correctness`
      #. :ref:`check-haale-allkiri-haale-signatuur-consistency`
      #. :ref:`check-haale-konteiner-correctness`
      #. :ref:`check-haale-konteiner-haale-allkiri-valija-sertifikaat-krypteeritud-sedel-consistency`
      #. :ref:`check-krypteeritud-sedel-correctness`
      #. :ref:`check-krypteeritud-sedel-public-key-consistency`

   #. Obtaining the validity confirmation - :ref:`entity-kehtivuskinnitus`

      #. :ref:`check-kehtivuskinnitus-correctness`
      #. :ref:`check-valija-sertifikaat-kehtivuskinnitus-consistency`

   #. Obtaining the timestamp - :ref:`entity-ajatempel`

      #. :ref:`check-ajatempel-correctness`
      #. :ref:`check-ajatempel-consistency-protocol-settings`

   #. Creating the registration request - :ref:`entity-registreerimisparing`

   #. Obtaining the registration proof - :ref:`entity-registreerimistoend`

      #. :ref:`check-registreerimisparing-registreerimistoend-consistency`
      #. :ref:`check-registreerimistoend-correctness`
      #. :ref:`check-registreerimistoend-haale-allkiri-consistency`
      #. :ref:`check-kehtivuskinnitus-ajatempel-order`

   #. Storing the vote, returning the qualifying elements and a unique
      identifier to the voter application.

Checks in the Voter Application
---------------------------

The voter application creates the encrypted ballot based on the voter's
plaintext expression of will and signs it using the voter's signing tool.

The role of the voter application after signing the vote is to ensure that the
collection service behaved in accordance with the protocol when obtaining the
vote-qualifying elements and that the vote is stored such that it can be taken
into account by the processing application.

The voter application performs at minimum the following checks:

#. The collection service obtained the validity confirmation for the voter's
   certificate from an authorized validity confirmation service. The voter
   application verifies the signature on the validity confirmation service
   response.

#. The collection service registered the vote signed by the voter in an
   authorized registration service. The voter application verifies that the
   request composed by the collection service was signed by the collection
   service and correctly referenced the signed vote. The voter application
   verifies that the registration service response is signed by the correct
   registration service provider and contains the request signed by the
   collection service.

If the verification of elements necessary for qualifying the vote does not
succeed, the voter application informs the user.

The voter application creates the following entities itself:

   #. :ref:`entity-tahteavaldus`

   #. :ref:`entity-juhuslikkus`

   #. :ref:`entity-krypteeritud-sedel`

   #. :ref:`entity-haale-allkiri`

   #. :ref:`entity-haale-konteiner`

The voter application receives the following entities from other parties:

   #. :ref:`entity-valija-sertifikaat`

   #. :ref:`entity-valija-identiteet`

   #. :ref:`entity-ringkonna-valikutenimekiri`

   #. :ref:`entity-haale-signatuur`

   #. :ref:`entity-kehtivuskinnitus`

   #. :ref:`entity-ajatempel`

   #. :ref:`entity-registreerimistoend`

   #. :ref:`entity-registreerimisparing`

The voter application does not directly interact with the following entities:

   #. :ref:`entity-registreerimisparing-konteiner`

   #. :ref:`entity-nimekirjatunnus`

   #. :ref:`entity-ringkonnatunnus`

   #. :ref:`entity-miksitud-krypteeritud-sedel`

The voter application performs the following activities and checks:

   #. activating the eID tool and identifying the voter

      #. :ref:`entity-valija-sertifikaat`
      #. :ref:`entity-valija-identiteet`

      #. :ref:`check-valija-sertifikaat-correctness`
      #. :ref:`check-valija-sertifikaat-consistency-protocol-settings`
      #. :ref:`check-valija-identiteet-correctness`

   #. Identifying the district-based choices list -
      :ref:`entity-ringkonna-valikutenimekiri`

   #. Creating the expression of will - :ref:`entity-tahteavaldus`

   #. Generating the random number - :ref:`entity-juhuslikkus`

   #. Encrypting the ballot - :ref:`entity-krypteeritud-sedel`

   #. Signing the encrypted ballot - :ref:`entity-haale-signatuur`

   #. Creating the digital signature from the signature - :ref:`entity-haale-allkiri`

      #. :ref:`check-haale-signatuur-correctness`
      #. :ref:`check-haale-signatuur-krypteeritud-sedel-valija-sertifikaat-consistency`

   #. Creating the signed container - :ref:`entity-haale-konteiner`

   #. Transmitting the signed container to the collection service.

   #. Verifying the collection service response

      #. :ref:`entity-kehtivuskinnitus`
      #. :ref:`entity-ajatempel`
      #. :ref:`entity-registreerimistoend`
      #. :ref:`entity-registreerimisparing`

      #. :ref:`check-kehtivuskinnitus-correctness`
      #. :ref:`check-valija-sertifikaat-kehtivuskinnitus-consistency`
      #. :ref:`check-ajatempel-correctness`
      #. :ref:`check-ajatempel-consistency-protocol-settings`
      #. :ref:`check-kehtivuskinnitus-ajatempel-order`

      #. :ref:`check-registreerimisparing-correctness`
      #. :ref:`check-registreerimisparing-haale-allkiri-consistency`
      #. :ref:`check-registreerimisparing-registreerimistoend-consistency`
      #. :ref:`check-registreerimistoend-correctness`
      #. :ref:`check-registreerimistoend-haale-allkiri-consistency`

Checks in the Verification Application
-----------------------------

Similarly to the voter application, the role of the verification application
after the vote has been signed is to ensure that the collection service
behaved in accordance with the protocol when obtaining the vote-qualifying
elements and that the vote is stored such that it can be taken into account
by the processing application.

Additionally, the task of the verification application is to provide the voter
with feedback on whether their expression of will was correctly formalized as
a vote by the voter application.

If the verification of elements necessary for qualifying the vote does not
succeed, the verification application informs the user. The voter must verify
the correctness of the expression of will themselves.

The verification application identifies the following entities itself:

   #. :ref:`entity-tahteavaldus`

The verification application receives the following entities from other parties:

   #. :ref:`entity-juhuslikkus`

   #. :ref:`entity-krypteeritud-sedel`

   #. :ref:`entity-valija-sertifikaat`

   #. :ref:`entity-valija-identiteet`

   #. :ref:`entity-haale-signatuur`

   #. :ref:`entity-haale-allkiri`

   #. :ref:`entity-haale-konteiner`

   #. :ref:`entity-kehtivuskinnitus`

   #. :ref:`entity-ajatempel`

   #. :ref:`entity-registreerimistoend`

   #. :ref:`entity-registreerimisparing`

   #. :ref:`entity-ringkonna-valikutenimekiri`

The verification application does not directly interact with the following entities:

   #. :ref:`entity-registreerimisparing-konteiner`

   #. :ref:`entity-nimekirjatunnus`

   #. :ref:`entity-ringkonnatunnus`

   #. :ref:`entity-miksitud-krypteeritud-sedel`

The verification application performs the following activities and checks:

   #. :ref:`check-valija-sertifikaat-correctness`
   #. :ref:`check-valija-sertifikaat-consistency-protocol-settings`
   #. :ref:`check-valija-sertifikaat-kehtivuskinnitus-consistency`
   #. :ref:`check-valija-identiteet-correctness`
   #. :ref:`check-haale-signatuur-correctness`
   #. :ref:`check-haale-signatuur-krypteeritud-sedel-valija-sertifikaat-consistency`
   #. :ref:`check-haale-allkiri-correctness`
   #. :ref:`check-haale-allkiri-haale-signatuur-consistency`
   #. :ref:`check-haale-konteiner-correctness`
   #. :ref:`check-haale-konteiner-haale-allkiri-valija-sertifikaat-krypteeritud-sedel-consistency`
   #. :ref:`check-kehtivuskinnitus-correctness`
   #. :ref:`check-ajatempel-correctness`
   #. :ref:`check-ajatempel-consistency-protocol-settings`
   #. :ref:`check-kehtivuskinnitus-ajatempel-order`
   #. :ref:`check-registreerimisparing-correctness`
   #. :ref:`check-registreerimisparing-haale-allkiri-consistency`
   #. :ref:`check-registreerimisparing-registreerimistoend-consistency`
   #. :ref:`check-registreerimistoend-correctness`
   #. :ref:`check-registreerimistoend-haale-allkiri-consistency`
   #. :ref:`check-ringkonna-valikutenimekiri-correctness`
   #. :ref:`check-juhuslikkus-correctness`
   #. :ref:`check-juhuslikkus-public-key-consistency`
   #. :ref:`check-krypteeritud-sedel-correctness`
   #. :ref:`check-krypteeritud-sedel-public-key-consistency`
   #. :ref:`check-krypteeritud-sedel-juhuslikkus-consistency`
   #. :ref:`check-tahteavaldus-correctness`
   #. :ref:`check-tahteavaldus-ringkonna-valikutenimekiri-consistency`

Checks in the Processing Application
------------------------------

The input of the processing application is the e-ballot box and the
registration service extract of registration requests. The processing
application first checks the elements of both data sets individually and then
attempts to establish a correspondence between them.

The processing application decides which of the voter's votes was the last one
and proceeds to the next processing stage. I.e., one of the vote-qualifying
elements fulfills the role of fixing the vote storage time, and based on this
element, the temporal order of individual votes is established. Depending on the
IVXV profile, this element may be part of the validity confirmation (BDOC-TM),
a separate timestamp (BDOC-TS), or part of the registration proof (BDOC-TS).

The following entities are made available to the processing application:

   #. :ref:`entity-krypteeritud-sedel`

   #. :ref:`entity-valija-sertifikaat`

   #. :ref:`entity-valija-identiteet`

   #. :ref:`entity-haale-signatuur`

   #. :ref:`entity-haale-allkiri`

   #. :ref:`entity-haale-konteiner`

   #. :ref:`entity-kehtivuskinnitus`

   #. :ref:`entity-ajatempel`

   #. :ref:`entity-registreerimisparing`

   #. :ref:`entity-registreerimisparing-konteiner`

   #. :ref:`entity-registreerimistoend`

   #. :ref:`entity-nimekirjatunnus`

   #. :ref:`entity-ringkonna-valikutenimekiri`

The processing application identifies/creates the following entities:

   #. :ref:`entity-ringkonnatunnus`


The processing application does not directly interact with the following entities:

   #. :ref:`entity-miksitud-krypteeritud-sedel`

   #. :ref:`entity-tahteavaldus`

   #. :ref:`entity-juhuslikkus`

The work of the processing application is divided into four stages:

   #. Verification

   #. Removal of repeated votes

   #. Revocation/restoration

   #. Anonymization


The processing application performs the following checks in the verification stage:

   #. e-ballot box element checks are performed for all vote elements:

      #. :ref:`check-valija-sertifikaat-correctness`
      #. :ref:`check-valija-sertifikaat-consistency-protocol-settings`
      #. :ref:`check-valija-identiteet-correctness`
      #. :ref:`check-nimekirjatunnus-correctness`
      #. :ref:`check-nimekirjatunnus-consistency-protocol-settings`
      #. :ref:`check-valija-identiteet-nimekirjatunnus-eligibility`
      #. :ref:`check-ringkonnatunnus-correctness`
      #. :ref:`check-haale-signatuur-correctness`
      #. :ref:`check-haale-signatuur-krypteeritud-sedel-valija-sertifikaat-consistency`
      #. :ref:`check-haale-allkiri-correctness`
      #. :ref:`check-haale-allkiri-haale-signatuur-consistency`
      #. :ref:`check-haale-konteiner-correctness`
      #. :ref:`check-haale-konteiner-haale-allkiri-valija-sertifikaat-krypteeritud-sedel-consistency`
      #. :ref:`check-kehtivuskinnitus-correctness`
      #. :ref:`check-valija-sertifikaat-kehtivuskinnitus-consistency`
      #. :ref:`check-ajatempel-correctness`
      #. :ref:`check-ajatempel-consistency-protocol-settings`
      #. :ref:`check-kehtivuskinnitus-ajatempel-order`
      #. :ref:`check-registreerimistoend-correctness`
      #. :ref:`check-registreerimistoend-haale-allkiri-consistency`

   #. registration service extract checks are performed for each
      registration request

      #. :ref:`check-registreerimisparing-correctness`
      #. :ref:`check-registreerimisparing-konteiner-correctness`
      #. :ref:`check-registreerimisparing-konteiner-registreerimispäring-consistency`

   #. The processing application establishes a correspondence between the
      e-ballot box and the registration service extract, taking as a basis the
      entity :ref:`entity-registreerimisparing-konteiner` from the registration
      service extract and the entity :ref:`entity-registreerimistoend` from the
      e-ballot box. The connecting link between the two views is the
      :ref:`entity-registreerimisparing`.

   #. e-ballot box and registration service extract correspondence checks

      #. :ref:`check-registreerimisparing-haale-allkiri-consistency`
      #. :ref:`check-registreerimisparing-registreerimistoend-consistency`

The processing application performs the following checks in the repeated vote
removal stage:

   #. The processing application identifies the temporally last vote among
      each voter's votes.

   #. The processing application performs the encrypted ballot correctness
      checks.

      #. :ref:`check-krypteeritud-sedel-correctness`
      #. :ref:`check-krypteeritud-sedel-public-key-consistency`


No additional checks are performed in the subsequent stages of the processing
application. In the revocation/restoration stage, votes corresponding to
personal identification codes are removed/restored from/to the e-ballot box
purged of repeated votes. In the anonymization stage, qualifying elements are
removed from the e-votes, and the resulting list of encrypted ballots is
forwarded to the mixing application.

Checks in the Mixing Application
-----------------------------

The following entities are made available to the mixing application:

   #. :ref:`entity-krypteeritud-sedel`

   #. :ref:`entity-ringkonnatunnus`

The mixing application creates the following entities:

   #. :ref:`entity-miksitud-krypteeritud-sedel`

The mixing application does not directly interact with the following entities:

   #. :ref:`entity-tahteavaldus`

   #. :ref:`entity-juhuslikkus`

   #. :ref:`entity-valija-sertifikaat`

   #. :ref:`entity-valija-identiteet`

   #. :ref:`entity-haale-signatuur`

   #. :ref:`entity-haale-allkiri`

   #. :ref:`entity-haale-konteiner`

   #. :ref:`entity-kehtivuskinnitus`

   #. :ref:`entity-ajatempel`

   #. :ref:`entity-registreerimisparing`

   #. :ref:`entity-registreerimisparing-konteiner`

   #. :ref:`entity-registreerimistoend`

   #. :ref:`entity-nimekirjatunnus`

   #. :ref:`entity-ringkonna-valikutenimekiri`


The mixing application performs the following activities and checks:

   #. :ref:`check-ringkonnatunnus-correctness`
   #. :ref:`check-krypteeritud-sedel-correctness`
   #. :ref:`check-krypteeritud-sedel-public-key-consistency`

   #. The mixing application groups the input encrypted ballots by district
      identifiers and shuffles the encrypted ballots within each district.

   #. The mixing application computes a new mixed encrypted ballot for each
      reshuffled encrypted ballot.

   #. The mixing application composes zero-knowledge proofs for the correct
      mixing of the ballots.

Checks in the Key Application
--------------------------

The following entities are made available to the key application:

   #. :ref:`entity-miksitud-krypteeritud-sedel`

   #. :ref:`entity-ringkonnatunnus`

   #. :ref:`entity-ringkonna-valikutenimekiri`

The key application identifies the following entities:

   #. :ref:`entity-tahteavaldus`

The key application does not directly interact with the following entities:

   #. :ref:`entity-juhuslikkus`

   #. :ref:`entity-krypteeritud-sedel`

   #. :ref:`entity-valija-sertifikaat`

   #. :ref:`entity-valija-identiteet`

   #. :ref:`entity-haale-signatuur`

   #. :ref:`entity-haale-allkiri`

   #. :ref:`entity-haale-konteiner`

   #. :ref:`entity-kehtivuskinnitus`

   #. :ref:`entity-ajatempel`

   #. :ref:`entity-registreerimisparing`

   #. :ref:`entity-registreerimisparing-konteiner`

   #. :ref:`entity-registreerimistoend`

   #. :ref:`entity-nimekirjatunnus`


The key application performs the following activities and checks:

   #. :ref:`check-miksitud-krypteeritud-sedel-correctness`
   #. :ref:`check-miksitud-krypteeritud-sedel-public-key-consistency`
   #. Decryption of votes
   #. :ref:`check-ringkonnatunnus-correctness`
   #. :ref:`check-tahteavaldus-correctness`
   #. :ref:`check-tahteavaldus-ringkonnatunnus-valikutenimekiri-consistency`
