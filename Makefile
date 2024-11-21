
CFLAGS=-c -Wall -I./inc
OBJ=main.o proc.o rcv.o xmt.o mode_code.o
#OBJ=main.o proc.o rcv.o xmt.o

main_app: $(OBJ)
	gcc $^ -o $@

main.o: src/main.c
	gcc -c $^ -o $@ $(CFLAGS)

rcv.o: src/rcv.c
	gcc -c $^ -o $@ $(CFLAGS)

xmt.o: src/xmt.c
	gcc -c $^ -o $@ $(CFLAGS)

proc.o: src/proc.c
	gcc -c $^ -o $@ $(CFLAGS)

mode_code.o: src/mode_code.c
	gcc -c $^ -o $@ $(CFLAGS)

clean:
	rm *.o
	rm main_app

.PHONY: test_app

