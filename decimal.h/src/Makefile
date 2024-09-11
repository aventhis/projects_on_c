CC=gcc
FLAGS=-std=c11 -g -Wall -Werror -Wextra
GLFLAGS=--coverage
FILENAME = s21_decimal
LIBNAME = $(FILENAME).a

SOURCE = $(wildcard ./qtests/unit_tests/s21_*.c) 
SOURCETESTH = $(wildcard ./qtests/unit_tests/s21_*.h) 

S21__C=s21_*.c
S21__H=s21_*.h
S21__O=s21_*.o
TESTS=test
SYSTEM := $(shell uname -s)

ifeq ($(SYSTEM), Linux)
    # Код для компиляции под Linux
	OPEN_CMD = xdg-open
    ADD_LIB =  -lcheck -lm -lsubunit
else ifeq ($(SYSTEM), Darwin)
    # Код для компиляции под macOS
	OPEN_CMD = open
	ADD_LIB =  -lcheck 
	BREW := ${HOME}/homebrew
else
    $(error Unsupported system: $(SYSTEM))
endif

PATH := $(BREW)/bin:$(PATH)

all: $(LIBNAME) 

$(LIBNAME): 
		$(CC) $(FLAGS) -c ./*/$(S21__C)    
		ar rcs $(LIBNAME) $(S21__O)
		ranlib $(LIBNAME)

s21_covered:
		$(CC) $(FLAGS) -c ./*/$(S21__C) ${SOURCE} $(GLFLAGS)
		ar rc $(LIBNAME) $(S21__O)
		ranlib $(LIBNAME)

test: clean $(LIBNAME)
	$(CC) ${SOURCE} -c $(FLAGS) $(GLFLAGS)
	$(CC) s21_*.o $(LIBNAME) -o $(TESTS) ${ADD_LIB} $(FLAGS) $(GLFLAGS)
	./$(TESTS)

tests: clean $(LIBNAME)
	$(CC) $(FLAGS) -c ./comparsion/$(S21__C) ./helpers/$(S21__C) ./others/$(S21__C) ./qtests/test.c 
	$(CC) test.o $(LIBNAME) -o test $(FLAGS)
	./test

testc: clean s21_covered
	$(CC) ${SOURCE} -c $(FLAGS) $(GLFLAGS)
	$(CC) s21_*.o $(LIBNAME) -o $(TESTS) ${ADD_LIB} $(FLAGS) $(GLFLAGS)
	./$(TESTS)

install:
	if [ $(SYSTEM) = "Linux" ]; then \
		sudo apt-get install -y lcov; \
		sudo apt-get install -y check; \
		sudo apt-get install -y libcapture-tiny-perl; \
		sudo apt-get install -y libdatetime-perl; \
	else \
		brew install lcov; \
	fi

gcov_report: testc
	./$(TESTS)
	lcov -t "$(FILENAME)" -o $(FILENAME).info -c -d . --no-external 
	genhtml -o report $(FILENAME).info  
	open report/index.html

gcov_report2: testc
	# $(CC) $(FLAGS) -o $(FILENAME) ./*/$(S21__C) ${SOURCE} $(GLFLAGS) ${ADD_LIB}
	# ./$(FILENAME)
	lcov -t "$(FILENAME)" -o $(FILENAME).info -c -d . --no-external
	genhtml -o report $(FILENAME).info 
	open report/index.html

## # Запуск с без lcov
# gcov_report2: testс
#     ./$(TESTS)#lcov -t "$(FILENAME)" -o $(FILENAME).info -c -d .
#     geninfo . -b . -o $(FILENAME).info --no-external    
# 	genhtml -o report $(FILENAME).info
#     open report/index.html

test_sega: clean $(LIBNAME) 
	$(CC) $(FLAGS)  $(SOURCE) -L. $(LIBNAME) -o $(TESTS) $(ADD_LIB) -fsanitize=address -g
	./$(TESTS)

leaks: test
	leaks --atExit -- ./$(TESTS)

check:
		clang-format -style=google -i */*.c *.h ${SOURCE} ${SOURCETESTH}
		cppcheck enable=all missningIncludeSystem ${SOURCE}
		cppcheck enable=all missningIncludeSystem ./*/$(S21__C)

pcheck:
		clang-format -style=google -n */*.c *.h ${SOURCE} ${SOURCETESTH}
		cppcheck enable=all missningIncludeSystem ${SOURCE}
		cppcheck enable=all missningIncludeSystem ./*/$(S21__C)		
		
clean:
		rm -rf *.gcno *.html report
		rm -rf *.gcov 
		rm -rf *.gcda
		rm -rf $(TESTS) *.a
		rm -rf *.info
		rm -rf *.o
		rm -rf *.out
		rm -rf *.dSYM

aclean:
		rm -rf *.gcno *.html report
		rm -rf *.gcov 
		rm -rf *.gcda
		rm -rf $(TESTS)
		rm -rf *.info
		rm -rf *.o
		rm -rf *.out
		rm -rf test.dSYM

rebuild: clean all
