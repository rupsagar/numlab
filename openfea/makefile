# binary output
BIN 			= openfea

# directories : src, inc, obj, bin, lib, res
SRCDIR 			= src src/key src/read src/element
INCDIR 			= inc
OBJDIR 			= obj
BINDIR			= bin

# file extensions
CXXEXT 			= .cpp
INCEXT			= .h
OBJEXT			= .o
DEPEXT			= .d

# compiler
CXX 			= g++

# compiler flags
OPT 			= -O0
DEPFLAGS 		= -MP -MD
CXXFLAGS 		= -Wall -Wextra -g $(foreach D, $(INCDIR), -I./$(D)) $(OPT) $(DEPFLAGS)

# recursive wildcard
# rwildcard = $(foreach d,$(wildcard $(1:=/*)),$(call rwildcard,$d,$2) $(filter $(subst *,%,$2),$d))

# files
CXXFILES 		= $(foreach D, $(SRCDIR), $(wildcard $(D)/*$(CXXEXT)))
# CXXFILES 		= $(call rwildcard,src,*.cpp)
INCFILES		= $(foreach D, $(INCDIR), $(wildcard $(D)/*$(INCEXT)))
OBJFILES 		= $(addprefix $(OBJDIR)/, $(addsuffix $(OBJEXT), $(basename $(notdir $(CXXFILES)))))
DEPFILES 		= $(patsubst %$(OBJEXT), %$(DEPEXT), $(OBJFILES))

.PHONY : all build run clean test makefile

all : build run

build : $(OBJFILES)
	$(CXX) $(CXXFLAGS) $^ -o $(BINDIR)/$(BIN)

%$(OBJEXT) : $(CXXFILES) $(INCFILES)
	$(CXX) $(CXXFLAGS) -c $(foreach D, $(SRCDIR), $(wildcard $(D)/$(notdir $*)$(CXXEXT))) -o $@

run :
	@$(BINDIR)/$(BIN)

clean :
	rm -rf $(OBJFILES) $(DEPFILES) $(BINDIR)/$(BIN) *.stackdump

test: 
	@echo $(CXXFILES)
