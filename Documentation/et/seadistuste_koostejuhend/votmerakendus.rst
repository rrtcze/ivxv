..  IVXV collector service management service description

.. _app-key:

Key Application
================

The key application `key` consists of the tools *groupgen*, *init*, *testkey*,
*decrypt* and *util*. All tools require the presence of a signed trust root
and the specific tool's configuration. Below we describe the configurations
of the specific tools.

.. _key-groupgen:

Selecting the Vote Encryption Key Specification
--------------------------------------------------------------------------------

To use the ElGamal cryptosystem for encrypting votes, it is important to select
the vote encryption key specification, i.e., to select the group parameters
in which mathematical operations are performed. It is important that these
parameters are selected transparently, to avoid the existence of backdoors
that would allow opening encrypted votes without possessing the secret key.

Since the group parameters must meet certain conditions for security,
there is no fast method for selecting them. To find suitable group parameters,
some parameters must be randomly selected and then checked whether they meet
the given conditions.

The process of generating group parameters can be conducted transparently
in two ways:

  #. Using known defined parameters
  #. Generating parameters deterministically based on a public algorithm


Using Known Parameters
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Several standards and applications have already defined parameters that are
suitable for use in the ElGamal cryptosystem. Using widely adopted parameters
increases the likelihood that they have been independently verified.

One such standard is [RFC3526]_, which also uses deterministic parameter
generation. For this standard, the correctness of the defined parameters can
be verified with the following Sage script:

.. literalinclude:: genparam.py
   :language: python
   :linenos:


Deterministic and Verifiable Generation of New Parameters
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Parameters suitable for the ElGamal cryptosystem can be generated using
the *groupgen* tool.

Generating the key specification is a time-consuming activity that may
take hours depending on the hardware. A group generated once can be used
for multiple elections.

:groupgen.paramtype: The type of group underlying the ElGamal cryptosystem.
                     Supported values:
                     #. ``mod`` - residue class ring ``Zp``

:groupgen.length: The security parameter characterizing the group underlying the
                  ElGamal cryptosystem. For residue class rings, a suitable value
                  is 3072.

:groupgen.init_template: Location where the group parameters are written. The output
                         is suitable for use in composing the key generation
                         configuration.

:groupgen.random_source: List of sources used as input for the random number
                         generator. See also :numref:`random-gen`.

When using elliptic curves, the supported curve is P-384, for which parameter
generation is not necessary.

When using a random number generator whose initial value is uniquely definable
and published for finding random parameters, third parties can verify that the
published group parameters are the first such parameters found that meet the
conditions. The example configuration uses DPRNG with a public seed file.
See also :numref:`random-gen`.

:file:`key.groupgen.yaml`:

.. literalinclude:: config-examples/key.groupgen.yaml
   :language: yaml
   :linenos:

With this configuration, the random number generator's initial value is read
from the file ``public_seed_file``. It is important that in this case the key
application is launched in single-threaded mode::

  $ key groupgen --conf usaldusjuur.asice --params key.groupgen.asice --threads 1

.. _key-init:

Generating the Vote Encryption Key
--------------------------------------

The key application tool *init* is used to generate the vote encryption key.
The key is generated with a threshold scheme ``MofN`` specified in the
configuration, which means that out of N key custodians, at least M custodians
must participate in the decryption of votes, otherwise decryption is not possible.


:init.identifier: Unique identifier of the election.

:init.out:

       Output directory of the key application tool *init*. The following
       files are created in this directory:

       #. Signing key certificate in PEM format (``sign.pem``)
       #. Encryption key certificate in PEM format (``enc.pem``)
       #. Encryption key in PEM format (``pub.pem``)
       #. Encryption key in DER format (``pub.der``)

:init.skiptest: Skip key share verification tests.

:init.fastmode: Automatic terminal assignment for cards. Default value
                is true.

----

:init.paramtype: Group parameters underlying the ElGamal cryptosystem, which
                 also determine the key's security level. Only one group
                 specification can be in use at a time - either a residue
                 class ring or an elliptic curve.

:init.paramtype.ec: Parameters defining the elliptic curve.

:init.paramtype.ec.name: Name of the curve to use, currently P-384.

:init.paramtype.mod: Parameters defining the residue class ring in decimal
                     representation. Parameters can be created using the key
                     application tool *groupgen*.

:init.paramtype.mod.p: Modulus of the residue class ring.

:init.paramtype.mod.g: Generator of the residue class ring.

