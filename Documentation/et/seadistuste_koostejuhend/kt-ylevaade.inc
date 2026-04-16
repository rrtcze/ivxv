..  IVXV collector service management service description

Overview
--------

Collector service management is performed through signed orders. Orders are
prepared by the operator using a text editor or imported from the Election
Information System. Orders are signed with an ID card.

List of collector service management orders:

#. Trust root configuration;

#. Technical configuration;

#. Election configuration;

#. Choices list;

#. Districts list;

#. Voter list;

#. Voter list skipping;

#. User authorization assignment.

In addition to orders, a set of cryptographic keys must also be generated for
the collector service.


Order format
************

The collector service order format is mostly YAML or JSON; a specific format
is used for the voter list.

YAML format orders:

#. Trust root configuration;

#. Technical configuration;

#. Election configuration.

JSON format orders:

#. Choices list;

#. User authorization assignment.

Custom format orders:

#. Voter list.


YAML format orders
~~~~~~~~~~~~~~~~~~

In YAML format configurations, it is possible to include external files. For
this, the tag ``!container`` is used.

Example:

.. code-block:: yaml

   # field "ext_file" value is read from file "certificate-file.pem"
   ext_file: !container certificate-file.pem

.. caution::

   When including external files, it must be considered that configurations
   are loaded into the system in BDOC format containers (see section
   :ref:`korralduspaki-vorming`). This imposes the following requirements on
   including external files:

   * The external files used must be packaged in the same container as the
     configuration file;

   * External files must be located in the same directory as the configuration
     file.


.. _korralduspaki-vorming:

Order package format
********************

An order package is a BDOC format container containing the order file and
signatures. One order package may contain only one order. In the case of YAML
format configurations (trust root configuration, technical configuration, and
election configuration), the file may also contain external files used by the
configuration file.

.. vim:syntax=rst:
