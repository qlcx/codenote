/*linux ªÒµ√”≤≈Ã–Ú¡–∫≈*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <linux/hdreg.h>

int main(int argc,char *argv[])
{
        static int open_flags = O_RDONLY|O_NONBLOCK;
        static int errno = 1;
        static struct hd_driveid id;

        int fd;
        const char *devname = "/dev/sda";

        fd = open(devname,open_flags);
        if(fd < 0)
        {
                perror(devname);
                exit(errno);
        }

        ioctl(fd,HDIO_GET_IDENTITY,&id);
		printf("SerialNo = %s\n", id.serial_no);
        close(fd);

        return 0;
}
