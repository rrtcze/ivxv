..  IVXV collector service management service description

.. _app-processor:

Processing Application
======================

The processing application is a command-line application for verifying and further
processing the e-ballot box after the end of e-voting.

The main tools of the processing application are *check*, *squash*, *revoke* and
*anonymize*, which are executed in the listed order according to the prescribed
election procedures.
The input of the main tools always includes either the e-ballot box issued by the
collector service or the previous tool, and the digitally signed hash of the e-ballot box.
The output includes the e-ballot box resulting from the processing stage along with an
unsigned hash. Since applications are run on a computer without internet connection,
the hash files must be transferred to an external device for digital signing.
The e-ballot box hash is calculated using the function ``hex(sha256(<file>))``.

In addition to the main tools, the application has four additional tools:
*export*, *verify*, *stats* and *statsdiff*.

All tools require the presence of a signed trust root and the specific
tool's configuration.
For tools that produce output files, the output directory location must be specified
in the configuration. The output directory must not exist at the time of execution;
it is created by the application.
Below are descriptions of the tool configurations.

.. _processor-check:

E-ballot Box Processing - Verification
--------------------------------------

The *check* tool is used to verify the e-ballot box issued from the collector service.
The ballot box is verified against the trust root, voter lists, districts list,
and the registration service output.

During verification, the following main properties are checked:

* Data integrity and consistency of the districts list and voter lists;

* Data integrity of the e-ballot box;

* Voting eligibility of e-voters, i.e., inclusion in the voter list (checked
  if voter lists are described in the configuration);

* Compliance of votes contained in the e-ballot box with the digital signature format;

* Data integrity of registration data;

* Compliance of votes contained in the e-ballot box with registration data.

E-ballot box verification is a resource-intensive process. A computer with a 4-core
*i7* processor can process approximately 200 votes per second. During processing,
a progress bar is displayed to the user, based on which it is possible to estimate
the processing time.

:check.ballotbox:
        E-ballot box issued from the collector service.

:check.ballotbox_checksum:
        Digitally signed hash of the e-ballot box issued from the collector service.

        If not specified, the corrected e-ballot box is not output for subsequent
        stages. Useful for election-time verification of a non-final e-ballot box.

:check.signed_ballot_max_size_bytes:
        Maximum allowed size in bytes of a single signed vote in the e-ballot box
        issued from the collector service.

        If not specified, the default of 32768 bytes is used.

:check.districts:
        Digitally signed districts list.

:check.registrationlist:
        Registration data from the registration service. If not specified,
        compliance of votes contained in the e-ballot box with registration
        data is not checked.

:check.registrationlist_checksum:
        Digitally signed hash of the registration data. May be absent
        if ``registrationlist`` is absent.

:check.tskey:
        Collector service public key from the registration request certificate
        used for verifying registration requests.

:check.vlkey:
        Public key used for verifying voter lists.
        The argument is mandatory if voter lists are provided.

:check.voterlists_dir:
        Voter lists directory. If not specified, the voting eligibility of
        e-voters is not checked.

:check.voterlists:
        Voter lists. If not specified, the voting eligibility of
        e-voters is not checked.

:check.voterlists.path:
        Voter list file.

:check.voterlists.signature:
        Voter list signature, given with the algorithm
        ``ecdsa-with-SHA256``.

:check.districts_mapping:
        District and polling station mapping file for the voter list
        (optional).

:check.election_start:
        Voting start time. Votes with a voting time earlier than this are
        treated as test votes and are not sent for tallying.

:check.voterforeignehak:
        EHAK code used for determining district membership of voters
        permanently residing abroad. Default value "0000".

:check.out:
        Tool output directory. The following are created in this directory:

        #. E-ballot box corrected with integrity check :file:`<election id>-bb-1.json`;

        #. Hash of e-ballot box corrected with integrity check
           :file:`<election id>-bb-1.json.sha256sum`;

        #. E-ballot box processing errors report :file:`ballotbox_errors.txt`;

        #. Voter lists processing errors report
           :file:`voterlist_errors.txt`;

        #. *Log1* file, i.e., accepted votes
           :file:`<election id>.<question id>.check.log1`.

:file:`processor.check.yaml`:

.. literalinclude:: config-examples/processor.check.yaml
   :language: yaml
   :linenos:

.. _processor-squash:

E-ballot Box Processing - Repeat Vote Cancellation
---------------------------------------------------

The *squash* tool is used to cancel repeat e-votes.
The input for the tool is the e-ballot box prepared by the *check* tool.
During repeat vote cancellation, each voter's most recent vote is kept and
all earlier votes are removed.

:squash.ballotbox:
        E-ballot box corrected with integrity check.

