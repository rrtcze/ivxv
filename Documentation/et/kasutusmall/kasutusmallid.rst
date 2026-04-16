..  IVXV use cases

Use Cases
=========

Pre-voting Stage
----------------

Organizer - Defining the Election
``````````````````````````````````

Description
'''''''''''

Strictly speaking, this is not a use case of the electronic voting information system, but it is the starting point of electronic voting – the Organizer describes the election, questions, constituencies, voters, and the holders of various roles in the core e-voting processes – the Counter, the Collector, the Processor, etc.

Counter - Generating the Vote Encryption and Decryption Key
```````````````````````````````````````````````````````````

Description
'''''''''''

The Counter generates a key pair for encrypting and decrypting e-votes. The decryption key shares are distributed among the Key Custodians.

Precondition
''''''''''''

#. The Counter has the Key Application.
#. The technical configuration of the threshold scheme is available.
#. There is a sufficient number of Key Custodians and key carriers required for implementing the threshold scheme.

Trigger
'''''''

The Counter initiates the key pair generation in the Key Application.

Main Process
''''''''''''

#. The Key Application verifies the digital signature of the configuration.
#. The Key Application generates key shares according to the threshold scheme specification.
#. The Key Application requests key carriers from the Counter for storing the shares.
#. The Key Application stores the shares on the key carriers.
#. The Key Application uses the vote encryption key to encrypt a message.
#. The Key Application tests the key carriers and recovers the key with 2 different quorums for decrypting the message.
#. The Key Application signs the encryption key with the signing key.

Extensions
''''''''''

- In case of technical errors in any main process step, the event is logged in the technical error log. The user is presented with a message about the error situation.

Postcondition
'''''''''''''

The vote encryption and decryption key pair has been successfully generated; the decryption key is stored as shares on key carriers.


Organizer - Creating the Voting Application Configuration
``````````````````````````````````````````````````````````

Description
'''''''''''

The Organizer configures the texts, certificates, icons, and election parameters used by the Voting Application.

Precondition
''''''''''''
The following conditions must be met for configuration:

- The Organizer has prepared the Voting Application texts
- The Organizer has prepared the election parameters
- The vote encryption key is available.

Main Process
''''''''''''
#. The Organizer launches the Configuration Application.
#. The Organizer enters the election and question identifiers and types.
#. The Organizer enters the election questions.
#. The Organizer loads the vote encryption key.
#. The Organizer configures the Voting Application user interface – texts, fonts, colors, icons.
#. The Organizer verifies that all Voting Application views match the desired outcome.
#. The Organizer saves the created configuration.

Extensions
''''''''''

Postcondition
'''''''''''''
At the end of configuration, the Voting Application configuration is available, missing only the Collector Service technical information.

Organizer - Creating the Verification Application Configuration
```````````````````````````````````````````````````````````````

Precondition
''''''''''''
The Organizer has:

#. Certificates required for verifying the Voter's signature
#. Certificates required for verifying the Registration Service confirmation
#. Certificates required for verifying the Collector Service signature
#. The public key used for encrypting votes in the current election
#. Verification Application texts in HTML format
#. Verification Application fonts
#. Verification Application colors
#. The current election identifier and questions

Main Process
''''''''''''
1. The Organizer creates the Verification Application configuration
2. The Organizer verifies the success of the configuration by reviewing the application views

Extensions
''''''''''
1. If the views are not suitable, the Organizer modifies the settings and starts the main process from the beginning.


Collector - Configuring the Collector Service
``````````````````````````````````````````````

