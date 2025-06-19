OBJS = led.o button.o buzzer.o imu.o temp.o fnd.o colorled.o textlcd.o
TARGET = ledtest buttontest buzzertest accelMagGyroTest temperatureTest fndtest colorledtest textlcdtest

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

accelMagGyroTest: accelMagGyroTest.o $(LIB_NAME)
	$(CC) $(CFLAGS) -o $@ $< $(LDFLAGS)

temperatureTest: temperatureTest.o $(LIB_NAME)
	$(CC) $(CFLAGS) -o $@ $< $(LDFLAGS)

fndtest: fndtest.o $(LIB_NAME)
	$(CC) $(CFLAGS) -o $@ $< $(LDFLAGS)

textlcdtest: textlcdtest.o $(LIB_NAME)
	$(CC) $(CFLAGS) -o $@ $< $(LDFLAGS)

colorledtest: colorledtest.o $(LIB_NAME)
	$(CC) $(CFLAGS) -o $@ $< $(LDFLAGS)

$(LIB_NAME): $(OBJS)
	$(AR) rcs $@ $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(TARGET) $(OBJS) $(LIB_NAME) *.o
