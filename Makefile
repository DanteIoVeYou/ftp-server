CC=g++
FLAG=-std=c++11
server:unittest.cpp
	$(CC) -o $@ $^ $(FLAG)
.PHONY:clean
clean:
	rm -rf server