Description
'''''''''''
The Collector prepares the Collector Service for the election.

Precondition
''''''''''''
#. The Collector Service operating system is installed.
#. The Collector Service software packages are installed.

Trigger
'''''''
The use case begins when the Collector logs into the Collector Service before the start of the voting period.

Main Process
''''''''''''
1. The Collector carries out the following steps:

    a. Loads the certificate configuration required for verifying configuration packages.
    b. Loads the Identification Service configuration.
    c. Loads the Signing Service configuration.
    d. Loads the Registration Service configuration.
    e. Loads the microservices network configuration.
    f. Loads the storage technology configuration.
    g. Loads the authorized list loaders configuration.
    h. Loads the digitally signed list of polling districts/constituencies.
    i. Loads the digitally signed choices list.
    j. Loads the signed voter list.
    k. The Collector Service verifies the digital signatures on configuration packages and lists (technical use case Digital Signature Validity Verification in the Collector Service).
    l. The Collector Service verifies the identified signer's authorizations in the system.
    m. The Collector Service verifies the formal and substantive consistency of the configuration and initializes internal data structures.

Extensions
''''''''''
- If in main process step 1.k the digital signature validity is not verified, an error message is issued, the event is logged in the error log, and no changes are applied.
- If in main process step 1.l the digital signer's corresponding authorization is not found in the authorized persons list, an error message is issued, the event is logged in the error log, and no changes are applied.
- If in main process step 1.m formatting problems are detected, an error message is issued, the event is logged in the error log, and no changes are applied.
- If in main process step 1.m an inconsistency in the configuration is detected – wrong elections, duplicate polling district, duplicate constituency, polling district in a non-existent constituency, duplicate candidate, candidate with a non-existent constituency, duplicate voter, Voter with a non-existent polling district, etc. – an error message is issued, the event is logged in the error log, and no changes are applied.
- In case of technical errors in any main process step, the event is logged in the technical error log. The user is presented with a message about the error situation.

Postcondition
'''''''''''''
The Collector Service is consistently configured and can be transitioned to the voting stage.


Collector - Preparing the Voting Application
``````````````````````````````````````````````

Description
'''''''''''
The Collector prepares the Voting Application.

Precondition
''''''''''''
The following conditions must be met for preparation:

- The Organizer has created their part of the Voting Application configuration file
- The Voting Application has been compiled for all supported platforms.
- The Voting Application is unconfigured.
- The certificates required for trusting the Collector Service TLS certificate are available.
- The Collector Service URI is known.

Main Process
''''''''''''
#. The Collector launches the Configuration Application.
#. The Collector loads the Voting Application configuration file created by the Organizer.
#. The Collector loads the certificates required for trusting the Collector Service TLS certificate.
#. The Collector applies the created configuration to the Voting Application.
#. The Collector verifies that all Voting Application views match the desired outcome.

Extensions
''''''''''
If any required resource is missing, the configuration is aborted and the process is restarted when all preconditions are met.

Postcondition
'''''''''''''
At the end of configuration, the Voting Application starts up and uses the configured resources.


Collector - Preparing the Verification Application
````````````````````````````````````````````````````

Precondition
''''''''''''
The Collector has:

1. A compiled Verification Application
2. A key pair suitable for signing the Verification Application
3. The Collector Service network address
4. Certificates required for verifying the Collector Service certificate

Main Process
''''''''''''
1. The Collector configures the Verification Application with the Collector Service network address and corresponding certificates.
2. The Collector packages the application
3. The Collector signs the packaged application

Organizer - Test Voting
````````````````````````

Description
'''''''''''

The Organizer, in cooperation with the Collector, Processor, Counter, and Key Custodians, verifies the Collector Service's readiness for electronic voting and the consistent configuration of all components.

Precondition
''''''''''''

#. The e-vote encryption key has been created and tested
#. The Collector Service is configured
#. The Voting Application is configured
#. The Verification Application is configured

Main Process
''''''''''''
1. The Organizer conducts test voting

   #. The Collector transitions the Collector Service to the voting stage
   #. The Organizer casts one or more votes using the Voting Application
   #. The Organizer verifies votes using the Verification Application
   #. The Collector stops the Collector Service and exports the e-ballot box
   #. The Processor generates the list of e-voters
   #. The Processor creates the list of anonymized e-votes to be sent for counting
   #. The Counter together with the Key Custodians activates the Key Application and the vote decryption key
   #. The Counter decrypts the anonymized votes and produces the voting result

2. The Collector ends the test voting and returns the Collector Service to its initial state, where the stored vote database is empty.

Extensions
''''''''''

- The test voting may also include mixing and auditing workflows.

Postcondition
'''''''''''''
The electronic voting system components are verified to be consistently configured.

Voting Stage
------------

Organizer - Starting the Voting
````````````````````````````````

