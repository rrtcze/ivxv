..  IVXV arhitektuur

Introduction
============

The electronic voting information system IVXV has been created based on the
e-voting framework [ÜK2016]_ and the technical description of public
procurement 171780 [TK2016]_.
This document describes the architectural solution of IVXV. The electronic
voting information system consists of offline mode applications and
online mode components. Additionally, the information system depends on external
information systems and directly affects the components used for electronic
voting and vote verification.

The architecture document describes IVXV components, their mutual interfaces and
interfaces with external systems, as well as the protocols implemented by the
components.

IVXV Concept
------------------

A general but comprehensive overview of the technical and organizational
aspects of the electronic voting framework ("IVXV") and its application in
Estonian national elections is provided in the general description of the
e-voting framework [ÜK2016]_.

IVXV as an information system implements an e-voting protocol based on the
"envelope scheme". IVXV operates during the pre-voting phase, the voting
phase, the processing phase, and the counting phase, and provides means for
participation in the electronic voting process for the Organizer, the
Counter, the Voter, the Collector, the Processor, the Mixer, the Auditor,
the Client Support, and the compiler and supplementor of the voter lists.

The components of the information system are the Collector Service, the
Processing Application, the Key Application, and the Audit Application. Closely
related to the information system are the Voter Application, the Verification
Application, and the Mixing Application.

The information system uses external services in its operation - the
Authentication Service, the Signing Service, the Registration Service,
the Election Information System, and X-Road.

IVXV Cryptographic Protocol
-------------------------------

To achieve the security, verifiability, ballot secrecy, voting correctness,
and voter independence of electronic voting, the cryptographic protocol for
electronic voting is strictly defined [HMVW16]_. The protocol provides the
necessary and sufficient overview of IVXV's structure and its security aspects.
IVXV components implement sub-parts of the cryptographic protocol.

Notation
----------

To illustrate the architectural solution sketch, the document uses UML diagrams,
where we distinguish the following aspects of entities – actors, interfaces,
components – encoded with colors and labels ``<<>>``:

* Label ``<<IVXV>>`` (Yellow) – the interface or component of the information
  system is defined/implemented during the work carried out within the scope
  of the specific procurement

* Label ``<<External>>`` (Red) – the information system depends on a third-party
  component or an existing interface for the implementation of some
  functionality, the redefinition of which also requires work by third parties.

* Label ``<<NEC>>`` (Brown) – similar to the previous, but the owner of the
  interface/component is the NEC (National Electoral Committee).

* Label ``<<Undefined>>`` (Black) – an important interface for the information
  system is undefined.

.. figure:: model/img/example.png

   Example diagram
