..  IVXV configuration preparation guide

.. _kt-election:

Preparing election configuration for the collector service
----------------------------------------------------------

The election configuration defines the configuration for a single election.

The election configuration is prepared by the election organizer.
The configuration file name must always end with the string :file:`election.yaml`.
The possible prefix of the file name must always end with a period.

:identifier:

        Required field.
        Unique election identifier.

:questions:

        List containing one or more unique identifiers of election questions.
        Uniqueness must be guaranteed only within the questions of a specific
        election. Required field.

----

:period:

        Required field.
        Sub-block for e-voting period data.

:period.servicestart:

        Required field.
        Start time of vote reception in the collector service. From this moment
        on, the collector service starts to serve connections. This time must
        precede the election start time and is intended for casting a test vote
        before the start of elections.

        For votes received before the time specified by the ``electionstart``
        parameter, a corresponding error message is returned to the voter
        application at the end of vote submission (the vote arrived before the
        start of elections). Such votes are automatically cancelled during
        processing.

:period.electionstart:

        Required field.
        E-voting start time. Votes cast from this moment on are counted in
        vote tallying.

:period.electionstop:

        Required field.
        E-voting end time. From this moment, issuing of choices lists is
        stopped.

:period.servicestop:

        Required field.
        E-voting termination time. From this moment, vote reception is stopped
        and services stop working.

----

:voting:

        Sub-block for vote submission parameters.

:voting.ratelimitstart:

        The number of votes submitted by the voter after which the voting rate
        limit is applied. Invalid votes are also counted, because otherwise they
        could be used to overload the system despite the limit. If the field is
        missing or the value is 0, the limit applies from the first vote.

:voting.ratelimitminutes:

        Time in minutes that must elapse between two vote submissions when the
        voter has a voting rate limit applied. If the field is missing or the
        value is 0, voting rate limits are disabled.

----

:verification:

        Required field.
        Sub-block for vote verification parameters.

:verification.count:

        Required field.
        Maximum number of allowed verifications for a single vote.

:verification.minutes:

        Required field.
        Duration of the vote verification period in minutes. After casting
        a vote, it can be verified during this period.

:verification.latestonly:

        Boolean value indicating whether only the voter's most recently cast
        vote can be verified. If the value is false or missing, all of the
        voter's votes can be verified (within other restrictions).

----

:voterforeignehak:

        EHAK code used for determining district affiliation of voters
        permanently residing abroad.

        If the parameter is set, voters permanently residing abroad belong to
        the districts to which the administrative unit corresponding to the
        EHAK code specified in the parameter also belongs. Additionally, the
        districts list must contain an administrative unit with such an EHAK
        code.

        If the parameter is not set, the EHAK code "0000" is used. If the
        parameter is not set and the districts list does not contain an
        administrative unit corresponding to the default code, then the voter
        list must not contain voters permanently residing abroad.

:ignorevoterlist:

        District identifier whose choices are to be presented to all voters.
        If this value is not empty, the collector service does not use the
        voter list and presents the choices of the district specified by the
        value to all voters and allows voting for everyone who passes identity
        verification and vote signature verification.

----

:voterlist:

        Required field.
        Voter list verification parameters.

:voterlist.key:

        Required field.
        ECDSA key pair public key for verifying voter list signatures.

:vis:
        Sub-block containing the Election Information System configuration.

:vis.url:

        Required field.
        Election Information System URL.

:vis.ca:

        Election Information System TLS certificate trust chain.

:vis.min:

        Election Information System voter list acquisition frequency in
        minutes (default value is 15).

:xroad:
        Sub-block containing the X-Road connected service configuration.

:xroad.ca:

        X-Road service TLS certificate trust chain.

----

:ballot:
        Sub-block containing ballot verification configuration.

:ballot.encpkeygroup:

