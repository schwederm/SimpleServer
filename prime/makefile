CXX = g++
CXXFLAGS = -Wall -g

TARGET = prime

SRCS = $(TARGET).cpp

OBJS = $(SRCS:.cpp=.o)

all: $(TARGET) run

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $^

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(DEPS)

run: $(TARGET)
	./$(TARGET)

clean:
	rm $(OBJS) $(TARGET).exe