CC=g++
CFLAGS=-Wall -Werror -Wextra

SRC=model/*.cc

TEST_SRC=test/*.cc
TEST_EXEC=gtest
TEST_FLAGS=-lgtest -lpthread

NAME=SmartCalc


all: clean calc 


calc:
	make -C view/
	mv view/$(NAME) .


tests:
	g++ $(FLAGS) $(SRC) $(TEST_SRC) -o $(TEST_EXEC) $(TEST_FLAGS)
	./$(TEST_EXEC)


gcov_report : clean
	g++ $(FLAGS) --coverage $(SRC) $(TEST_SRC) -o $(TEST_EXEC) $(TEST_FLAGS)
	./$(TEST_EXEC)
	lcov -t "$(TEST_EXEC)" -o SmartCalc_gcov.info -c -d .
	genhtml -o report SmartCalc_gcov.info
	open report/index.html
	google-chrome report/index.html

install: uninstall
	make clean
	make
	mkdir ./build
	mv $(NAME) build

uninstall:
	rm -rf ./build

dist: all
	tar -cf $(NAME).tar $(NAME) README.md

dvi:
	open README.md


clean:
	make -C view/ clean
	rm -rf ./*.gcno ./*.gcda report $(TEST_EXEC) a.out *.info *.o
	rm -rf $(NAME)
	rm -rf $(NAME).tar