Required field.
        Abstract group to which the public key generated in the Key Application
        for encrypting votes belongs.

        Possible values ``RFC3526ModPGroup2048`` (key length is 2048 bits or
        256 bytes), ``RFC3526ModPGroup3072``, ``RFC3526ModPGroup4096``,
        ``RFC3526ModPGroup8192``, ``NIST-P256``, ``NIST-P384``, ``NIST-P521`` and
        ``Edwards25519``. NB! Please ensure that the selected group from the list
        was also used during public key generation in the Key Application (see the
        Key Application configuration file).

This group is used for verifying the correctness of encrypted votes.

        This field is ignored if `encpkey` is set.

:ballot.encpkey:

        Public key for encrypting votes in the voter application.

        The key group is used for verifying the correctness of encrypted votes.

----

:auth:

        Required field.
        Sub-block containing voter identification configuration.

:auth.ticket:

        Sub-block containing ticket-based voter identification configuration.

        Ticket-based voter identification is used for Mobile-ID/Smart-ID/Web eID,
        where the ``mid``/``smartid``/``webeid`` service identifies the voter and
        issues them a ticket to identify themselves to other services.

        This sub-block is empty, but its presence or absence determines whether
        ticket-based voter identification is allowed or not.

:auth.tls:

        Sub-block containing TLS-based voter identification configuration.

        TLS-based voter identification is used for ID cards.

:auth.tls.roots:

        Required field.
        Voter TLS client certificate trust roots.

:auth.tls.intermediates:

        Voter TLS client certificate intermediate certificates. For TLS
        authentication, it must be possible to build a chain from the voter's
        client certificate to the trust root using these certificates.

:auth.tls.ocsp:

        Sub-block containing voter TLS client certificate status verification
        configuration. If this block is missing, the validity of voter
        certificates is not verified from an external validity confirmation
        service.

:auth.tls.ocsp.url:

        Voter TLS client certificate validity confirmation service address.
        If not configured, the validity confirmation service address is used
        directly from the TLS client certificate.

:auth.tls.ocsp.responders:

        Voter TLS client certificate validity confirmation service OCSP
        responder certificates. If a responder certificate is not found among
        them, a certificate issued by the same issuer as the certificate being
        verified and authorized for signing OCSP responses is searched for
        among the certificates in the response.

:auth.tls.ocsp.retry:

        Voter TLS client certificate status verification retry count. If the
        certificate status verification fails due to a network or server error,
        it can be automatically retried. The field value specifies the number of
        attempts made in addition to the initial request. Therefore, if the
        value is 1, a maximum of two requests are made in total. If the field
        is missing or the value is 0, no automatic retries are performed.

----

:identity:

        Method for deriving a unique identifier from the identified voter's
        X.500 distinguished name. Currently supported options are ``commonname``,
        ``serialnumber`` and ``pnoee``.

        For Estonian electronic identity documents, with ``commonname`` the
        identifier is in the form "LASTNAME,FIRSTNAME,PERSONALCODE" and with
        the other options it is "PERSONALCODE".

        While ``serialnumber`` returns the ``serialNumber`` field from the
        distinguished name unchanged, ``pnoee`` first removes the non-mandatory
        "PNOEE-" prefix from it. The latter is in accordance with standard
        ETSI EN 319 412-1 section 5.1.3 for Estonian personal identification
        codes, but also allows serial numbers that do not conform to the
        standard.


----

:age:

        Sub-block containing voter age verification configuration. If this
        block is missing, the voter's age is not verified.

:age.method:

        Required field.
        Method used for determining the voter's date of birth. Currently only
        ``estpic`` is supported, which assumes that the voter's unique
        identifier is an Estonian personal identification code and extracts
        the date of birth from it.

:age.timezone:

        Required field.
        IANA time zone name in which the voter's age is calculated, i.e., in
        which time zone the voter must be of voting age.

:age.limit:

        Required field.
        The voter must be at least this old to vote. If the value is 0,
        the voter's age is not verified.

----

:vote:

        Required field.
        Sub-block containing vote signature verification configuration.

:vote.bdoc:

        Sub-block containing vote BDOC signature verification configuration.

