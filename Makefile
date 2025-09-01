# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++20 -Wall

# Find all .cpp files starting with day_
SOURCES = $(wildcard day_*.cpp)
# Generate executable names from source files (e.g., day_1.cpp -> day_1)
EXECUTABLES = $(patsubst %.cpp,%,$(SOURCES))

# Default target: build all executables
all: $(EXECUTABLES)

# Rule to build an executable from a .cpp file
# This is a pattern rule that says how to make a file '%' from a file '%.cpp'
%: %.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

# Target to run a specific day's solution
# Example usage: make run day=1
run:
	@if [ -z "$(day)" ]; then \
		echo "Usage: make run day=<day_number>"; \
	else \
		$(CXX) $(CXXFLAGS) -o day_$(day) day_$(day).cpp && ./day_$(day); \
	fi

# Target to clean up compiled files
clean:
	rm -f $(EXECUTABLES)

# Phony targets are not files
.PHONY: all run clean
