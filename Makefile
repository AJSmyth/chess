CFLAGS = -std=c11 -Wno-return-local-addr
OBJS = main.o game.o board.o
CF = main.c game.c board.c
OUT = chess

$(OUT): $(OBJS)
	gcc $(OBJS) $(CFLAGS) -o $(OUT)

%.o: %.c
	gcc -c $(CFLAGS) $<

clean:
	rm *.o $(OUT)

test: $(CF) 
	gcc -c $(CF) -DTEST $(CFLAGS)
	gcc $(OBJS) $(CFLAGS) -o $(OUT)
