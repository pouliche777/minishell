S = src/
O = obj/
L = libft/

SOURCES = $Ssplit_args.c $Sredir.c $Sspaces.c $Schange_var.c $Schange_var_utils.c $Sminishell.c $Sutils.c $Sparsing.c $Slexer.c $Spipes.c $Sbuilt_in_utils.c $Sbuilt_in.c $Sredirection.c $Ssignals.c $Svariables.c $Squotes.c $Senv.c $Senv_1.c 

OBJS = $(SOURCES:$S%=$O%.o)

LIB = libft/libft.a
CC = gcc
RM = rm -rf
CFLAGS = -Wall -Wextra -Werror -g 

NAME = minishell

all: $(NAME)

$O:
	@mkdir $@

$(OBJS): | $O

$(OBJS): $O%.o: $S%
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	@make -C $(L) 
	@$(CC) $(CFLAGS) -lreadline $(LIB) $^ -o $@
	@echo "\033[0;32m Compilation complétée"

clean: 
		@$(RM) $(OBJS)
		@$(RM) $O
		@echo "\033[0;31m Fichiers .o suprimmes"

fclean:	clean

	@$(RM) $(NAME)
	@echo "\033[0;31m executable suprime"


re:	fclean $(NAME)