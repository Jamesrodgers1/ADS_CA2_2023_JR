# Define the compiler
CC=g++

# Define any compile-time flags
CFLAGS=-Wall -g

# Define library paths and libraries
LFLAGS=-L/path/to/libs
LIBS=-ltinyxml2

# Define the C++ source files
SRCS=test.cpp Ads_CA2_Tree.cpp tinyxml2.cpp

# Define the C++ object files
OBJS=$(SRCS:.cpp=.o)

# Define the executable file
MAIN=project1

.PHONY: clean

# Default target
all: $(MAIN)
    @echo Project compiled

$(MAIN): $(OBJS)
    $(CC) $(CFLAGS) $(INCLUDES) -o $(MAIN) $(OBJS)

# Rule to create object files
.cpp.o:
    $(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Clean up
clean:
    rm -f *.o *~ $(MAIN)