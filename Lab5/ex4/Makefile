TARGET   = main

CC       = g++

# compiling flags here
CFLAGS   = -std=c++17 -Wall --pedantic -O3

LINKER   = g++
# linking flags here
LFLAGS   = -Wall -lm 

# change these to proper directories where each file should be
SRCDIR   = src
OBJDIR   = obj
BINDIR   = bin
OUTPUT_CSV = outputCSV
SOURCES  := $(wildcard $(SRCDIR)/*.cpp)
INCLUDES := $(wildcard $(SRCDIR)/*.hpp)
OBJECTS  := $(SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)
rm       = rm -f


$(BINDIR)/$(TARGET): $(OBJECTS)
	@$(LINKER) $(OBJECTS) $(LFLAGS) -o $@
	@echo "Linking complete!"
#@echo "EXECUTING $(TARGET)"
#$(BINDIR)/$(TARGET)

$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.cpp
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "Compiled "$<" successfully!"

clean:
	@$(rm) $(OBJECTS)
	@echo "Cleanup complete!"


remove: clean
	@$(rm) $(BINDIR)/$(TARGET)
	@echo "Executable removed!"

