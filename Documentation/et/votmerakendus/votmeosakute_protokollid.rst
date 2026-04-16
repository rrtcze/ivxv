..  IVXV technical documentation

Interfacing Different Types of Key Share Protocols
==================================================

Key Share Generation Protocol Interface
---------------------------------------

The class `ee.ivxv.key.protocol.GenerationProtocol` defines the interface that
an ElGamal or RSA key share generation protocol must implement. The interface is
as follows::

    public interface GenerationProtocol {
        byte[] generateKey() throws ProtocolException;
    }

To generate different types of key shares, the `generateKey()` method must be
implemented, which returns the encoded public key as an X.509 certificate in DER
format. The protocol class must be in a subpackage of
`ee.ivxv.key.protocol.generation`.

The protocol parameters must be set during the initialization of the protocol
class instance.

Decryption Protocol Interface
-----------------------------

The decryption and key share generation protocols do not have to be in a
one-to-one relationship, i.e., a key share generation protocol may correspond to
multiple decryption protocols. Therefore, the decryption protocol interface is
defined independently of the key share generation interface. The protocol must
implement the `ee.ivxv.key.protocol.DecryptionProtocol` interface::

    public interface DecryptionProtocol {
        ElGamalDecryptionProof decryptMessage(byte[] msg) throws ProtocolException;
    }

The method `decryptMessage()` takes a cryptogram in DER format as input and
returns an `ElGamalDecryptionProof` instance. If the protocol does not support
issuing a decryption proof, the corresponding fields are set to null
(`null`).

Similarly to the key share generation protocol, the protocol parameters must be
set during the initialization of the class instance.

Signing Protocol Interface
--------------------------

In addition to the decryption protocol, a signing protocol can also be
implemented. Similarly to the decryption protocol, a single key generation
method may correspond to multiple signing protocols. The protocol must
implement the `ee.ivxv.key.protocol.SigningProtocol` interface::

    public interface SigningProtocol {
        byte[] sign(byte[] msg) throws ProtocolException;
    }

The method `sign()` takes as input the message to be signed and returns an
RSA-PSS signature with the following parameters:

.. _RSA-PSS parameetrid:

- message hash function: SHA2-256
- mask generation function: MGF1, mask hash function SHA2-256, and mask length
  32 bytes
- salt length: 32 bytes
- trailer byte: `0xbc`

Similarly to the key share generation protocol, the protocol parameters must be
set during the initialization of the class instance.

Supported Protocols
--------------------

Currently, the following key share generation protocols are implemented:

* `ee.ivxv.key.protocol.generation.desmedt.DesmedtGeneration`: Key shares are
  such that it would be possible to use the [DF89]_ distributed
  decryption protocol. Key shares are stored directly on a token supporting
  the PKCS15 interface. The following arguments can be provided during class
  instance initialization:

  + `PKCS15Card[] cards`: an array of objects implementing the PKCS15Card
    interface (e.g., smart cards or software tokens).
  + `ElGamalParameters params`: ElGamal cryptosystem parameters.
  + `ThresholdParameters tparams`: threshold scheme parameters.
  + `Rnd rnd`: randomness input for key share generation
  + `byte[] cardShareAID`: key share access identifier on the PKCS15
    token. Defines which access identifier is used to access the key share.
  + `byte[] cardShareName`: key share identifier on the PKCS15 token.

* `ee.ivxv.key.protocol.generation.shoup.ShoupGeneration`: Key shares are
  such that it would be possible to use a [Shoup00]_-based distributed
  signing protocol. Key shares are stored directly on a token supporting
  the PKCS15 interface. The following arguments can be provided during class
  instance initialization:

  + `PKCS15Card[] cards`: an array of objects implementing the PKCS15Card
    interface (e.g., smart cards or software tokens).
  + `int modLen`: RSA key length in bits
  + `ThresholdParameters tparams`: threshold scheme parameters.
  + `Rnd rnd`: randomness input for key share generation
  + `byte[] cardShareAID`: key share access identifier on the PKCS15
    token. Defines which access identifier is used to access the key share.
  + `byte[] cardShareName`: key share identifier on the PKCS15 token.

The following decryption protocols are implemented:

