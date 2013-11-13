#ifndef __KERN_FS_SYSFILE_H__
#define __KERN_FS_SYSFILE_H__

#include <defs.h>

struct stat;

int sysfile_open(const char *path, uint32_t open_flags);
int sysfile_close(int fd);
int sysfile_read(int fd, void *base, size_t len);
int sysfile_write(int fd, void *base, size_t len);
int sysfile_fstat(int fd, struct stat *stat);
int sysfile_dup(int fd1, int fd2);
int sysfile_pipe(int *fd_store);
int sysfile_mkfifo(const char *name, uint32_t open_flags);

#endif /* !__KERN_FS_SYSFILE_H__ */

