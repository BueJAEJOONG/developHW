OBJS = led.o button.o buzzer.o
TARGET = ledtest buttontest buzzertest

CROSS_COMPILE   := arm-linux-gnueabi-
CC              := $(CROSS_COMPILE)gcc
AR              := $(CROSS_COMPILE)ar

CFLAGS = -I.

LDFLAGS = -L. -lMyPeri -lpthread

LIB_NAME = libMyPeri.a

all: $(TARGET)


ledtest: ledtest.o $(LIB_NAME)
	$(CC) $(CFLAGS) -o $@ $< $(LDFLAGS)

buttontest: buttontest.o $(LIB_NAME)
	$(CC) $(CFLAGS) -o $@ $< $(LDFLAGS)

buzzertest: buzzertest.o $(LIB_NAME)
	$(CC) $(CFLAGS) -o $@ $< $(LDFLAGS)

$(LIB_NAME): $(OBJS)
	$(AR) rcs $@ $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(TARGET) $(OBJS) $(LIB_NAME) *.o

.PHONY: all clean
