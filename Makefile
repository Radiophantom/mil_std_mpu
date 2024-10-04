
CFLAGS=-c -Wall -I./inc
OBJ=main.o

main_app: $(OBJ)
	gcc $^ -o $@

main.o: src/main.c
	gcc -c $^ -o $@ $(CFLAGS)

clean:
	rm *.o
	rm main_app

.PHONY: test_app

