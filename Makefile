SOURCEDIR = src
DESTDIR = bin

CFLAGS = -std=c11 -Wno-return-local-addr 
LIBS := $(shell ncursesw5-config --libs) -ltinfo
OBJS := $(patsubst %.c, %.o, $(wildcard $(SOURCEDIR)/*.c))
OUT = chess

$(OUT): $(OBJS)
	gcc $(OBJS) $(CFLAGS) $(LIBS) $(shell ncursesw5-config --cflags) --enable-widec -o $(DESTDIR)/$(OUT)

%.o: %.c
	gcc -c $< $(CFLAGS) -o $@

clean:
	rm $(OBJS) $(DESTDIR)/$(OUT)
