..  IVXV collector service management service description

.. _kt-trust:

Collector service trust root configuration
-------------------------------------------

The collector service trust root contains data for verifying signatures of
configurations (including the trust root itself) and a list of the system's
initial authorizations.

The trust root configuration is prepared by the election organizer.
The configuration file name must always end with the string :file:`trust.yaml`.
The possible prefix of the file name must always end with a period.

.. attention::

   Loading the trust root configuration resets the collector service. Therefore,
   changing the trust chain of an already configured collector service is not
   possible. Changing authorizations is possible using the corresponding commands.

:container:

        Required field.
        Sub-block that contains the configuration for verifying signatures of
        configuration files.

:container.bdoc:

        Sub-block that contains the configuration for verifying BDOC signatures
        of configuration files.

:container.bdoc.filecount:
        Required field. Maximum allowed number of files in the ZIP container, and
        since it is a BDOC container, the value 3 must always be added to this value,
        because the BDOC container contains, in addition to content files, the
        ``signatures0.xml``, ``manifest.xml``, and ``mimetype`` files.

:container.bdoc.bdocsize:
        Required field.
        Maximum allowed size of the BDOC container in bytes.

:container.bdoc.filesize:
        Required field.
        Maximum allowed decompressed size of files in the BDOC container
        in bytes.

:container.bdoc.roots:

        Required field.
        Trust roots of the signer certificates of configurations.

:container.bdoc.intermediates:

        Intermediate certificates of the signer certificates of configurations.
        To establish trust, it must be possible to create a chain from the signer
        certificate to the trust root using these certificates.

:container.bdoc.profile:

        Required field.
        Required BDOC profile for configuration signatures. Supported options are
        ``BES`` (basic profile described in BDOC specification section 5),
        ``TS`` (timestamp profile described in BDOC
        specification section 6.2).

:container.bdoc.ocsp.responders:

        Used only when ``container.bdoc.profile`` is ``TS``.

        OCSP responder certificates that issued validity confirmations. If the
        responder certificate is not found among these, then a certificate is
        searched from the certificates in the OCSP response that was issued by
        the same issuer as the configuration signer certificate and is
        authorized for signing OCSP responses. When using AIA logic,
        this field may be empty.

:container.bdoc.tsp.signers:

        Required field.
        Used only when ``container.bdoc.profile`` is ``TS``.

        Timestamp service response signing certificates.

:container.bdoc.tsp.delaytime:

        Required field.
        Used only when ``container.bdoc.profile`` is ``TS``.

        Maximum time offset between timestamp creation and signing
        in seconds.

:container.bdoc.tsdelaytime:

        Used only when ``container.bdoc.profile`` is ``TS``.

        Maximum time offset between timestamp and validity confirmation creation
        in seconds. If the field is missing or the value is 0, both must have
        been created in the same second.

:authorizations:

        Required field.
        Initial list of persons with collector service administrator
        authorizations (see :ref:`rollid`), which is applied to the system when
        loading the trust root. Each person has an entry with the value of their
        ID card ``Common Name`` (CN) field. Must contain at minimum the data of
        the person who signed the trust root.


Example
*******

:file:`example.trust.yaml`:

.. literalinclude:: config-examples/example.trust.yaml
   :language: yaml
   :linenos:
