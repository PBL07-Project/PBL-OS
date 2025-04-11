CXX = g++
CXXFLAGS = -std=c++17 -Wall `pkg-config gtkmm-3.0 --cflags` -I/usr/include/mysql
LDFLAGS = `pkg-config gtkmm-3.0 --libs` -lmysqlclient

SRC = main.cpp db/db.cpp
OBJ = $(SRC:.cpp=.o)
TARGET = chat_app

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(OBJ) -o $@ $(LDFLAGS)

clean:
	rm -f $(OBJ) $(TARGET)
