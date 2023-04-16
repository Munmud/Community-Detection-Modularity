CC = gcc
CFLAGS = -std=c11 -lm -O -fPIC
HEADER_FILE = modularity.h memory.h community_detection.h eigen.h
OBJS = modularity.o memory.o eigen.o community_detection.o
LIBS = -lgsl -lgslcblas

all: library.so library.dll


library.so: $(OBJS)
	$(CC) $(CFLAGS) -shared $^ -o $@ $(LIBS) 

library.dll: $(OBJS)
	$(CC) $(CFLAGS) -shared $^ -o $@ $(LIBS) 
	rm -f *.o

community_detection.o: community_detection.c $(HEADER_FILE)
	$(CC) $(CFLAGS) -c community_detection.c

modularity.o: modularity.c $(HEADER_FILE)
	$(CC) $(CFLAGS) -c modularity.c

memory.o: memory.c $(HEADER_FILE)
	$(CC) $(CFLAGS) -c memory.c

eigen.o: eigen.c $(HEADER_FILE)
	gcc $(CFLAGS) -c eigen.c $(LIBS)

clean:
	rm -f *.o *.so *.dll