Description
'''''''''''
Starting the voting transitions the Collector Service to the voting stage – the issuance of choices lists, storage of votes, and responding to verification requests begins.

Trigger
'''''''

#. The voting start time specified in the election settings is reached.
#. The Organizer transmits a digitally signed order to start voting via the Management Service.

Main Process
''''''''''''

1. The Collector Service begins issuing choices lists, storing votes, and responding to verification requests.

Postcondition
'''''''''''''

The Collector Service issues choices lists, stores votes, and responds to verification requests.

Voter - Electronic Voting with the Voting Application
``````````````````````````````````````````````````````

Description
'''''''''''
The Voter uses the Voting Application to cast an electronic vote in an ongoing election in whose voter list they are included.

Precondition
''''''''''''
The Voter has downloaded the Voting Application configured for the current election to their computer.

Trigger
'''''''
The use case starts when the Voter has launched the Voting Application.

Main Process
''''''''''''
#. The Voter authenticates themselves with an electronic identity document (technical use case Authentication in the Voting Application) to the Collector Service.
#. The Collector Service sends the following to the Voting Application based on the personal identification code (technical use case Issuing Choices Lists to the Voting Application):

    - The list of questions and choices for the Voter's constituency of residence in the election,
    - a notification about previous voting, if an electronic vote has already been stored for the same personal identification code in this election.

3. The Voting Application presents the Voter's personal data, the description of the current election, and the questions.
#. The Voting Application presents the choices list for the Voter's constituency of residence.
#. The Voter makes a selection from the displayed choices in the context of all questions.
#. The Voting Application presents the Voter with the data of the selections made (choice name, choice number, and in certain elections also the electoral list name or independent candidate) and asks for confirmation of the selections.
#. The Voter confirms the selections made.
#. The Voting Application encrypts the Voter's selections with the election public key and initiates the digital signing of the vote (technical use case Digital Signing in the Voting Application) with the Voter's electronic identity document. The Voting Application sends the digitally signed vote to the Collector Service for storage (technical use case Vote Storage in the Collector Service).
#. The Voting Application verifies the Registration Confirmation sent by the Collector Service in response, displays a message to the Voter about the successful storage of the vote, and the verification code needed for vote verification.

Extensions
''''''''''
- The Voter may use accessibility technologies (e.g., screen readers) during the main process.
- Errors occurring at any stage of the main process are fatal and result in the interruption of the voting process. If the cause of the error is resolved, the use case must be restarted.

Most significant errors:

- Use of the electronic identity document failed
- Communication disruption between the Voting Application and the Collector Service
- Authentication failed
- The Voter does not have voting rights in the current election
- Digital signing failed
- Technical errors

Postcondition
'''''''''''''
Upon successful electronic voting, the Voter is shown a verification code that can be used to verify that the electronic vote reached the Collector Service and corresponds to the Voter's will.
Interrupting the use case before digitally signing the electronic vote does not affect the Voter's previously stored vote in the Collector Service.

Voter - Verifying the Electronic Vote with the Verification Application
````````````````````````````````````````````````````````````````````````

Description
'''''''''''
The Voter uses the Verification Application immediately after voting with the Voting Application to verify that the electronic vote correctly reached the Collector Service.

Precondition
''''''''''''
#. The Voter has a mobile device with the Verification Application.
#. The Voter has used the Voting Application for voting.
#. The vote verification time window has not yet expired.
#. The last view of the Voting Application is open on screen and displays the QR code containing the information needed for verification.

Trigger
'''''''
The use case starts when the Voter has launched the Verification Application.

Main Process
''''''''''''
The main process is unidirectional; going back in the process requires terminating the Verification Application.

#. The Verification Application loads settings from the Collector Service.
#. The Verification Application displays a welcome text.
#. The Voter points the mobile device camera at the QR code displayed in the Voting Application.
#. The Verification Application analyzes the QR code and identifies the random number used for encrypting the vote and the session identifier that identifies the vote in the Collector Service.
#. The Verification Application contacts the Collector Service with the session identifier.
#. The Verification Application verifies the Collector Service certificate and displays to the Voter information about the success of the verification.
#. The Verification Application downloads from the Collector Service the vote signed by the Collector Service, the Registration Service confirmation, and the choices lists associated with the vote (technical use case Issuing a Vote for Verification from the Collector Service).
#. The Verification Application ensures that the vote meets the requirements of the verification protocol. The Verification Application verifies the Registration Service confirmation and the Voter's signature. The Verification Application displays to the Voter information about the success of the verifications, the data of the Voter who signed the vote, and the questions for which an encrypted expression of will is found in the vote.
#. The Voter initiates the verification algorithm.
#. The Verification Application clears the view of the data of the Voter who signed the vote.
#. The Verification Application determines the content of the encrypted expression of will using the verification algorithm and the random number obtained from the QR code.
#. The Verification Application displays to the Voter the question identifier and the identified choice for each encrypted expression of will.

