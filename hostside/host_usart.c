#include <fcntl.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    unsigned int usbdev;
    unsigned char c;
    system("stty -F /dev/ttyUSB0 115200 icanon raw");
    usbdev = open("/dev/ttyUSB0", O_RDWR);
    setbuf(stdout, NULL);
    fprintf(stderr, "Waiting for data..\n");
    while (1) {
        while (!read(usbdev, &c, 1));
        printf("%c", c);
    }
    return 0;
}