:squash.ballotbox_checksum:
        Digitally signed hash of the e-ballot box corrected with integrity check.

:squash.districts:
        Digitally signed districts list.

:squash.enckey:
        Location of the encryption public key file (key application output).
        The key is used for pre-checking encrypted votes, to distinguish
        genuinely encrypted votes from arbitrary binary garbage.

:squash.out:
        Tool output directory. The following are created in this directory:

        #. E-ballot box cleaned of repeat votes :file:`<election id>-bb-2.json`;

        #. Hash of e-ballot box cleaned of repeat votes :file:`<election
           id>-bb-2.json.sha256sum`;

        #. List of e-voters in JSON format :file:`<election
           id>-ivoterlist.json`;

        #. List of e-voters in PDF format :file:`<election
           id>-ivoterlist.pdf`;

        #. Revocation and restoration report :file:`<election
           id>-revocation-report.csv`;

        #. Revocation and restoration report without personal data
           :file:`<election
           id>-revocation-report.csv.anonymous`;

        #. *Log2* file, i.e., cancelled votes :file:`<election id>.<question
           id>.squash.log2`.

:file:`processor.squash.yaml`:

.. literalinclude:: config-examples/processor.squash.yaml
   :language: yaml
   :linenos:


.. _processor-revoke:

E-ballot Box Processing - Vote Revocation and Restoration Based on Polling Station Info
---------------------------------------------------------------------------------------

The *revoke* tool is used for revoking and restoring votes based on polling station info.
The tool receives as input the e-ballot box prepared by the *squash* tool and
applies the revocation and restoration lists provided as input.

:revoke.ballotbox:
        E-ballot box cleaned of repeat votes.

:revoke.ballotbox_checksum:
        Digitally signed hash of the e-ballot box cleaned of repeat votes.

:revoke.districts:
        Digitally signed districts list.

:revoke.revocationlists:
        List of revocation and restoration lists. May be empty.

:revoke.out:
        Tool output directory. The following are created in this directory:

        #. E-ballot box cleaned of repeat voter votes :file:`<election
           id>-bb-3.json`;

        #. Hash of e-ballot box cleaned of repeat voter votes
           :file:`<election id>-bb-3.json.sha256sum`;

        #. Revocation and restoration report :file:`<election
           id>-revocation-report.csv`;

        #. Revocation and restoration report without personal data
           :file:`<election
           id>-revocation-report.csv.anonymous`;

        #. List of e-voters in JSON format :file:`<election
           id>-ivoterlist.json``;

        #. *Log2* file, i.e., cancelled votes
           :file:`<election id>.<question id>.revoke.log2`.

:file:`processor.revoke.yaml`:

.. literalinclude:: config-examples/processor.revoke.yaml
   :language: yaml
   :linenos:


.. _processor-anonymize:

E-ballot Box Processing - Anonymization
----------------------------------------

The *anonymize* tool is used for anonymizing the e-ballot box.
The tool receives as input the e-ballot box prepared by the *revoke* tool and removes
voter information from it.

:anonymize.ballotbox:
        E-ballot box cleaned of repeat voter votes.

:anonymize.ballotbox_checksum:
        Digitally signed hash of the e-ballot box cleaned of repeat voter votes.

