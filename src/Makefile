#This Makefile is specialised to build School 21 static library projects
LIB = s21_matrix.a
TEST_LIB = $(addprefix test_, $(LIB))
CC = gcc
#For M1-M3 macs, force GCC compiler
ifeq ($(shell uname -p), arm)
		CC = gcc-13
		GCOV = gcov-13
endif
GCOV = gcov
DOC_DIR = doc
FLAGS = -Wall -Werror -Wextra -std=c11
OPTFLAGS = -g -pedantic
GFLAGS = -fprofile-arcs -ftest-coverage
IN_FLAGS = $(shell pkg-config --cflags check)
CHFLAGS = $(shell pkg-config --cflags --libs check)
EXTRAFLAGS= -lm
GOFLAGS = -lgcov
TEST_DIR = tests
BUILD_DIR = build
BUILD_TEST_DIR = build_tests
TEST_BUILD_DIR = test_build
GCOV_DIR = gcov_report
S21_SOURCES = $(wildcard s21_*.c)
TESTS = unittests.c
S21_OBJECTS=$(addprefix $(BUILD_DIR)/, $(S21_SOURCES:.c=.o))
TEST_S21_OBJECTS=$(addprefix $(TEST_BUILD_DIR)/, $(S21_SOURCES:.c=.o))
TEST_OBJECTS=$(addprefix $(BUILD_TEST_DIR)/, $(notdir $(TESTS:.c=.o)))
OPENOS = vi
ifeq ($(shell uname -s), Linux)
		OPENOS = xdg-open
endif
ifeq ($(shell uname -s), Darwin)
		OPENOS = open
endif


all : $(LIB) test 

run : test
	./test


#  ////////////////////  BUILD TEST  //////////////////////
test: unittests_nofork $(TEST_OBJECTS) $(TEST_LIB)
	$(CC) $(FLAGS) $(OPTFLAGS) $(TEST_OBJECTS) -o $@ $(CHFLAGS) $(EXTRAFLAGS) $(TEST_LIB) $(GOFLAGS)

$(TEST_OBJECTS) : $(BUILD_TEST_DIR)/%.o : $(TEST_DIR)/%.c
	@mkdir -p $(BUILD_TEST_DIR)
	$(CC) $(FLAGS) $(IN_FLAGS) -c $< -o $@

$(TEST_LIB): $(TEST_S21_OBJECTS)
	ar -rcs $@ $^

$(TEST_S21_OBJECTS): $(TEST_BUILD_DIR)/%.o : %.c $(LIB:.a=.h)
	@mkdir -p $(TEST_BUILD_DIR)
	$(CC) $(FLAGS) $(OPTFLAGS) $(GFLAGS) -c $< -o $@


#  ////////////////////  BUILD LIB  //////////////////////
$(LIB): $(S21_OBJECTS)
	ar -rcs $@ $^

$(S21_OBJECTS): $(BUILD_DIR)/%.o : %.c $(LIB:.a=.h)
	@mkdir -p $(BUILD_DIR)
	$(CC) $(FLAGS) -c $< -o $@


#  /////////////////////  REMOVAL  //////////////////////
clean:
	@echo ==Cleaning...==
	@rm -rf $(GCOV_DIR) $(BUILD_DIR) $(BUILD_TEST_DIR) $(TEST_BUILD_DIR) $(DOC_DIR)/html $(DOC_DIR)/latex
	@rm -rf unit_tests/_unittests.check
	@rm -rf *.html
	@rm -rf a.out test
	@rm -rf *.a
	@rm -rf *.css
	@rm -rf *.gch $(TEST_DIR)/*.gch
	@rm -rf ./external/external
	@echo ==EVERYTHING REMOVED!==
	@echo ==Done!==

rebuild: 
	$(MAKE) clean
	$(MAKE) all


#  ///////////////////  DEPENDENCIES  ////////////////////
installdeps:
ifeq ($(shell uname -s), Linux)
		sudo apt-get install pkg-config graphviz check checkmk gcovr -y
endif
ifeq ($(shell uname -s), Darwin)
		brew install pkg-config graphviz check checkmk gcovr
endif


#  /////////////////////  EXTRAS  //////////////////////
.PHONY: all clean rebuild run installdeps 


#  /////////////////////  INCLUDES  //////////////////////
include makefiles/assemble_tests.mk
include makefiles/gcov_lib.mk
include makefiles/linters.mk
include makefiles/valgrind.mk