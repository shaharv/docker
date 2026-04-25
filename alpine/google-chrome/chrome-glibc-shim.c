#define _GNU_SOURCE
#define _LARGEFILE64_SOURCE

#include <fcntl.h>
#include <sched.h>
#include <sys/types.h>
#include <unistd.h>

#ifdef posix_fallocate64
#undef posix_fallocate64
#endif

int posix_fallocate64(int fd, off64_t offset, off64_t len)
{
	return posix_fallocate(fd, (off_t)offset, (off_t)len);
}

int sched_getscheduler(pid_t pid)
{
	(void)pid;
	return SCHED_OTHER;
}

int sched_getparam(pid_t pid, struct sched_param *param)
{
	(void)pid;
	if (param != 0) {
		param->sched_priority = 0;
	}
	return 0;
}
