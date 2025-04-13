CXX = g++
CXXFLAGS = -std=c++17 -Wall $(shell pkg-config gtkmm-3.0 --cflags)
LDFLAGS = $(shell pkg-config gtkmm-3.0 --libs) -lmysqlclient

SRCS = main.cpp homepage.cpp login.cpp register.cpp database.cpp
TARGET = deepchat

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRCS) $(LDFLAGS)

clean:
	rm -f $(TARGET) *.o

.PHONY: all clean