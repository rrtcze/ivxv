..  IVXV protocols

================================================================================
Overview
================================================================================

The electronic voting protocol suite (hereinafter protocol suite) defines the
message exchange between the components of the electronic voting system, the
data structures used, algorithms, and interfaces with external systems.
Message exchange is presented as UML interaction diagrams that unambiguously
define the sequence of messages. Data structure descriptions are accompanied
by specifications in BNF, ASN.1, or JSON-schema notation. Algorithms are
presented as pseudocode.

NB! In all data structure fields of the protocol suite, the permitted
characters and the minimum and maximum field lengths must be strictly adhered
to. The use of additional spaces, tabs, etc. is prohibited, and applications
implementing the specification must refuse to process data that does not
conform to the format.

The protocol suite defines the electronic voting protocol and the supporting
structures necessary for implementing this protocol.

Electronic Voting Protocol
====================================

The electronic voting protocol specifies:

#. the format of the electronic vote, which enables unambiguous determination
   of the voter's intent in a specific election;

#. the encryption of the electronic vote to ensure vote secrecy;

#. the digital signing of the electronic vote to ensure integrity and voter
   identification;

#. the qualification of the electronic vote by the collection service, to
   mark the acceptance of the vote;

The protocol assumes that the election organizer defines the election and
generates a key pair for vote encryption, the public component of which is
made available to the voter application.

Through the protocol, the voter's intent moves into the e-ballot box stored
in the collection service and is taken into account in forming the result
through the following sequence of events:

#. The voter uses the voter application to electronically formalize their
   expression of will:

   #. the expression of will is formalized as an electronic vote;

   #. the formalized vote is encrypted;

   #. the encrypted vote is signed on the voter's computer.

#. The collection service stores the electronic vote, forming a qualified
   digital signature on the vote in the process:

   #. the electronic vote is registered in an external registration service;

   #. a digital timestamp is obtained for the electronic vote;

   #. a validity confirmation is obtained for the voter's certificate;

   #. elements qualifying the electronic vote are also returned to the voter
      application for verification and to inform the voter of the
      qualification results;

   #. the voter is enabled to verify the qualified electronic vote using the
      verification application.

.. note::

   The digital signing of an electronic vote differs from the usual digital
   signing of documents, where all actions necessary for qualifying the
   signature are initiated directly on the signer's device. The obligation to
   qualify the electronic vote lies with the collection service, whose task
   is to verify the correct signing of accepted votes. Since the load on
   related services is high during the e-voting period, qualification
   managed by the collection service allows for better service quality.

#. The voter may use the verification application to verify the correct
   handling of their vote by the collection service;

#. At the end of the voting period, the collection service issues the
   e-ballot box to the election organizer, and the registration service
   issues an extract of the votes registered by the collection service;

   #. as part of the e-ballot box, the following are handed over to the
      election organizer:

      #. the voter's encrypted expression of will together with the signature;

      #. the registration service's confirmation of vote registration;

      #. the digital timestamp issued by the timestamping service for the
         electronic vote;

      #. the confirmation issued by the validity confirmation service
         regarding the validity of the voter's certificate;

      #. as part of the registration service extract, the following are
         handed over to the election organizer:

         #. all requests sent by the collection service to the registration
            service during the e-voting period for registering electronic
            votes.

#. The election organizer calculates the voting result:

   #. the validity of signatures on the handed-over electronic votes is
      verified;

   #. it is verified that all votes registered in the registration service
      have been handed over as part of the e-ballot box;

   #. the encrypted votes and digital signatures are separated;

   #. the encrypted votes are cryptographically anonymized;

   #. the encrypted votes are decrypted;

   #. the voting result is calculated based on the decrypted votes.

The protocol is analogous to the postal voting protocol on paper, where the
voter's intent reaches the election commission in two envelopes – inside the
outer envelope is an inner envelope, which in turn contains the ballot with
the voter's expression of will. The outer envelope carries information
identifying the voter and enables, among other things, verification of the
voter's right to vote. The inner envelope is anonymous and protects vote
secrecy. Before counting the votes, the inner envelopes are separated from
the outer ones.

In the context of electronic voting, the inner envelope is formalized as an
encrypted vote and the outer envelope as a digitally signed document.
