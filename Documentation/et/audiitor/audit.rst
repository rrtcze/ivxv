
================================================================================
IVXV Guide for the Auditor
================================================================================

Compiling Applications
================================================================================


PREREQUISITES
--------------------------------------------------------------------------------

All activities are performed under regular user -- in the examples `ubuntu` --
privileges, using the `sudo` command when necessary.

Generally, all activities are performed in the user's home directory::

  cd $HOME

Install the software required for building the auditor tools::

  sudo apt-get install --no-install-recommends -y autoconf automake build-essential libgmp-dev libtool git openjdk-11-jdk-headless python unzip zip wget make


INTCHECK
--------------------------------------------------------------------------------

Verificatum mixnet integrity check is performed with the `intcheck` application::

  wget https://github.com/vvk-ehk/intcheck/archive/master.zip
  unzip master.zip
  rm master.zip
  mv intcheck-master intcheck
  chmod +x intcheck/src/intcheck.py

Verify that the application is installed correctly::

  ./intcheck/src/intcheck.py -h


JAVA APPLICATIONS
--------------------------------------------------------------------------------

To perform the data audit, the `auditor` application is needed, whose source
code is published in the IVXV repository::

  wget https://github.com/vvk-ehk/ivxv/archive/master.zip
  unzip master.zip
  rm master.zip
  mv ivxv-master ivxv


Install Java dependency packages::

  cd $HOME/ivxv/common/external
  wget -O gradle-8.11.zip https://services.gradle.org/distributions/gradle-8.11-bin.zip
  unzip gradle-8.11.zip
  rm gradle-8.11.zip
  cd $HOME/ivxv/common/java
  make sync

Verify that the preparations are done correctly::

  cd $HOME/ivxv
  make clean-java

Build the Java applications::

  make java

Applications to be delivered to the NEC::

  $HOME/ivxv/auditor/build/distributions/auditor-1.10.3.zip
  $HOME/ivxv/key/build/distributions/key-1.10.3.zip
  $HOME/ivxv/processor/build/distributions/processor-1.10.3.zip

Executable files::

  $HOME/ivxv/auditor/build/install/auditor/bin/auditor
  $HOME/ivxv/key/build/install/key/bin/key
  $HOME/ivxv/processor/build/install/processor/bin/processor


VERIFICATUM
--------------------------------------------------------------------------------

The Verificatum mixnet adapter is required for verifying the mixing proof::

  cd $HOME
  wget https://github.com/vvk-ehk/ivxv-mixnet-adapter/archive/master.zip
  unzip master.zip
  rm master.zip
  mv ivxv-mixnet-adapter-master ivxv-verificatum

Download the Verificatum software::

  git clone https://github.com/verificatum/verificatum-gmpmee gmpmee
  git clone https://github.com/verificatum/vmgj
  git clone https://github.com/verificatum/vcr
  git clone https://github.com/verificatum/vmn

Obtaining the exact version of the software and integrity check::

  cd gmpmee
  git checkout 4aafc31
  rm -rf .git/
  cd ..
  ./intcheck/src/intcheck.py verify gmpmee ivxv-verificatum/doc/gmpmee.dirsha256sum

  cd vmgj
  git checkout 8d7d412
  rm -rf .git/
  cd ..
  ./intcheck/src/intcheck.py verify vmgj ivxv-verificatum/doc/vmgj.dirsha256sum

  cd vcr
  git checkout af9fd82
  rm -rf .git/
  cd ..
  ./intcheck/src/intcheck.py verify vcr ivxv-verificatum/doc/vcr.dirsha256sum

  cd vmn
  git checkout bb00543
  rm -rf .git/
  cd ..
  ./intcheck/src/intcheck.py verify vmn ivxv-verificatum/doc/vmn.dirsha256sum

Building the Verificatum adapter::

  cd $HOME/ivxv-verificatum
  make zipext

Initializing the random number generator for Verificatum::

  cd $HOME
  ./vcr/bin/vog -rndinit RandomDevice /dev/urandom


Auditing
================================================================================

From here on, we assume that the reader is familiar with the document "IVXV
Configuration Preparation Guide" to the following extent:

* Ch. 2, IVXV configurations in the election organization process
* Ch. 3, IVXV applications
* Ch. 6, Auditor application
* Ch. 10, Mixing of e-votes

