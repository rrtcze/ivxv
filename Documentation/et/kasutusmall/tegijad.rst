..  IVXV use cases

Actors
======

Organizer
---------

The *Organizer* is a person who organizes elections within the framework of which the electronic voting system is used. The Organizer defines the electronic voting configuration, including all other role holders. The Organizer substantively manages the Collector Service.

The Organizer is involved in the pre-voting stage with compiling and/or approving the lists of voters, polling districts, constituencies, and choices – candidates (in elections) or response options (in referendums).

The Organizer creates and/or approves the configurations of the Voting Application and the Verification Application.

The Organizer is involved during the voting stage with supplementing and/or approving supplements to the voter lists.

The Organizer is involved during the processing stage with compiling and/or approving e-vote revocation and restoration applications.

The Organizer may also fulfill specific roles related to the operation of the core e-voting processes. For example, in typical cases the Organizer also holds the main secret of the e-voting system – the vote decryption key – and thus also fulfills the role of the vote opener and tallier, i.e., the Counter.

Voter
-----

The *Voter* is a person who uses the electronic voting system during the voting stage

- for voting with the Voting Application,
- for vote verification with the Verification Application.

The Voter has an electronic identity document – ID card, Mobile-ID, Smart-ID, or Web eID.

Collector
---------

The *Collector* is a person who technically manages the Collector Service, the Voting Application, and the Verification Application.

The *Collector Service* is a server system that verifies voting eligibility using the Identification Service, issues the candidate list, helps the Voting Application create an e-vote using the Signing Service, stores votes in the e-ballot box, and registers them in the Registration Service. The Collector Service responds to vote integrity verification requests made by the Verification Application.

The *Collector Service Administrator* is either the Organizer, the Collector, or Client Support. The Collector is the technical administrator of the Collector Service. The substantive administrator of the Collector Service is the Organizer. The Collector Service provides an informational interface for Client Support.

The *Management Service* is a service that the Collector Service Administrator uses to obtain information from the Collector Service or to relay commands to the Collector Service.

The *Voting Application* is an application that the Voter uses to cast an e-vote in an ongoing election. The Voting Application communicates with the Collector Service and allows the Voter to make a choice, encrypt it, and digitally sign it. The Voting Application displays a QR code that allows the Voter to use the Verification Application to verify that the e-vote correctly reached the Collector Service.

The Collector prepares a configured voting application from the compiled voting application, which is signed and distributed to voters.

The *Verification Application* is an application that allows the Voter to verify on a smart device platform separate from the computer that their e-vote reached the Collector Service and the Registration Service and correctly expressed their will.

The Collector configures the verification application so that it is capable of loading actual configurations from the network, and signs the verification application.

The Collector is the technical administrator of the Voting Application and the Verification Application; the substantive administrator is the Organizer.

The core processes performed by the Collector take place during the voting stage; initiating and concluding activities occur during both the pre-voting and processing stages.

The Collector digitally signs the data (e-votes and logs) to be handed over to the Processor at the end of the voting period.

Processor
---------

The *Processor* is a person who, using the Processing Application, processes the e-votes collected during the voting period in the processing stage:

- verifies digital signatures and the completeness of data received from the Collector,
- revokes duplicate e-votes and, when parallel voting is used, also the e-votes of those Voters who voted at a polling station during the advance voting period,
- anonymizes e-votes by removing personal digital signatures from them, having previously sorted them by constituency.

The Processor may additionally cryptographically anonymize e-votes using the Mixing Application.

The *Processing Application* is an application used to verify the individual integrity of votes and the integrity of the e-ballot box, revoke votes, issue lists of voters who voted electronically, and produce anonymized votes grouped by constituency. The inputs of the Processing Application are provided by the Collector, the Registration Service, and the Organizer. The Processing Application may also be operated by the Auditor to verify the correctness of the Processor's work results.

Mixer
-----

The *Mixer* is a person who cryptographically anonymizes e-votes during the processing stage using the Mixing Application.

The *Mixing Application* is an application whose input is anonymized encrypted votes grouped by constituency and which outputs cryptographically shuffled votes such that they cannot be matched to the input. The mixing is performed in such a way that decrypting and tallying both the input and output votes produces the same result. In addition to the shuffled votes, the Mixing Application outputs a mixing proof that confirms the semantic equivalence of the input and output votes.

Counter
-------

The *Counter* is a person who, using the Key Application:

- generates the vote encryption and decryption key during the pre-voting stage,
- decrypts the encrypted votes and tallies them into e-voting results during the counting stage.

The Counter may act individually; generally, the e-voting encryption key is protected with a threshold scheme where instead of a single complete key, multiple key shares are created, and key operations can only be performed with the participation of a certain quorum of key shares. In such cases, the Counter is assisted by Key Custodians.

A *Key Custodian* is a person whose task is to safeguard the key share entrusted to them and to provide it to the Counter only when there is a legal basis for doing so.

The *Key Application* is an application used to generate the vote encryption and decryption key for each election. The Key Application is also used for counting votes and producing results.

Auditor
-------

The *Auditor* is a person who, during the auditing stage, verifies the integrity and consistency of data that was exchanged between the central parties of the system, based on the system description and data published by the Organizer. The Auditor uses the Audit Application in their work. If the Auditor also verifies the correctness of the Processor's operation, then the Auditor also uses the Processing Application.

The *Audit Application* is an application that allows verifying the correctness of the Counter's and Mixer's work. The correctness of the Counter's work can also be verified publicly.

Client Support
--------------

*Client Support* is a person whom the Voter contacts in case of problems during the voting stage. Client Support assists the Voter in resolving problems using information obtained from the Collector Service.

Identification Service
----------------------

The *Identification Service* is a service used when necessary to identify the voter's identity.

Signing Service
---------------

The *Signing Service* is a service used when necessary for signing the vote
and obtaining a validity confirmation for it. The need for the
Signing Service depends on the signing device – for Mobile-ID,
Smart-ID, Web eID, and ID card, the architecture of these services differs.

Registration Service
--------------------

The *Registration Service* is a service through which the Collector Service must register all votes received from Voting Applications. After the end of the voting period, the service provider transmits information about registered votes to the Processor.
