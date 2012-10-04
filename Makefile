
PREFIX=/usr/local
SBINDIR=$(PREFIX)/sbin
BINDIR=$(PREFIX)/bin
LIBDIR=$(PREFIX)/lib
INCDIR=$(PREFIX)/include

MAJOR=0
MINOR=3
BUILD=0
VERSION=$(MAJOR).$(MINOR).$(BUILD)


PROGLDFLAGS=$(LDFLAGS) -L. -llcd
LIBLDFLAGS=$(LDFLAGS)

PROGRAMS  = lcdd lcdwrite
LIBNAME   = liblcd
SHAREDLIB = $(LIBNAME).so.$(VERSION)
SHAREDLIBS = $(SHAREDLIB) $(LIBNAME).so.$(MAJOR) $(LIBNAME).so
STATICLIB = $(LIBNAME).a
LIBS      = $(STATICLIB) $(SHAREDLIBS)


all: $(LIBS) $(PROGRAMS)

$(SHAREDLIBS): lcdcommon_cpp.o
	g++ $(LIBLDFLAGS) -o $(SHAREDLIB) -shared lcdcommon_cpp.o
	ln -sf $(SHAREDLIB) $(LIBNAME).so.$(MAJOR)
	ln -sf $(LIBNAME).so.$(MAJOR) $(LIBNAME).so

$(STATICLIB): lcdcommon.o
	ar -r $(STATICLIB) lcdcommon.o

lcdcommon_cpp.o: lcdcommon.c lcd.h
	g++ $(CXXFLAGS) -fPIC -o lcdcommon_cpp.o -c lcdcommon.c

lcdcommon.o: lcdcommon.c lcd.h
	gcc $(CFLAGS) -c lcdcommon.c

lcdd: lcdd.o auxfunctions.o $(SHAREDLIBS)
	g++ -o lcdd lcdd.o auxfunctions.o $(PROGLDFLAGS) 

lcdwrite: lcdwrite.o liblcd.so 
	g++ -o lcdwrite lcdwrite.o $(PROGLDFLAGS)

lcdd.o: lcdd.cpp
	g++ $(CXXFLAGS) -c lcdd.cpp

lcdwrite.o: lcdwrite.cpp
	g++ $(CXXFLAGS) -c lcdwrite.cpp

auxfunctions.o: auxfunctions.c
	gcc $(CFLAGS) -c auxfunctions.c

clean:
	rm -f auxfunctions.o lcdd.o lcdwrite.o lcdcommon.o lcdcommon_cpp.o

realclean: clean
	rm -f $(LIBS) $(PROGRAMS)

install: install_progs install_libs

install_progs: $(PROGRAMS)
	install -v -d -m755 $(SBINDIR)
	install -v -m755 lcdd $(SBINDIR)
	install -v -d -m755 $(BINDIR)
	install -v -m755 lcdwrite $(BINDIR)
	
install_libs: $(LIBS)
	install -v -d -m755 $(LIBDIR)
	install -v -m644 $(STATICLIB) $(LIBDIR)
	install -v -m755 $(SHAREDLIB) $(LIBDIR)
	ln -sfv $(SHAREDLIB) $(LIBDIR)/$(LIBNAME).so.$(MAJOR)
	ln -sfv $(LIBNAME).so.$(MAJOR) $(LIBDIR)/$(LIBNAME).so
	install -v -d -m755 $(INCDIR)
	install -v -m644 lcd lcd.h $(INCDIR)

.PHONY: all
.PHONY: install
.PHONY: clean
.PHONY: realclean
