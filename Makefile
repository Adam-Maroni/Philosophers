#--------------------MANDATORY--------------------
NAME = philo
CC = gcc
FLAGS = -Wall -Werror -Wextra -g
INC = inc/
SRC_PATH = src
LIBRARIES = -pthread
SRC = $(addprefix $(SRC_PATH)/, \
	src/check_args.c \
	src/libft_utils2.c \
	src/libft_utils.c \
	src/philo_list.c \
	src/timestamp.c \
	src/philosophers_handler.c \
	src/meals_handler.c \
	src/death_handler.c \
	src/message.c \
	src/main.c \
      )
OBJ_PATH = obj
OBJ = $(addprefix $(OBJ_PATH)/, $(notdir $(SRC:.c=.o)))

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(addprefix -I, $(INC))  $(LIBRARIES) $(OBJ)  -o $(NAME)
	
$(OBJ_PATH)/%.o : $(SRC_PATH)/%.c
	$(CC) $(FLAGS) $(addprefix -I, $(INC)) $(LIBRARIES) -c $< -o $@ 

clean: 
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all
#-----------------------------------------------



#--------------------TESTING--------------------
COVERAGE_PATH = ./tests/coverage
COVERAGE_OUTPUT = $(COVERAGE_PATH)/coverage.html
ARGS = $(NB_PHILOSOPHER) $(TIME_TO_DIE) $(TIME_TO_EAT) $(TIME_TO_SLEEP)

NB_PHILOSOPHER = "4"
TIME_TO_DIE = "4000" 
TIME_TO_SLEEP = "200"
TIME_TO_EAT = "400"
NB_OF_TIME_EACH_PHILO_MUST_EAT = "5"

debug: $(NAME)
	gdb -x tests/gdbscripts/1.gdb --args ./$(NAME) $(ARGS)

mem_check: 
	$(CC) -fsanitize=thread -D TSAN_OPTIONS=second_deadlock_stack=1 -g $(addprefix -I, $(INC))  $(LIBRARIES) $(OBJ)  -o $(NAME)
	#":valgrind -q --tool=helgrind ./$(NAME) $(ARGS)
	./$(NAME) $(ARGS)

simple_test: $(NAME)
	-./$(NAME) $(ARGS)

code_coverage:
	@make -s FLAGS+="-fprofile-arcs -ftest-coverage" re
	@./$(NAME) $(ARGS)
	@mv -f $(addsuffix .gcno, $(basename $(OBJ))) $(COVERAGE_PATH)
	@mv -f $(addsuffix .gcda, $(basename $(OBJ))) $(COVERAGE_PATH)
	@rm -f $(COVERAGE_OUTPUT)
	@gcovr --html --html-details --output=$(COVERAGE_OUTPUT)
	@firefox $(COVERAGE_OUTPUT)
#-----------------------------------------------


#--------------------DOCUMENTATION--------------
DOC_HTML = doc/index.html
DOXYFILE = Doxyfile
WEB_BROWSER = firefox

doc: FORCE
	doxygen $(DOXYFILE)
	$(WEB_BROWSER) $(DOC_HTML)
FORCE:
#-----------------------------------------------

