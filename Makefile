CC = clang
CFLAGS = -Wall -Wextra -Werror -I.
NAME = my_ls
SRC_CORE = my_ls.c \
      lib/addnode.c \
      lib/infotostruct.c \
      lib/executeflags.c \
      lib/printstats.c \
      lib/printpermissions.c \
      lib/my_putchar.c \
      lib/printime.c \
	  lib/sort_files_time.c
SRC = main.c $(SRC_CORE)
OBJ = $(SRC:.c=.o)
SRC_TESTS = tests/test.c $(SRC_CORE)

all : $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

lib/%.o : lib/%.c lib.h
	$(CC) $(CFLAGS) -c $< -o $@

%.o : %.c lib.h
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: tests
tests:
	gcc $(CFLAGS) -o unit_tests $(SRC_TESTS) -lcriterion --coverage
	./unit_tests

clean :
	rm -f $(OBJ)

fclean : clean
	rm -f $(NAME) unit_tests *.gcno *.gcda *.o

re : fclean all

.PHONY : all clean fclean re