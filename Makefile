CC=g++
FLAG=-std=c++17 -lpthread
CRYPT=md5.cpp
SRC1=server.cpp
SRC2=client.cpp
all:server client
server:$(SRC1)
	$(CC) -o $@ $^ $(CRYPT) $(FLAG)
client:$(SRC2)
	$(CC) -o $@ $^ $(FLAG) 
.PHONY:clean
clean:
	rm -rf server client
