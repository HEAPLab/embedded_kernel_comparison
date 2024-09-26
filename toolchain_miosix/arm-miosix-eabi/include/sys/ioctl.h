
#ifndef _SYS_IOCTL_H
#define _SYS_IOCTL_H

#ifdef __cplusplus
extern "C" {
#endif

/* keep in sync with miosix/filesystem/ioctl.h */
enum Ioctl
{
    IOCTL_SYNC=100,
    IOCTL_TCGETATTR=101,
    IOCTL_TCSETATTR_NOW=102,
    IOCTL_TCSETATTR_FLUSH=103,
    IOCTL_TCSETATTR_DRAIN=104,
    IOCTL_FLUSH=105
};

int ioctl(int fd, int cmd, void *arg);

#ifdef __cplusplus
}
#endif

#endif /*_SYS_IOCTL_H*/
