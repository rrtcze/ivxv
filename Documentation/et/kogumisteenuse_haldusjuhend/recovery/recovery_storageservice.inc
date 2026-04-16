Crash occurrence indicators
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Management web interface.
Select **Services** from the left menu. If the storage service has crashed,
its **Status** is **Failure**.

Management command line interface.
Log in as the **ivxv-admin** user and query service statistics::

   $ sudo su - ivxv-admin
   $ ivxv-status

If the storage service has crashed, its **State** is **FAILURE**.


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

All requests sent to the crashed storage service machine will fail.
The voter cannot authenticate or vote.


Crash recovery steps
^^^^^^^^^^^^^^^^^^^^

The crash can be classified as follows:

   #. The storage service is healthy and only needs a restart

   #. The storage service data (key, certificate, etc.) is corrupted or machine
      crash

   #. There is a bug in the storage service source code

The storage service is healthy and only needs a restart
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. seealso::

   * Use the chapter
     **Service is healthy and only needs a restart, except X-Road service**
     from the :ref:`recovery-stateless` guide

Storage service data (key, certificate, etc.) is corrupted or machine crash
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. seealso::

   * Use the chapter
     **Service machine has crashed, except proxy and X-Road services**
     from the :ref:`recovery-stateless` guide


.. note::

   In step 10, the old storage service **id** and **address** fields need to be replaced:

   .. code-block:: yaml

     - id: zone1
       services:
         storage:
           - id:          storage@storage1.ivxv.ee
             address:     ivxv1:2379
             peeraddress: ivxv1:2380

   with new ones:

   .. code-block:: yaml

      - id: zone1
        services:
          storage:
            - id:          storage@storage4.ivxv.ee
              address:     ivxv4:2379
              peeraddress: ivxv4:2380

   In step 12, the storage service TLS private key also needs to be updated::

      $ ivxv-secret-load --service=storage@storage4.ivxv.ee tls-key /opt/ivxv-install/service_definition/storage@storage4.ivxv.ee.key

   and certificate:::

      $ ivxv-secret-load --service=storage@storage4.ivxv.ee tls-cert /opt/ivxv-install/service_definition/storage@storage4.ivxv.ee.pem

Verify that the replacement went smoothly:

   #. SSH log in to the new collector machine as the *root* user::

      $ sudo su

   #. Query the database cluster status, for example, if the cluster consists of
      the *ivxv4*, *ivxv2*, *ivxv3* machines::

      $ cd /var/lib/ivxv/service/storage@storage4.ivxv.ee
      $ env ETCDCTL_API=3 etcdctl --endpoints=ivxv4:2379,ivxv2:2379,ivxv3:2379 --cert tls.pem --key tls.key --cacert ca.pem endpoint status -w table

There is a bug in the storage service source code
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

If there is a bug in the storage service source code, it can be
replaced with a newer version without corrupting the existing database
cluster.

.. seealso::

   * Use the chapter
     **There is a bug in the service source code, except X-Road service**
     from the :ref:`recovery-stateless` guide