:anonymize.out:
        Tool output directory. The following are created in this directory:

        #. E-ballot box cleaned of voter personal data :file:`<election
           id>-bb-4.json`;

        #. Hash of e-ballot box cleaned of voter personal data :file:`<election
           id>-bb-4.json.sha256sum`;

        #. *Log3* file, i.e., votes sent for tallying :file:`<election
           id>.<question id>.anonymize.log3`.

:file:`processor.anonymize.yaml`:

.. literalinclude:: config-examples/processor.anonymize.yaml
   :language: yaml
   :linenos:


Additional Processing Application Tools
----------------------------------------

Tool *verify*
*****************

*Verify* is an auxiliary tool that can verify the signature of a digitally signed
container and display the container data.

:verify.file:
        File to verify.


:file:`processor.verify.yaml`:

.. literalinclude:: config-examples/processor.verify.yaml
   :language: yaml
   :linenos:


Tool *export*
*****************

*Export* is an auxiliary tool that can export complete digitally signed vote
containers from the e-ballot box issued by the collector service. It is
possible to export either all votes at once or a specific voter's votes.

:export.ballotbox:
        E-ballot box issued from the collector service.

:export.ballotbox_checksum:
        Digitally signed hash of the e-ballot box issued from the collector service.

:export.signed_ballot_max_size_bytes:
        Maximum allowed size in bytes of a single signed vote in the e-ballot box
        issued from the collector service.

        If not specified, the default of 32768 bytes is used.

:export.voter_id:
        Voter identifier (optional).

:export.out:
        Tool output directory. The following are created in this directory:

        #. E-ballot box processing errors report :file:`ballotbox_errors.txt`
           (optional);

        #. Digitally signed containers of votes exported from the e-ballot box.


:file:`processor.export.yaml`:

.. literalinclude:: config-examples/processor.export.yaml
   :language: yaml
   :linenos:


Tool *stats*
****************

*Stats* is an auxiliary tool that can calculate vote and voter statistics
based on the e-ballot box. Statistics can be limited by time period and the output
can be limited to aggregate data or broken down by district. NB! The tool does not
verify digital signatures; for processing votes, use the *check*,
*squash*, *revoke*, *anonymize* workflow.

:stats.ballotbox:
        E-ballot box from which to compile statistics. If the file extension is
        ``.json``, then it must be a processed e-ballot box. Otherwise,
        it must be an e-ballot box issued from the collector service.

:stats.signed_ballot_max_size_bytes:
        Maximum allowed size in bytes of a single signed vote in the e-ballot box
        issued from the collector service.

        If not specified, the default of 32768 bytes is used.

:stats.election_day:
        Election day. All e-voters' ages are calculated for statistics
        purposes relative to this date.

:stats.period_start:
        Statistics period start time (optional). Votes with a voting time
        earlier than this are not included in statistics.

:stats.period_end:
        Statistics period end time (optional). Votes with a voting time
        later than this are not included in statistics.

:stats.districts:
        Digitally signed districts list. Required for outputting statistics
        by district. If not specified, only aggregate statistics are output.

:stats.vlkey:
        Public key used for verifying voter lists.
        The argument is mandatory when using voter lists.

:stats.voterlists:
        Voter lists. Required for determining voter's district from the
        e-ballot box issued from the collector service.

        The argument is mandatory if the e-ballot box is issued from the collector service and
        statistics are output by district.

:stats.voterlists.path:
        Voter list file.

:stats.voterlists.signature:
        Voter list signature, given with the algorithm
        ``ecdsa-with-SHA256``.

:check.voterforeignehak:
        EHAK code used for determining district membership of voters
        permanently residing abroad. Default value "0000".

:stats.out:
        Tool output directory. The following are created in this directory:

        #. E-ballot box statistics in JSON format :file:`<election id>-stats.json`
           (:file:`ELECTION-stats.json` if the election cannot be identified);

        #. E-ballot box statistics in CSV format :file:`<election id>-stats.csv`
           (:file:`ELECTION-stats.csv` if the election cannot be identified);

        #. E-ballot box processing errors report :file:`ballotbox_errors.txt`
           (created when errors occur);

        #. Voter lists processing errors report
           :file:`voterlist_errors.txt` (created when errors occur).


:file:`processor.stats.yaml`:

.. literalinclude:: config-examples/processor.stats.yaml
   :language: yaml
   :linenos:


Tool *statsdiff*
********************

*Statsdiff* is an auxiliary tool that can calculate the difference between two
statistics files. The result is a third statistics file whose all values come
from the base file with the compared file's values subtracted.

:statsdiff.compare:
        Statistics comparison base file in JSON format.

:statsdiff.to:
        Compared statistics file in JSON format. The compared statistics file comes from
        the IVXV log monitor. To use the *statsdiff* utility, the **time:** and **meta:**
        JSON entries must be removed from this file. These entries are not significant
        for statistics comparison and are simply the statistics file generation timestamp,
        which is always different in the **statsdiff.compare** and **statsdiff.to** files.

:statsdiff.diff:
        Tool output file. The statistics difference is saved to this file
        in JSON format.


:file:`processor.statsdiff.yaml`:

.. literalinclude:: config-examples/processor.statsdiff.yaml
   :language: yaml
   :linenos:

.. _processor-checkAndSquash:

E-ballot Box Processing - Verification and Repeat Vote Cancellation
--------------------------------------------------------------------

This tool performs both verification and repeat vote cancellation.
More information about the operations performed can be found in the subsections:

* *E-ballot Box Processing - Verification*
* *E-ballot Box Processing - Repeat Vote Cancellation*

:checkAndSquash.ballotbox:
        E-ballot box issued from the collector service.

:checkAndSquash.ballotbox_checksum:
        Digitally signed hash of the e-ballot box issued from the collector service.

        If not specified, the corrected e-ballot box is not output for subsequent
        stages. Useful for election-time verification of a non-final e-ballot box.

:checkAndSquash.signed_ballot_max_size_bytes:
        Maximum allowed size in bytes of a single signed vote in the e-ballot box
        issued from the collector service.

        If not specified, the default of 32768 bytes is used.

:checkAndSquash.districts:
        Digitally signed districts list.

:checkAndSquash.registrationlist:
        Registration data from the registration service. If not specified,
        compliance of votes contained in the e-ballot box with registration
        data is not checked.

:checkAndSquash.registrationlist_checksum:
        Digitally signed hash of the registration data. May be absent
        if ``registrationlist`` is absent.

:checkAndSquash.tskey:
        Collector service public key from the registration request certificate
        used for verifying registration requests.

:checkAndSquash.vlkey:
        Public key used for verifying voter lists.
        The argument is mandatory if voter lists are provided.

:checkAndSquash.voterlists_dir:
        Voter lists directory. If not specified, the voting eligibility of
        e-voters is not checked.

:checkAndSquash.voterlists:
        Voter lists. If not specified, the voting eligibility of
        e-voters is not checked.

:checkAndSquash.voterlists.path:
        Voter list file.

:checkAndSquash.voterlists.signature:
        Voter list signature, given with the algorithm
        ``ecdsa-with-SHA256``.

:checkAndSquash.districts_mapping:
        District and polling station mapping file for the voter list
        (optional).

:checkAndSquash.election_start:
        Voting start time. Votes with a voting time earlier than this are
        treated as test votes and are not sent for tallying.

:checkAndSquash.voterforeignehak:
        EHAK code used for determining district membership of voters
        permanently residing abroad. Default value "0000".

:checkAndSquash.enckey:
        Location of the encryption public key file (key application output).
        The key is used for pre-checking encrypted votes, to distinguish
        genuinely encrypted votes from arbitrary binary garbage.

:checkAndSquash.out:
        Tool output directory. The following are created in this directory:

        #. E-ballot box cleaned of repeat votes :file:`<election id>-bb-2.json`;

        #. Hash of e-ballot box cleaned of repeat votes :file:`<election
           id>-bb-2.json.sha256sum`;

        #. List of e-voters in JSON format :file:`<election
           id>-ivoterlist.json`;

        #. List of e-voters in PDF format :file:`<election
           id>-ivoterlist.pdf`;

        #. Revocation and restoration report :file:`<election
           id>-revocation-report.csv`;

        #. Revocation and restoration report without personal data
           :file:`<election
           id>-revocation-report.csv.anonymous`;

        #. *Log1* file, i.e., accepted votes
           :file:`<election id>.<question id>.log1`.

        #. *Log2* file, i.e., cancelled votes :file:`<election id>.<question
           id>.log2`.

        #. E-ballot box processing errors report :file:`ballotbox_errors.txt`
           (optional);

        #. Voter lists processing errors report
           :file:`voterlist_errors.txt` (optional);


:file:`processor.checkAndSquash.yaml`:

.. literalinclude:: config-examples/processor.checkAndSquash.yaml
   :language: yaml
   :linenos:

.. _processor-revokeAndAnonymize:

E-ballot Box Processing - Vote Revocation, Restoration Based on Polling Station Info and Anonymization
-------------------------------------------------------------------------------------------------------

The *revokeAndAnonymize* tool is used for revoking votes, restoring votes based on
polling station info, and anonymization. The tool receives as input the e-ballot box
prepared by the *squash* or *checkAndSquash* tool and applies the revocation and
restoration lists provided as input.

:revokeAndAnonymize.ballotbox:
        E-ballot box cleaned of repeat votes.

:revokeAndAnonymize.ballotbox_checksum:
        Digitally signed hash of the e-ballot box cleaned of repeat votes.

:revokeAndAnonymize.districts:
        Digitally signed districts list.

:revokeAndAnonymize.revocationlists:
        List of revocation and restoration lists. May be empty.

:revokeAndAnonymize.out:
        Tool output directory. The following are created in this directory:

        #. E-ballot box cleaned of repeat voter votes and anonymized
           :file:`<election id>-bb-4.json`;

        #. Hash of e-ballot box cleaned of repeat voter votes and anonymized
           :file:`<election id>-bb-4.json.sha256sum`;

        #. Revocation and restoration report :file:`<election
           id>-revocation-report.csv`;

        #. Revocation and restoration report without personal data
           :file:`<election
           id>-revocation-report.csv.anonymous`;

        #. List of e-voters in JSON format :file:`<election
           id>-ivoterlist.json``;

        #. *Log2* file, i.e., cancelled votes
           :file:`<election id>.<question id>.log2`.

        #. *Log3* file, i.e., votes sent for tallying :file:`<election
           id>.<question id>.log3`.

:file:`processor.revokeAndAnonymize.yaml`:

.. literalinclude:: config-examples/processor.revokeAndAnonymize.yaml
   :language: yaml
   :linenos:
