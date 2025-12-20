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
DEBUG_OBJECTS = $(DEBUG_OBJDIR)/MiniBLAS.o $(DEBUG_OBJDIR)/MiniLA.o \
	$(DEBUG_OBJDIR)/NLSL.o $(DEBUG_OBJDIR)/NumbersCopy.o $(DEBUG_OBJDIR)/Log.o \
	$(DEBUG_OBJDIR)/Array.o $(DEBUG_OBJDIR)/Stopwatch.o
DEBUG_APP_OBJECTS = ./app.o
DEBUG_TARGET = ./app.exe

.PHONY	:	debug
.PHONY	:	clean_debug

debug	:	$(DEBUG_TARGET)

$(DEBUG_TARGET)	:	$(DEBUG_OBJECTS) $(DEBUG_APP_OBJECTS)
	$(CC) -o $@ $^ -lm -lpthread

$(DEBUG_APP_OBJECTS)	:	app.c
	$(CC) $(DEBUG_CCFLAGS) -o $@ $<

clean_debug	:
	rm -f $(DEBUG_TARGET) $(DEBUG_APP_OBJECTS)
