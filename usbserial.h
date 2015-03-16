#ifndef USBSERIAL_H
#define USBSERIAL_H

#include <sys/types.h>

#ifdef _WIN32
#include <Winsock2.h>
	#define __func__ __FUNCTION__
	#define DEFAULT_USB_DEV	"\\\\.\\COM3"
	typedef int tcflag_t;
#else
	#define DEFAULT_USB_DEV	"/dev/ttyUSB0"
	#define _fileno fileno
#endif

struct serial_opt {
    char *name;
    int handler;
    tcflag_t baud;
#ifndef _WIN32
	struct termios options;
#endif
    int timeout;
};

typedef struct s_usbserial_ops {

	void (*serial_port_close)(struct serial_opt *serial);
	int (*serial_port_open)(struct serial_opt *serial);
	int (*serial_port_read)(int fd, char *read_buffer, size_t max_chars_to_read);
	int (*serial_port_write)(int fd, char *write_buffer);

} usbserial_ops;

usbserial_ops * serial_initialize(struct serial_opt * options);

#endif