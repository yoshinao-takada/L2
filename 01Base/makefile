CC = gcc
SLCPP = node ../99Tools/slcpp.js
INCDIR = ../include
INCFLAGS = -I$(INCDIR)
DEBUG_CCFLAGS = $(INCFLAGS) -g -c
RELEASE_CCFLAGS = $(INCFLAGS) -O3 -c
BINDIR = ../bin
DEBUG_BINDIR = $(BINDIR)/debug
RELEASE_BINDIR = $(BINDIR)/release
DEBUG_OBJDIR = $(DEBUG_BINDIR)/o
RELEASE_OBJDIR = $(RELEASE_BINDIR)/o
DEBUG_OBJECTS = $(DEBUG_OBJDIR)/Array.o $(DEBUG_OBJDIR)/NumbersCopy.o $(DEBUG_OBJDIR)/Log.o
RELEASE_OBJECTS = $(RELEASE_OBJDIR)/Array.o $(RELEASE_OBJDIR)/NumbersCopy.o $(RELEASE_OBJDIR)/Log.o
DEBUG_TARGET = $(DEBUG_BINDIR)/01BaseDone
RELEASE_TARGET = $(RELEASE_BINDIR)/01BaseDone
HEADERS = $(INCDIR)/SLC/Numbers.h $(INCDIR)/SLC/Array.h $(INCDIR)/SLC/NumbersCopy.h \
	$(INCDIR)/SLC/Log.h

.PHONY	:	debug
.PHONY	:	release
.PHONY	:	clean_debug
.PHONY	:	clean_release

debug	:	$(DEBUG_TARGET) $(INCDIR)/SLC/ExIO.h

$(DEBUG_TARGET)	:	$(DEBUG_OBJECTS)
	mkdir -p $(DEBUG_BINDIR)
	touch $@

$(DEBUG_OBJDIR)/Array.o	:	Array.c $(INCDIR)/SLC/Array.h
	mkdir -p $(DEBUG_OBJDIR)
	$(CC) $(DEBUG_CCFLAGS) -o $@ $<

$(DEBUG_OBJDIR)/NumbersCopy.o	:	NumbersCopy.c $(INCDIR)/SLC/NumbersCopy.h
	mkdir -p $(DEBUG_OBJDIR)
	$(CC) $(DEBUG_CCFLAGS) -o $@ $<

$(DEBUG_OBJDIR)/Log.o	:	Log.c $(INCDIR)/SLC/Log.h $(INCDIR)/SLC/ExIO.h
	mkdir -p $(DEBUG_OBJDIR)
	$(CC) $(DEBUG_CCFLAGS) -o $@ $<

release	:	$(RELEASE_TARGET) $(INCDIR)/SLC/ExIO.h

$(RELEASE_TARGET)	:	$(RELEASE_OBJECTS)
	mkdir -p $(RELEASE_BINDIR)
	touch $@

$(RELEASE_OBJDIR)/Array.o	:	Array.c $(INCDIR)/SLC/Array.h
	mkdir -p $(RELEASE_OBJDIR)
	$(CC) $(RELEASE_CCFLAGS) -o $@ $<

$(RELEASE_OBJDIR)/NumbersCopy.o	:	NumbersCopy.c $(INCDIR)/SLC/NumbersCopy.h
	mkdir -p $(RELEASE_OBJDIR)
	$(CC) $(RELEASE_CCFLAGS) -o $@ $<

$(RELEASE_OBJDIR)/Log.o	:	Log.c $(INCDIR)/SLC/Log.h $(INCDIR)/SLC/ExIO.h
	mkdir -p $(RELEASE_OBJDIR)
	$(CC) $(RELEASE_CCFLAGS) -o $@ $<

Array.c	:	Array.c.md
	$(SLCPP) $<

NumbersCopy.c	:	NumbersCopy.c.md
	$(SLCPP) $<

Log.c	:	Log.c.md
	$(SLCPP) $<

../include/SLC/Numbers.h	:	Numbers.h.md
	$(SLCPP) $<

../include/SLC/Array.h	:	Array.h.md
	$(SLCPP) $<

../include/SLC/NumbersCopy.h	:	NumbersCopy.h.md
	$(SLCPP) $<

../include/SLC/Log.h	:	Log.h.md
	$(SLCPP) $<

clean_debug	:
	rm -f $(DEBUG_OBJECTS) $(DEBUG_TARGET) $(HEADERS)
	rm -f ./*.c

clean_release	:
	rm -f $(RELEASE_OBJECTS) $(RELEASE_TARGET) $(HEADERS)
	rm -f ./*.c

clean	:
	rm -f $(DEBUG_OBJECTS) $(DEBUG_TARGET) $(HEADERS)
	rm -f $(RELEASE_OBJECTS) $(RELEASE_TARGET) $(HEADERS)
	rm -f ./*.c
