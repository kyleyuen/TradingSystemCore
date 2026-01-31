CC = g++
CXXFLAGS = -std=c++11 -O2 -Wall -Wextra
SRCS = main.cpp PriceDataTracker.cpp readCSV.cpp
OBJS = $(SRCS:.cpp=.o)
TARGET = tracker

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CXXFLAGS) -o $@ $(OBJS)

%.o: %.cpp
	$(CC) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean
