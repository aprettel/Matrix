CXX   = g++ 
OS:= $(shell uname -s)
CXXFLAGS  = -std=c++17 -Wall -Werror -Wextra
TEST_LIBS  = -lstdc++ -lm -lgtest -pthread 
SOURCES  = $(wildcard *.cc)
OBJECTS  = $(patsubst %.cc, %.o, $(SOURCES))
EXECUTABLE  = test
LIB   = s21_matrix_oop.a

all: test

s21_matrix_oop.a : $(OBJECTS)
	ar -rcs $(LIB) $(OBJECTS)
	ranlib $(LIB)

test: $(LIB)
ifeq ($(OS), Darwin)
	$(CXX) $(CXXFLAGS) *.cc $(LIB) -o $(EXECUTABLE) $(TEST_LIBS)
else
	$(CXX) $(CXXFLAGS) *.cc -o $(EXECUTABLE) $(TEST_LIBS) 
endif
	./$(EXECUTABLE)

gcov_report: clean
	$(CXX) --coverage  *.cc -o $(EXECUTABLE) $(TEST_LIBS)
	./$(EXECUTABLE)
	lcov -o coverage.info -c -d . --ignore-errors mismatch 
	genhtml coverage.info --output-directory report
	open ./report/index.html
	rm -rf *.gcno *.gcda *.gcov

style: 
	clang-format -style=Google -n *.cc *.h 

leaks: test
ifeq ($(OS), Darwin)
	CK_FORK=no leaks --atExit -- ./$(EXECUTABLE)
else
	CK_FORK=no valgrind --trace-children=yes --track-origins=yes --leak-check=full --show-leak-kinds=all -s ./$(EXECUTABLE)
endif

clean:
	rm -rf *.a *.o *.o $(EXECUTABLE) *.a* *.gcno *.gcda *.gcov *.info report