# Makefile for philosophers
.SILENT:

# Variables
NAME = philo

# args for testing
TEST_ARGS_1=1 800 200 200
TEST_ARGS_2=5 800 200 200
TEST_ARGS_3=5 800 200 200 7
TEST_ARGS_4=4 410 200 200
TEST_ARGS_5=4 310 200 100
TEST_ARGS_6=2 300 50 50 42	

# START - Debug options
# uncomment the line below or use valgrind like:
# valgrind --tool=helgrind ./philo PARAMS
# CFLAGS_DBG = -fsanitize=address -fsanitize-address-use-after-scope
# CFLAGS_DBG = -fsanitize=thread 
# if 1, print more infos about the program during execution
PUT_MORE_INFOS=0			
# END - Debug options

# Compiler options
CC = cc
CFLAGS = -Wall -Werror -Wextra -g -pthread -DPUT_MORE_INFOS=$(PUT_MORE_INFOS) $(CFLAGS_DBG)
RM = rm -f

# Color codes
RESET = \033[0m
RED = \033[0;31m
GREEN = \033[0;32m
ORANGE = \033[0;33m

# ->Files
SRCS = \
	check.c \
	forks.c \
	free.c \
	lib_utils.c \
	main.c \
	msg.c \
	msg_txt.c \
	philo.c \
	philo_actions.c \
	philos.c \
	table.c \
	time.c 

# Object files
OBJS = $(SRCS:.c=.o)

# TARGETS
.PHONY: all clean fclean re norm bonus

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(CFLAGS) -o $(NAME)
	echo "$(GREEN)$(NAME): created$(RESET)"

clean:
	$(RM) $(OBJS)
	echo "$(RED)$(NAME): cleaned object files$(RESET)"
	
fclean: clean
	$(RM) $(NAME)
	echo "$(RED)$(NAME): cleaned program$(RESET)"

re: fclean all

pretty: enable_pretty re

enable_pretty:
	$(eval PUT_MORE_INFOS = 1)

disable_pretty:
	$(eval PUT_MORE_INFOS = 0)

run_1: pretty
	@echo "------------------------------------------------------------"
	@echo -n "ARGUMENTS:\t$(TEST_ARGS_1)" | tr ' ' ' '
	@echo  ""
	@echo -n "RESULT:\t	He should die...\n"
	@echo "------------------------------------------------------------"
	./$(NAME) $(TEST_ARGS_1)

run_2: pretty
	@echo "------------------------------------------------------------"
	@echo -n "ARGUMENTS:\t$(TEST_ARGS_2)" | tr ' ' ' '
	@echo  ""
	@echo -n "RESULT:\t	No one dies!\n"
	@echo "------------------------------------------------------------"
	sleep 1
	./$(NAME) $(TEST_ARGS_2)

run_3: disable_pretty re
	@echo "------------------------------------------------------------"
	@echo -n "ARGUMENTS:\t$(TEST_ARGS_3)" | tr ' ' ' '
	@echo  ""
	@echo -n "RESULT:\t	No one dies and stop after 7 meals...\n"
	@echo "------------------------------------------------------------"
	./$(NAME) $(TEST_ARGS_3)

run_4: pretty
	@echo "------------------------------------------------------------"
	@echo -n "ARGUMENTS:\t$(TEST_ARGS_4)" | tr ' ' ' '
	@echo  ""
	@echo -n "RESULT:\t	No one dies!\n"
	@echo "------------------------------------------------------------"
	sleep 1
	./$(NAME) $(TEST_ARGS_4)

run_5: pretty
	@echo "------------------------------------------------------------"
	@echo -n "ARGUMENTS:\t$(TEST_ARGS_5)" | tr ' ' ' '
	@echo  ""
	@echo -n "RESULT:\t	Someone dies!\n"
	@echo "------------------------------------------------------------"
	sleep 1
	./$(NAME) $(TEST_ARGS_5)

run_6: pretty
	@echo "------------------------------------------------------------"
	@echo -n "ARGUMENTS:\t$(TEST_ARGS_6)" | tr ' ' ' '
	@echo  ""
	@echo -n "RESULT:\t	Check timesstamps...\n"
	@echo "------------------------------------------------------------"
	sleep 1
	./$(NAME) $(TEST_ARGS_6)

norm:
	norminette