* `ee.ivxv.key.protocol.decryption.recover.RecoverDecryption`: Key shares are
  read from tokens supporting the PKCS15 interface, the private key is
  reconstructed from them in memory, and decryption with a decryption proof is
  performed. The following arguments can be provided during class instance
  initialization:

  + `PKCS15Card[] cards`: an array of objects implementing the PKCS15Card
    interface (e.g., smart cards or software tokens).
  + `ThresholdParameters tparams`: threshold scheme parameters.
  + `byte[] cardShareAID`: key share access identifier on the PKCS15
    token. Defines which access identifier is used to access the key share.
  + `byte[] cardShareName`: key share identifier on the PKCS15 token.

The following signing protocols are implemented:

* `ee.ivxv.key.protocol.signing.shoup.ShoupSigning`: Key shares are read from
  tokens supporting the PKCS15 interface, signing shares are constructed in
  memory without reconstructing the key, and the signing shares are combined
  into an RSA-PSS signature. The following arguments can be provided during
  class instance initialization:

  + `PKCS15Card[] cards`: an array of objects implementing the PKCS15Card
    interface (e.g., smart cards or software tokens).
  + `ThresholdParameters tparams`: threshold scheme parameters.
  + `Rnd rnd`: randomness input for RSA-PSS signature salt generation.
  + `byte[] cardShareAID`: key share access identifier on the PKCS15
    token. Defines which access identifier is used to access the key share.
  + `byte[] cardShareName`: key share identifier on the PKCS15 token.

Interfacing Protocols with the Key Application
----------------------------------------------

The following description applies to both key share generation and decryption
protocols.

.. note:: The current description is general. Once the configuration and
   argument parsing has been finalized and the protocols have been interfaced
   with the key application, the following section should be updated.

To interface a new protocol with the key application, a class implementing the
corresponding protocol interface must first be created. The key application must
determine at startup, during configuration processing, from either command-line
arguments or the configuration file, which protocol is to be used. Then, using
the corresponding class's static method, a new protocol class instance must be
initialized using the remaining command-line arguments or configuration file.
After that, the key can be generated or the message can be decrypted.

Descriptions of Supported Protocols
------------------------------------

Shamir's Secret Sharing Scheme
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Let us have a secret value :math:`s = a_0` and we wish to share it among
:math:`n` parties such that at least :math:`t` parties can reconstruct the
secret. For this, we choose coefficients :math:`a_1` through :math:`a_{t-1}`
and consider the polynomial in variable :math:`x`:

.. math::
    P(x) = a_{t-1}  x^{t-1} + .. + a_1  x + a_0

Let :math:`x_1` through :math:`x_n` be unique non-zero values (generally
:math:`1` through :math:`n`), in which case we get the shares :math:`s_i =
P(x_i)` and the secret value :math:`s = P(0)`.

Geometrically speaking, :math:`P(x)` is a polynomial and the shares are points
on that polynomial. From elementary mathematics we know that to draw a polynomial
of degree :math:`t-1`, :math:`t` points are sufficient (two points for a line,
three points for a parabola, etc.). The secret value is the value of this
polynomial at the y-axis intercept.

Looking at reconstruction numerically rather than geometrically, we can use the
Lagrange interpolation method. The symbol :math:`\prod` denotes a product of
multiple terms, and the symbol :math:`\sum` denotes a sum of multiple terms.

Now, let us additionally denote the :math:`t` parties participating in the
secret value reconstruction as :math:`U`. The Lagrange interpolation formula
states:

.. math::
    \overline{P}(x) = \sum\limits_{j \in U} s_j \frac{\prod\limits_{i \in U, j \neq i}x-x_i}{\prod\limits_{i \in U, j \neq i}x_j-x_i}

Indeed: let us fix :math:`j` — note that when :math:`x = x_j`, the value of the
fraction is :math:`1` (since the factors in the numerator and denominator cancel
each other out) and when :math:`x \neq x_j`, but :math:`x = x_k`, for some
other :math:`k \in U`, the fraction is :math:`0` (since the numerator contains
:math:`x_k - x_i = 0` for some :math:`i \in U`). Therefore:

.. math::
    \overline{P}(x_j) = s_j + 0 \sum_{i \in U, i \neq j} s_i = s_j = P(x_j)