Extensions
''''''''''
#. If the Verification Application detects the absence of a network connection, the Voter is directed to activate a network connection.
#. If the Verification Application detects an error in the Collector Service certificate, the application terminates with an error message.
#. If the vote or Registration Service confirmation was not received from the Collector Service, the Voter is instructed to inform Client Support and the application terminates with an error message.
#. If the Collector Service sends a message that verification of the specific vote is no longer possible (time or attempt limit exceeded), the application terminates with a corresponding message.
#. If the vote received from the Collector Service does not meet the requirements, the application terminates with an error message.
#. If verification of the Voter's signature fails, the application terminates with an error message.
#. If verification of the Registration Service confirmation fails, the application terminates with an error message.
#. If the verification algorithm does not find a suitable choice from the candidate list, an error message is displayed after the specific election and question identifier.
#. If the QR code contains verification codes for more than one question, the verification is performed for all referenced questions.
#. If the signed vote sent from the Collector Service contains encrypted votes for which there is no verification code, the Verification Application presents the Voter with the identifiers of those elections/questions and a corresponding warning. The remaining votes are verified.
#. If the signed vote sent from the Collector Service does not contain all votes for which there is a verification code, the Verification Application presents the Voter with the identifiers of those elections/questions and a corresponding warning. The remaining votes are verified.
#. If the verification algorithm terminates with an error message, the Voter is instructed to inform Client Support.

Postcondition
'''''''''''''
If the vote verification exceeds the allowed verification limit, the Collector Service no longer allows the vote to be verified.


Collector Service Administrator - Displaying the Collector Service Status
``````````````````````````````````````````````````````````````````````````

Trigger
'''''''
The Collector Service Administrator enters the Collector Service Management Service.

Main Process
''''''''''''

#. The Management Service authenticates the user and determines the authenticated user's authorizations in the Management Service
#. According to the scope of authorizations, the Collector Service displays a subset of the following information:

   #. Election identifier, questions, voting stage
   #. Running service servers
   #. Loaded lists - constituencies, voters, choices
   #. Voting statistics
   #. Collector Service authorized users
   #. Collector Service technical log


Organizer - Ending the Voting
``````````````````````````````

Description
'''''''''''
Ending the voting terminates the acceptance of votes by the Collector Service. Ending the voting occurs gradually – Voters who received the candidate list before the official end of voting must be able to vote within a reasonable time.

Trigger
'''''''

#. The voting end time specified in the election settings is reached.
#. The Organizer transmits a digitally signed order to end voting via the Management Service.

Main Process
''''''''''''
1. The Collector Service responds to all candidate list requests with an error message, but continues to serve vote storage requests.
2. The Collector Service stops accepting votes after the time specified in the order/configuration has elapsed.
3. The Collector Service responds to all requests from Voting Applications with an error message.

Postcondition
'''''''''''''
The Collector Service no longer accepts new votes.


Processing Stage
----------------

Collector - Exporting the E-ballot Box
````````````````````````````````````````

Description
'''''''''''

The Collector exports the e-ballot box from the Collector Service database.

Precondition
''''''''''''

Electronic voting has ended.

Trigger
'''''''

The Collector selects the e-ballot box export functionality from the Management Service.

Main Process
''''''''''''

#. The Collector Service creates an extract from the vote database that contains all vote-related information stored in the storage service.

Postcondition
'''''''''''''

The e-ballot box has been exported.


Processor - Verifying the E-ballot Box
```````````````````````````````````````

Description
'''''''''''

The Processor verifies the consistency of the e-ballot box received from the Collector and its compliance with the information received from the Registration Service.

Precondition
''''''''''''

- The e-ballot box has been exported
- The registration confirmations have been exported

Trigger
'''''''

The Processor launches the corresponding functionality in the Processing Application user interface.

Main Process
''''''''''''

#. The Processing Application loads the settings
#. The Processing Application verifies the digital signature of the settings
#. The Processing Application verifies the consistency of the settings
#. The Processing Application loads the e-ballot box
#. The Processing Application verifies the digital signatures of the e-votes
#. The Processing Application loads the registration confirmations
#. The Processing Application verifies the registration confirmations
#. The Processing Application verifies the consistency of the e-ballot box and the registration confirmations

