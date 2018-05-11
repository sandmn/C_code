.PHONY:clean
main:main.o add.o sub.o
	gcc $^ -o $@

%.o:%.c
	gcc $^ -c -o $@

clean:
	rm *.o main
