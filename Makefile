CFLAGS = -std=c11 -Wno-return-local-addr
OBJS = main.o game.o board.o
OUT = chess

$(OUT): $(OBJS)
    gcc $(OBJS)  $(CFLAGS) -o $(OUT)

%.o: %.c
    gcc -c $(CFLAGS) $<

clean:
    rm *.o $(OUT)