Since the parties know the values :math:`s_i = P(x_i)` (shares), by combining
and multiplying them with the basis polynomial

.. math::
    L(U,x,j) = \frac{\prod\limits_{i \in U, j \neq i}x - x_i}{\prod\limits_{i \in U, j \neq i}x_j - x_i}

and fixing :math:`x = 0`, we obtain the shared secret.

`ee.ivxv.key.protocol.generation.desmedt.DesmedtGeneration`
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Considering that the ElGamal key parameter is a group :math:`G` with generator
:math:`g`, the private key is chosen as :math:`x`, which is at most
:math:`ord(g)`, i.e., the multiplicative order of :math:`g` in group :math:`G`.
The corresponding public key is the value :math:`y = g^x`. The private key
set becomes the value :math:`(G, g, x)` and the public key set becomes the
value :math:`(G, g, y)`. The group :math:`G` is chosen such that its order is
some prime :math:`p` such that :math:`p = 2  q + 1`, where :math:`q` is also
a prime. In this case, the group :math:`G` is described by the prime :math:`p`.

From algebra we know that if the order of :math:`G` is :math:`2q + 1`, then the
order of every element of this group is either :math:`1`, :math:`2`, :math:`q`,
or :math:`2q`. We are interested in a generator whose order is :math:`q` and
which is a quadratic residue, as it generates a sufficiently large subgroup
whose all elements are quadratic residues. Otherwise, one bit of information
about the encrypted message could leak. To find such a generator, we examine
random elements of the group and check their order and quadratic residuosity
until we find a suitable element. We designate such an element as the generator.

The instance generates a random :math:`0<x<q` as the private key, shares it
among the parties given as arguments using Shamir's secret sharing. Each private
key share is encoded as an unshared private key set.

Then :math:`y = g^x` is computed and the encoded public key set is returned.

`ee.ivxv.key.protocol.generation.shoup.ShoupGeneration`
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The RSA key pair is generated as follows: two primes :math:`p` and :math:`q`
of bit length :math:`\textit{modLen}/2` are generated and :math:`n = pq` is
computed. The public key :math:`e` is chosen such that :math:`\gcd(e, \phi(n))
= 1`, but in this protocol :math:`e` is fixed as :math:`e=65537`. Therefore,
:math:`p` and :math:`q` must be chosen until this condition holds. The private
key :math:`d` is chosen such that :math:`de \equiv 1 \pmod{\phi(n)}`, where
:math:`\phi` is Euler's :math:`\phi`.

The number :math:`\phi(n)` indicates how many of the numbers :math:`1 \leq m <
n` are such that :math:`\gcd(m,n) = 1`, where :math:`\gcd(a,b)` is the greatest
common divisor of two numbers :math:`a` and :math:`b`. It is obvious that if
:math:`p` is a prime, then :math:`\phi(p) = p-1`. Additionally, it is easy to
show that if :math:`p` and :math:`q` are primes, then :math:`\phi(pq) =
\phi(p)\phi(q)`.

Euler's theorem states that if :math:`a` and :math:`n` are coprime, then:

.. math::
    a^{\phi(n)} \equiv 1 \pmod{n}

Therefore, if for signing message :math:`m` we compute :math:`s \equiv m^d
\pmod{n}`, then for verification we check whether :math:`s^e \equiv m
\pmod{n}`. Indeed: :math:`(m^d)^e \equiv m^{de} \equiv m^{k\phi(n)+1} \equiv
m^{k\phi(n)}m \equiv 1^km \equiv m \pmod{n}`.

The private key :math:`d` is split into parts using Shamir's secret sharing,
each part is encoded as an unshared private key component and stored for the
corresponding party. The public key set is encoded and returned.

`ee.ivxv.key.protocol.decryption.recover.RecoverDecryption`
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The protocol works by reconstructing the ElGamal key and decrypting cryptograms
with it.

More precisely, let :math:`U` be the indices of the cards that form the
:math:`\mathit{cards}` variable given as an argument. The instance reads the
private key sets from the cards, verifies the integrity of the key sets (i.e.,
the consistency of the group :math:`G` and generator :math:`g` descriptions),
and decodes the private key :math:`x_i` from each set.

Then the private key :math:`x` is computed using Lagrange interpolation:

