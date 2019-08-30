ifeq ($(CC),)
CC := gcc
endif
CFLAGS := -lSDL

SOURCEDIR = ./src
BUILDDIR = build
EXECUTABLE = test-graphic

SOURCES = $(wildcard $(SOURCEDIR)/*.c)

all: dir $(BUILDDIR)/$(EXECUTABLE)

dir:
	mkdir -p $(BUILDDIR)

$(BUILDDIR)/$(EXECUTABLE): $(SOURCES)
	$(CC) $< -o $@  $(CFLAGS)

clean:
	rm -f $(BUILDDIR)/* $(BUILDDIR)/$(EXECUTABLE)