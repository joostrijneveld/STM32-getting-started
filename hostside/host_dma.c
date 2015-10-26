#include <fcntl.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    unsigned int usbdev;
    unsigned char c;
    system("stty -F /dev/ttyUSB0 921600 icanon raw");
    usbdev = open("/dev/ttyUSB0", O_RDWR);
    setbuf(stdout, NULL);
    fprintf(stderr, "Waiting for signal..\n");
    while (!read(usbdev, &c, 1));
    unsigned char buf[] = "Defend at noon\r\n";
    write(usbdev, buf, 16);
    printf("Written 16 bytes\r\n");
    while (1) {
        while (!read(usbdev, &c, 1));
        printf("%c", c);
    }
    return 0;
}
