/*
 * kexec-dev.c
 *
 * By Hashcode
 */

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <sys/types.h>

#include "kexec-dev.h"

int dev_kexec_open() {
        int fd = open("/dev/ion", O_RDWR);
        if (fd < 0)
                fprintf(stderr, "open /dev/ion failed!\n");
        return fd;
}

static int dev_kexec_ioctl(int fd, int req, void *arg) {
        int ret = ioctl(fd, req, arg);
        if (ret < 0) {
                fprintf(stderr, "ioctl %d failed with code %d: %s\n", req,
                       ret, strerror(errno));
                return -errno;
        }
        return ret;
}

int dev_kexec_load(void *entry, int nr_segments,
		   struct kexec_segment *segment, unsigned long kexec_flags)
{
	int ret = 0;
	int fd = dev_kexec_open();
	if (!fd) {
		struct kexec_param data = {
			.entry = entry,
			.nr_segments = nr_segments,
			.segment = segment,
			.kexec_flags = kexec_flags,
		};
		ret = dev_kexec_ioctl(fd, KEXEC_IOC_LOAD, &data);
        	close(fd);
	}
	return ret;
}

int dev_kexec_reboot(int magic_num)
{
	int ret = 0;
	int fd = dev_kexec_open();
	if (!fd) {
		ret = dev_kexec_ioctl(fd, KEXEC_IOC_REBOOT, NULL);
        	close(fd);
	}
	return ret;
}
