CC      = g++
CFLAGS  = -g
RM      = rm -f


default: all

all: Pi

Pi: Pi.cpp BigInt.cpp
	$(CC) $(CFLAGS) -o Pi Pi.cpp BigInt.cpp

clean veryclean:
	$(RM) Pi
