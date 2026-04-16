..  IVXV technical documentation

Running List of E-votes
=======================

The service mediates the running list from the vote collector service to X-Road.

.. figure:: model/xteevotesorder.png

   X-Road security server communication with the vote collector service

Election events whose list can be queried are configured in the service.

The service provides three endpoints:

1. ``Election event list`` - returns the list of active election events

2. ``Last sequence number`` - returns the last e-vote sequence number registered in the vote collector service for a specific election event.

3. ``E-vote batch`` - returns the e-vote batch from the vote collector service for an election event, starting from the e-vote with the given sequence number.
