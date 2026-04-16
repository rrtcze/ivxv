..  IVXV configuration preparation guide

.. _kt-voter-list-skip:

Voter list skipping
-------------------

Voter list skipping means replacing a faulty voter list registered in the
management service with an empty list.

The procedure is necessary in a situation where the management service has
downloaded and registered in the management service a voter changeset list from
the Election Information System that cannot be applied to the collector service
(the list is faulty or not compatible with other collector service settings).

The voter list skipping order is prepared by the election organizer.

The configuration file name must always end with the string :file:`.skip.yaml`.

:election:

        Required field.
        Unique election identifier.

:skip_voter_list:

        Required field.
        Version of the voter changeset list to be skipped.

:changeset:

        Required field.
        Sequence number of the voter changeset list to be skipped.

Example
*******

:file:`example.voters.skip.yaml`:

.. literalinclude:: config-examples/example.voters.skip.yaml
   :language: yaml
   :linenos:

.. vim:syntax=rst:
