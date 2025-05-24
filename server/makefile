CXX = g++
CXXFLAGS = -Wall -g

TARGET = server

SRCS = $(TARGET).cpp

OBJS = $(SRCS:.cpp=.o)

LIBS = -lws2_32

all: $(TARGET) run

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $^

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LIBS)

run: $(TARGET)
	./$(TARGET)

clean:
	rm $(OBJS) $(TARGET).exe