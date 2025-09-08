# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++20 -Wall

# Find all .cpp files starting with day
SOURCES = $(wildcard day*.cpp)
# Generate executable names from source files (e.g., day1.cpp -> day1)
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
		if [ -d "day$(day)" ]; then \
			echo "Running day $(day) part 1"; \
			$(CXX) $(CXXFLAGS) -o day$(day)/part1 day$(day)/part1.cpp && ./day$(day)/part1; \
			echo "Running day $(day) part 2"; \
			$(CXX) $(CXXFLAGS) -o day$(day)/part2 day$(day)/part2.cpp && ./day$(day)/part2; \
		else \
			$(CXX) $(CXXFLAGS) -o day$(day) day$(day).cpp && ./day$(day); \
		fi \
	fi


# Target to clean up compiled files
clean:
	rm -f $(EXECUTABLES)

# Phony targets are not files
.PHONY: all run clean