Extensions
''''''''''
- In case of technical errors in any main process step, the event is logged in the technical error log. The user is presented with a message about the error situation and the process is stopped.
- The user has the option to carry out the process in such a way that Voters associated with errors are separated from the rest of the e-ballot box. The result is a report of problematic votes and a cleaned e-ballot box.

Postcondition
'''''''''''''

The e-ballot box verification report unambiguously identifies correct and problematic votes.


Processor - Compiling the List of Electronic Voters
`````````````````````````````````````````````````````
Description
'''''''''''
After the end of the voting period, the Processor compiles lists of persons who voted electronically, organized by polling district. The lists are both human-readable and machine-readable.

Precondition
''''''''''''

The e-ballot box has been successfully verified.

Trigger
'''''''
The Processor launches the corresponding functionality in the Processing Application user interface.

Main Process
''''''''''''
1. The Processing Application revokes duplicate votes, keeping only the chronologically last vote cast by each Voter.
2. The Processing Application sorts the valid votes by polling district.
3. The Processing Application creates the electronic voters list file.

    1. For each valid vote, the Processing Application adds a record to the file containing the personal identification code, name, polling district number, and row number in the constituency list. The data is taken from the voter list.

4. The Processing Application presents the total number of accepted votes and the number of electronic voters.
5. The Processor saves the list to an external data carrier.

Extensions
''''''''''
If in main process step 3 the personal identification code is not found in the voter list, corresponding information is logged and the main process continues.

Postcondition
'''''''''''''
Valid votes have been entered into the electronic voters list. Duplicate votes have been revoked.

Processor - Anonymizing E-votes Going to Mixing/Counting
``````````````````````````````````````````````````````````

Description
'''''''''''

The Processor applies revocation and restoration lists and creates an anonymized set of e-votes going to counting.

Precondition
''''''''''''

The e-ballot box has been successfully verified and the electronic voters list has been compiled.

Trigger
'''''''

The Processor launches the corresponding functionality in the Processing Application user interface.

Main Process
''''''''''''

    The Processing Application verifies the digital signatures of the revocation and restoration lists.
    The Processing Application verifies the consistency of the revocation and restoration lists in order.
    The Processing Application applies the revocation and restoration lists in order.
    The Processing Application compiles the list of votes going to mixing/counting by separating the cryptograms from the digital signatures.
    The Processing Application outputs the final electronic voters list in machine-readable format.

Extensions
''''''''''

 - If in main process step 1 the Organizer's signature verification or authorization check fails, an error message is issued. No changes are applied.

Postcondition
'''''''''''''

The set of votes going to mixing/counting has been compiled; the electronic voters list has been issued.

Mixer - Mixing
````````````````

Description
'''''''''''

Precondition
''''''''''''

Trigger
'''''''

Main Process
''''''''''''

#. The Mixer launches the Mixing Application and loads the anonymized e-votes
#. The Mixing Application re-randomizes and permutes the e-votes, resulting in new e-votes
#. The Mixing Application generates a proof that the new e-votes are substantively equivalent to the original e-votes
#. The Mixing Application outputs both the mixed votes and the Mixing Proof

Extensions
''''''''''

Postcondition
'''''''''''''

Provably equivalent mixed votes to the original votes have been output.

Counting Stage
--------------

Counter - Determining the Electronic Voting Result
````````````````````````````````````````````````````

Description
'''''''''''
After the end of the revocation period, the envelopes are sorted by constituency. The outer envelopes are opened, i.e., the digital signatures are removed, leaving votes encrypted with the vote encryption key, which are decrypted using the Key Application.

Main Process
''''''''''''
#. The Counter initiates the vote tallying with the Key Application.
#. The Key Custodians activate the vote decryption key according to the key management procedures.
#. The Key Application reads the encrypted votes from an external data carrier.
#. The Key Application performs a technical check of the vote file and initiates the decryption of the votes.
#. The Key Application verifies the compliance of the decrypted vote with the plaintext vote format.
#. The Key Application verifies the validity of the vote by ensuring that the candidate revealed during decryption was among the choices in the given constituency.
#. The Key Application tallies the qualifying votes by polling district, constituency, and candidate.
#. The Key Application records the voting result on a data carrier.
#. The voting result is imported into the election information system.

