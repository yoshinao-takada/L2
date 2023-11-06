CC = gcc
# markdown to c preprocessor
SLCPP = node ../98Tools/slcpp.js
INCDIR = ../include
INCFLAGS = -I$(INCDIR)
DEBUG_CCFLAGS = $(INCFLAGS) -D_DEBUG -g -c
RELEASE_CCFLAGS = $(INCFLAGS) -DNDEBUG -O3 -c
BINDIR = ../bin
DEBUG_BINDIR = $(BINDIR)/debug
RELEASE_BINDIR = $(BINDIR)/release
DEBUG_OBJDIR = $(DEBUG_BINDIR)/o
RELEASE_OBJDIR = $(RELEASE_BINDIR)/o
DEBUG_OBJECTS = $(DEBUG_OBJDIR)/00BaseUT.o $(DEBUG_OBJDIR)/ArrayUT.o $(DEBUG_OBJDIR)/NumbersCopyUT.o \
	$(DEBUG_OBJDIR)/LogUT.o $(DEBUG_OBJDIR)/StopwatchUT.o $(DEBUG_OBJDIR)/NumbersUT.o
DEBUG_TEST_OBJECTS = $(DEBUG_OBJDIR)/NumbersCopy.o $(DEBUG_OBJDIR)/Log.o \
	$(DEBUG_OBJDIR)/Array.o $(DEBUG_OBJDIR)/Stopwatch.o
RELEASE_OBJECTS = $(RELEASE_OBJDIR)/00BaseUT.o $(RELEASE_OBJDIR)/ArrayUT.o $(RELEASE_OBJDIR)/NumbersCopyUT.o \
	$(RELEASE_OBJDIR)/LogUT.o $(RELEASE_OBJDIR)/StopwatchUT.o $(RELEASE_OBJDIR)/NumbersUT.o
RELEASE_TEST_OBJECTS = $(RELEASE_OBJDIR)/NumbersCopy.o $(RELEASE_OBJDIR)/Log.o \
	$(RELEASE_OBJDIR)/Array.o $(RELEASE_OBJDIR)/Stopwatch.o
DEBUG_TARGET = $(DEBUG_BINDIR)/00BaseUT.exe
RELEASE_TARGET = $(RELEASE_BINDIR)/00BaseUT.exe

.PHONY	:	debug
.PHONY	:	release
.PHONY	:	clean_debug
.PHONY	:	clean_release

debug	:	$(DEBUG_TARGET)

$(DEBUG_TARGET)	:	$(DEBUG_OBJECTS) $(DEBUG_TEST_OBJECTS)
	mkdir -p $(DEBUG_BINDIR)
	$(CC) -o $@ $^ -lm -lpthread

$(DEBUG_OBJDIR)/00BaseUT.o	:	00BaseUT.c
	mkdir -p $(DEBUG_OBJDIR)
	$(CC) $(DEBUG_CCFLAGS) -o $@ $<

$(DEBUG_OBJDIR)/ArrayUT.o	:	ArrayUT.c
	mkdir -p $(DEBUG_OBJDIR)
	$(CC) $(DEBUG_CCFLAGS) -o $@ $<

$(DEBUG_OBJDIR)/LogUT.o	:	LogUT.c
	mkdir -p $(DEBUG_OBJDIR)
	$(CC) $(DEBUG_CCFLAGS) -o $@ $<

$(DEBUG_OBJDIR)/NumbersCopyUT.o	:	NumbersCopyUT.c
	mkdir -p $(DEBUG_OBJDIR)
	$(CC) $(DEBUG_CCFLAGS) -o $@ $<

$(DEBUG_OBJDIR)/StopwatchUT.o	:	StopwatchUT.c
	mkdir -p $(DEBUG_OBJDIR)
	$(CC) $(DEBUG_CCFLAGS) -o $@ $<

$(DEBUG_OBJDIR)/NumbersUT.o	:	NumbersUT.c
	mkdir -p $(DEBUG_OBJDIR)
	$(CC) $(DEBUG_CCFLAGS) -o $@ $<

release	:	$(RELEASE_TARGET)

$(RELEASE_TARGET)	:	$(RELEASE_OBJECTS) $(RELEASE_TEST_OBJECTS)
	$(CC) -o $@ $^ -lm -lpthread

$(RELEASE_OBJDIR)/00BaseUT.o	:	00BaseUT.c
	mkdir -p $(RELEASE_OBJDIR)
	$(CC) $(RELEASE_CCFLAGS) -o $@ $<

$(RELEASE_OBJDIR)/ArrayUT.o	:	ArrayUT.c
	mkdir -p $(RELEASE_OBJDIR)
	$(CC) $(RELEASE_CCFLAGS) -o $@ $<

$(RELEASE_OBJDIR)/LogUT.o	:	LogUT.c
	mkdir -p $(RELEASE_OBJDIR)
	$(CC) $(RELEASE_CCFLAGS) -o $@ $<

$(RELEASE_OBJDIR)/NumbersCopyUT.o	:	NumbersCopyUT.c
	mkdir -p $(RELEASE_OBJDIR)
	$(CC) $(RELEASE_CCFLAGS) -o $@ $<

$(RELEASE_OBJDIR)/StopwatchUT.o	:	StopwatchUT.c
	mkdir -p $(RELEASE_OBJDIR)
	$(CC) $(RELEASE_CCFLAGS) -o $@ $<

$(RELEASE_OBJDIR)/NumbersUT.o	:	NumbersUT.c
	mkdir -p $(RELEASE_OBJDIR)
	$(CC) $(RELEASE_CCFLAGS) -o $@ $<

00BaseUT.c	:	00BaseUT.c.md
	$(SLCPP) $<

NumbersUT.c	:	NumbersUT.c.md
	$(SLCPP) $<

NumbersCopyUT.c	:	NumbersCopyUT.c.md
	$(SLCPP) $<

LogUT.c	:	LogUT.c.md
	$(SLCPP) $<

ArrayUT.c	:	ArrayUT.c.md
	$(SLCPP) $<

StopwatchUT.c	:	StopwatchUT.c.md
	$(SLCPP) $<

clean_debug	:
	rm -f $(DEBUG_OBJECTS) $(DEBUG_TARGET)
	rm -f NumbersCopyUT.c LogUT.c

clean_release	:
	rm -f $(RELEASE_OBJECTS) $(RELEASE_TARGET)
	rm -f NumbersCopyUT.c LogUT.c

clean	:	clean_debug clean_release
