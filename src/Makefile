BD=../build/
CC=gcc -std=c11
CFLAGS=-Wall -Wextra -Werror -lm
GCOV_LIBS=--coverage
SOURCES=s21_3dv.c
H=s21_3dv.h
LIBO=s21_3dv.o
LIBA=s21_3dv.a
EXE=test.out
HTML=lcov -t "test" -o rep.info -c -d .

OS = $(shell uname)

ifeq ($(OS), Darwin)
	TST_LIBS=-lcheck -lm -g
else
	TST_LIBS=-lcheck -pthread -lrt -lm -D_GNU_SOURCE -lsubunit -lpthread -g
endif

all: install

build: $(BD)QT_OpenGL.pro
	cd $(BD)/QT_OpenGL; qmake QT_OpenGL.pro
	make -C $(BD)/QT_OpenGL

./$(BD)QT_OpenGL.pro:
	mkdir $(BD)
	cp *.* $(BD)
	cp -R QT_OpenGL $(BD)
	cp -R QtGifImage $(BD)

install: clean build
	mkdir ../application
ifeq ($(OS), Darwin)
	cd $(BD)/QT_OpenGL; mv QT_OpenGL.app ../../application
else
	cd $(BD)/QT_OpenGL; mv QT_OpenGL ../../application
endif
	make clean

dist:
	rm -rf ../3DViewer_v1.0/
	mkdir ../3DViewer_v1.0/
	mkdir ../3DViewer_v1.0/src
	cp Makefile *.* ../3DViewer_v1.0/src/
	cd ..; tar cvzf 3DViewer_v1.0.tgz 3DViewer_v1.0/
	# mv 3DViewer_v1.0.tgz $(HOME)/Desktop/
	rm -rf ../3DViewer_v1.0/

test: s21_3dv.a
	$(CC) $(CFLAGS) s21_3dv.c tests.c -L. --coverage $(LIBA) $(TST_LIBS) -o $(BUILD_PATH)$(EXE)
	./test.out

s21_3dv.a: clean
	$(CC) $(CFLAGS) -c $(SOURCES) -o $(BUILD_PATH)$(LIBO)
	ar rcs $(LIBA) $(LIBO)
	ranlib $(LIBA)

gcov_report: clean test
	$(HTML)
	genhtml -o report rep.info
	open report/index.html

check:
	cppcheck --enable=all --suppress=missingIncludeSystem --inconclusive --check-config *.c
	cd ../materials/linters/; cp .clang-format ../../src
	cd QT_OpenGL; clang-format -i *.cpp
	cd QT_OpenGL; clang-format -i *.h
	clang-format -i *.c
	clang-format -i *.h
	cd QT_OpenGL; clang-format -n *.cpp
	cd QT_OpenGL; clang-format -n *.h
	clang-format -n *.c
	clang-format -n *.h
	rm -rf clang-format
	make test
ifeq ($(OS), Darwin)
	leaks --atExit -- test
else
	CK_FORK=no valgrind -s --leak-check=full --log-file=RESULT_VALGRIND.txt ./test.out
endif

dvi:
	texi2pdf info.tex
	texi2dvi info.tex
	
clean: 
	@rm -rf *.a && rm -rf *.o *.out *.out.dSYM
	@rm -rf *.info && rm -rf *.gcda && rm -rf *.gcno &&  rm -rf *.gcov
	@rm -rf report/ && rm -rf *.
	@rm -rf ../build*
	@rm -rf 3DViewer_v1.0*
	@rm -rf ../3DViewer_v1.0.tgz
	@rm -rf info.aux info.dvi info.log info.pdf
	
uninstall:
	@rm -R ../application

