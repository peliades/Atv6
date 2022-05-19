bin: main.c
	gcc main.c -o $@ -lpthread 

.PHONY: run clean

run:
	./bin

clean:
	rm bin