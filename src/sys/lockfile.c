// SPDX-License-Identifier: GPL-3.0-only
// Copyright (C) 2026 seclususs

#include "daemon/lockfile.h"
#include "daemon/logger.h"
#include <errno.h>
#include <fcntl.h>
#include <sys/file.h>
#include <unistd.h>

#ifndef LOCK_FILE_PATH
#define LOCK_FILE_PATH "/data/local/tmp/pascal_gov.lock"
#endif

int pascal_gov_lockfile_acquire(void)
{
#ifdef __INTELLISENSE__
	int fd = open(LOCK_FILE_PATH, O_CREAT | O_RDWR | O_CLOEXEC);
#else
	int fd = open(LOCK_FILE_PATH, O_CREAT | O_RDWR | O_CLOEXEC, 0600);
#endif

	if (fd < 0) {
		int err = errno;
		LOGE("lockfile: failed to open lockfile err=%d", err);
		return -err;
	}

	if (flock(fd, LOCK_EX | LOCK_NB) == -1) {
		LOGE("lockfile: another process is already running");
		close(fd);
		return -EAGAIN;
	}

	return 0;
}
