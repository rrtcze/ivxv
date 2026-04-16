..  IVXV collector service management service description

.. _kontroll:

Verification Application Configuration
=======================================

The verification application configuration is in JSON format.

The actual content of the two configurations may be identical even when
different URLs are proactively used to anticipate possible differences.
Previously, the use of different URLs has been justified by, e.g., the longer
delivery cycle of iOS applications, which requires publishing test
configurations.

The configuration consists of five main groups

* :token:`versions` - Required application version
* :token:`texts` - Texts used in the user interface
* :token:`errors` - Error messages used in the user interface
* :token:`colors` - User interface color codes
* :token:`params` - Parameters required for application operation
* :token:`elections` - Text corresponding to each question identifier in
  the user interface

All configurable values can be seen in the example configuration. All values
are mandatory.

Version Configuration
---------------------

The verification application version must be greater than or equal to the
version specified in the configuration. Versions belong to the group :token:`versions`:

* :token:`android_version_code` - Minimum version code for the Android application.
  The value must be a positive JSON integer.
* :token:`ios_bundle_version` - Minimum version string for the iOS application. The
  value must be a JSON string consisting of positive integers separated by dots.

Parameter Configuration
-----------------------

Parameters required for application operation belong to the group :token:`params`:

* :token:`verification_url` - List of collector service hostnames
  or IP addresses with port. Order is not important. The value
  must be a JSON list even for a single URL.
* :token:`verification_tls` - List of collector service TLS
  certificates in PEM format. Order is not important. The value must
  be a JSON list even for a single certificate.
* :token:`help_url` - Help information view URL
* :token:`close_timeout` - Time window during which the user can see
  their choice before the application closes. In milliseconds.
* :token:`close_interval` - Interval at which the
  :token:`close_timeout` value is updated in the user interface. In milliseconds.
* :token:`con_timeout_1` - Timeout for the first connection attempt
  to the collector service. In milliseconds.
* :token:`con_timeout_2` - If no connection was established with any
  collector service instance in the first round, retry with this
  timeout. In milliseconds.
* :token:`public_key` - Election public key used to encrypt
  voters' ballots. In PEM format.
* :token:`tspreg_service_cert` - Time-stamping service certificate in PEM
  format.
* :token:`ocsp_service_cert` - OCSP service certificates in PEM
  format. Order is not important. The value must be a JSON list even
  for a single value. If the field is empty, the OCSP
  responder certificate is detected automatically.
* :token:`tspreg_client_cert` - Collector service certificate
  for making registration requests in PEM format.

Text Configuration
------------------

Texts used in the user interface belong to the group :token:`texts`. The following
texts are parameterizable:

* :token:`lbl_close_timeout` - Verification application closing message with
  counter. The text must contain the marker XX, which is automatically replaced
  with the time remaining until the application closes in seconds.

Example
-------

.. literalinclude:: config-examples/android-ios-config.json
   :language: json
