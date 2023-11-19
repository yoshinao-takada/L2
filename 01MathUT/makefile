CC = gcc
SLCPP = node ../98Tools/slcpp.js
INCDIR = ../include
INCFLAGS = -I$(INCDIR)
DEBUG_CCFLAGS = $(INCFLAGS) -g -c
RELEASE_CCFLAGS = $(INCFLAGS) -O3 -c
BINDIR = ../bin
DEBUG_BINDIR = $(BINDIR)/debug
RELEASE_BINDIR = $(BINDIR)/release
DEBUG_OBJDIR = $(DEBUG_BINDIR)/o
RELEASE_OBJDIR = $(RELEASE_BINDIR)/o
DEBUG_TEST_OBJECTS = $(DEBUG_OBJDIR)/MiniBLAS.o $(DEBUG_OBJDIR)/MiniLA.o \
	$(DEBUG_OBJDIR)/NLSL.o $(DEBUG_OBJDIR)/NumbersCopy.o $(DEBUG_OBJDIR)/Log.o \
	$(DEBUG_OBJDIR)/Array.o $(DEBUG_OBJDIR)/Stopwatch.o
DEBUG_OBJECTS = $(DEBUG_OBJDIR)/01MathUT.o \
	$(DEBUG_OBJDIR)/MiniBLASUT.o $(DEBUG_OBJDIR)/MiniLAUT.o \
	$(DEBUG_OBJDIR)/NLSLUT.o $(DEBUG_OBJDIR)/GeomUT.o
RELEASE_TEST_OBJECTS = $(RELEASE_OBJDIR)/01MathUT.o \
	$(RELEASE_OBJDIR)/MiniBLAS.o $(DEBUG_OBJDIR)/MiniLA.o \
	$(RELEASE_OBJDIR)/NLSL.o $(RELEASE_OBJDIR)/NumbersCopy.o $(RELEASE_OBJDIR)/Log.o \
	$(RELEASE_OBJDIR)/Array.o $(RELEASE_OBJDIR)/Stopwatch.o
RELEASE_OBJECTS = $(RELEASE_OBJDIR)/MiniBLASUT.o $(RELEASE_OBJDIR)/MiniLAUT.o \
	$(RELEASE_OBJDIR)/NLSLUT.o $(RELEASE_OBJDIR)/GeomUT.o
DEBUG_TARGET = $(DEBUG_BINDIR)/01MathUT.exe
RELEASE_TARGET = $(RELEASE_BINDIR)/01MathUT.exe
HEADERS = $(INCDIR)/SLC/MiniBLAS.h $(INCDIR)/SLC/MiniLA.h $(INCDIR)/SLC/NLSL.h
.PHONY	:	debug
.PHONY	:	release
.PHONY	:	clean_debug
.PHONY	:	clean_release

#---------------DEBUG---------------------
debug	:	$(DEBUG_TARGET)

$(DEBUG_TARGET)	:	$(DEBUG_OBJECTS) $(DEBUG_TEST_OBJECTS)
	mkdir -p $(DEBUG_BINDIR)
	$(CC) -o $@ $^ -lm -lpthread

$(DEBUG_OBJDIR)/01MathUT.o	:	01MathUT.c
	mkdir -p $(DEBUG_OBJDIR)
	$(CC) $(DEBUG_CCFLAGS) -o $@ $<

$(DEBUG_OBJDIR)/MiniBLASUT.o	:	MiniBLASUT.c
	mkdir -p $(DEBUG_OBJDIR)
	$(CC) $(DEBUG_CCFLAGS) -o $@ $<

$(DEBUG_OBJDIR)/MiniLAUT.o	:	MiniLAUT.c
	mkdir -p $(DEBUG_OBJDIR)
	$(CC) $(DEBUG_CCFLAGS) -o $@ $<

$(DEBUG_OBJDIR)/NLSLUT.o	:	NLSLUT.c
	mkdir -p $(DEBUG_OBJDIR)
	$(CC) $(DEBUG_CCFLAGS) -o $@ $<

$(DEBUG_OBJDIR)/GeomUT.o	:	GeomUT.c
	mkdir -p $(DEBUG_OBJDIR)
	$(CC) $(DEBUG_CCFLAGS) -o $@ $<
#---------------RELEASE---------------------
release	:	$(RELEASE_TARGET)

$(RELEASE_TARGET)	:	$(RELEASE_OBJECTS) $(RELEASE_TEST_OBJECTS)
	mkdir -p $(RELEASE_BINDIR)
	$(CC) -o $@ $^ -lm -lpthread

$(RELEASE_OBJDIR)/01MathUT.o	:	01MathUT.c
	mkdir -p $(RELEASE_OBJDIR)
	$(CC) $(RELEASE_CCFLAGS) -o $@ $<

$(RELEASE_OBJDIR)/MiniBLASUT.o	:	MiniBLASUT.c
	mkdir -p $(RELEASE_OBJDIR)
	$(CC) $(RELEASE_CCFLAGS) -o $@ $<

$(RELEASE_OBJDIR)/MiniLAUT.o	:	MiniLAUT.c
	mkdir -p $(RELEASE_OBJDIR)
	$(CC) $(RELEASE_CCFLAGS) -o $@ $<
#---------- .c source file -------------------
01MathUT.c	:	01MathUT.c.md
	$(SLCPP) $<

MiniBLASUT.c	:	MiniBLASUT.c.md
	$(SLCPP) $<

MiniLAUT.c	:	MiniLAUT.c.md
	$(SLCPP) $<

NLSLUT.c	:	NLSLUT.c.md
	$(SLCPP) $<

GeomUT.c	:	GeomUT.c.md
	$(SLCPP) $<
#---------------CLEAN---------------------
clean_debug	:
	rm -f $(DEBUG_TARGET) $(DEBUG_OBJECTS) *.c

clean_release	:
	rm -f $(RELEASE_TARGET) $(RELEASE_OBJECTS) *.c

clean	:
	$(MAKE) clean_debug
	$(MAKE) clean_release
