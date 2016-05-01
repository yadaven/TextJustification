_DEPS=generic_stuff.h matrix.h
_OBJ=matrix.o textjusttification.o driver.o
SRCDIR=src
INCDIR=include
OBJDIR=obj
EXECDIR=exe
CC=gcc
CFLAGS=-I$(INCDIR) -g

OBJS=$(patsubst %,$(OBJDIR)/%,$(_OBJ))
DEPS=$(patsubst %,$(INCDIR)/%,$(_DEPS))


$(OBJDIR)/%.o: $(SRCDIR)/%.c $(DEPS)
	${CC} ${CFLAGS} -c $< -o $@

$(EXECDIR)/driver: $(OBJS) 
	${CC} -o $@ ${CFLAGS} $^

clean:
	rm -rf obj/*

 