Let the package `audit-examples.tar` also be installed, which has the following
structure::

   audit-conv
   |-- auditor.yaml -- configuration example
   |-- inputs
   |   |-- <Inputs provided by the NEC>
   |-- process
   |   |-- <Working directory with configurations>
   |
   audit-mix
   |-- auditor.yaml -- configuration example
   |-- inputs
   |   |-- <Inputs provided by the NEC>
   |-- process
   |   |-- <Working directory with configurations>
   |
   audit-mixver
   |-- inputs
   |   |-- <Inputs provided by the NEC>
   |
   audit-pdec
   |-- auditor.yaml -- configuration example
   |-- inputs
   |   |-- <Inputs provided by the NEC>
   |-- process
   |   |-- <Working directory with configurations>
   |
   audit-vertally
   |-- inputs
   |   |-- <Inputs provided by the NEC>
   |
   processor
   |-- <Processor application inputs and outputs>

The general procedure is as follows:

* Review the configuration example
* Verify that the required NEC inputs are available
* Create the file structure in the `process` directory based on the configuration example
* Run the application and tool in the `process` directory (pre-prepared configurations are
  already in place)

Detailed instructions follow.

Consistency Check of Generated Public Keys
--------------------------------------------------------------------------------

During key generation, two keys are created — the result file signing key and
the vote encryption key.

The result file signing key is encoded as an X509 certificate in the file
`RK2051-sign.pem`. The vote encryption key is provided in three encodings:

* As an X509 certificate in the file `RK2051-enc.pem`
* As a DER-encoded public key in the file `RK2051-pub.der`
* As a PEM-encoded public key in the file `RK2051-pub.pem`

It is possible to verify that the certificate containing the result file
signing key is correctly self-signed. This can be done as follows::

    openssl verify -CAfile RK2051-sign.pem -check_ss_sig RK2051-sign.pem

For a correct certificate, the output is::

    RK2051-sign.pem: OK

It is possible to verify that the certificate containing the vote encryption
key is correctly signed with the result file signing key. This can be done as
follows::

    openssl verify -CAfile RK2051-sign.pem -check_ss_sig RK2051-enc.pem

For a correctly signed certificate, the output is::

    RK2051-enc.pem: OK

.. note:: Due to a known OpenSSL bug, OpenSSL versions older than `1.1.1b`
   cannot verify the certificate trust chain. For the above check to succeed,
   at least OpenSSL version `1.1.1b` is required.

Additionally, it is possible to verify that the different encodings of the vote
encryption key correspond to each other. We verify that the key in the X509
certificate matches the DER-encoded key and additionally that the PEM-encoded
key matches the DER-encoded key. Due to transitivity, all three encodings are
therefore consistent.

First, the vote encryption key must be extracted from the corresponding
certificate. Since OpenSSL does not support the ElGamal encryption scheme
used, the OpenSSL `asn1parse` tool must be used to export the public key.

First, find the offset of the public key in the certificate::

    openssl asn1parse -in RK2051-enc.pem

The public key is in the corresponding `SubjectPublicKeyInfo` field::

    156:d=2  hl=4 l= 816 cons: SEQUENCE
    160:d=3  hl=4 l= 415 cons: SEQUENCE
    164:d=4  hl=2 l=   9 prim: OBJECT            :1.3.6.1.4.1.3029.2.1
    175:d=4  hl=4 l= 400 cons: SEQUENCE
    179:d=5  hl=4 l= 385 prim: INTEGER           :FFFFFFFFFFFFFFFFC90FDA
        A22168C234C4C6628B80DC1CD129024E088A67CC74020BBEA63B139B22514A08
        798E3404DDEF9519B3CD3A431B302B0A6DF25F14374FE1356D6D51C245E485B5
        76625E7EC6F44C42E9A637ED6B0BFF5CB6F406B7EDEE386BFB5A899FA5AE9F24
        117C4B1FE649286651ECE45B3DC2007CB8A163BF0598DA48361C55D39A69163F
        A8FD24CF5F83655D23DCA3AD961C62F356208552BB9ED529077096966D670C35
        4E4ABC9804F1746C08CA18217C32905E462E36CE3BE39E772C180E86039B2783
        A2EC07A28FB5C55DF06F4C52C9DE2BCBF6955817183995497CEA956AE515D226
        1898FA051015728E5A8AAAC42DAD33170D04507A33A85521ABDF1CBA64ECFB85
        0458DBEF0A8AEA71575D060C7DB3970F85A6E1E4C7ABF5AE8CDB0933D71E8C94
        E04A25619DCEE3D2261AD2EE6BF12FFA06D98A0864D87602733EC86A64521F2B
        18177B200CBBE117577A615D6C770988C0BAD946E208E24FA074E5AB3143DB5B
        FCE0FD108E4B82D120A93AD2CAFFFFFFFFFFFFFFFF
    568:d=5  hl=2 l=   1 prim: INTEGER           :02
    571:d=5  hl=2 l=   6 prim: GENERALSTRING
    579:d=3  hl=4 l= 393 prim: BIT STRING

