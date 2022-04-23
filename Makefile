SOURCEDIR = src
DESTDIR = bin

CFLAGS = -std=c11 -Wno-return-local-addr 
LIBS := $(shell ncursesw5-config --libs) -ltinfo
SRCS := $(wildcard $(SOURCEDIR)/*.c)
OBJS := $(patsubst %.c, %.o, $(SRCS))
OUT = chess

$(OUT): $(OBJS)
	gcc $(OBJS) $(CFLAGS) -o $(OUT)
	#NCURSES build
	#gcc $(OBJS) $(CFLAGS) $(LIBS) $(shell ncursesw5-config --cflags) --enable-widec -o $(DESTDIR)/$(OUT)

%.o: %.c
	gcc -c $< $(CFLAGS) -o $@

clean:
	rm $(OBJS) $(DESTDIR)/$(OUT)

test: %.c 
	gcc -c $< -DTEST $(CFLAGS)
	gcc $(OBJS) $(CFLAGS) -o $(DESTDIR)/$(OUT)