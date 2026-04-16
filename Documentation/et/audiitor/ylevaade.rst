Mixing Proof Overview
=====================

Without using randomness, every encryption algorithm would be deterministic,
i.e., encrypting a voter's choice would always result in the same output. This
would allow an attacker to identify the original choice by encrypting all
possible choices and comparing this list with the observed encrypted choice.
Therefore, encryption must use randomness.

The use of randomness makes cryptograms unique — even if the same choice is
encrypted twice, the cryptograms are different. This means that if an attacker
is able to associate a cryptogram with the person who encrypted it at some
point in time, they can later identify the person just by seeing the
cryptogram. Since the ElGamal public key cryptosystem is long-term secure when
using appropriate parameters, this is not directly a problem.

The problem arises when it is necessary to prove that a cryptogram has been
correctly decrypted. If the choice aggregation algorithm operates on plaintext
strings (as it does in IVXV), then each cryptogram produces one decrypted
plaintext. A proof of correct decryption must bind both the cryptogram and the
decrypted plaintext. Therefore, it is possible for an attacker to establish a
link between a person and a cryptogram, and between a cryptogram and its
corresponding plaintext, i.e., they can learn what choice the person made.

To remove this link, IVXV uses cryptogram shuffling (mixnet). A mixnet
performs two operations simultaneously — it reorders the input cryptograms
(permutes) and updates the randomness in the cryptograms (re-randomizes). This
means that the cryptograms entering the mixnet are externally completely
independent from the cryptograms coming out of the mixnet. Since due to
external independence the mixnet could theoretically replace cryptograms, it is
necessary to add a mixing proof that cryptographically proves that the
operations were performed correctly and no additional operations were
performed. By verifying the mixing proof, it is possible to guarantee that the
mixnet has operated correctly.

Example Written with Small Parameters
--------------------------------------

IVXV uses the ElGamal public key cryptosystem for encrypting choices. In the
ElGamal cryptosystem, the parameters of a fixed algebraic group are defined
together with a generator :math:`g`. The secret key :math:`x` is chosen
uniformly from the range :math:`[0, q-1]`, where :math:`q` is the order of the
multiplicative subgroup. The public key corresponding to the secret key is
defined as:

.. math::
   pk = (g, g^x) = (g, y).

To encrypt a string-form choice `V`, it must first be encoded as a group
element

.. math::
   m = encode(V)

and then the cryptogram is computed using a one-time random number
:math:`0<=r<q`

.. math::
   c = (c_1, c_2) = (m y^r, g^r).

In this case, re-randomization is sufficient by computing with a second
one-time random number :math:`t`

.. math::
   c' = c * (y^t, g^t) = (m y^{r + t}, g^{r + t}).

Note also that in the previous equation :math:`(y^t, g^t)` is an encryption
of the element :math:`1`.

For decryption, compute

.. math::
   d = c_1 / c_2^x,

and decode :math:`S = decode(d)`.

If the cryptogram is correctly constructed and decryption is correctly
performed, then :math:`d=m`, since

.. math::
   d = c_1 / c_2^x = (m y^r) / (g^{rx}) = (m y^r) / (y^r) = m.

For example, assume the group is integers modulo :math:`p = 227`. In this
case, the generator :math:`g = 4` generates a subgroup of order :math:`q = 113`.
We choose an arbitrary secret key :math:`x = 100` and the corresponding public
key is :math:`pk = (g, g^x) = (4, 21)`.

Assume there are four different choices and their encodings into the subgroup
are as follows:

======  ========
choice  encoding
======  ========
orav       16
jänes      64
hunt       29
kits      116
======  ========

For the following choices and one-time random numbers, the cryptograms are as
follows:

======  ========  =======  =============
choice  encoding  random    cryptogram
======  ========  =======  =============
kits       116       71    (62, 205)
hunt       29        80    (161, 221)
kits       116       64    (7, 147)
kits       116       47    (139, 36)
orav       16        76    (26, 172)
hunt       29        86    (30, 212)
kits       116       88    (155, 175)
orav       16        85    (87, 212)
orav       16        32    (132, 104)
jänes      64        22    (113, 171)
======  ========  =======  =============


Let the permutation :math:`\pi` used by the mixnet be defined as follows:

======  =====
index   value
======  =====
   1      5
   2      8
   3      3
   4      6
   5      7
   6      2
   7      9
   8     10
   9      4
  10      1
======  =====

Let the random numbers used for re-randomization by the mixnet be:

======  ======================
index   additional random number
======  ======================
   1         43
   2        107
   3          6
   4         86
   5         56
   6         48
   7         35
   8        112
   9         55
  10        101
======  ======================

In this case, after reordering, the cryptograms are in the following order:

==========   ==========  =============
 original    new index    permuted
==========   ==========  =============
(62, 205)       5         (113, 171)
(161, 221)      8         (30, 212)
(7, 147)        3         (7, 147)
(139, 36)       6         (132, 104)
(26, 172)       7         (62, 205)
(30, 212)       2         (139, 36)
(155, 175)      9         (26, 172)
(87, 212)      10         (161, 221)
(132, 104)      4         (155, 175)
(113, 171)      1         (87, 212)
==========   ==========  =============

After re-randomization, the cryptograms are as follows:

==========  ================  ==================  ===============
 original   additional random  multiplied value    re-randomized
==========  ================  ==================  ===============
(113, 171)         43              (10, 103)         (222, 134)
(30, 212)         107              (28, 159)         (159, 112)
(7, 147)            6              (73, 10)          (57, 108)
(132, 104)         86              (100, 167)        (34, 116)
(62, 205)          56              (207, 113)        (122, 11)
(139, 36)          48              (78, 144)         (173, 190)
(26, 172)          35              (188, 73)         (121, 71)
(161, 221)        113              (173, 57)         (159, 112)
(155, 175)         55              (172, 85)         (101, 120)
(87, 212)         101              (103, 84)         (108, 102)
==========  ================  ==================  ===============

Let us verify how the permuted and re-randomized cryptograms decrypt:

===========  ==============  =========
cryptogram   decrypted       decoded
===========  ==============  =========
(222, 134)        64            jänes
(159, 112)        29            hunt
(57, 108)         116           kits
(34, 116)         16            orav
(122, 11)         116           kits
(173, 190)        116           kits
(121, 71)         16            orav
(159, 112)        29            hunt
(101, 120)        116           kits
(108, 102)        16            orav
===========  ==============  =========
