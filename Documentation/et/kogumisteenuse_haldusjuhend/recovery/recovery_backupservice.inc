
Crash occurrence indicators
^^^^^^^^^^^^^^^^^^^^^^^^^^^

Management web interface.
Select **Services** from the left menu. If the backup service has crashed,
its **Status** is **Failure**.

Management command line interface.
Log in as the **ivxv-admin** user and query service statistics::

   $ sudo su - ivxv-admin
   $ ivxv-status

If the backup service has crashed, its **State** is **FAILURE**.


Crash recovery prerequisites
^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Recovery from a crash is always possible.


Possible impact of crash on voting result
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

A backup service crash affects the voting result (data loss) if the
storage service also crashes additionally.


Crash recovery steps
^^^^^^^^^^^^^^^^^^^^

.. seealso::

   * Use the chapter
     **Service machine has crashed, except proxy and X-Road services**
     from the :ref:`recovery-stateless` guide, except steps 8, 10, 12-16.

.. note::

   In step 10, only the backup service **id** and **address**
   fields need to be replaced:

   .. code-block:: yaml

     - id: zone0
       services:
         log:
           - id:          backup@backup1.ivxv.ee
             address:     backup1

   with new ones:

   .. code-block:: yaml

     - id: zone0
       services:
         log:
           - id:          backup@backup2.ivxv.ee
             address:     backup2

SSH log in to the management machine as the **ivxv-admin** user::

    $ sudo su - ivxv-admin

Configure to avoid confirming the *prompt* message
*Are you sure you want to continue connecting (yes/no)? yes* when establishing
an SSH connection, for example, if the backup service machine's DNS **address** is *backup2*::

    $ ssh backup2
    $ echo "StrictHostKeyChecking no" >> /var/lib/ivxv/user/ivxv-admin/.ssh/config
