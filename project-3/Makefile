#
# Created by gmakemake (Ubuntu Jul 25 2014) on Tue Nov 26 15:33:56 2019
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

CFLAGS =	-std=c99 -ggdb -Wall -Wextra -pedantic
CLIBFLAGS =	-lm 


########## End of flags from header.mak


CPP_FILES =	
C_FILES =	offspring.c queue.c queue_test.c tree.c trimit.c
PS_FILES =	
S_FILES =	
H_FILES =	queue.h tree.h trimit.h
SOURCEFILES =	$(H_FILES) $(CPP_FILES) $(C_FILES) $(S_FILES)
.PRECIOUS:	$(SOURCEFILES)
OBJFILES =	queue.o tree.o trimit.o 

#
# Main targets
#

all:	offspring queue_test 

offspring:	offspring.o $(OBJFILES)
	$(CC) $(CFLAGS) -o offspring offspring.o $(OBJFILES) $(CLIBFLAGS)

queue_test:	queue_test.o $(OBJFILES)
	$(CC) $(CFLAGS) -o queue_test queue_test.o $(OBJFILES) $(CLIBFLAGS)

#
# Dependencies
#

offspring.o:	queue.h tree.h trimit.h
queue.o:	queue.h
queue_test.o:	queue.h tree.h
tree.o:	queue.h tree.h
trimit.o:	trimit.h

#
# Housekeeping
#

Archive:	archive.tgz

archive.tgz:	$(SOURCEFILES) Makefile
	tar cf - $(SOURCEFILES) Makefile | gzip > archive.tgz

clean:
	-/bin/rm -f $(OBJFILES) offspring.o queue_test.o core

realclean:        clean
	-/bin/rm -f offspring queue_test 
