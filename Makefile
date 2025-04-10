# Makefile for Real-Time Chat Application (.cc version)

# Compiler and Flags
CXX = g++
CXXFLAGS = -pthread -Wall -Wextra -std=c++11

# Targets
all: server client

server: server.cc
	$(CXX) $(CXXFLAGS) -o server server.cc

client: client.cc
	$(CXX) $(CXXFLAGS) -o client client.cc

clean:
	rm -f server client