:vote.bdoc.filecount:

        Required field. Maximum allowed number of files in the ZIP container,
        and since this is a BDOC container, 3 must always be added to this
        value, because the BDOC container contains ``signatures0.xml``,
        ``manifest.xml`` and ``mimetype`` files in addition to content files.
        A suitable value for this parameter is 4 (vote + 3 additional files).

:vote.bdoc.bdocsize:

        Required field.
        Maximum allowed size of the BDOC container in bytes.

:vote.bdoc.filesize:

        Required field.
        Maximum allowed decompressed size of files in the BDOC container
        in bytes.

:vote.bdoc.roots:

        Required field.
        Vote signer certificate trust roots.

:vote.bdoc.intermediates:

        Vote signer certificate intermediate certificates.
        For the vote to be counted, it must be possible to build a chain from
        the signer's certificate to the trust root using these certificates.

:vote.bdoc.profile:

        Required field.
        Required BDOC profile for vote signatures. Supported options are ``BES``
        (basic profile described in BDOC specification section 5) and
        ``TS`` (timestamp profile described in BDOC specification
        section 6.2).

        This should be ``BES``, because for all signing instruments the
        incoming vote is not qualified (e.g., Estonian ID card). The collector
        service qualifies the signatures on votes itself (see ``qualification``).

----

:mid:

        Sub-block containing Mobile-ID service provider configuration.

:mid.url:

        Required field.
        Mobile-ID service provider location.

:mid.relyingpartyuuid:

        Required field.
        Client identifier agreed upon with the Mobile-ID service provider.

:mid.relyingpartyname:

        Required field.
        Client name agreed upon with the Mobile-ID service provider.

:mid.language:

        Required field.
        Language of messages displayed to the Mobile-ID user. Possible values
        ``EST``, ``ENG``, ``RUS`` and ``LIT``.

:mid.authmessage:

        Required field.
        Message to display to the Mobile-ID user during authentication.

:mid.signmessage:

        Required field.
        Message to display to the Mobile-ID user during signing.

:mid.messageformat:

        Format of the message displayed to the user during authentication and
        signing. Possible values ``GSM-7`` (default value used by Mobile-ID)
        and ``UCS-2``.

:mid.authchallengesize:

        Challenge length sent to the Mobile-ID service during authentication.
        Possible values ``32`` (default), ``48`` and ``64``.

:mid.statustimeoutms:

        Parameter that is forwarded to the Mobile-ID service during
        authentication and signing status requests, which controls how long
        the Mobile-ID service waits for the end result of the user's action
        before responding that the action is in progress. If the value is
        missing, the wait is as short as possible: the exact time depends on
        the Mobile-ID service.

        This parameter can be used to reduce the number of requests sent to the
        Mobile-ID service during a single authentication or signing operation.

:mid.roots:

        Required field.
        Mobile-ID certificate trust roots.

:mid.intermediates:

        Mobile-ID certificate intermediate certificates. For Mobile-ID
        authentication, it must be possible to build a chain from the Mobile-ID
        certificate to the trust root using these certificates.

:mid.ocsp:

        Sub-block containing voter Mobile-ID certificate status verification
        configuration.

:mid.ocsp.url:

        Voter Mobile-ID certificate validity confirmation service address.
        If not configured, the validity confirmation service address is used
        directly from the Mobile-ID client certificate.

:mid.ocsp.responders:

        Mobile-ID certificate OCSP responder certificates. If a responder
        certificate is not found among them, a certificate issued by the same
        issuer as the certificate being verified and authorized for signing
        OCSP responses is searched for among the certificates in the response.

----

:smartid:

        Sub-block containing Smart-ID service provider configuration.

:smartid.url:

        Required field.
        Smart-ID service provider location.

:smartid.relyingpartyuuid:

        Required field.
        Client identifier agreed upon with the Smart-ID service provider.

:smartid.relyingpartyname:

        Required field.
        Client name agreed upon with the Smart-ID service provider.

:smartid.authinteractionsorder:

        Required field.
        Order of interactions displayed to the Smart-ID user during authentication.
        The first interaction supported by the application is selected from the order.
        Possible  values: ``displayTextAndPIN`` with ``displayText60``,
        ``verificationCodeChoice`` with ``displayText60``,
        ``confirmationMessage`` with ``displayText200`` or
        ``confirmationMessageAndVerificationCodeChoice`` with ``displayText200``.