.. math::
    x = P(0) = \sum\limits_{j\in U} s_j \frac{\prod\limits_{i\in U, j \neq i} -x_i}{\prod\limits_{i\in U, j \neq i} x_j-x_i}

To decrypt the cryptogram :math:`c=(c_1,c_2)=(my^r,g^r)`, the following is
computed:

.. math::
    d = \frac{c_1}{c_{2}^x}

For the decryption proof, a random :math:`r` is chosen and the following
commitments are constructed:

.. math::
    a = c_{2}^r \\
    b = g^r

Then the Fiat-Shamir challenge is computed as follows, where `H` is the hash
function `SHA2-256` and `B2I` is a method that converts a byte array to an
integer uniformly in the range::

    K = H("DECRYPTION" || y || c || d || a || b)
    k = B2I(K, q)

Now the decryption proof response is computed:

.. math::
    s = kx + r

The complete decryption proof is the set :math:`(a,b,s)`. The return value is
:math:`(d,(a,b,s))`.

`ee.ivxv.key.protocol.signing.shoup.ShoupSigning`
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

In this protocol, key reconstruction does not take place.

Let :math:`U` be the indices of the cards that form the :math:`\mathit{cards}`
variable given as an argument. The class instance reads the private key sets and
verifies their integrity (i.e., the consistency of the modulus and public key).
The key modulus :math:`n` and public key :math:`e` are read into memory.
Additionally, the private keys :math:`d_i` are decoded and read into memory. To
generate a signature for message :math:`m`, EMSA-PSS encoding [RFC8017]_ is
applied to it, using the previously defined `RSA-PSS parameetrid`_, yielding the
message :math:`M` for signing.

We denote by :math:`n!` the factorial of the number :math:`n`, i.e., :math:`n!
= 1 \cdot 2 \cdot 3 \cdot \ldots \cdot n`. Recall that the Lagrange
interpolation basis polynomial was:

.. math::
    L(U,x,j) = \frac{\prod\limits_{i\in U, j \neq i} x-x_i}{\prod\limits_{i\in U, j \neq i} x_j-x_i}

We define the modified Lagrange basis polynomial as follows:

.. math::
    L'(U,x,j) = n! \frac{\prod\limits_{i\in U, j \neq i} x-x_i}{\prod\limits_{i\in U, j \neq i} x_j- x_i}

Since we know that the points :math:`1 \leq x_i,x_j \leq n`, we have
:math:`|x_j-x_i|<n`. Therefore, by multiplying the Lagrange basis polynomial
by :math:`n!`, we get that :math:`L'(U,j)` is always an integer.

.. warning: Since `|k|=|-k|`, in some cases factors from the factorial may
   cancel out, resulting in a fraction. We have experimentally verified all
   cases up to schemes with 15 parties, and no fractions occur. For more
   parties, fractionality must be checked and the protocol modified if
   necessary.

To construct the signature, we compute:

.. math::
    s = \prod\limits_{j\in U} {(M^{x_j})}^{L'(U,0,j)} = M^{\sum\limits_{j\in U} x_j L'(U,0,j)} = M^{n!d}

Since we used modified Lagrange interpolation, compared to a regular RSA
signature, this is raised to the power of :math:`n!`. From Bézout's lemma we
know that for :math:`x` and :math:`y`, there exist :math:`a` and :math:`b` such
that :math:`ax+by=\gcd(x,y)`. Moreover, such values of :math:`a` and :math:`b`
can be found using the extended Euclidean algorithm for finding the greatest
common divisor.

Using the extended Euclidean algorithm, :math:`a` and :math:`b` are found such
that :math:`ae+bn!=\gcd(e,n!)`. Since the public key :math:`e` is a chosen
prime, :math:`\gcd(e,n!)=1`. We compute:

.. math::
    \sigma = M^as^b

Considering that :math:`de = 1 \pmod{\phi(n)}`, this is indeed a correct
signature:

.. math::
    \sigma^e &= M^{ae}s^{be}      \\
             &= M^{ae}M^{n!dbe} \\
             &= M^{ae}M^{n!bde} \\
             &= M^{ae}M^{n!b}     \\
             &= M^{ae+bn!}         \\
             &= M^{\gcd(e,n!)}       \\
             &= M

The protocol instance returns :math:`\sigma` as the signature.
