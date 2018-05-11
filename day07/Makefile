:PHONY:clean
myls:myls.o
	gcc -g $^ -o $@ -Wall
%.o:%.c
	gcc $^ -c -o $@
clean:
	rm *.o myls
