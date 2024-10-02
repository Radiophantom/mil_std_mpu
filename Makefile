
CFLAGS=-I.
OBJ=main.o

main_app: $(OBJ)
	gcc -o $@ $^ $(CFLAGS)

%.o: %.c %.h
	gcc -c -o $@ $< $(CFLAGS)

clean:
	rm *.o
	rm main_app

.PHONY: test_app

