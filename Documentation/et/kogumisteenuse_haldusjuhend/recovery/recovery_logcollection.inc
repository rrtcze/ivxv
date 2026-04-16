Crash occurrence indicators
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Management web interface.
Select **Services** from the left menu. If the log collection service has crashed,
its **Status** is **Failure**.

Management command line interface.
Log in as the **ivxv-admin** user and query service statistics::

   $ sudo su - ivxv-admin
   $ ivxv-status

If the log collection service has crashed, its **State** is **FAILURE**.


Crash recovery prerequisites
^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Recovery from a crash is always possible.


Possible impact of crash on voting result
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

There is no impact on the voting result, however with a crashed log collection
service, some of the backed up logs are also lost and can no longer be
recovered. At the same time, these logs are still preserved on the collector
machines and on the log monitor machine. The only place where the log collection
service crash manifests is the backup service machine, where some of the backed
up logs will be missing.


Crash recovery steps
^^^^^^^^^^^^^^^^^^^^
.. seealso::

   * Use the chapter
     **Service machine has crashed, except proxy and X-Road services**
     from the :ref:`recovery-stateless` guide, except steps 10, 12-16.


.. note::

   In step 10, only the log collection service **id** and
   **address** fields need to be replaced:

   .. code-block:: yaml

     - id: zone0
       services:
         log:
           - id:          log@log1.ivxv.ee
             address:     log1:20514

   with new ones:

   .. code-block:: yaml

     - id: zone0
       services:
         log:
           - id:          log@log2.ivxv.ee
             address:     log2:20514
