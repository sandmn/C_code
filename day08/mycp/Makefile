.PHONY: clean
mycp:mycp.o
	gcc $^ -g -o $@

mycp.o:mycp.c
	gcc -c $^ -o $@

clean:
	rm *.o mycp
