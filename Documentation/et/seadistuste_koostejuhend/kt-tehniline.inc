..  IVXV configuration preparation guide

.. _kt-technical:

Preparing the collector service technical configuration
-------------------------------------------------------

The technical configuration defines the technical parameters of the collector
service. The same technical configuration should be usable with different
election configurations [#]_.

.. [#] But not simultaneously: the collector service supports only one election.

The technical configuration is prepared by the collector service provider.

The configuration file name must always end with the string :file:`technical.yaml`.
The possible prefix of the file name must always end with a period.

:debug:
        Boolean value, whether debug messages are written to logs.

:snidomain:
        Required field.
        Domain used for configuring the SNI value of services.
        Previously the value `ivxv.invalid` has been used, but real domains
        whose name management is under the organizer's control can also be
        used, e.g. `ivxv.ee`

----

:filter:
        Required field.
        Sub-block containing connection filter settings.

:filter.tls:
        Required field.
        Sub-block containing connection TLS filter settings.

:filter.tls.handshaketimeout:
        Required field.
        Maximum time in seconds for performing the TLS handshake.

:filter.tls.ciphersuites:
        Required field.
        Cipher suites allowed for TLS protocol version 1.2.
        Currently supported options are::

            TLS_RSA_WITH_AES_128_CBC_SHA
            TLS_RSA_WITH_AES_256_CBC_SHA
            TLS_RSA_WITH_AES_128_GCM_SHA256
            TLS_RSA_WITH_AES_256_GCM_SHA384
            TLS_ECDHE_ECDSA_WITH_AES_128_CBC_SHA
            TLS_ECDHE_ECDSA_WITH_AES_256_CBC_SHA
            TLS_ECDHE_RSA_WITH_AES_128_CBC_SHA
            TLS_ECDHE_RSA_WITH_AES_256_CBC_SHA
            TLS_ECDHE_RSA_WITH_AES_128_GCM_SHA256
            TLS_ECDHE_ECDSA_WITH_AES_128_GCM_SHA256
            TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384
            TLS_ECDHE_ECDSA_WITH_AES_256_GCM_SHA384

        If TLS protocol version 1.3 is negotiated during the TLS handshake,
        the cipher suite cannot be configured and all secure ciphers supported
        by the server are allowed. Currently these are::

            TLS_AES_128_GCM_SHA256
            TLS_AES_256_GCM_SHA384
            TLS_CHACHA20_POLY1305_SHA256

:filter.codec:
        Required field.
        Sub-block containing connection codec filter settings.

:filter.codec.rwtimeout:
        Required field.
        Maximum time in seconds for reading a complete request from the voter.
        Maximum time in seconds for writing a complete response to the voter.

:filter.codec.requestsize:
        Maximum request size in bytes. If the field is missing or the value
        is 0, the request size is not limited.

:filter.codec.logrequests:
        Boolean value, whether all incoming requests are written to logs
        in original form. The request log is stored separately from the
        regular log.

----

:network:
        Required field.
        List of collector service network segments.

        All collector service network segment parameters are defined by the collector service provider.

:network.*.id:
        Required field.
        Network segment identifier.

:network.*.services:
        Required field.
        Sub-block containing the microservice configuration for this
        network segment of the collector service.

        .. todo:: Although all parameters in this block are defined by the
                Collector, should the Organizer at least confirm the external
                addresses of proxy services, since these are the endpoints
                that the voter and verification applications must connect to?

:network.*.services.proxy:
        List containing proxy service instance configuration.

:network.*.services.mid:
        List containing Mobile-ID support service instance configuration.

:network.*.services.smartid:
        List containing Smart-ID support service instance configuration.

:network.*.services.webeid:
        List containing Web eID support service instance configuration.

:network.*.services.sessionstatus:
        List containing Session status support service instance configuration.

:network.*.services.choices:
        List containing choices service instance configuration.

:network.*.services.voting:
        List containing voting service instance configuration.

:network.*.services.verification:
        List containing verification service instance configuration.

:network.*.services.storage:
        List containing storage service instance configuration.

:network.*.services.log:
        List containing log collection service instance configuration.

:network.*.services.backup:
        Backup service instance configuration.

:network.*.services.*.id:
        Required field.
        Microservice instance identifier.

:network.*.services.*.address:
        Required field.
        Microservice instance network address and port.

        .. todo:: The same parameter is used to describe both which address
                the service should listen on and from which address the
                management service and proxy service can access the service.
                If internal and external addresses start to differ, this
                parameter needs to be split into two.

:network.*.services.*.peeraddress:
        Microservice inter-instance communication network address and port.
        Used only when instances providing the same service need to
        communicate with each other (e.g. storage service).

        .. todo:: The same parameter is used to describe both which address
                the service should listen on and from which address other
                instances can access the service. If internal and external
                addresses start to differ, this parameter needs to be split
                into two.

:network.*.services.*.origin:
        Required field.
        Microservice instance fully qualified domain name and port.

----

:status:
        Required field.
        Sub-block containing a list of status reporting servers.

:status.name:
        Required field. Currently only ``session`` is supported.

        Name of the status reporting server.

:status.servername:
        Required field.
        SNI of the status reporting server.

:status.authttl:
        Required field.
        Time in seconds. Default value 0.

        Maximum time for authentication.

:status.choicettl:
        Required field.
        Time in seconds. Default value 0.

        Maximum time for making a choice.

:status.votettl:
        Required field.
        Time in seconds. Default value 0.

        Maximum time for casting a vote.

:status.verifyttl:
        Required field.
        Time in seconds. Default value 0.

        Maximum time for vote verification.

----

:logging:
        Sub-block containing a list of microservice remote logging servers.
        This block describes:

        * Log monitoring service. Always the first in the list. IVXV log
          starting from the INFO level is sent to this service;

        * If needed, additional external log collectors, to which the
          complete log starting from the DEBUG level is sent.

        Logging is performed over the RELP protocol.

        All log server parameters are defined by the collector service provider.

:logging.address:
        Required field.
        Log server address (IP address or hostname).

:logging.port:
        Log server port (integer, default *20514*).

----

:storage:
        Required field.
        Sub-block containing storage protocol configuration.

        All storage protocol parameters are defined by the collector service provider.

:storage.protocol:
        Required field.
        Collector service storage protocol. Currently only ``etcd`` is supported.

:storage.conf:
        Required field.
        Storage protocol configuration. Contents depend on the value of the
        ``storage.protocol`` parameter.

:storage.conf.ca:
        Required field.
        Used only when ``storage.protocol`` is ``etcd``.

        CA certificate of the storage service TLS certificates.

:storage.conf.conntimeout:
        Required field.
        Used only when ``storage.protocol`` is ``etcd``.

        Maximum time in seconds for establishing a connection with the etcd server.

:storage.conf.optimeout:
        Required field.
        Used only when ``storage.protocol`` is ``etcd``.

        Maximum time in seconds for performing a single storage operation.

:storage.conf.size:
        Optional field.
        Used only when ``storage.protocol`` is ``etcd``.

        Database size in bytes.

:storage.conf.electiontimeout:
        Optional field.
        Used only when ``storage.protocol`` is ``etcd``.

        Time in milliseconds used for checking leader availability.

:storage.conf.heartbeattimeout:
        Optional field.
        Used only when ``storage.protocol`` is ``etcd``.

        Time in milliseconds used for checking database host availability.

:storage.conf.snapshotcount:
        Optional field.
        Used only when ``storage.protocol`` is ``etcd``.

        Number of database storage requests after which the database state
        is backed up.

:storage.conf.bootstrap:
        Required field.
        Used only when ``storage.protocol`` is ``etcd``.

        List of storage service identifiers that are part of the initial
        etcd cluster. Necessary so that the storage service instance knows
        at first startup whether it is creating a new cluster or joining
        an existing one.

        In the initial technical configuration, the list must match the
        storage service identifiers listed in the ``network`` block. When
        later adding or removing services, the ``storage.conf.bootstrap``
        value must not be updated.

:storage.ordertimeout:
         Time in seconds. Default value 5.

         Maximum time for writing a vote to the vote ordering table.

----

:backup:
        Backup parameters.

        List of backup times in the format HH:MM.

:file:`example.technical.yaml`:

.. literalinclude:: config-examples/example.technical.yaml
   :language: yaml
   :linenos:

.. vim:syntax=rst:
