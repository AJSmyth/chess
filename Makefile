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

tar:
	tar -zcvf Chess_V1.0.tar.gz ./README ./COPYRIGHT ./INSTALL ./bin ./doc/Chess_UserManual.pdf
	tar -zcvf Chess_V1.0_src.tar.gz ./README ./COPYRIGHT ./INSTALL ./doc ./bin ./src ./Makefile

clean_tar:
	rm *.tar.gz
