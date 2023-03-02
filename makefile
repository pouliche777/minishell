# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: slord <slord@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/22 14:33:49 by bperron           #+#    #+#              #
#    Updated: 2023/03/02 12:33:10 by slord            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#valgrind --show-leak-kinds=all --trace-children=yes --track-fds=yes --leak-check=full --track-origins=yes --suppressions=supp.txt ./minishell

S = src/
O = obj/
L = libft/

SOURCES = $Sredir_utils.c $Sexecute_utils.c $Sexecute.c $Sexit.c $Sheredoc.c $Sutils2.c $Secho.c $Ssplit_args.c $Sredir.c $Sspaces.c $Schange_var.c $Schange_var_utils.c $Sminishell.c $Sutils.c $Sparsing.c $Slexer.c $Spipes.c $Sbuilt_in_utils.c $Sbuilt_in.c $Sredirection.c $Ssignals.c $Svariables.c $Squotes.c $Senv.c $Senv_1.c $Sheredoc_utils.c

OBJS = $(SOURCES:$S%=$O%.o)

LIB = libft/libft.a
CC = gcc
RM = rm -rf
CFLAGS = -Wall -Wextra -Werror -g
RL = -L./readline -lreadline

NAME = minishell

all: $(NAME)

$O:
	@mkdir $@

$(OBJS): | $O

$(OBJS): $O%.o: $S%
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	@make -sC $(L) 
	@$(CC) $(CFLAGS) $(RL) $(LIB) -lcurses $^ -o $@
	@echo "\033[0;32m Compilation complétée"

clean: 
	@make -sC $(L) clean
	@$(RM) $(OBJS)
	@$(RM) $O
	@echo "\033[0;31m Fichiers .o suprimmes"

fclean:	clean
	@make -sC $(L) fclean
	@$(RM) $(NAME)
	@echo "\033[0;31m executable suprime"


re:	fclean $(NAME)