----

:init.signaturekeylen: Length of the signing key generated by the key
                       application.

:init.signcn: Subject name (field *CN*) of the signing certificate created
              by the key application.

:init.signsn: Serial number of the signing certificate created by the key
              application.

:init.enccn: Subject name (field *CN*) of the encryption certificate created
             by the key application.

:init.encsn: Serial number of the encryption certificate created by the key
             application.

----

:init.required_randomness: Mandatory amount of entropy in bytes to be read
                           from randomness sources.

:init.random_source: List of sources used as input for the random number
                     generator. See also :numref:`random-gen`.

----

:init.genprotocol: Specification of the algorithm and threshold scheme used
                   for key generation.

:init.genprotocol.desmedt:

      With the Desmedt algorithm, the key is generated by a trusted dealer,
      i.e., in the key application's memory. Private key shares are stored
      on smart cards.

      Additionally, the number of threshold scheme participants and the
      minimum quorum must be specified.

      Number of cards 7 - possible quorums 1,2,3,4 - recommended quorum 4
      Number of cards 8 - possible quorums 1,2,3,4 - recommended quorum 4
      Number of cards 9 - possible quorums 1,2,3,4,5 - recommended quorum 5

:init.genprotocol.desmedt.threshold: Threshold scheme M value - quorum.

:init.genprotocol.desmedt.parties: Threshold scheme N value.

:file:`key.init.yaml`:

.. literalinclude:: config-examples/key.init.yaml
   :language: yaml
   :linenos:



.. _key-testkey:

Testing the Vote Encryption Key
----------------------------------

Testing the vote encryption key verifies the key reconstruction capability
such that each share participates in at least two quorums. All shares must
participate in testing.

:testkey.identifier: Unique identifier of the election.

:testkey.out: Directory location of the encryption public key.

:testkey.threshold: Threshold used for testing, same as specified during
                    key creation.

:testkey.parties: Number of parties used for testing, same as specified
                  during key creation.

:testkey.fastmode: Automatic terminal assignment for cards. Default
                   value is true.


:file:`key.testkey.yaml`:

.. literalinclude:: config-examples/key.testkey.yaml
   :language: yaml
   :linenos:


.. _key-decrypt:

Decrypting E-votes
--------------------------------------

The key application tool *decrypt* is used for decrypting electronic votes.
For decryption to succeed, the quorum specified by the threshold scheme of
key custodians must participate. If the scheme ``5of9`` was applied, then
exactly 5 key custodians participate in the decryption. With fewer custodians,
decryption is not possible.

:decrypt.identifier:

        Unique identifier of the election.

----

:decrypt.protocol:

:decrypt.protocol.recover:

      With the Desmedt algorithm, the key is generated by a trusted dealer,
      i.e., in the key application's memory. Private key shares are stored
      on smart cards.

:decrypt.protocol.recover.threshold:

      Threshold scheme M value - quorum, which was specified during key creation.

:decrypt.protocol.recover.parties:

      Threshold scheme N value, which was specified during key creation.

----

:decrypt.anonballotbox:

      E-ballot box with anonymized votes created by the processing application
      or mixing application.

:decrypt.anonballotbox_checksum:

      Signed SHA256 checksum file of the e-ballot box with anonymized votes.

:decrypt.questioncount:

      Number of questions in the anonymized e-ballot box. Default value is 1.

:decrypt.candidates:

      Election choices list in signed form.

:decrypt.districts:

      Election districts list in signed form.

:decrypt.provable:

      Optional issuance of correct decryption proof. Default value is true.

:decrypt.prove_invalid:

      Optional issuance of correct decryption proof also for incorrect
      ballots. Requires issuance of decryption proof. Default value is false.

:decrypt.check_decodable:

      Verification of cryptogram correctness before decryption. If the
      cryptogram input does not come from a trusted source, then cryptogram
      correctness must be verified. Trusted sources are the processing
      application and the mixer. Default value is false.

:decrypt.out:

      Output directory of the key application tool *decrypt*. Upon successful
      decryption, the following are created in this directory:

      #. Electronic voting result
      #. Electronic voting result signature
      #. Decrypted ballot box
      #. Decrypted ballot box signature
      #. List of invalid ballots
      #. Decryption proof for valid ballots
      #. Decryption proof for invalid ballots (optional)

The decrypted ballot box does not contain sensitive data.

:file:`key.decrypt.yaml`:

