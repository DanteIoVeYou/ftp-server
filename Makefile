CC=g++
FLAG=-std=c++17
CRYPT=hash-library/md5.cpp
server:unittest.cpp
	$(CC) -o $@ $^ $(CRYPT) $(FLAG)
.PHONY:clean
clean:
	rm -rf server
