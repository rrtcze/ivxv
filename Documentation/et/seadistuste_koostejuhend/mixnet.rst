..  IVXV guide for preparing and using the Verificatum mixnet

E-vote Mixing
====================================================

.. _mix-install:

Installing the Verificatum Mixnet
---------------------------------

Prerequisites
^^^^^^^^^^^^^

This guide is intended for use with the Ubuntu 20.04 LTS (Bionic Beaver) distribution and
assumes that commands are executed with regular user privileges, with the right to
escalate privileges using the `sudo` command. Additionally, the following
files are expected to be present in the user's home directory:

From the Github repository (https://github.com/vvk-ehk/intcheck):

* :file:`intcheck.py` - tool for verifying directory integrity

From the IVXV delivery file:

* :file:`gmpmee.dirsha256sum` - ``gmpmee`` directory hash;

* :file:`vmgj.dirsha256sum` - ``vmgj`` directory hash;

* :file:`vcr.dirsha256sum` - ``vcr`` directory hash;

* :file:`vmn.dirsha256sum` - ``vmn`` directory hash;

* :file:`ivxv-verificatum-1.10.3-runner.zip` - IVXV adapter for
  using Verificatum.

From the election organizer:

* :file:`data/bb-4.json` - anonymized e-ballot box;

* :file:`data/pub.pem` - key used for encrypting votes.

There must be no other files in the :file:`data/` directory.

After the process is completed, the following files are needed in the :file:`data/` directory:

* :file:`shuffled.json` - mixed e-ballot box;

* :file:`proof.zip` - proof of correct mixing.


Building Verificatum
^^^^^^^^^^^^^^^^^^^^

Installing packages required for building::

    sudo apt-get install --no-install-recommends -y autoconf autoconf automake \
    build-essential libgmp-dev libtool git openjdk-11-jdk-headless \
    python unzip wget

Downloading Verificatum source code::

    git clone https://github.com/verificatum/verificatum-gmpmee gmpmee
    git clone https://github.com/verificatum/vmgj
    git clone https://github.com/verificatum/vcr
    git clone https://github.com/verificatum/vmn

Creating clean archives from source code for integrity verification::

    cd gmpmee
    git checkout 4aafc31
    rm -rf .git/
    cd ../vmgj
    git checkout 8d7d412
    rm -rf .git/
    cd ../vcr
    git checkout af9fd82
    rm -rf .git/
    cd ../vmn
    git checkout bb00543
    rm -rf .git/
    cd ..

Verifying Verificatum source code integrity::

    chmod +x ./intcheck.py
    ./intcheck.py verify gmpmee gmpmee.dirsha256sum
    ./intcheck.py verify vmgj vmgj.dirsha256sum
    ./intcheck.py verify vcr vcr.dirsha256sum
    ./intcheck.py verify vmn vmn.dirsha256sum

Building `gmpmee`::

    cd gmpmee/
    make -f Makefile.build
    ./configure
    make
    sudo make install

Building `vmgj`::

    cd ../vmgj/
    make -f Makefile.build
    ./configure
    make
    sudo make install

Building `vcr`::

    cd ../vcr/
    make -f Makefile.build
    ./configure --enable-vmgj
    make
    sudo make install

Building `vmn`::

    cd ../vmn/
    make -f Makefile.build
    ./configure
    make
    sudo make install


Unpacking the IVXV Verificatum adapter and launch script::

    cd ..
    unzip ivxv-verificatum-1.10.3-runner.zip

Copying Verificatum libraries to the adapter's external libraries directory::

    cp /usr/local/share/java/verificatum-vmgj-1.2.2.jar mixer/lib/verificatum-vmgj.jar
    cp /usr/local/share/java/verificatum-vcr-vmgj-3.0.4.jar mixer/lib/verificatum-vcr-vmgj.jar
    cp /usr/local/share/java/verificatum-vmn-3.0.4.jar mixer/lib/verificatum-vmn.jar
    cp /usr/local/lib/libgmpmee.so.0.0.0 mixer/lib/libgmpmee.so.0
    cp /usr/local/lib/libvmgj-1.2.2.so mixer/lib/libvmgj-1.2.2.so



.. _mix-mix:


E-vote Mixing
----------------------------------------

Starting the Verificatum mixnet::

    cd data
    ../mixer/bin/mix.py --pubkey pub.pem --ballotbox bb-4.json \
    --shuffled shuffled.json --proof-zipfile proof.zip shuffle

Starting the Verificatum mixnet with prior emptying of the entropy source::

    cd data
    ../mixer/bin/mix.py --pubkey pub.pem --ballotbox bb-4.json \
    --shuffled shuffled.json --proof-zipfile proof.zip --empty-entropy-pool \
    shuffle

.. _mix-verify:

Verifying the Mixing Proof
-------------------------------

The mixing proof can also be verified using the Verificatum adapter::

    cd ..
    mkdir verify
    cp data/proof.zip verify
    cd verify
    ../mixer/bin/mix.py verify --proof-zipfile proof.zip
