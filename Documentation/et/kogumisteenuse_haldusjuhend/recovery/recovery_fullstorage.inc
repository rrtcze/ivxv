Crash occurrence indicators
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Management web interface.
Select **Services** from the left menu. If the storage services have crashed,
their **Status** is **Failure**.

Management command line interface.
Log in as the **ivxv-admin** user and query service statistics::

   $ sudo su - ivxv-admin
   $ ivxv-status

If the storage services have crashed, their **State** is **FAILURE**.


Crash recovery prerequisites
^^^^^^^^^^^^^^^^^^^^^^^^^^^^

For crash recovery it is sufficient that the services' CA TLS private key and
certificate are preserved, which can be used to generate backup keys and
certificates for the service. Alternatively, backup keys and certificates for
the service can also be pre-generated before the elections.

If the CA for all services is the same, it is advisable to put the CA TLS
certificate into the voter and verification application settings instead. If the
CA differs between services, then all service TLS certificates must be placed
into the application settings immediately before the elections.


Possible impact of crash on voting result
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

If the storage service cluster crashes, there is certainly data loss.
The extent of data loss depends on the backup service, i.e., how often the
e-ballot box was backed up.

Additionally, voters who have already voted may become confused when voting
a second time, as the voter application displays the greeting text
"You have not yet voted".


Crash recovery steps
^^^^^^^^^^^^^^^^^^^^

.. seealso::

   * Perform the procedures from the chapter
     **Service data (key, certificate, etc.) is corrupted or machine crash**
     in the :ref:`recovery-storageservice` guide for each new collector machine.

.. note::

   In step 10, all old **id** and **address** entries need to be replaced
   with new ones, and additionally the storage service **bootstrap**
   setting needs to be changed:

   .. code-block:: yaml

      bootstrap:
      - storage@storage1.ivxv.ee
      - storage@storage2.ivxv.ee
      - storage@storage3.ivxv.ee

   as follows:

   .. code-block:: yaml

      bootstrap:
      - storage@storage4.ivxv.ee
      - storage@storage5.ivxv.ee
      - storage@storage6.ivxv.ee

Now the collector's pre-crash state needs to be restored, except for the lost votes:

   #. SSH log in to the management machine as the **ivxv-admin** user::

         $ sudo su - ivxv-admin

   #. Load the districts list::

         $ ivxv-config-apply --type=districts

   #. Load the choices list::

         $ ivxv-config-apply --type=choices

   #. Load both the initial voter list and all intermediate change lists::

         $ ivxv-config-apply --type=voters

.. warning::
   Do not forget that at the end of the elections, votes must be downloaded
   together with the backed up votes, to ensure the integrity of the e-ballot
   box to at least some extent::

      $ ivxv-export-votes --consolidate
