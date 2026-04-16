..  IVXV collector service management service description

.. _kt-management:

Collector service authorization description
-------------------------------------------

Assigning authorizations to users is done through roles defined in the system.
Each role has an assigned set of permissions and the user has all authorizations
that have been assigned to them through associated roles.

The authorization assignment order assigns a user their roles in the system.

Authorizations are prepared as a JSON format file, which specifies:

#. Order content (``action=user-permissions``);

#. Authorized user's *Common Name* field from their ID card (field ``cn``);

#. User roles list as a comma-separated list (field ``roles``).

File format:

.. code-block:: JavaScript

   {
       "action": "user-permissions",
       "cn": "<user-CN">,
       "roles": "role1[,role2]"
   }


.. _rollid:

Roles
*****

The collector service has the following roles:

#. **Collector service administrator** (``admin``) is intended for technical
   management of the collector service;

#. **Election manager** (``election-conf-manager``) is intended for
   establishing election settings;

#. **Viewer** (``viewer``) is intended for viewing data provided through the
   management service;

#. **User without permissions** (``none``). This role is intended for
   maintaining a user account record in a situation where the user has not been
   assigned any other role (for example after being added or after being
   removed from all other roles).

.. list-table::
   Roles and authorizations matrix
   :header-rows: 1

   *  -
      - ``admin``
      - ``election-`` ``conf-`` ``manager``
      - ``viewer``
      - ``none``

   *  - Viewing general status and statistics
      - ✓
      - ✓
      - ✓
      - `-`

   *  - Applying election settings
      - ✓
      - ✓
      - `-`
      - `-`

   *  - Downloading e-ballot box
      - ✓
      - ✓
      - `-`
      - `-`

   *  - User management
      - ✓
      - `-`
      - `-`
      - `-`

   *  - Applying technical configuration
      - ✓
      - `-`
      - `-`
      - `-`

   *  - Viewing logs
      - ✓
      - `-`
      - `-`
      - `-`


Authorization rules
*******************

* A user can have multiple roles simultaneously;

* A role grants the user permissions associated with the role; no role revokes permissions.

.. vim:syntax=rst:
