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
	$(DEBUG_OBJDIR)/NLSL.o $(DEBUG_OBJDIR)/Geom.o
RELEASE_OBJECTS = $(RELEASE_OBJDIR)/MiniBLAS.o $(DEBUG_OBJDIR)/MiniLA.o \
	$(RELEASE_OBJDIR)/NLSL.o $(RELEASE_OBJDIR)/Geom.o
DEBUG_TARGET = $(DEBUG_BINDIR)/01MathDone
RELEASE_TARGET = $(RELEASE_BINDIR)/01MathDone
HEADERS = $(INCDIR)/SLC/MiniBLAS.h $(INCDIR)/SLC/MiniLA.h $(INCDIR)/SLC/NLSL.h \
	$(INCDIR)/SLC/Geom.h

.PHONY	:	debug
.PHONY	:	release
.PHONY	:	clean_debug
.PHONY	:	clean_release

debug	:	$(DEBUG_TARGET) $(HEADERS)

$(DEBUG_TARGET)	:	$(DEBUG_OBJECTS)
	mkdir -p $(DEBUG_BINDIR)
	touch $@

$(DEBUG_OBJDIR)/MiniBLAS.o	:	MiniBLAS.c $(INCDIR)/SLC/MiniBLAS.h
	mkdir -p $(DEBUG_OBJDIR)
	$(CC) $(DEBUG_CCFLAGS) -o $@ $<

$(DEBUG_OBJDIR)/MiniLA.o	:	MiniLA.c $(INCDIR)/SLC/MiniLA.h $(INCDIR)/SLC/MiniBLAS.h
	mkdir -p $(DEBUG_OBJDIR)
	$(CC) $(DEBUG_CCFLAGS) -o $@ $<

$(DEBUG_OBJDIR)/NLSL.o	:	NLSL.c $(INCDIR)/SLC/NLSL.h $(INCDIR)/SLC/MiniLA.h $(INCDIR)/SLC/MiniBLAS.h
	mkdir -p $(DEBUG_OBJDIR)
	$(CC) $(DEBUG_CCFLAGS) -o $@ $<

$(DEBUG_OBJDIR)/Geom.o	:	Geom.c $(INCDIR)/SLC/Geom.h $(INCDIR)/SLC/NLSL.h $(INCDIR)/SLC/MiniLA.h $(INCDIR)/SLC/MiniBLAS.h
	mkdir -p $(DEBUG_OBJDIR)
	$(CC) $(DEBUG_CCFLAGS) -o $@ $<

release	:	$(RELEASE_TARGET) $(HEADERS)

$(RELEASE_TARGET)	:	$(RELEASE_OBJECTS)
	mkdir -p $(RELEASE_BINDIR)
	touch $@

$(RELEASE_OBJDIR)/MiniBLAS.o	:	MiniBLAS.c $(INCDIR)/SLC/MiniBLAS.h
	mkdir -p $(RELEASE_OBJDIR)
	$(CC) $(RELEASE_CCFLAGS) -o $@ $<

$(RELEASE_OBJDIR)/MiniLA.o	:	MiniLA.c $(INCDIR)/SLC/MiniLA.h $(INCDIR)/SLC/MiniBLAS.h
	mkdir -p $(RELEASE_OBJDIR)
	$(CC) $(RELEASE_CCFLAGS) -o $@ $<

$(RELEASE_OBJDIR)/NLSL.o	:	NLSL.c $(INCDIR)/SLC/NLSL.h $(INCDIR)/SLC/MiniLA.h $(INCDIR)/SLC/MiniBLAS.h
	mkdir -p $(RELEASE_OBJDIR)
	$(CC) $(RELEASE_CCFLAGS) -o $@ $<

$(RELEASE_OBJDIR)/Geom.o	:	Geom.c $(INCDIR)/SLC/Geom.h $(INCDIR)/SLC/NLSL.h $(INCDIR)/SLC/MiniLA.h $(INCDIR)/SLC/MiniBLAS.h
	mkdir -p $(RELEASE_OBJDIR)
	$(CC) $(RELEASE_CCFLAGS) -o $@ $<

MiniBLAS.c	:	MiniBLAS.c.md
	$(SLCPP) $<

MiniLA.c	:	MiniLA.c.md
	$(SLCPP) $<

NLSL.c	:	NLSL.c.md
	$(SLCPP) $<

Geom.c	:	Geom.c.md
	$(SLCPP) $<

$(INCDIR)/SLC/MiniBLAS.h	:	MiniBLAS.h.md
	mkdir -p $(INCDIR)/SLC
	$(SLCPP) $<

$(INCDIR)/SLC/MiniLA.h	:	MiniLA.h.md
	mkdir -p $(INCDIR)/SLC
	$(SLCPP) $<

$(INCDIR)/SLC/NLSL.h	:	NLSL.h.md
	mkdir -p $(INCDIR)/SLC
	$(SLCPP) $<

$(INCDIR)/SLC/Geom.h	:	Geom.h.md
	mkdir -p $(INCDIR)/SLC
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
