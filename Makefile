
PREFIX=/usr/local
SBINDIR=$(PREFIX)/sbin
BINDIR=$(PREFIX)/bin

all: lcdd lcdwrite

lcdd: lcdd.o auxfunctions.o
	g++ $(LDFLAGS) -o lcdd lcdd.o auxfunctions.o

lcdwrite: lcdwrite.o auxfunctions.o
	g++ $(LDFLAGS) -o lcdwrite lcdwrite.o auxfunctions.o

lcdd.o: lcdd.cpp
	g++ $(CXXFLAGS) -c lcdd.cpp

lcdwrite.o: lcdwrite.cpp
	g++ $(CXXFLAGS) -c lcdwrite.cpp

auxfunctions.o: auxfunctions.c
	gcc $(CFLAGS) -c auxfunctions.c

clean:
	rm -f auxfunctions.o lcdd.o lcdwrite.o

realclean: clean
	rm -f lcdd lcdwrite

install: all
	install -v -d -m755 $(SBINDIR)
	install -v -d -m755 $(BINDIR)
	install -v -m755 lcdd $(SBINDIR)
	install -v -m755 lcdwrite $(BINDIR)

.PHONY: clean