Extensions
''''''''''
- In case of technical errors in any main process step, the event is logged in the technical error log. The user is presented with a message about the error situation and the process is stopped.
- If the checks performed in main process steps 4 and 5 fail, the given vote is considered invalid and the process continues with the next encrypted vote.

Postcondition
'''''''''''''
The voting result has been entered into the election information system.

Auditing Stage
--------------

Auditor - Auditing
````````````````````

Description
'''''''''''

After the voting result has been determined, the Auditor can verify the Mixing Proof and the Counting Proof.


Precondition
''''''''''''

- The voting result, cryptograms, and counting proof are available
- The pre-mixing cryptograms, post-mixing cryptograms, and mixing proof are available

Main Process
''''''''''''

1. The Auditor uses the Audit Application to verify the Counting Proof
2. The Auditor uses the Audit Application to verify the Mixing Proof

Extensions
''''''''''

Postcondition
'''''''''''''

The Counting Proof and the Mixing Proof have been verified.


Technical Use Cases
-------------------

Authentication in the Voting Application
``````````````````````````````````````````

Description
'''''''''''
Through the Voting Application and using the electronic identity document, the Collector Service identifies the Voter's identity.

Trigger
'''''''
The use case is triggered when the Voter launches the Voting Application and proceeds to vote.

Main Process – ID Card
''''''''''''''''''''''
1. The Voter inserts the ID card into the reader.
2. The Voting Application contacts the Collector Service to initiate the protocol.
3. The Collector Service sends its certificate to the Voting Application.
4. The Voting Application verifies the Collector Service certificate.
5. The Collector Service requires the Voter's authentication according to the TLS protocol.
6. The Voting Application asks the voter for the PIN1 code to use the ID card authentication key.
7. The Voter enters the PIN1 code.
8. The Voting Application and the Collector Service carry out the TLS protocol; the Voter's certificate is sent to the Collector Service.
9. The Collector Service verifies the Voter's certificate.
10. The Collector Service identifies the Voter's personal identification code.

Main Process – Mobile-ID
'''''''''''''''''''''''''
1. The Voter enters the mobile phone number containing their Mobile-ID SIM card into the Voting Application.
2. The Voting Application contacts the Collector Service to initiate the protocol.
3. The Collector Service sends its certificate to the Voting Application.
4. The Voting Application verifies the Collector Service certificate.
5. The Voting Application sends the phone number to the Collector Service.
6. The Collector Service initiates authentication through the Mobile-ID service.
7. The Collector Service sends the Mobile-ID verification code to the Voting Application, which displays it to the voter.
8. The Voter receives an authentication message on their mobile phone.
9. The Voter compares the verification code in the authentication message with the one displayed in the Voting Application.
10. The Voter enters the PIN1 code to use the authentication key.
11. The Collector Service and the Mobile-ID service carry out the authentication; the Voter's certificate is sent to the Collector Service.
12. The Collector Service verifies the Voter's certificate.
13. The Collector Service identifies the Voter's personal identification code.
14. The Voting Application regularly queries whether authentication has been completed; the Collector Service responds.

Extensions
''''''''''
- If the ID card is not in the reader, the Voting Application terminates with an error message (ID card).
- If the Collector Service is not available, the Voting Application terminates with an error message.
- If the validity of the Collector Service certificate cannot be verified or if the certificate does not match the Collector Service name, the Voting Application terminates with an error message.
- If the use of the ID card fails, the Voting Application terminates with an error message (ID card).
- If the Voter's certificate verification in the Collector Service yields a negative result, an error message is sent to the Voting Application and authentication is terminated.
- If the Mobile-ID protocol execution fails, the Collector Service responds to the Voting Application's request with an error message and authentication is terminated (Mobile-ID).

Postcondition
'''''''''''''
The Collector Service knows the Voter's certificate and has identified the personal identification code from it.

Digital Signing in the Voting Application
````````````````````````````````````````````

