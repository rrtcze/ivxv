Crash occurrence indicators
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Management web interface.
Select **Services** from the left menu. If the service has crashed,
its **Status** is **Failure**.

Management command line interface.
Log in as the **ivxv-admin** user and query service statistics::

   $ sudo su - ivxv-admin
   $ ivxv-status

If the service has crashed, its **State** is **FAILURE**.


Crash recovery prerequisites
^^^^^^^^^^^^^^^^^^^^^^^^^^^^

For crash recovery it is sufficient that the services' CA TLS private key and
certificate are preserved, which can be used to generate backup keys and
certificates for the service. Alternatively, backup keys and certificates for
the service can also be pre-generated before the elections.

If the CA for all services is the same, it is advisable to put the CA
certificate into the voter and verification application settings instead. If the
CA differs between services, then all service TLS certificates must be placed
into the application settings immediately before the elections.


Possible impact of crash on voting result
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Depending on the service, the consequences may be as follows:

   * if the choices, Mobile-ID, proxy, session, Smart-ID,
     voting, Web-eID services crash, the voter will not be able to vote

   * if the queue and X-Road services crash, VIS will not be able to query
     data via X-Road

   * if the verification service crashes, the voter will not be able to
     verify their vote


Crash recovery steps
^^^^^^^^^^^^^^^^^^^^

.. seealso::

   * The storage service is not covered in this guide, there is
     a separate guide :ref:`recovery-storageservice`

The crash can be classified as follows:

   #. The service is healthy and only needs a restart, except X-Road service

   #. The service data (TLS private key, certificate, etc.) is corrupted, except
      proxy and X-Road services

   #. There is a bug in the service source code, except X-Road service

   #. X-Road service recovery, including crash and source code bug

   #. The service machine has crashed, except proxy and X-Road services

   #. The proxy service machine has crashed

The service is healthy and only needs a restart, except X-Road service
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

   #. SSH log in to the management machine as the **ivxv-admin** user::

         $ sudo su - ivxv-admin

   #. Restart the service, for example the choices service::

         $ ivxv-service restart choices@choices1.ivxv.ee

Service data (TLS private key, certificate, etc.) is corrupted, except proxy and X-Road services
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

   #. Replace the crashed service's **id** in the technical configuration
      with the backup service's **id**, whose TLS private key and certificate
      have been generated

   #. Sign the technical configuration

   #. Load the configuration through the management web interface **Settings**

   #. SSH log in to the management machine as the **ivxv-admin** user::

         $ sudo su - ivxv-admin

   #. Load the TLS private key and certificate, for example the choices service::

         $ ivxv-secret-load --service=choices@choices4.ivxv.ee tls-key /opt/ivxv-install/service_definition/choices@choices4.ivxv.ee.key
         $ ivxv-secret-load --service=choices@choices4.ivxv.ee tls-cert /opt/ivxv-install/service_definition/choices@choices4.ivxv.ee.pem

   #. If it is a choices, Mobile-ID, Smart-ID, voting, Web-eID, or
      verification service, then the private key for signing cookies
      also needs to be uploaded::

         $ ivxv-secret-load mid-token-key /opt/ivxv-install/service_definition/ticket.key

   #. If it is a voting service, then the private key for signing the TSP
      response hash also needs to be uploaded::

         $ ivxv-secret-load tsp-regkey /opt/ivxv-install/service_definition/tspreg.key

   #. Start the services::

         $ ivxv-config-apply --type=election

There is a bug in the service source code, except X-Road service
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

   #. Copy the new *.deb* package to the management machine

   #. SSH log in to the management machine as the **sudo** user::

         $ sudo su

   #. Copy the *.deb* package to the */etc/ivxv/debs/* folder

   #. Log out from the **sudo** user::

         $ exit

   #. SSH log in to the management machine as the **ivxv-admin** user::

         $ sudo su - ivxv-admin

   #. Update the service *.deb* package on all machines, for example the choices service::

         $ ivxv-update-packages --service=choices --package=/etc/ivxv/debs/ivxv-choices_1.9.12~dev_amd64.deb

   #. Restart the service on each host, for example restarting the choices service
      with a three-shoulder configuration::

         $ ivxv-service restart choices@choices1.ivxv.ee
         $ ivxv-service restart choices@choices2.ivxv.ee
         $ ivxv-service restart choices@choices3.ivxv.ee

