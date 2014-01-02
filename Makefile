CC=g++ -g -fPIC -Wall -ansi -D_GNU_SOURCE -O2 -m64
ROOTFLAG = `${ROOTSYS}/bin/root-config --cflags`
LIB=`${ROOTSYS}/bin/root-config --libs`
GLIB=`${ROOTSYS}/bin/root-config --glibs`

OBJECTS=AnaInput.o hDraw.o Rtuple.o CosmicsStudy.o 

all:test.exe

AnaInput.o : AnaInput.cc AnaInput.h
	$(CC) -c -o $@ $< $(ROOTFLAG) $(LIB)

hDraw.o : hDraw.cc hDraw.h
	$(CC) -c -o $@ $< $(ROOTFLAG) $(LIB)

Rtuple.o : Rtuple.cc Rtuple.h
	$(CC) -c -o $@ $< $(ROOTFLAG) $(LIB)

CosmicsStudy.o : CosmicsStudy.cc CosmicsStudy.h
	$(CC) -c -o $@ $< $(ROOTFLAG) $(LIB)

test.exe : main.cc $(OBJECTS)
	$(CC) -o $@ $< $(OBJECTS) $(ROOTFLAG) $(LIB) $(GLIB)

clean : 
	rm -rf *.o test.exe
