TARGET		= getimage
OBJECTS 	= arduino-serial-lib.o getimage.o
#######################################################################################
# -I/usr/local/opt/libpng12/include
# -L/usr/local/opt/libpng12/lib

CFLAGS   = -g -Wall -DNO_FREETYPE -I/usr/local/include 
CXXFLAGS = -g -Wall -DNO_FREETYPE -I/usr/local/include
ASFLAGS  = -Wall
LDFLAGS  = -g -Wall -L/usr/local/opt/libpng12/lib -L/usr/local/lib -lpng -lpngwriter -lz

CC = gcc
AS = gcc
CXX = g++

########################################################################################
$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) $(LDFLAGS) -o $(TARGET)

serial_test: arduino-serial-lib.o serial_test.o
	$(CXX) arduino-serial-lib.o serial_test.o $(LDFLAGS) -o serial_test

serial_test.o: arduino-serial-lib.h 
arduino-serial-lib.o : arduino-serial-lib.h 
getimage.o: arduino-serial-lib.h

clean: 
	rm -f $(OBJECTS) $(TARGET)