Description
'''''''''''
Using the Voting Application, a digital signature is applied to the encrypted vote using the digital signature device.

Precondition
''''''''''''
The Voter has made their selections and confirmed them. The Voting Application has encrypted the selections with the Collector Service public key.
In the case of Mobile-ID, the Collector Service already knows the Voter's mobile phone number with the Mobile-ID SIM card, as authentication has been successfully completed.

Trigger
'''''''
The Voter has selected the voting functionality in the Voting Application; all selections have been encrypted with the Collector Service public key.

Main Process – ID Card
''''''''''''''''''''''
1. The Voting Application creates a BDOC container in BES format.
2. The Voting Application adds the encrypted selections as data files to the container.
3. The Voting Application creates the hash to be signed according to the BDOC standard.
4. The Voting Application initiates the signing of the hash with the ID card.
5. The Voter enters the PIN2 code to use the signing key.
6. The Voting Application adds the Voter's signature and signing certificate to the BDOC container.

Main Process – Mobile-ID
'''''''''''''''''''''''''
1. The Voting Application creates a BDOC container in BES format.
2. The Voting Application adds the encrypted selections as data files to the container.
3. The Voting Application sends the container to the Collector Service.
4. The Collector Service creates the hash to be signed according to the BDOC standard.
5. The Collector Service initiates the signing of the hash with the Mobile-ID service.
6. The Collector Service sends the Mobile-ID verification code to the Voting Application, which displays it to the voter.
7. The Voter receives a signing message on their mobile phone.
8. The Voter compares the verification code in the signing message with the one displayed in the Voting Application.
9. The Voter enters the PIN2 code to use the signing key.
10. The Collector Service and the Mobile-ID service carry out the signing; a digitally signed BDOC container in TS format with validity confirmation is sent to the Collector Service.
11. The Voting Application regularly queries whether signing has been completed; the Collector Service responds.
12. The BDOC container in TS format is forwarded to the Voting Application for verification.

Extensions
''''''''''
- If the ID card is not in the reader, the Voting Application terminates with an error message (ID card).
- If the Collector Service is not available, the Voting Application terminates with an error message.
- If the use of the ID card fails, the Voting Application terminates with an error message (ID card).
- If the Mobile-ID protocol execution fails, the Collector Service responds to the Voting Application's request with an error message and signing is terminated (Mobile-ID).

Postcondition
'''''''''''''
The Voter's vote has been digitally signed.

Digital Signature Validity Verification in the Collector Service
`````````````````````````````````````````````````````````````````

Description
'''''''''''
The Collector Service verifies digital signatures on e-votes signed with ID card and Mobile-ID, as well as on input files used for configuration and revocation.

Precondition
''''''''''''
The Collector Service certificate configuration has been completed. The Collector Service validity confirmation service configuration has been completed.

Trigger
'''''''
The Collector Service initiates the digital signature validity verification.

Main Process
''''''''''''
1. The Collector Service identifies the profile according to which the verification is to be performed:

    1. A vote signed with an ID card may be in BES or TS format, may contain multiple data files, and must contain exactly one signature.
    2. A vote signed with Mobile-ID must be in TS format, may contain multiple data files, and must contain exactly one signature.
    3. Other files must be in TS format, may contain exactly one data file, and must contain exactly one signature.

2. The Collector Service verifies the signature's compliance with the required profile.
3. If the signature is in BES format, the Collector Service contacts the validity confirmation service to verify the certificate's validity. The Collector Service appends the validity confirmation to the digital signature, resulting in a TS format signature.
4. The Collector Service verifies the TS format signature:

    1. The signature.
    2. The certificate validity confirmation.

Extensions
''''''''''
- In case of technical errors in any main process step, the event is logged in the technical error log. The calling process is presented with a message about the error situation.
- If loading the validity confirmation fails in main process step 3, the event is logged in the technical error log. The calling process is presented with a message about the error situation.
- If the checks fail in main process step 4, the event is logged in the technical error log. The calling process is presented with a message about the error situation.

Issuing Choices Lists to the Voting Application
`````````````````````````````````````````````````

Description
'''''''''''
The Collector Service issues the choices list to the Voting Application.

Precondition
''''''''''''
The Voter's authentication has been successfully completed.

Trigger
'''''''
The Voting Application has contacted the Collector Service to download the choices list.

Main Process
''''''''''''
1. The Collector Service uses the personal identification code to determine which constituency the Voter belongs to.
2. The Collector Service checks whether a vote has already been stored for the Voter.
3. The Collector Service sends the Voting Application the constituency-specific candidate list for all elections in which the personal identification code is listed, along with information about possible repeated voting.

