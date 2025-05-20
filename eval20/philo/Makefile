HEADER = philosopher.h

OBJDIR = obj_files

CDIR = src/

C_PARSING_DIR = src/parsing/

SRC =	$(CDIR)philosopher.c 						\
		$(CDIR)philo_utils.c						\
		$(CDIR)ending_management.c					\
		$(CDIR)free_init.c							\
		$(CDIR)ascii_to.c							

PARSING_SRC = $(C_PARSING_DIR)parsing.c			\
			  $(C_PARSING_DIR)parsing_utils.c	\

NAME =  philo

CFLAGS = -Wall -Werror -Wextra -g

RM = rm -rf 

OBJ = $(addprefix $(OBJDIR)/,$(SRC:$(CDIR)%.c=%.o)) 

OBJ_PARSING = $(addprefix $(OBJDIR)/,$(PARSING_SRC:$(C_PARSING_DIR)%.c=%.o)) 

CC = cc

all : $(NAME) 

$(NAME) :	$(OBJ_FUNC) $(OBJ) $(OBJ_PARSING)
			@$(CC) $(CFLAGS) $(OBJ) $(OBJ_PARSING) -o $(NAME)
			@echo  "\e[1;4mPhilosopher Compiled ✅"

$(OBJDIR)/%.o: $(CDIR)%.c
	@mkdir -p $(OBJDIR)
	@$(CC) $(CFLAGS) -I$(HEADER) -c $< -o $@

$(OBJDIR)/%.o: $(C_PARSING_DIR)%.c
	@mkdir -p $(OBJDIR)
	@$(CC) $(CFLAGS) -I$(HEADER) -c $< -o $@

clean : 
	@$(RM) $(OBJ) $(OBJDIR)

fclean :	clean		
			@$(RM) $(NAME)

re : fclean all

.PHONY : clean fclean all re
