#--- dtwb ---

BIN = dtwb

CC = vc

VBCCINCLUDE = C:/vbcc/targets/m68k-amigaos/include/
OSINCLUDE = C:/vbcc/include_h/

CFLAGS =-quiet -c -O2 -sc -sd -c99 -I$(VBCCINCLUDE) -I$(OSINCLUDE)
START = C:/vbcc/targets/m68k-amigaos/lib/startup.o

SRCDIR = src
OBJDIR = obj

OBJECTS = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(wildcard $(SRCDIR)/*.c))
HEADERS = $(wildcard $(SRCDIR)/*.h)

LIBS = -LC:/vbcc/targets/m68k-amigaos/lib -lvc -lamiga
LINK = vlink -nostdlib -bamigahunk -Bstatic -Cvbcc -s -x $(START)

RM = rm

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(HEADERS)
	$(CC) $(CFLAGS) $< -o $@

$(BIN): $(OBJECTS)
	$(LINK) $(OBJECTS) -o $@ $(LIBS)

.PHONY: dt cls

dt:	$(BIN)

cls:
	$(RM) $(OBJECTS) $(BIN)
