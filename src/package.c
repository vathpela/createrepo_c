/* createrepo_c - Library of routines for manipulation with repodata
 * Copyright (C) 2012  Tomas Mlcoch
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

#include "package.h"
#include "logging.h"

#define PACKAGE_CHUNK_SIZE 2048

Dependency *
dependency_new (void)
{
    Dependency *dep;

    dep = g_new0 (Dependency, 1);

    return dep;
}

PackageFile *
package_file_new (void)
{
    PackageFile *file;

    file = g_new0 (PackageFile, 1);

    return file;
}

ChangelogEntry *
changelog_entry_new (void)
{
    ChangelogEntry *entry;

    entry = g_new0 (ChangelogEntry, 1);

    return entry;
}

Package *
package_new (void)
{
    Package *package;

    package = g_new0 (Package, 1);
    package->chunk = g_string_chunk_new (PACKAGE_CHUNK_SIZE);

    return package;
}

void
package_free (Package *package)
{
    g_string_chunk_free (package->chunk);

/* Note: Since glib 2.28
 * g_slist_foreach && g_slist_free could be replaced with one function:
 * g_slist_free_full()
 */

    if (package->requires) {
        g_slist_foreach (package->requires, (GFunc) g_free, NULL);
        g_slist_free (package->requires);
    }

    if (package->provides) {
        g_slist_foreach (package->provides, (GFunc) g_free, NULL);
        g_slist_free (package->provides);
    }

    if (package->conflicts) {
        g_slist_foreach (package->conflicts, (GFunc) g_free, NULL);
        g_slist_free (package->conflicts);
    }

    if (package->obsoletes) {
        g_slist_foreach (package->obsoletes, (GFunc) g_free, NULL);
        g_slist_free (package->obsoletes);
    }

    if (package->files) {
        g_slist_foreach (package->files, (GFunc) g_free, NULL);
        g_slist_free (package->files);
    }

    if (package->changelogs) {
        g_slist_foreach (package->changelogs, (GFunc) g_free, NULL);
        g_slist_free (package->changelogs);
    }

    g_free (package);
}