X-Road service recovery, including crash and source code bug
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

   #. First, try restarting the systemd X-Road service::

         $ sudo systemctl restart xroad-service

   #. In case of failure, a new *.deb* package needs to be delivered, and
      the old package removed::

         $ sudo apt purge xroad-service

   #. Once the new *.deb* package has been copied to the machine, it needs to be installed::

         $ sudo apt install ./xroad-service_*.deb

   #. Use the X-Road service guide to install the TLS certificates into the correct
      directories

   #. Start the systemd X-Road service::

         $ sudo systemctl start xroad-service

The service machine has crashed, except proxy and X-Road services
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

   #. Install a fresh Ubuntu machine

      .. important::
         Please verify which Ubuntu version is currently
         being used

   #. Install the base software packages on the service machine from the APT
      package repository::

         $ sudo apt-get install acl locales unzip zstd --yes

   #. Now the management, collector, backup, log, proxy, log
      monitoring machines' **ip** and DNS **name** need to be added to the new
      service machine's */etc/hosts* file

   #. Then in the management, collector, backup, log, proxy machines,
      the crashed service machine's **ip** and DNS **name** need to be deleted
      and new ones added

      .. attention::

         This is the most important step, as here you must choose a DNS
         **name** that will be added to the technical configuration in the future.

         The rule is simple: each new service machine's DNS **name** must be
         unique and must not be the same as those previously assigned to crashed
         service machines. The management service database has registered
         the DNS **names** of all machines in the system, even those of crashed
         instances. The management service's peculiarity is that it does not
         install software on machines whose DNS **name** is already
         registered in the management service database.

   #. SSH log in to the management machine as the **ivxv-admin** user::

         $ sudo su - ivxv-admin

   #. Since the management service installs the required infrastructure on all system
      machines automatically, it is necessary to avoid confirming the SSH connection
      *prompt* message *Are you sure you want to continue connecting (yes/no)? yes*.

      Delete the old service machine's SSH public key from the */etc/ssh/ssh_known_hosts*
      file, and add a new one, for example, if the new service machine's DNS **name** is
      *ivxv4*::

         $ ssh-keyscan -t ecdsa ivxv4 | grep -v ^# >> /etc/ssh/ssh_known_hosts

   #. SSH log in to the new service machine as the **root** user::

         $ sudo su

   #. Since the management service transmits service logs to the log monitor,
      in addition to *syslog* *RELP* protocol, also over SSH protocol, it is
      likewise necessary to avoid confirming the SSH connection *prompt* message,
      for example, with the monitoring machine *logmonitor* DNS **address**::

         $ ssh-keyscan -t ecdsa logmonitor | grep -v ^# >> /etc/ssh/ssh_known_hosts

   #. Since the management service needs to install software from the APT package
      repository, which is impossible without acquiring root user privileges, you
      must copy the management machine's SSH public key, located in the
      */var/lib/ivxv/user/ivxv-admin/.ssh/id_ed25519.pub* file, and add
      it to the new service machine's */root/.ssh/authorized_keys* file

   #. Now in the technical configuration, the service **id** and
      **names** (**address**) need to be replaced, for example:

      .. code-block:: yaml

         - id: zone1
            services:
               mid:
                  - id:         mid@mid1.ivxv.ee
                   address:     ivxv1:4441
               choices:
                  - id:         choices@choices1.ivxv.ee
                   address:     ivxv1:4442
               voting:
                  - id:         voting@voting1.ivxv.ee
                   address:     ivxv1:4443
               verification:
                  - id:         verification@verification1.ivxv.ee
                   address:     ivxv1:4444
               smartid:
                  - id:         smartid@smartid1.ivxv.ee
                   address:     ivxv1:4445
               votesorder:
                  - id:         votesorder@votesorder1.ivxv.ee
                   address:     ivxv1:4446
               webeid:
                  - id:         webeid@webeid1.ivxv.ee
                   address:     ivxv1:4447
                   origin:      https://ivxv1.test.ivxv.ee:443
               sessionstatus:
                  - id:         sessionstatus@sessionstatus1.ivxv.ee
                   address:     ivxv1:4448

      with new **id** and **address**:

      .. code-block:: yaml

         - id: zone1
            services:
               mid:
                  - id:         mid@mid4.ivxv.ee
                   address:     ivxv4:4441
               choices:
                  - id:         choices@choices4.ivxv.ee
                   address:     ivxv4:4442
               voting:
                  - id:         voting@voting4.ivxv.ee
                   address:     ivxv4:4443
               verification:
                  - id:         verification@verification4.ivxv.ee
                   address:     ivxv4:4444
               smartid:
                  - id:         smartid@smartid4.ivxv.ee
                   address:     ivxv4:4445
               votesorder:
                  - id:         votesorder@votesorder4.ivxv.ee
                   address:     ivxv4:4446
               webeid:
                  - id:         webeid@webeid4.ivxv.ee
                   address:     ivxv4:4447
                   origin:      https://ivxv4.test.ivxv.ee:443
               sessionstatus:
                 - id:          sessionstatus@sessionstatus4.ivxv.ee
                   address:     ivxv4:4448

      .. attention::
         Note that both **id** and **address** have changed.
         The proxy and storage service **id** and **address** remain the same
         **if and only if** those services were not part of the crashed machine;
         otherwise, those services' **id** and **address** must be similarly changed.

   #. Sign the new technical configuration. Load it through the
      management web interface, selecting **Settings** from the left.

   #. SSH log in to the management machine as the **ivxv-admin** user::

         $ sudo su - ivxv-admin

   #. Load all service TLS private keys and certificates, for example::

         $ ivxv-secret-load --service=choices@choices4.ivxv.ee tls-key /opt/ivxv-install/service_definition/choices@choices4.ivxv.ee.key
         $ ivxv-secret-load --service=voting@voting4.ivxv.ee tls-key /opt/ivxv-install/service_definition/voting@voting4.ivxv.ee.key
         $ ivxv-secret-load --service=mid@mid4.ivxv.ee tls-key /opt/ivxv-install/service_definition/mid@mid4.ivxv.ee.key
         $ ivxv-secret-load --service=smartid@smartid4.ivxv.ee tls-key /opt/ivxv-install/service_definition/smartid@smartid4.ivxv.ee.key
         $ ivxv-secret-load --service=sessionstatus@sessionstatus4.ivxv.ee tls-key /opt/ivxv-install/service_definition/sessionstatus@sessionstatus4.ivxv.ee.key
         $ ivxv-secret-load --service=verification@verification4.ivxv.ee tls-key /opt/ivxv-install/service_definition/verification@verification4.ivxv.ee.key
         $ ivxv-secret-load --service=votesorder@votesorder4.ivxv.ee tls-key /opt/ivxv-install/service_definition/votesorder@votesorder4.ivxv.ee.key
         $ ivxv-secret-load --service=webeid@webeid4.ivxv.ee tls-key /opt/ivxv-install/service_definition/webeid@webeid4.ivxv.ee.key
         $ ivxv-secret-load --service=choices@choices4.ivxv.ee tls-cert /opt/ivxv-install/service_definition/choices@choices4.ivxv.ee.pem
         $ ivxv-secret-load --service=voting@voting4.ivxv.ee tls-cert /opt/ivxv-install/service_definition/voting@voting4.ivxv.ee.pem
         $ ivxv-secret-load --service=mid@mid4.ivxv.ee tls-cert /opt/ivxv-install/service_definition/mid@mid4.ivxv.ee.pem
         $ ivxv-secret-load --service=smartid@smartid4.ivxv.ee tls-cert /opt/ivxv-install/service_definition/smartid@smartid4.ivxv.ee.pem
         $ ivxv-secret-load --service=sessionstatus@sessionstatus4.ivxv.ee tls-cert /opt/ivxv-install/service_definition/sessionstatus@sessionstatus4.ivxv.ee.pem
         $ ivxv-secret-load --service=verification@verification4.ivxv.ee tls-cert /opt/ivxv-install/service_definition/verification@verification4.ivxv.ee.pem
         $ ivxv-secret-load --service=votesorder@votesorder4.ivxv.ee tls-cert /opt/ivxv-install/service_definition/votesorder@votesorder4.ivxv.ee.pem
         $ ivxv-secret-load --service=webeid@webeid4.ivxv.ee tls-cert /opt/ivxv-install/service_definition/webeid@webeid4.ivxv.ee.pem

   #. Add the cookie signing key::

      $ ivxv-secret-load mid-token-key /opt/ivxv-install/service_definition/ticket.key

   #. Add the voting service TSP hash signing key::

      $ ivxv-secret-load tsp-regkey /opt/ivxv-install/service_definition/tspreg.key

   #. Start the services::

      $ ivxv-config-apply --type=election

The proxy service machine has crashed
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. seealso::

   * Use the chapter
     **The service machine has crashed, except proxy and X-Road services**
     from this guide, except steps 6, 10-12.

.. note::

   In step 8, only the old proxy service **id** and **address** need to be replaced:

   .. code-block:: yaml

     - id: zone1
       services:
         proxy:
           - id:          proxy@proxy1.ivxv.ee
             address:     proxy1:443

   with new ones:

   .. code-block:: yaml

     - id: zone1
       services:
         proxy:
           - id:          proxy@proxy4.ivxv.ee
             address:     proxy4:443
