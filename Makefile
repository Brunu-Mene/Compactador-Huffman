TARGETc := Compacta
TARGETd := Descompacta
LIBS := -lm
OBJDIR := obj/
SRCDIR := src/
INCLUDEDIR := include/
INCLUDE_PATHS := -Iinclude
CLIc := client/CMain.c
CLId := client/DMain.c
CC := gcc

all: $(TARGETc) $(TARGETd)

SRC = $(wildcard $(SRCDIR)*.c)
HEADERS = $(wildcard $(INCLUDEDIR)*.h)

CLIENTc = $(OBJDIR)$(basename $(notdir $(CLIc)))
CLIENTd = $(OBJDIR)$(basename $(notdir $(CLId)))

OBJECTSc := $(SRC:$(SRCDIR)%.c=$(OBJDIR)%.o)
OBJECTSc += $(CLIENTc).o

OBJECTSd := $(SRC:$(SRCDIR)%.c=$(OBJDIR)%.o)
OBJECTSd += $(CLIENTd).o

$(OBJDIR)%.o: $(SRCDIR)%.c $(HEADERS)
	@ mkdir -p $(OBJDIR)
	$(CC) $(INCLUDE_PATHS) $(CFLAGS) -c -o $@ $<

$(CLIENTc).o: $(CLIc)
	$(CC) $(INCLUDE_PATHS) $(CFLAGS) -c -o $@ $<

$(CLIENTd).o: $(CLId)
	$(CC) $(INCLUDE_PATHS) $(CFLAGS) -c -o $@ $<
  

$(TARGETc): $(OBJECTSc)
	$(CC) $(INCLUDE_PATHS) $(OBJECTSc) $(LIBS) -o $@

$(TARGETd): $(OBJECTSd)
	$(CC) $(INCLUDE_PATHS) $(OBJECTSd) $(LIBS) -o $@

clean:
	-rm -f -r obj
	-rm -f *.o
	-rm -f $(TARGETc)
	-rm -f $(TARGETd)
