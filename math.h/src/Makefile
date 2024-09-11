CC=gcc
FLAGS=-std=c11 -g -Wall -Werror -Wextra
GLFLAGS=--coverage
LIBNAME = s21_math.a

SOURCE = $(wildcard ./qtests/test_*.c) 

S21_MATH_C=s21_*.c
S21_MATH_H=s21_*.h
S21_MATH_O=s21_*.o
TESTS=test
SYSTEM := $(shell uname -s)

ifeq ($(SYSTEM), Linux)
    # Код для компиляции под Linux
	OPEN_CMD = xdg-open
    ADD_LIB =  -lcheck -lm -lsubunit
else ifeq ($(SYSTEM), Darwin)
    # Код для компиляции под macOS
	OPEN_CMD = open
    ADD_LIB = -lcheck
	BREW := ${HOME}/homebrew
else
    $(error Unsupported system: $(SYSTEM))
endif

PATH := $(BREW)/bin:$(PATH)

all: $(LIBNAME) 

$(LIBNAME): 
		$(CC) $(FLAGS) -c $(S21_MATH_C)        
		ar rcs $(LIBNAME) $(S21_MATH_O)
		ranlib $(LIBNAME)

s21_covered:
		 $(CC) $(FLAGS) -c $(S21_MATH_C) ${SOURCE} $(GLFLAGS)  ${ADD_LIB}
		ar rc $(LIBNAME) $(S21_MATH_O)
		ranlib $(LIBNAME)

test: clean $(LIBNAME)
	$(CC) ${SOURCE} -c $(FLAGS) $(GLFLAGS) 
	$(CC) $(TESTS)*.o $(LIBNAME) -o $(TESTS) ${ADD_LIB} $(FLAGS) $(GLFLAGS) 

install:
	if [ $(OS) = "LINUX" ]; then \
		sudo apt-get install -y lcov; \
		sudo apt-get install -y check; \
		sudo apt-get install -y libcapture-tiny-perl; \
		sudo apt-get install -y libdatetime-perl; \
	else \
		brew install lcov; \
	fi

gcov_report: test
	./$(TESTS)
	lcov -t "s21_math" -o s21_math.info -c -d .
	genhtml -o report s21_math.info
	open report/index.html


check:
		clang-format -style=google -i *.c *.h
		clang-format -style=google -i ${SOURCE} ./qtests/test_*.h 
		cppcheck enable=all missningIncludeSystem ${SOURCE}
		
clean:
		rm -rf *.gcno *.html report
		rm -rf *.gcov 
		rm -rf *.gcda
		rm -rf $(TESTS) *.a
		rm -rf *.info
		rm -rf *.o
		rm -rf *.out

aclean:
		rm -rf *.gcno *.html report
		rm -rf *.gcov 
		rm -rf *.gcda
		rm -rf $(TESTS)
		rm -rf *.info
		rm -rf *.o
		rm -rf *.out

rebuild: clean all
