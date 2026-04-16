..  IVXV configuration preparation guide

.. _kt-krypto:

Collector service cryptographic keys
-------------------------------------

To secure the collector service data exchange, a set of cryptographic keys
must be created. The composition of the set depends on the technical
configuration of the collector service.

#. Service cryptographic key and TLS certificate - used to secure inter-service
   communication for all services except the proxy service;

#. Voting service timestamp request signing key - used to sign timestamp
   requests if the timestamp service is used as the registration service;

#. Mobile-ID/Smart-ID/Web eID support service shared encryption secret – used for symmetric
   AES-256 encryption. With the encryption secret, the Mobile-ID support service encrypts
   the identity token issued to the voter, which the voter uses to prove their
   identity to other services.



Generation of service cryptographic key and TLS certificate
***********************************************************

The service cryptographic key and TLS certificate are generated for all services
except the proxy service. All service certificates must be issued by the same
certification authority (CA – *Certificate Authority*).


Generation of CA certificate
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The certification authority cryptographic key and certificate are generated
with the following command:

.. code-block:: shell-session

   $ openssl req -newkey ec -pkeyopt ec_paramgen_curve:P-256 -x509 -nodes
     -days 365 -out ca.pem -keyout ca.key -utf8
     -subj "/C=EE/O=Example/OU=IVXV Test Certificates/CN=Service CA"

The command output is the files :file:`ca.key` (key) and :file:`ca.pem` (certificate).


Generation of service instance cryptographic key and TLS certificate
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The service instance cryptographic key and certificate request are generated
with the following command:

.. code-block:: shell-session

   $ openssl req -newkey ec -pkeyopt ec_paramgen_curve:P-256 -nodes
     -out <teenuse-id>-tls.csr -keyout <teenuse-id>-tls.key -utf8
     -subj "/C=EE/O=Example/OU=IVXV Test Certificates/CN=<teenuse-id>"

The command output is the files :file:`<teenuse-id>-tls.key` (key) and
:file:`<teenuse-id>-tls.csr` (certificate request).

.. attention::

   For the storage service, the CN value in the certificate request must be
   the hostname instead of the service identifier: unlike other services,
   the storage service does not use an alternative TLS name.

The service instance TLS certificate is generated with the following command:

.. code-block:: shell-session

   $ openssl x509 -req -days 365 -CA ca.pem -CAkey ca.key -set_serial 1
     -extfile service-cert-openssl.cnf -extensions ext_<teenuse-tüüp>
     -in <teenuse-id>-tls.csr -out <teenuse-id>-tls.pem

The command output is the file :file:`<teenuse-id>-tls.pem`.

To generate the certificate, the configuration file
:file:`service-cert-openssl.cnf` must exist in the filesystem.

.. literalinclude:: ../../../tests/testdata/testca/service/service-cert-openssl.cnf
   :caption: File ``service-cert-openssl.cnf``
   :language: ini


Generation of voting service timestamp request signing key and certificate
**************************************************************************

The voting service registration request key is generated with the following
command:

.. code-block:: shell-session

   $ openssl genrsa -out tspreg.key 2048

The command output is the file :file:`tspreg.key`.

The voting service registration request key certificate is generated with
the following command:

.. code-block:: shell-session

   $ openssl req -x509 -nodes -days 365 -out tspreg.pem -key tspreg.key -utf8
     -subj "/C=EE/O=Example/OU=IVXV Test Certificates/CN=Collector Registration"

The command output is the file :file:`tspreg.pem`.

.. note::

   The voting service timestamp request signing key needs to be generated
   only if the timestamp service is used as the registration service.


Generation of Mobile-ID/Smart-ID/Web eID support service shared encryption secret
*********************************************************************************

The shared encryption secret is generated with the following command:

.. code-block:: shell-session

   $ openssl rand -out mobid-shared-secret.key 32

The command output is a 32-byte file :file:`mobid-shared-secret.key`, which
the Mobile-ID, Smart-ID, and Web eID services will use for symmetric AES-256
encryption.

.. note::

   The Mobile-ID/Smart-ID/Web eID support service shared encryption secret needs to be
   generated only if the Mobile-ID, Smart-ID, or Web eID support service is in use.

.. vim:syntax=rst:
