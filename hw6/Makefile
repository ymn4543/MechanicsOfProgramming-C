#
# Created by gmakemake (Ubuntu Jul 25 2014) on Sun Oct 27 19:00:28 2019
#

#
# Definitions
#

.SUFFIXES:
.SUFFIXES:	.a .o .c .C .cpp .s .S
.c.o:
		$(COMPILE.c) $<
.C.o:
		$(COMPILE.cc) $<
.cpp.o:
		$(COMPILE.cc) $<
.S.s:
		$(CPP) -o $*.s $<
.s.o:
		$(COMPILE.cc) $<
.c.a:
		$(COMPILE.c) -o $% $<
		$(AR) $(ARFLAGS) $@ $%
		$(RM) $%
.C.a:
		$(COMPILE.cc) -o $% $<
		$(AR) $(ARFLAGS) $@ $%
		$(RM) $%
.cpp.a:
		$(COMPILE.cc) -o $% $<
		$(AR) $(ARFLAGS) $@ $%
		$(RM) $%

CC =		gcc
CXX =		g++

RM = rm -f
AR = ar
LINK.c = $(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS)
LINK.cc = $(CXX) $(CXXFLAGS) $(CPPFLAGS) $(LDFLAGS)
COMPILE.c = $(CC) $(CFLAGS) $(CPPFLAGS) -c
COMPILE.cc = $(CXX) $(CXXFLAGS) $(CPPFLAGS) -c
CPP = $(CPP) $(CPPFLAGS)
########## Flags from header.mak

CFLAGS = -std=c99 -ggdb -Wall -Wextra -pedantic

########## End of flags from header.mak


CPP_FILES =	
C_FILES =	mapADT.c mapTest1.c mapTest2.c mapTest3.c
PS_FILES =	
S_FILES =	
H_FILES =	mapADT.h
SOURCEFILES =	$(H_FILES) $(CPP_FILES) $(C_FILES) $(S_FILES)
.PRECIOUS:	$(SOURCEFILES)
OBJFILES =	mapADT.o 

#
# Main targets
#

all:	mapTest1 mapTest2 mapTest3 

mapTest1:	mapTest1.o $(OBJFILES)
	$(CC) $(CFLAGS) -o mapTest1 mapTest1.o $(OBJFILES) $(CLIBFLAGS)

mapTest2:	mapTest2.o $(OBJFILES)
	$(CC) $(CFLAGS) -o mapTest2 mapTest2.o $(OBJFILES) $(CLIBFLAGS)

mapTest3:	mapTest3.o $(OBJFILES)
	$(CC) $(CFLAGS) -o mapTest3 mapTest3.o $(OBJFILES) $(CLIBFLAGS)

#
# Dependencies
#

mapADT.o:	mapADT.h
mapTest1.o:	mapADT.h
mapTest2.o:	mapADT.h
mapTest3.o:	mapADT.h

#
# Housekeeping
#

Archive:	archive.tgz

archive.tgz:	$(SOURCEFILES) Makefile
	tar cf - $(SOURCEFILES) Makefile | gzip > archive.tgz

clean:
	-/bin/rm -f $(OBJFILES) mapTest1.o mapTest2.o mapTest3.o core

realclean:        clean
	-/bin/rm -f mapTest1 mapTest2 mapTest3 
