CXX = g++
CXXFLAGS = -Wall -g

TARGET = client

SRCS = $(TARGET).cpp

OBJS = $(SRCS:.cpp=.o)

LIBS = -lws2_32 -lmswsock -ladvapi32

all: $(TARGET) run

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $^

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LIBS)

run: $(TARGET)
	./$(TARGET) localhost

clean:
	rm $(OBJS) $(TARGET).exe