/*
 * Copyright (C) 2008 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>
#include <fcntl.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/mount.h>

#include <linux/kdev_t.h>

#define LOG_TAG "Vold"

#include <cutils/log.h>
#include <cutils/properties.h>

#include "Ntfs.h"

static char FSCK_NTFS_PATH[] = "/system/bin/fsck_ntfs";
static char MKNTFS_PATH[] = "/system/bin/newfs_ntfs";
static char NTFS_3G_PATH[] = "/system/bin/ntfs-3g";
extern "C" int logwrap(int argc, const char **argv, int background);
extern "C" int mount(const char *, const char *, const char *, unsigned long, const void *);

int Ntfs::check(const char *fsPath) {
    SLOGW("Skipping NTFS check\n");
    return 0;
}

int Ntfs::doMount(const char *fsPath, const char *mountPoint,
                 bool ro, bool remount, bool executable,
                 int ownerUid, int ownerGid, int permMask, bool createLost) {
    int rc;
    const char *args[11];
    char mountData[255];

    sprintf(mountData,
            "locale=utf8,uid=%d,gid=%d,fmask=%o,dmask=%o",
            ownerUid, ownerGid, permMask, permMask);

    args[0] = NTFS_3G_PATH;
    args[1] = fsPath;
    args[2] = mountPoint;
    args[3] = "-o";
    args[4] = mountData;
    args[5] = NULL;
    rc = logwrap(5, args, 0);

    return rc;
}

int Ntfs::format(const char *fsPath, unsigned int numSectors) {
    SLOGE("Skipping ntfs format\n");
    errno = EIO;
    return -1;
}