We see that the offset of the `SubjectPublicKeyInfo` field is 156 bytes.
Extract the public key and verify correspondence with the issued public key::

    openssl asn1parse -in RK2051-enc.pem -strparse 156 -noout -out extracted.der
    diff -s extracted.der RK2051-pub.der

For equivalent keys, the output is::

    Files extracted.der and RK2051-pub.der are identical

Second, we verify the correspondence of the DER-encoded key with the
PEM-encoded key. To do this, we convert the PEM-encoded key to DER encoding
and compare::

    openssl asn1parse -in RK2051-pub.pem -noout -out converted.der
    diff -s converted.der RK2051-pub.der

For equivalent keys, the output is::

    Files converted.der and RK2051-pub.der are identical

Verification of the Voting Result Signature
--------------------------------------------------------------------------------

During both regular decryption and provable decryption, two files are
produced:

* Result file `RK2051.1.tally`
* Signature file `RK2051.1.tally.signature`

Together with the vote encryption key, the result file signing key and the
corresponding certificate (`RK2051-sign.pem`) are generated. The decrypted
result is signed with this key, and the signature must be verified.

Extract the public key from the signing key certificate::

  openssl x509 -in RK2051-sign.pem -noout -pubkey > sign.pub

Use the public key to verify the result file signature::

  openssl dgst -sha256 -sigopt rsa_padding_mode:pss -sigopt rsa_pss_saltlen:32 -sigopt rsa_mgf1_md:sha256 -verify sign.pub -signature RK2051.1.tally.signature RK2051.1.tally

NB! The result files produced during regular decryption and provable decryption
must be identical. To verify, use the UNIX tool `diff`::

  diff decout/RK2051.1.tally pdecout/RK2051.1.tally

Sample files are in the package::

  cd $HOME/audit-examples/audit-vertally


IVXV <-> Verificatum Conversion Correctness Check
--------------------------------------------------------------------------------

The conversion correctness check is performed with the `convert` tool. NB! The
`process` directory must be prepared from inputs based on `auditor.yaml`::

  cd $HOME/audit-examples/audit-conv/process
  $HOME/ivxv/auditor/build/install/auditor/bin/auditor convert -c conf.bdoc -p auditor.yaml.bdoc

Mixing Proof Verification with the `auditor` Tool
--------------------------------------------------------------------------------

The mixing proof verification is performed with the `mixer` tool. NB! The
`process` directory must be prepared from inputs based on `auditor.yaml`::

  cd $HOME/audit-examples/audit-mix/process
  $HOME/ivxv/auditor/build/install/auditor/bin/auditor mixer -c conf.bdoc -p auditor.yaml.bdoc

Decryption Proof Verification
--------------------------------------------------------------------------------

The decryption proof verification is performed with the `decrypt` tool. NB! The
`process` directory must be prepared from inputs based on `auditor.yaml`::

  cd $HOME/audit-examples/audit-pdec/process
  $HOME/ivxv/auditor/build/install/auditor/bin/auditor decrypt -c conf.bdoc -p auditor.yaml.bdoc

Mixing Proof Verification with the Original Verificatum Tool
--------------------------------------------------------------------------------

Mixing proof verification using Verificatum::

  cd $HOME/audit-examples/audit-mixver
  $HOME/ivxv-verificatum/release/mixer/bin/mix.py verify --proof-zipfile shuffle_proof.zip

Processing Audit
--------------------------------------------------------------------------------

Additionally, all processor application inputs and outputs are included in the
package to simplify the processing audit. Additional auditing tools, e.g.,
`integrity`, are described in the document "IVXV Configuration Preparation Guide".
