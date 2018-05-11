.PHONY:clean
tree:tree.o
	gcc $^ -g -o $@

tree.o:tree.c
	gcc $^ -c -o $@

clean:
	rm *.o tree
	