.. literalinclude:: config-examples/key.decrypt.yaml
   :language: yaml
   :linenos:

After decryption, it is possible to verify the correctness of the issued
electronic voting result signature. To do this, the following steps must be
taken:

1. Extract the signature verification key from the signing certificate::

    openssl x509 -in initout/sign.pem -noout -pubkey > sign.pub

2. Verify the voting result signature::

    openssl dgst -sha256 -sigopt rsa_padding_mode:pss -sigopt \
    rsa_pss_saltlen:32 -sigopt rsa_mgf1_md:sha256 -verify sign.pub \
    -signature decout/TESTCONF.tally.signature decout/TESTCONF.tally

For a correct signature, the value `Verified OK` is displayed.

Similar steps can be used to verify the correctness of the issued decrypted
ballot box signature.

Additional Key Application Tools
------------------------------------

:util.listreaders: List connected card readers.

:file:`key.util.yaml`:

.. literalinclude:: config-examples/key.util.yaml
   :language: yaml
   :linenos:


.. _random-gen:

Random Number Generation in the Key Application
------------------------------------------------

The key application tools *groupgen* and *init* require random numbers for their
operation, and various entropy sources can be used for generating them, which
are combined by the key application into a single source.

During combination, it is important that the independence of inputs is preserved,
i.e., the combined output must not be worse than any of the inputs. In the IVXV
framework, entropy combination is performed using the SHAKE-256 variable-length
hash function (XOF), using the scheme described in [BDPA10]_.

When using a finite-length entropy source, the entire value is read and given
as input to SHAKE-256. When adding an unlimited-length source, its reference
is stored in the combiner's memory.

When requesting processed randomness from the combiner, the same number of bytes
is first read from each stored entropy source and given as input to SHAKE-256.
Then the SHAKE-256 instance is copied, the copied SHAKE-256 mode is switched to
reading, and the required number of bytes of output is read.


:random_source: List of sources used as input for the random number generator.

:random_source.random_source_type: Type of the random number generator source.

:random_source.random_source_path: Configurable location of the random number
                                   generator source. The argument is optional
                                   depending on the source type.

----

:random_source_type\: file: Reading entropy from a file.

:random_source_path\: `randomness_file`: The file to use.

----

:random_source_type\: system: Entropy source provided by the operating system
                              (on Linux `/dev/urandom`).

----

:random_source_type\: DPRNG: A deterministic pseudo-random number generator (DPRNG) is
                             intended for generating byte sequences using a given
                             seed value. With the same seed value, the method
                             always generates the same sequence.
:random_source_path\: `seed_file`: The DPRNG seed value is obtained by hashing
                                   the referenced file with SHA256.

----

:random_source_type\: stream: Reading entropy from a stream device.

:random_source_path\: `/dev/urandom`: The device to use.

----

:random_source_type\: user: An entropy source that obtains randomness from an
                            external program via a socket. An IVXV-specific
                            protocol is used.

:random_source_path\: `user_entropy.exe`: Path to the program that must be
                                          launched for obtaining randomness.


Combining entropy sources in the described manner allows implementing
different random number generation scenarios. For example, when generating the
vote encryption key, it is necessary to ensure the confidentiality of the key
and to be certain that the generation process cannot be repeated later. The
example configuration uses an external program for reading user input and a
system random number generator:

:file:`rnd.init.yaml`:

.. literalinclude:: config-examples/rnd.init.yaml
   :language: yaml
   :linenos:


The application is launched in multi-threaded mode::

  $ key init --conf usaldusjuur.asice --params rnd.init.asice

The vote encryption key specification, unlike the vote encryption key itself,
is public, and the randomness used in its generation may also be made public.
The example configuration uses DPRNG with a public seed file.

:file:`rnd.groupgen.yaml`:

.. literalinclude:: config-examples/rnd.groupgen.yaml
   :language: yaml
   :linenos:

If the goal is reproducibility of the generation process, the application must
be launched in single-threaded mode::

  $ key groupgen --conf usaldusjuur.asice --params rnd.groupgen.asice --threads 1



.. [BDPA10] G. Bertoni, J. Daemen, M. Peeters, G. Van Assche: Sponge-Based
   Pseudo-Random Number Generators. CHES 2010: 33-47

.. [RFC3526] T. Kivinen, M. Kojo: More Modular Exponential (MODP) Diffie-Hellman
   groups for Internet Key Exchange (IKE). IETF RFC3526, 2003
