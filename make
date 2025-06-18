all: main.elf
	scp main.elf ecube@192.168.30.3:/home/ecube/

main.elf: libNyperi.a main.o
	arm-linux-gnueabi-gcc main.o -lMyperi -L. -o main.elf

libMyperi.a: button.o led.o buzzer.o
	arm-linux-gnueabi-ar rc libMyperi.a button.o buzzer.o

button.o: button.h button.c
	arm-linux-gnueabi-gcc -c button.c -o button.o

led.o: led.h led.c
	arm_linux-gnueabi-gcc -c led.c -o led.o

buzzer.o: buzzer.h buzzer.o
	arm_linux-gnueabi-gcc -c buzzer.c -o buzzer.o

clear :
	rm *.0
	rm libMyperi.a

