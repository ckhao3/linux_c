OBJ=rcver
rcver:$(OBJ).o
	gcc rcver.o -o rcver
rcver.o:$(OBJ).c proto.h
	gcc -c rcver.c -o rcver.o
clean:
	rm -rf *.o $(OBJ)