Extensions
''''''''''
- In case of technical errors in any main process step, the event is logged in the technical error log. The Voting Application is notified of the process failure.
- If in main process step 2 it is clear that the Voter is not on the current election's voter list, a corresponding error message is sent to the Voting Application.

Vote Storage in the Collector Service
``````````````````````````````````````

Description
'''''''''''
The Collector Service stores the Voter's vote.

Precondition
''''''''''''
The digital signing of the vote in the Voting Application has been successfully completed.

Trigger
'''''''
The Voting Application has sent the vote for storage.

Main Process
''''''''''''
1. The Collector Service verifies the digital signature of the vote (technical use case Digital Signature Validity Verification in the Collector Service). During the verification, the addition of a validity confirmation to the signature is ensured, among other things.
2. The Collector Service verifies the identity of the personal identification codes authenticated during the TLS protocol when loading the choices list and signing the vote.
3. The Collector Service registers the receipt of the vote in the Registration Service.
4. The Collector Service generates a unique identifier associated with the vote.
5. The Collector Service saves the vote along with the unique identifier.
6. The Collector Service returns a success message to the Voting Application along with the unique identifier referencing the vote and the Registration Service confirmation.

Extensions
''''''''''
- In case of technical errors in any main process step, the event is logged in the technical error log. The Voting Application is notified of the process failure. The vote is not stored.
- If in main process step 1 the digital signature verification fails, the event is logged in the technical error log. The Voting Application is notified of the process failure. The vote is not stored.
- If in main process step 2 the personal identification codes differ, the event is logged in the technical error log. The Voting Application is notified of the process failure. The vote is not stored.

Postcondition
'''''''''''''
The digitally signed vote has been provided with a validity confirmation, a Collector Service-side confirmation, and stored in the Collector Service associated with a unique identifier.

Issuing a Vote for Verification from the Collector Service
````````````````````````````````````````````````````````````

Description
'''''''''''
The Collector Service issues the signed vote and registration confirmation to the Verification Application for verification.

Trigger
'''''''
The Verification Application has submitted a vote verification request with a unique identifier to the Collector Service.

Main Process
''''''''''''
1. The Collector Service checks whether an electronic vote corresponds to the unique identifier.
2. The Collector Service checks whether verification of the vote corresponding to the unique identifier is still possible according to the time and attempt conditions.
3. The Collector Service increments the verification attempt counter for the specific vote.
4. The Collector Service issues to the Verification Application the vote referenced by the unique identifier along with the constituency choices list and the registration confirmation corresponding to the vote.

Extensions
''''''''''
- In case of technical errors in any main process step, the event is logged in the technical error log. The Verification Application is notified of the process failure. The vote is not issued.
- If in main process step 1 no vote corresponding to the unique identifier is found, the event is logged in the technical error log. The Verification Application is notified of the process failure. The vote is not issued.
- If in main process step 2 the checks yield a negative result, the event is logged in the technical error log. The Verification Application is notified of the process failure. The vote is not issued.

Revocation/Restoration of Electronic Votes Based on Application
````````````````````````````````````````````````````````````````

Description
'''''''''''
Import of a digitally signed revocation/restoration entries file approved by the Organizer by the Processor. The Processing Application performs the revocations/restorations, logging the activities. The Processor is shown the result of the revocation/restoration – a report of revocations/restorations with results.

Trigger
'''''''

The Processing Application launches the corresponding functionality.

Main Process
''''''''''''
#. The Processing Application verifies the digital signature of the application.
#. The Processing Application checks that the application has been signed by an authorized user.
#. The Processing Application reads entries from the file and carries out the operations, marking the vote as either revoked or restored.
#. The Collector Service displays the results of applying the application.

Extensions
''''''''''
- If in main process step 1 the digital signature is found to be invalid, a corresponding entry is logged in the technical error log and the process is stopped.
- If in main process step 2 it is found that the signer of the application does not have the corresponding authorizations, a corresponding entry is logged in the technical error log and the process is stopped.
- If in main process step 3 it is found that the Voter's vote identified by the personal identification code is in an incompatible state or the Voter has not voted, a corresponding entry is logged in the report and the process continues with the next entry.
- In case of technical errors in any main process step, the event is logged in the technical error log. The user is presented with a message about the error situation and the process is stopped.

Postcondition
'''''''''''''
Revoked votes will not be counted; restored votes will be counted.
