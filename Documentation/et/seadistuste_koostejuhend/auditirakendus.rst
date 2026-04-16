..  IVXV collector service management service description

.. _app-auditor:

Audit Application
=================

The IVXV key application enables the use of provable decryption -
along with the result, a decryption proof of correct opening of e-votes
is issued. To avoid compromising vote secrecy during decryption proof
verification, IVXV enables the use of vote mixing, which preserves
the content of votes but cryptographically removes the link between
a specific vote and the person who cast that vote.

IVXV uses the Verificatum software for mixing e-votes, which takes
encrypted votes as input and produces mixed encrypted votes and a
mixing proof as output.

The verification of the mixing proof and decryption proof is performed using
the audit application tools *convert*, *mixer* and *decrypt*.

The verification of the processing application operations is performed using
the audit application tool *integrity*.

#. The *convert* tool verifies the correctness of conversions between IVXV
   data formats and Verificatum data formats.
#. The *mixer* tool verifies the correctness of the mixing proof.
#. The *decrypt* tool verifies the correctness of the decryption proof.
#. The *integrity* tool verifies the correctness of the processing application logs.

For verifying the correct tallying of e-votes, it is necessary and sufficient
to use all four audit application tools.

All tools require the presence of a signed trust root and the specific
tool's configuration. Below we describe the configurations of the
specific tools.

.. _auditor-convert:

Verification of Correct E-vote Conversion
------------------------------------------

The mixing proof format produced by Verificatum is different from the format
used in the IVXV framework, as are the IVXV and Verificatum encrypted vote
formats. Adapters for format conversions are packaged into the IVXV framework,
and the audit application provides the ability to verify the correctness of
these conversions.

The *convert* tool verifies that the mixing proof issued by Verificatum
corresponds to the files in the IVXV framework.

:convert.input_bb: Location of the IVXV pre-mixing e-ballot box.

:convert.output_bb: Location of the IVXV post-mixing e-ballot box.

:convert.pub: Location of the IVXV public key.

:convert.protinfo: Location of the Verificatum mixing protocol file.

:convert.proofdir: Location of the Verificatum mixing proof.

:file: `auditor.convert.yaml`:

.. literalinclude:: config-examples/auditor.convert.yaml
   :language: yaml
   :linenos:

.. _auditor-mix:

E-vote Mixing Proof Verification
---------------------------------

The *mixer* tool verifies the correctness of the Verificatum mixing proof.

:mixer.protinfo: Location of the Verificatum mixing proof protocol file.

:mixer.proofdir: Location of the Verificatum mixing proof.

:mixer.threaded: Use multi-threaded implementation. Default value
                 is false. The number of threads used depends on
                 the command-line arguments. If command-line arguments
                 are absent, the optimal number of threads is selected
                 based on the detected number of cores.

:file:`auditor.mixer.yaml`:

.. literalinclude:: config-examples/auditor.mixer.yaml
   :language: yaml
   :linenos:

.. _auditor-decrypt:

E-vote Decryption Proof Verification
--------------------------------------

The *decrypt* tool verifies the correctness of the decryption proof.

:decrypt.proofs: Location of the decryption proof for valid ballots.

:decrypt.pub: Location of the public key corresponding to the secret key
              used for decryption.

:decrypt.discarded: List of invalid ballots.

:decrypt.anon_bb: E-ballot box with anonymized votes created by the
                  processing application or mixing application.

:decrypt.plain_bb: Decrypted ballot box.

:decrypt.tally: Electronic voting result.

:decrypt.candidates: Election choices list in signed form.

:decrypt.districts: Election districts list in signed form.

:decrypt.out: Location of decryption proof verification results. This is
              a directory where ballots whose decryption proof was invalid
              are saved.

:decrypt.invalidity_proofs: Optional location of the decryption proof for
                            invalid ballots.

:decrypt.abort_early: Optional termination of the audit application upon the
                      first failed verification. Default value is true.

:file:`auditor.decrypt.yaml`:

.. literalinclude:: config-examples/auditor.decrypt.yaml
   :language: yaml
   :linenos:

.. _auditor-integrity:

Processing Application Log Verification
-----------------------------------------

The *integrity* tool verifies that the logs issued by the processing
application connect the e-ballot box with the anonymized e-ballot box.

:integrity.ballotbox: E-ballot box issued from the collector service.

:integrity.anon_bb: E-ballot box with anonymized votes created by the
                    processing application.

:integrity.log_accepted: Accepted votes *log1* file.

:integrity.log_squashed: Cancelled repeated votes *log2* file.

:integrity.log_revoked: Votes revoked and restored based on polling station
                        info *log2* file.

:integrity.log_anonymised: Votes sent for tallying *log3* file.

:integrity.bb_errors: E-ballot box processing errors report.

:integrity.abort_early: Optional termination of the audit application upon the
                        first failed verification. Default value is true.

:file: `auditor.integrity.yaml`:

.. literalinclude:: config-examples/auditor.integrity.yaml
   :language: yaml
   :linenos:
