<<<<<<< HEAD
SOURCEDIR = src
DESTDIR = bin

CFLAGS = -std=c11 -Wno-return-local-addr
LIBS := $(shell ncursesw5-config --libs) -ltinfo
SRCS := $(wildcard $(SOURCEDIR)/*.c)
OBJS := $(patsubst %.c, %.o, $(SRCS))
OUT = chess

$(OUT): $(OBJS)
	gcc -g $(OBJS) $(CFLAGS) -o $(DESTDIR)/$(OUT)
	#NCURSES build
	#gcc $(OBJS) $(CFLAGS) $(LIBS) $(shell ncursesw5-config --cflags) --enable-widec -o $(DESTDIR)/$(OUT)

%.o: %.c
	gcc -c $< $(CFLAGS) -o $@

clean:
	rm $(OBJS) $(DESTDIR)/$(OUT)

test:
	$(foreach src, $(SRCS), gcc -c $(src) -DTEST $(CFLAGS) -o $(basename $(src)).o;)
	gcc $(OBJS) $(CFLAGS) -o $(DESTDIR)/$(OUT)
=======
build:
	gcc -std=c11 -c main.c
	gcc -std=c11 -c -Wno-return-local-addr game.c
	gcc -std=c11 -c board.c
	gcc -std=c11 -c gui.c
	#link
	gcc -std=c11 main.o board.o game.o gui.o -o a -lncurses
>>>>>>> e085263 (Initial Rebase Commit)
