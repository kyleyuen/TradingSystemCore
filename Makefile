CC = g++
CXXFLAGS = -std=c++11 -O2 -Wall -Wextra -Iinclude
SRCS = src/main.cpp src/PriceDataTracker.cpp src/readCSV.cpp src/Indicators.cpp src/SMATrendStrategy.cpp
OBJDIR = build/obj
BINDIR = build
OBJS = $(patsubst src/%.cpp,$(OBJDIR)/%.o,$(SRCS))
TARGET = $(BINDIR)/tracker

all: $(TARGET)

$(TARGET): $(OBJS)
	mkdir -p $(BINDIR)
	$(CC) $(CXXFLAGS) -o $@ $(OBJS)

$(OBJDIR)/%.o: src/%.cpp
	mkdir -p $(dir $@)
	$(CC) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf build

.PHONY: all clean test

test: $(TARGET)
	$(TARGET)

