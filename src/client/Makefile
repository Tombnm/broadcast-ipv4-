CFLAGS+=-I../include

All:client

client:client.o
	gcc $^ -o $@ $(CFLAGS)

clean:
	rm -rf *.o client
