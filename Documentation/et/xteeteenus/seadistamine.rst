..  IVXV technical documentation

Configuration
=============

The ``xroad-service.json`` file is used to configure the service.

``server.address`` - Server port

``server.batchmaxsize`` - Batch size, recommended size 1000

``server.openapipath`` - OpenAPI file location. Served at https://host/openapi.

``server.tls`` - Server TLS configuration

``xroad.certificate`` - X-Road security server certificate

``elections`` - List of election events

``elections.name`` - Election event name

``elections.address`` - IVXV server address

``elections.servername`` - Queue service SNI

``elections.rootca`` - IVXV CA certificate

``elections.clientcert`` - Client certificate, the client CA must be added to the IVXV configuration

``elections.clientkey`` - Client key

Starting
========

The service does not start automatically, and once "Configuration" is complete, the root user must run `systemctl start xroad-service`.

Stopping
========

If the service goes down for various reasons (machine restart, error conditions, manual stop via `systemctl stop xroad-service`), the "Starting" procedure must be repeated to bring the service back up.
