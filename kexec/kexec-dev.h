#ifndef __KEXEC_DEV_H
#define __KEXEC_DEV_H

#include <linux/types.h>
#include "kexec.h"

struct kexec_param {
	void *entry;
	int nr_segments;
	struct kexec_segment *segment;
	unsigned long kexec_flags;
};

int dev_kexec_open();
static int dev_kexec_ioctl(int fd, int req, void *arg);
int dev_kexec_load(void *entry, int nr_segments,
		   struct kexec_segment *segment, unsigned long kexec_flags);
int dev_kexec_reboot(int magic_num);


/* Ioctl defines */
#define KEXEC_IOC_MAGIC		'K'

#define KEXEC_IOC_LOAD		_IOW(KEXEC_IOC_MAGIC, 0, struct kexec_param)
#define KEXEC_IOC_REBOOT	_IOW(KEXEC_IOC_MAGIC, 1, int)

#endif /* __KEXEC_DEV_H */
