..  IVXV use cases

Introduction
============

This document describes the use case model of the electronic voting system. The document is divided into two parts: actors and use cases. The first part describes the actors of the use case model. The second part describes the use cases of the electronic voting system.

References
----------
1.  [UML] – UML Distilled. A Brief Guide to the Standard Object Modeling Language UML 2.0. Martin Fowler. Cybernetica AS.

Methodology Used
----------------

Use Case Model
``````````````
    Use cases are a tool that helps understand the functional requirements of a system. Use cases present an external view of the system by describing interactions between system users and the system for fulfilling user goals. The use case model consolidates all significant use cases of the system being analyzed [UML].

Actor
`````
    An actor is a role that a user plays in relation to the system. An actor does not have to be a human. If the system being modeled provides a service to another computer system, that other system is an actor.

Use Case
````````

Description
'''''''''''

A use case is a collection of scenarios united by a common user goal. Each scenario is a sequence of actions performed in the system that produces a visible and useful result for the actor.

Precondition
''''''''''''

A precondition describes the conditions that the system must ensure are met before it allows the execution of the use case to begin.

Trigger
'''''''

A trigger specifies the event that initiates the use case.

Main Process
''''''''''''

The main process describes the primary scenario of the use case.

Extensions
''''''''''

An extension in a use case names a condition that results from different interactions than those described in the success main scenario, and states what those differences are.

Postcondition
'''''''''''''

The fulfillment of the postcondition is guaranteed by the system at the end of the use case execution.

E-voting Stages
---------------

E-voting is organizationally divided into five stages:

- pre-voting stage
- voting stage
- processing stage
- counting stage
- auditing stage

Definitions
-----------

The term *person* may denote both a natural person and a legal person. We assume that the person carrying out specific actions is always a uniquely identifiable natural person who may act as an authorized representative of a legal person.

The term *server system* denotes a complete set of software and hardware components that together implement a specific protocol and provide a service to many users over an extended period of time.

The term *interface* denotes a clearly specified point of contact between system components that enables information exchange between components.

The term *application* denotes a software component that is launched at a specific point in time on a single hardware component by a single user. An application may communicate with a server system to fulfill its task.

The term *service* denotes a component external to the system with which the system exchanges data through specific interfaces to fulfill its tasks.
