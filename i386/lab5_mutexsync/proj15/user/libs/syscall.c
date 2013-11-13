#include <defs.h>
#include <unistd.h>
#include <stdarg.h>
#include <syscall.h>

#define MAX_ARGS            5

static inline uint32_t
syscall(int num, ...) {
    va_list ap;
    va_start(ap, num);
    uint32_t a[MAX_ARGS];
    int i;
    for (i = 0; i < MAX_ARGS; i ++) {
        a[i] = va_arg(ap, uint32_t);
    }
    va_end(ap);

    uint32_t ret;
    asm volatile (
        "int %1;"
        : "=a" (ret)
        : "i" (T_SYSCALL),
          "a" (num),
          "d" (a[0]),
          "c" (a[1]),
          "b" (a[2]),
          "D" (a[3]),
          "S" (a[4])
        : "cc", "memory");
    return ret;
}

int
sys_exit(int error_code) {
    return syscall(SYS_exit, error_code);
}

int
sys_fork(void) {
    return syscall(SYS_fork);
}

int
sys_wait(int pid, int *store) {
    return syscall(SYS_wait, pid, store);
}

int
sys_yield(void) {
    return syscall(SYS_yield);
}

int
sys_sleep(unsigned int time) {
    return syscall(SYS_sleep, time);
}

int
sys_kill(int pid) {
    return syscall(SYS_kill, pid);
}

size_t
sys_gettime(void) {
    return syscall(SYS_gettime);
}

int
sys_getpid(void) {
    return syscall(SYS_getpid);
}

int
sys_brk(uintptr_t *brk_store) {
    return syscall(SYS_brk, brk_store);
}

int
sys_mmap(uintptr_t *addr_store, size_t len, uint32_t mmap_flags) {
    return syscall(SYS_mmap, addr_store, len, mmap_flags);
}

int
sys_munmap(uintptr_t addr, size_t len) {
    return syscall(SYS_munmap, addr, len);
}

int
sys_shmem(uintptr_t *addr_store, size_t len, uint32_t mmap_flags) {
    return syscall(SYS_shmem, addr_store, len, mmap_flags);
}

int
sys_putc(int c) {
    return syscall(SYS_putc, c);
}

int
sys_pgdir(void) {
    return syscall(SYS_pgdir);
}

sem_t
sys_sem_init(int value) {
    return syscall(SYS_sem_init, value);
}

int
sys_sem_post(sem_t sem_id) {
    return syscall(SYS_sem_post, sem_id);
}

int
sys_sem_wait(sem_t sem_id, unsigned int timeout) {
    return syscall(SYS_sem_wait, sem_id, timeout);
}

int
sys_sem_free(sem_t sem_id) {
    return syscall(SYS_sem_free, sem_id);
}

int
sys_sem_get_value(sem_t sem_id, int *value_store) {
    return syscall(SYS_sem_get_value, sem_id, value_store);
}

int
sys_send_event(int pid, int event, unsigned int timeout) {
    return syscall(SYS_event_send, pid, event, timeout);
}

int
sys_recv_event(int *pid_store, int *event_store, unsigned int timeout) {
    return syscall(SYS_event_recv, pid_store, event_store, timeout);
}

