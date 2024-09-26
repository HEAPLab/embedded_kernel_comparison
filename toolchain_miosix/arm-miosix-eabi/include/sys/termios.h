/* Adapted from sys/sysvi386/sys */

#ifndef _SYS_TERMIOS_H
#define _SYS_TERMIOS_H

/* c_iflag */
#define IGNBRK  000001
#define BRKINT  000002
#define IGNPAR  000004
#define INPCK   000020
#define ISTRIP  000040
#define INLCR   000100
#define IGNCR   000200
#define ICRNL   000400
#define IXON    002000
#define IXOFF   010000
#define IUTF8   040000

/* c_oflag */
#define OPOST   000001
#define OCRNL   000004
#define ONLCR   000010
#define ONOCR   000020
#define ONLRET  000040

/* c_cflag */
#define B0      0
#define B50     50
#define B75     75
#define B110    110
#define B134    134
#define B150    150
#define B200    200
#define B300    300
#define B600    600
#define B1200   1200
#define B1800   1800
#define B2400   2400
#define B4800   4800
#define B9600   9600
#define B19200  19200
#define B38400  38400
#define B57600  57600
#define B115200 115200
#define B230400 230400

#define CSIZE   (0x03<<24)
#define CS5     (0x00<<24)
#define CS6     (0x01<<24)
#define CS7     (0x02<<24)
#define CS8     (0x03<<24)
#define CSTOPB  (0x04<<24)
#define PARENB  (0x08<<24)
#define PAODD   (0x10<<24)
#define CRTSCTS (0x20<<24)
#define CREAD   (0x40<<24)

/* c_lflag */
#define ISIG    0000001
#define ICANON  0000002
#define ECHO    0000010
#define ECHOE   0000020
#define ECHOK   0000040
#define ECHONL  0000100
#define NOFLSH  0000200
#define TOSTOP  0001000

/* c_cc indices */
#define VEOF    4   /* also VMIN -- thanks, AT&T */
#define VEOL    5   /* also VTIME -- thanks again */
#define VERASE  2
#define VINTR   0
#define VKILL   3
#define VMIN    4   /* also VEOF */
#define VQUIT   1
#define VSUSP   10
#define VTIME   5   /* also VEOL */
#define VSTART  11
#define VSTOP   12

/* tcsetattr opt */
#define TCSAFLUSH  0
#define TCSANOW    1
#define TCSADRAIN  2

/* tcflush opt */
#define TCIFLUSH   0
#define TCOFLUSH   1
#define TCIOFLUSH  2

#define NCCS 13

typedef unsigned char cc_t;
typedef unsigned int tcflag_t;
typedef unsigned int speed_t;

struct termios
{
    tcflag_t c_iflag;
    tcflag_t c_oflag;
    tcflag_t c_cflag;
    tcflag_t c_lflag;
    cc_t c_cc[NCCS];
};

int tcgetattr(int fd, struct termios *t);
int tcsetattr(int fd, int opt, const struct termios *t);
speed_t cfgetospeed(const struct termios *t);
int cfsetospeed(struct termios *t, speed_t speed);
int tcdrain(int fd);
int tcflush(int fd, int opt);

#endif /*_SYS_TERMIOS_H*/
