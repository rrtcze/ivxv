..  IVXV protocols

=====
Appendices
=====

ASN.1 Specification of Data Structures
========================================

.. literalinclude:: ivxv-elgamal-general.asn1
   :language: asn1
   :name: asn-general
   :linenos:
   :caption: IVXV ElGamal general data structures

.. literalinclude:: ivxv-elgamal-modp.asn1
   :language: asn1
   :name: asn-modp
   :linenos:
   :caption: IVXV ElGamal ModP specific data structures

.. literalinclude:: ivxv-elgamal-ecc.asn1
   :language: asn1
   :name: asn-ecc
   :linenos:
   :caption: IVXV ElGamal ECC specific data structures



Specification of the Electronic Vote Format
==============================================

A proposal consistent with the current protocol version for the NEC decision
to establish the format of the ballot and the electronic vote.

.. literalinclude:: paragraph.txt


Errors in the Processing Process
========================

We provide an overview of error codes in the processing process. The error
codes describe errors in the verification of individual elements - vote,
registration proof, registration request - and in establishing correspondence
between votes, registration proofs, and registration requests.

Most error situations are rather hypothetical (e.g., `REG_NO_NONCE`), yet these
are situations that may occur programmatically and therefore must also be
handled.

An error situation means that the specific element does not proceed to the
next phase of processing.

.. list-table:: Processing process error codes
   :widths: 40 60
   :header-rows: 1

   * - Error code
     - Description
   * - ``INVALID_FILE_NAME``
     - The file name does not match the expected pattern. Refers to an unknown file in the ballot box.
   * - ``MISSING_FILE``
     - A file required as part of the vote is missing. E.g., timestamp.
   * - ``REPEATED_FILE``
     - A file required as part of the vote appears multiple times. E.g., validity confirmation.
   * - ``UNKNOWN_FILE_TYPE``
     - The file type is unknown or unsupported.
   * - ``INVALID_FILE_SIZE``
     - The size of the signed vote file does not meet the criteria required in the configuration.
   * - ``INVALID_BALLOT_SIGNATURE``
     - The vote has an invalid signature.
   * - ``MISSING_VOTER_SIGNATURE``
     - The vote does not contain the voter's signature.
   * - ``VOTER_NOT_FOUND``
     - The voter was not in the voter list at the time of voting.
   * - ``VOTERLIST_NOT_FOUND``
     - The voter list corresponding to the version was not found.
   * - ``TIME_BEFORE_START``
     - The vote was cast before the start of the voting period. Refers to a test vote.
   * - ``REG_RESP_INVALID``
     - The registration proof/timestamp is invalid. Error in the TSA or processor.
   * - ``REG_REQ_INVALID``
     - The registration request is invalid. Error in the collection service or processor.
   * - ``REG_RESP_NOT_UNIQUE``
     - The registration proof is not unique. Error in the collection service or processor.
   * - ``REG_REQ_NOT_UNIQUE``
     - The registration request is not unique. A vote with the same hash has been submitted repeatedly.
   * - ``REG_NO_NONCE``
     - The registration proof does not contain a nonce.
   * - ``REG_NONCE_NOT_SIG``
     - The submitted nonce is not signed in accordance with the IVXV protocol.
   * - ``REG_NONCE_ALG_MISMATCH``
     - The algorithm used for signing the nonce does not match the expected one.
   * - ``REG_NONCE_SIG_INVALID``
     - The nonce signature is invalid.
   * - ``UNKNOWN_FILE_IN_VOTE_CONTAINER``
     - The vote container contains an unknown file.
   * - ``TECHNICAL_ERROR``
     - A technical error occurred during processing.
   * - ``REG_RESP_REQ_UNMATCH``
     - The registration proof data does not match the registration request data.
   * - ``REG_REQ_WITHOUT_BALLOT``
     - A registration request has been submitted, but the vote is missing from the ballot box. Collection service error.
   * - ``BALLOT_WITHOUT_REG_REQ``
     - A vote has been submitted without a corresponding registration request. TSA error.
   * - ``SAME_TIME_AS_LATEST``
     - Two votes from the same voter may both be eligible as the last one.
   * - ``INVALID_SIGNATURE_PROFILE``
     - The vote's signature profile is invalid.


During processing, invalid ballots are identified to the extent that
public key checks allow. Although the collection service does not allow
invalid ballots to be stored, the processing application must repeat the
checks to ensure, among other things, the avoidance of possible software bugs.


.. list-table:: Cryptogram validity check error codes
   :widths: 30 70
   :header-rows: 1

   * - Error code
     - Description
   * - ``INVALID_BYTES``
     - The byte sequence is not decodable as ElGamalCiphertext
   * - ``INVALID_GROUP``
     - The value is not an element of the expected group
   * - ``INVALID_RANGE``
     - The value is outside the permitted range.
   * - ``INVALID_QR``
     - The value is not a quadratic residue (MODP).
   * - ``INVALID_POINT``
     - The value is not a point on the curve (ECC).
   * - ``INVALID``
     - Invalid ciphertext.

