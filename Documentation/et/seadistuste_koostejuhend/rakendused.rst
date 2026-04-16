..  IVXV collector service management service description


.. _ivxv-rakendused:

IVXV Applications
=================

.. _app-install:

Installing Applications
--------------------------------------------------------------------------------

IVXV applications are:

* key application `key` (:numref:`app-key`),
* processing application `processor` (:numref:`app-processor`),
* audit application `auditor` (:numref:`app-auditor`).

IVXV applications are developed in the Java programming language, using Java 21.
The applications have been tested on Windows 11 and Ubuntu 22.04 platforms using OpenJDK
or Oracle Java.

Applications are delivered as ZIP format files::

  <application>-<delivery_number>.zip

After unpacking the ZIP file, the following directory tree is created::

   <application>-<delivery_number>
   |-- bin
   |   |-- <application>
   |   |-- <application.bat>
   |-- lib
   |   |-- *.jar

If the directory path `<application>-<delivery_number>/bin` is added to the `PATH` environment variable, the application
can subsequently be launched from the command line::

  $ <application>

When installing applications, it should be noted that the reports described in
the central system protocols use a time format without a time zone (`yyyymmddhhmmss`).
To display a time-stamped value with a time zone (for example, the voting time from
the e-ballot box received from the collector service) in a report, Java applications
first convert the timestamp to the operating system's time zone and then remove
the time zone information.
Therefore, the time zone must be configured on the machines running the applications
to match the local time in which timestamps are desired to be displayed.

.. _app-trust:

Describing the Application Trust Root
--------------------------------------

The use of applications requires the use of digitally signed configurations.
The certificates required for verifying signatures must be provided to the
application as part of the trust root. The trust root is also digitally signed.

The trust root configuration is prepared by the election organizer.

:ca:

    Comma-separated list of CA certificates and intermediate certificates
    contained in the container.

:ocsp:

    Comma-separated list of OCSP certificates contained in the container.

:tsa:

    Comma-separated list of TSA certificates contained in the container.

All certificates are provided in PEM format.

The trust root is presented to the application in a BDOC container, where the
trust root specification is described in the file `ivxv.properties` and all
root elements are loaded into the container.


Example
*******

:file:`ivxv.properties`:

.. literalinclude:: config-examples/ivxv.properties.real
   :linenos:


Launching Applications
--------------------------------------------

Applications are launched from the command line, and their operation is
controlled by command-line parameters and digitally signed configurations. All
applications display help information when needed::

  $ <application> --help

  Application 'application'        - Application

  Usage:
    <application> <tool> --conf <conf> [--params <params>] [--force <force>] [--quiet <quiet>] [--lang <lang>] [--container_threads <container_threads>] [--threads <threads>]
    <application> <tool> -h | --help
    <application> -h | --help

  Tools:
    tool_foo         - Perform action FOO
    tool_bar         - Perform action BAR

  Command-line arguments:
    -h --help             - Help
    -c --conf (*)         - Configuration
    -p --params           - Tool parameters
    -f --force            - Do not ask for user confirmation
    -q --quiet            - Quiet launch mode
    --lang                - Language
    -ct --container_threads - Number of threads used by the signed containers library (<= 0 for dynamic)
    -t --threads          - Number of threads used by the application for parallel processing (<= 0 for dynamic)
  Application completed without errors

When using applications, a specific tool, trust root, and configuration file
must be specified::

  $ <application> tool_foo --conf trustroot.asice --params tool_foo.conf.asice

  Loading configuration from file trustroot.asice
  Verifying configuration signature
  Configuration signature was given by NAME LASTNAME
  Configuration signature time is 24.12.2018 18:00
  Configuration signature is correct and valid

  FOO!

  Application completed without errors

Instructions for preparing application tools and their configuration files
are given in the following chapters. Command-line arguments are the same for
all applications:

:-h --help:
    Display help information for the application or a specific tool.

:-c --conf (*):
    Digitally signed file with trust root. Mandatory parameter.

:-p --params:
    Digitally signed tool parameters.

:-f --force:
    Do not ask for user confirmation.

:-q --quiet:
    Quiet launch mode.

:--lang:
    If the application is compiled as multilingual, then language selection.
    By default, only Estonian language is enabled in applications.

:-ct --container_threads:
    Number of threads used by the signed containers library. By default,
    the number of threads is selected dynamically by the library based on the
    available number of cores.

:-t --threads:
    Number of threads used by the application for parallel processing. By default,
    the number of threads is selected dynamically by the application based on the
    available number of cores.


Both production versions and test versions of applications exist.
Test applications are adapted for efficient testing of procedures but are not
suitable for conducting actual elections. For example, the test version of the
key application does not allow the use of smart cards. Test versions of
applications display a warning upon launch::

  ********************************************************************
  *                           !!! WARNING !!!                        *
  *                                                                  *
  * The application has been launched in development mode and the     *
  * application behavior may differ from normal mode.                *
  * To launch the application in normal mode, the application must   *
  * be recompiled.                                                   *
  ********************************************************************

Application Runtime Environment Parameters
--------------------------------------------

When auditing, processing, or decrypting a large e-ballot box, it may be
necessary to increase the process memory limit.

This can be done using the application-specific environment variable
``{APPLICATION}_OPTS``, which defines additional arguments for the Java virtual machine.
``{APPLICATION}`` is one of ``AUDITOR``, ``KEY``, or ``PROCESSOR``. To increase
the process memory limit, use the argument ``-Xmx{N}G``, where ``{N}``
is the memory limit size in gigabytes.

For example, to allocate 10 gigabytes of memory to the processing application,
set ``PROCESSOR_OPTS=-Xmx10G``.


.. list-table:: Application Memory Limit Parameters
   :header-rows: 1

   * - Application
     - Default memory limit
     - Environment variable
   * - Audit application
     - 8GB
     - ``AUDITOR_OPTS``
   * - Processing application
     - 8GB
     - ``PROCESSOR_OPTS``
   * - Key application
     - None
     - ``KEY_OPTS``


Applications work with both 32-bit and 64-bit Java data models, however
for the most efficient operation, applications should be used on a 64-bit
platform with a 64-bit Java data model. If the application is unable to detect
a 64-bit model upon launch, a warning is displayed::

  ********************************************************************
  *                           !!! WARNING !!!                        *
  *                                                                  *
  * Detection of the 64-bit Java data model failed. The application  *
  * will be less efficient. To increase application performance,     *
  * use a Java environment with a 64-bit data model.                 *
  ********************************************************************

If the application memory limit is 4GB or more, a 32-bit data model
Java is unable to launch the application. The following error message is
displayed::

  Invalid maximum heap size: -Xmx4G
  The specified size exceeds the maximum representable size.
  Error: Could not create the Java Virtual Machine.
  Error: A fatal exception has occurred. Program will exit.