:smartid.signinteractionsorder:

        Required field.
        Order of interactions displayed to the Smart-ID user during signing.
        The first interaction supported by the application is selected from the order.
        Possible  values: ``displayTextAndPIN`` with ``displayText60``,
        ``verificationCodeChoice`` with ``displayText60``,
        ``confirmationMessage`` with ``displayText200`` or
        ``confirmationMessageAndVerificationCodeChoice`` with ``displayText200``.

:smartid.authchallengesize:

        Challenge length sent to the Smart-ID service during authentication.
        Possible values ``32`` (default), ``48`` and ``64``.

:smartid.statustimeoutms:

        Parameter forwarded to the Smart-ID service during authentication and
        signing status requests, which controls how long the Smart-ID service
        waits for the end result of the user's action before responding that
        the action is in progress.
        If the value is missing, the wait is as short as possible: the exact
        time depends on the Smart-ID service.

        This parameter helps reduce the number of requests sent to the Smart-ID
        service during authentication or signing.

:smartid.roots:

        Required field.
        Smart-ID certificate trust roots.

:smartid.intermediates:

        Smart-ID certificate intermediate certificates. For Smart-ID
        authentication, it must be possible to build a chain from the Smart-ID
        certificate to the trust root using these certificates.

:smartid.ocsp:

        Sub-block containing voter Smart-ID certificate status verification
        configuration.

:smartid.ocsp.url:

        Voter Smart-ID certificate validity confirmation service address.
        If not configured, the validity confirmation service address is used
        directly from the Smart-ID client certificate.

:smartid.ocsp.responders:

        Smart-ID certificate OCSP responder certificates. If a responder
        certificate is not found among them, a certificate that is
        1) issued by the same issuer as the certificate being verified;
        and
        2) authorized for signing OCSP responses
        is searched for among the certificates in the response.

----

:qualification:

        List of external qualifying requests made for each vote, together
        with their configurations.

        A list of protocol and configuration blocks is used here instead of
        giving each protocol its own block, because the order of qualifying
        requests is important and configurable.

:qualification.*.protocol:

        Required field.
        Qualifying request protocol. Currently supported are ``ocsp``
        (standard OCSP), ``tsp`` (PKIX timestamp) and ``tspreg`` (PKIX
        timestamp as a registration proof).

:qualification.*.conf:

        Required field.
        Qualifying request protocol configuration. The content depends on
        the value of the ``qualification.*.protocol`` parameter.

:qualification.*.conf.url:

        Optional field only for ``ocsp``, because if not configured, the
        validity confirmation service address is used directly from the client
        certificate. Address to which the qualifying request is made.

:qualification.*.conf.responders:

        Used only when ``qualification.*.protocol`` is ``ocsp``.

        OCSP responder certificates. If a responder certificate is not found
        among them, a certificate issued by the same issuer as the certificate
        being verified and authorized for signing OCSP responses is searched
        for among the certificates in the response. When using AIA logic, this
        field may be left empty.

:qualification.*.conf.signers:

        Required field.
        Used only when ``qualification.*.protocol`` is ``tsp``
        or ``tspreg``.

        Timestamp service response signing certificates.

:qualification.*.conf.delaytime:

        Required field.
        Used only when ``qualification.*.protocol`` is ``tsp``
        or ``tspreg``.

        Maximum time offset between timestamp creation and signing in seconds.

:qualification.*.conf.retry:

        Qualifying request retry count. If the request fails due to a network
        or server error, it can be automatically retried. The field value
        specifies the number of attempts made in addition to the initial
        request. Therefore, if the value is 1, a maximum of two requests are
        made in total. If the field is missing or the value is 0, no automatic
        retries are performed.

Example
*******

:file:`example.election.yaml`:

.. literalinclude:: config-examples/example.election.yaml
   :language: yaml
   :linenos:

.. vim:syntax=rst:
