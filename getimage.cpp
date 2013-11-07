#include <stdio.h>
#include <stdlib.h>
#include <pngwriter.h>
#include "arduino-serial-lib.h"

using namespace std;

#define SERIAL_PORT		"/dev/tty.usbmodem1421"
#define OUT_FILENAME	"image.png"
#define BAUD			9600
#define TIMEOUT			5000
#define WIDTH 			640
#define HEIGHT			480
#define NUM_PIXELS		(WIDTH*HEIGHT)
#define IMAGE_SIZE		(NUM_PIXELS*3)

// for image with width of 3
#define XVAL_I(idx)	((idx/3)%WIDTH +1)
#define YVAL_I(idx)	(HEIGHT - ((idx/3)/WIDTH))

#define BYTE_TO_INT_COLOR(col)		(int)(col*(65536/256))

void png_image(unsigned char *img, char* filename)
{
	pngwriter image(640, 480, 1.0, filename); 

	for( int i = 0; i < IMAGE_SIZE; i+=3 )
	{
		image.plot(XVAL_I(i), YVAL_I(i), BYTE_TO_INT_COLOR(img[i]), 
			BYTE_TO_INT_COLOR(img[i+1]), BYTE_TO_INT_COLOR(img[i+2]));
	}

	image.close();
}

int main()
{
	int fd = -1;
	unsigned char image_data[IMAGE_SIZE];

	fd = serialport_init(SERIAL_PORT, BAUD);
	if(fd == -1)
	{
		printf("Error connecting to serial!");
		exit(-1);
	}

	serialport_write(fd, "x"); // start the stream

	serialport_read(fd, image_data, IMAGE_SIZE, TIMEOUT);

	png_image(image_data, OUT_FILENAME);

	return 0;
}