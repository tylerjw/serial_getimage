#include "arduino-serial-lib.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>   // UNIX standard function definitions 


#define SERIAL_PORT		"/dev/tty.usbmodem1421"
#define BAUD			9600
#define TIMEOUT			5000

int main()
{
	int fd = -1;
	unsigned char image_data[10];

	fd = serialport_init(SERIAL_PORT, BAUD);
	if(fd < 0)
	{
		printf("Error connecting to serial!");
		exit(-1);
	}
	printf("fd: %d\n", fd);
	printf("waiting for reset\n");
	usleep(TIMEOUT*1000);
	printf("Sending start character\n");
	serialport_writebyte(fd, 'x'); // start the stream
	printf("Waiting for data... \n");
	serialport_read(fd, image_data, 10, TIMEOUT);
	printf("Read the data!\n");
	for(int i=0; i<10; i++)
		printf("%d ",image_data[i]);
	printf("\n");

	return 0;
}