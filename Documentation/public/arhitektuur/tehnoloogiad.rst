..  IVXV arhitektuur

.. _tehnoloogiad:

Technologies Used
========================

Collector Service Programming Language
----------------------------------

The core functionality of the collector service is programmed in Go, which
meets the following procurement requirements:

* Static typing;

* Automatic memory management;

* Open source compiler;

* Concurrency (parallelism).

The collector service management service is programmed in Python.


Applications Programming Language
------------------------------

The applications are programmed in Java, which meets the procurement
requirements for the language's wide adoption and sustainability.


Project Dependencies
-------------------

Third-party components used in the project along with the justified need for
their use are listed in the following tables. Separate tables are provided for
the framework's packaging and operation, and for the framework's development and
testing.

All external libraries used in the IVXV project reside in the
``ivxv-external.git`` repository or are available on the platform where
the application will run.

All components used in the collector service are open source.

.. tabularcolumns:: |p{0.2\linewidth}|p{0.1\linewidth}|p{0.15\linewidth}|p{0.55\linewidth}|
.. list-table::
   Third-party components used for IVXV framework operation
   :header-rows: 1

   *  - Name
      - Version
      - License (SPDX)
      - Usage need

   *  - `Bootstrap <http://getbootstrap.com>`_
      - 3.4.1, JavaScript
      - MIT
      - Collector service management service user interface design

   *  - Bouncy Castle
      - 1.78.1, Java
      - MIT
      - ASN1 handling, BigInteger data type utility functions

   *  - `Bottle <https://bottlepy.org/>`_
      - 0.13.2, Python
      - MIT
      - Framework for implementing the collector service management service web interface

   *  - CAL10N
      - 0.8.1, Java
      - MIT
      - Multilingual support, translation file validation

   *  - Digidoc 4j
      - 5.3.1, Java
      - LGPL-2.1-only
      - BDoc container handling

   *  - Apache Commons (collections4 4.4)
      - Java
      - Apache-2.0
      - Digidoc 4j and PDFBox dependencies

   *  - `Docopt <http://docopt.org/>`_
      - 0.6.2, Python
      - MIT
      - Implementation of the collector service administration utilities command line interface

   *  - `Fasteners <https://github.com/harlowja/fasteners>`_
      - 0.19, Python
      - Apache-2.0
      - Collector service management service process locking

   *  - `gin-gonic <https://github.com/gin-gonic>`_
      - 1.9.1, Go
      - MIT
      - Web framework for X-Road interface

   *  - `etcd <https://coreos.com/etcd>`_
      - 3.5.9, Go
      - Apache-2.0
      - Distributed key-value database used as the storage service

   *  - Glassfish JAXB
      - 4.0.5, Java
      - BSD-3-Clause
      - Java XML library

   *  - Gradle
      - 8.11, Java
      - Apache-2.0
      - Build framework for Java applications

   *  - `HAProxy <http://www.haproxy.org/>`_
      - 2.4.24
      - GPL-2.0-or-later
      - TCP proxy used as the proxy service

   *  - Jackson
      - 2.18.1, Java
      - Apache-2.0
      - Reading and writing JSON format files

   *  - Jinja2
      - 3.1.4, Python
      - BSD
      - Using Jinja templates in the management service

   *  - `jQuery <https://jquery.org/>`_
      - 3.7.1, JavaScript
      - MIT
      - Collector service management service user interface

   *  - jsonschema
      - 4.23.0, Python
      - MIT
      - JSON validation in the management service

   *  - Logback
      - 1.5.12, Java
      - EPL-1.0 or LGPL-v2.1-only
      - Logging API implementation

   *  - Logback JSON
      - 0.1.5, Java
      - EPL-1.0 or LGPL-v2.1-only
      - Logback logger extension for composing log entries in JSON format
        using the Jackson library

   *  - `Logrus <https://github.com/sirupsen/logrus>`_
      - 1.9.3, Go
      - MIT
      - Logging framework for X-Road interface

   *  - `metisMenu <https://github.com/onokumus/metisMenu>`_
      - 1.1.3, JavaScript
      - MIT
      - Collector service management service user interface

   *  - `FontAwesome <https://github.com/FortAwesome/Font-Awesome>`_
      - 6.7.2, JavaScript
      - MIT
      - Collector service management service user interface

   *  - `DataTables <https://github.com/DataTables/DataTablesSrc>`_
      - 2.3.2, JavaScript
      - MIT
      - Collector service management service user interface

   *  - PDFBox
      - 3.0.3, Java
      - Apache-2.0
      - PDF format report generation support for Java applications

   *  - `PyYAML <http://pyyaml.org/>`_
      - 6.0.2, Python
      - MIT
      - Collector service configuration file processing support for the management service

   *  - python-crontab
      - 3.3.0, Python
      - LGPLv3
      - Crontab in the management service

   *  - python-dateutil
      - 2.9.0, Python
      - BSD
      - Dates and times in the management service

   *  - python-debian
      - 0.1.49, Python
      - GPLv2
      - Reading Debian packages in the management service

   *  - pyopenssl
      - 24.2.1, Python
      - Apache
      - OpenSSL usage in the management service

   *  - `Schematics <https://github.com/schematics/schematics>`_
      - 2.1.1, Python
      - BSD-3-Clause
      - Collector service configuration file validation support for the management service

   *  - SnakeYAML
      - 2.3, Java
      - Apache-2.0
      - Reading YAML format data

   *  - `SB Admin 2 <https://github.com/BlackrockDigital/startbootstrap-sb-admin-2>`_
      - 3.3.7+1, JavaScript
      - MIT
      - Collector service management service user interface design

.. tabularcolumns:: |p{0.2\linewidth}|p{0.1\linewidth}|p{0.15\linewidth}|p{0.55\linewidth}|
.. list-table::
   Third-party components used for IVXV framework testing
   :header-rows: 1

   *  - Name
      - Version
      - License (SPDX)
      - Usage need

   *  - Hamcrest
      - 3.0, Java
      - BSD-3-Clause
      - More readable assert method usage in Java unit tests

   *  - JUnit
      - 5.10.0, Java
      - EPL-1.0
      - Java testing framework

   *  - JUnitParams
      - 1.1.1, Java
      - Apache-2.0
      - Test parameterization support

   *  - Mockito
      - 5.14.2, Java
      - MIT
      - Support for mocking dependencies of tested code

   *  - libdigidocpp-tools
      - 3.14.5 .1404
      - LGPL-2.1-or-later
      - Test data generation

   *  - PyTest
      - 7.4.2, Python
      - MIT
      - Unit testing support for Python

   *  - Requests
      - 2.32.3, Python
      - Apache 2.0
      - HTTP request module for Python tests

.. tabularcolumns:: |p{0.2\linewidth}|p{0.1\linewidth}|p{0.15\linewidth}|p{0.55\linewidth}|
.. list-table::
   Third-party tools used for IVXV framework development and/or testing
   :header-rows: 1

   *  - Name
      - Version
      - License (SPDX)
      - Usage need

   *  - `Behave <https://github.com/behave/behave>`_
      - 1.2.6, Python
      - BSD-2-Clause
      - Regression test runner (*Behavior-driven development*)

   *  - `Docker <http://www.docker.com/>`_
      - 18.06 (or newer)
      - Apache-2.0
      - Regression testing environment - software containers

   *  - `Sphinx <http://www.sphinx-doc.org/>`_
      - 7.2.5, Python
      - BSD
      - Documentation generation
