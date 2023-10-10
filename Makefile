# Jasmine Owens
# Makefile for project 6
#
# Reuse likely. Heavily inspired by the examples in this post:
# https://stackoverflow.com/questions/30573481/how-to-write-a-makefile-with-separate-source-and-header-directories
#
PROJNUM = 6

SDIR = src
HDIR = include
ODIR = obj
BDIR = bin
EXE = bin/editor

SRC_1 = $(wildcard $(SDIR)/editor.cpp $(SDIR)/filters.cpp $(SDIR)/MyGui.cpp )
OBJ_1 = $(SRC_1:$(SDIR)/%.c=$(ODIR)/%.o)

GRD = makefile ${SRC} ${HDR}

CC=g++
CFLAGS = -g0 -I$(HDIR)
OPENCV = -I"C:\opencv\build\include" -L"C:\opencv\build\x64\mingw\lib" -lopencv_core452 -lopencv_highgui452 -lopencv_imgproc452 -lopencv_imgcodecs452

# Create all files

all:    $(EXE)

bin/editor:  $(OBJ_1) | $(BDIR)
	$(CC)	$(CFLAGS) $^ -o $@ $(OPENCV)

#objects for exes
$(ODIR)/%.o: $(SDIR)/%.c | $(ODIR)
	$(CC)	$(CFLAGS) -c $< -o $@

$(BDIR) $(ODIR):
	mkdir -p $@

#
# Clean up script
#

.PHONY:
clean:
	rm -f *.o editor
