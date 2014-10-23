#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>

#define LAUNCHER_NODE           "/dev/launcher0"
#define LAUNCHER_FIRE           0x10
#define LAUNCHER_STOP           0x20
#define LAUNCHER_UP             0x02
#define LAUNCHER_DOWN           0x01
#define LAUNCHER_LEFT           0x04
#define LAUNCHER_RIGHT          0x08
#define LAUNCHER_UP_LEFT        (LAUNCHER_UP | LAUNCHER_LEFT)
#define LAUNCHER_DOWN_LEFT      (LAUNCHER_DOWN | LAUNCHER_LEFT)
#define LAUNCHER_UP_RIGHT       (LAUNCHER_UP | LAUNCHER_RIGHT)
#define LAUNCHER_DOWN_RIGHT     (LAUNCHER_DOWN | LAUNCHER_RIGHT)

#define BTNC                    0x01
#define BTNU                    0x10
#define BTNR                    0x08
#define BTND                    0x02
#define BTNL                    0x04

#define BTNS_ADDRESS            0x41240000

void cleanup(int status ,void* fd)
{
    close(*((int*) fd));
    printf("fd closed\n");
}

static void launcher_cmd(int fd, int cmd) {
    int retval = 0;
  
    retval = write(fd, &cmd, 1);
    while (retval != 1) {
        if (retval < 0) {
            fprintf(stderr, "Could not send command to %s (error %d)\n", LAUNCHER_NODE, retval);
        } 

        else if (retval == 0) {
            fprintf(stdout, "Command busy, waiting...\n");
        }

        else
        {
            fprintf(stdout, "... get out!\n");
        }
    }

    if (cmd == LAUNCHER_FIRE) {
        usleep(5000000);
    }
}

int main() {
    char c;
    int fd;
    int cmd = LAUNCHER_STOP;
    char *dev = LAUNCHER_NODE;
    unsigned int duration = 500;
    int* buttons;
    int memfd = open("/dev/mem", O_RDWR);
    if(memfd < 1)
    {
        perror("No file for you\n");
        exit(EXIT_FAILURE);
    }

    buttons = (int*) mmap(NULL, sizeof(int), PROT_READ, MAP_SHARED, memfd, BTNS_ADDRESS);

    if(buttons == MAP_FAILED)
    {
        perror("FML\n");
        exit(EXIT_FAILURE);
    }

    fd = open(dev, O_RDWR);
    if(fd == -1) {
        perror("Couldn't open file: %m");
        exit(1);
    }

    on_exit(cleanup, &fd);

    while(1)
    {
        fprintf(stdout, "buttons = 0x%02X\n", *buttons);

        cmd = 0;

        if(*buttons & BTNC)
        {
            cmd = LAUNCHER_FIRE;
        }

        else if(*buttons & BTNU && *buttons & BTNR)
        {
            cmd = LAUNCHER_UP_RIGHT;
        }

        else if(*buttons & BTNR && *buttons & BTND)
        {
            cmd = LAUNCHER_DOWN_RIGHT;
        }

        else if(*buttons & BTND && *buttons & BTNL)
        {
            cmd = LAUNCHER_DOWN_LEFT;
        }

        else if(*buttons & BTNL && *buttons & BTNU)
        {
            cmd = LAUNCHER_UP_LEFT;
        }

        else if(*buttons & BTNU)
        {
            cmd = LAUNCHER_UP;
        }

        else if(*buttons & BTNR)
        {
            cmd = LAUNCHER_RIGHT;
        }

        else if(*buttons & BTND)
        {
            cmd = LAUNCHER_DOWN;
        }

        else if(*buttons & BTNL)
        {
            cmd = LAUNCHER_LEFT;
        }
        else
        {
            cmd = LAUNCHER_STOP;
        }

        launcher_cmd(fd, cmd);
        usleep(duration * 1000);
        launcher_cmd(fd, LAUNCHER_STOP);

        fprintf(stdout, "we are looping\n");
    }

    return 0;
}

