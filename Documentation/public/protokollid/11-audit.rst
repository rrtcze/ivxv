..  IVXV protocols

========================
Voting Result Audit
========================

Mixing Proof Verification
=======================

For verifying the mixing proof, the algorithm as defined in the
`Verificatum verifier implementation manual
<https://www.verificatum.org/files/vmnv-3.0.3.pdf>`_ is used.

Note that when composing the mixing proof, data about the election, district,
polling division, and question identifiers is added to the cryptogram. For
addition, the corresponding field is encoded as a group element, using
randomness 0 for blinding. As an example, if the initial cryptogram is
:math:`c_0 = (c_{00}, c_{01})`, using the public key :math:`pk = (g, y)`, then
as input to Verificatum, the wide cryptogram
:math:`C = (c_{id}, c_d, c_s, c_q, c_0)` is used, where:

* the election identifier pseudo-cryptogram is given as :math:`c_{id} = (1,
  encode(id))`, where the function :math:`encode` encodes the string as an
  element of the corresponding group and `id` is the election identifier string.
* the district identifier pseudo-cryptogram is given as :math:`c_d = (1,
  encode(d))`, where `d` is the district identifier string.
* the polling division identifier pseudo-cryptogram is given as :math:`c_s = (1,
  encode(s))`, where `s` is the polling division identifier string.
* the question identifier pseudo-cryptogram is given as :math:`c_q = (1,
  encode(q))`, where `q` is the question identifier string.

In this case, the public key corresponding to the wide cryptogram is defined as
:math:`((g,1), (g,1), (g,1), (g,1), (g,y))`.

Correct Decryption Proof Verification
=========================================

Let a cryptogram :math:`c = (c_0, c_1)` be given, which is decrypted to the
value :math:`d` with the given public key :math:`pk` over the parameters
:math:`(p,g)` and with the decryption proof :math:`(a,b,s)`.

To verify the correct decryption, a non-interactive verifier challenge must be
computed. For this, :math:`"DECRYPTION" || pk || c || d || a || b` is encoded
in DER encoding. The byte sequence is used to initialize a deterministic
random number generator and from its output an integer of group order length
:math:`k` is read.

To verify the decryption proof, it must be verified that :math:`c_0^s
= a * (c_1/d)^k` and :math:`g^s = b * y^k`.

Correct Conversion Verification
===============================

To verify that the conversion between the IVXV e-ballot box and Verificatum
cryptograms has been done correctly, the conversion must be independently
repeated. After the independent conversion, the outputs obtained must be
compared. Since the conversion is a deterministic procedure, repetition
guarantees the correctness of the operation.
