CFLAGS = -std=c11 -Wno-return-local-addr 
LIBS = $(shell ncursesw5-config --libs) 
OBJS = main.o game.o gui.o board.o
OUT = a

$(OUT): $(OBJS)
	gcc $(OBJS)  $(CFLAGS) $(LIBS) $(shell ncursesw5-config --cflags) --enable-widec -o $(OUT)

%.o: %.c
	gcc -c $(CFLAGS) $<

clean:
	rm *.o $(OUT)
