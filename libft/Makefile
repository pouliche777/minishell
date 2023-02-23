# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bperron <bperron@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/01 12:36:53 by slord             #+#    #+#              #
#    Updated: 2023/02/23 13:42:15 by bperron          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SOURCES	=		ft_isalnum.c ft_isprint.c ft_memcmp.c ft_strlcat.c \
				ft_strncmp.c ft_atoi.c ft_isalpha.c ft_memcpy.c ft_strchr.c \
				ft_strlcpy.c ft_strnstr.c ft_tolower.c ft_bzero.c ft_isascii.c \
				ft_memmove.c ft_strdup.c ft_strlen.c ft_strrchr.c \
				ft_toupper.c ft_calloc.c  ft_isdigit.c ft_memchr.c  \
				ft_memset.c ft_substr.c ft_strjoin.c ft_itoa.c ft_strtrim.c \
				ft_striteri.c ft_strmapi.c ft_putchar_fd.c ft_putstr_fd.c \
				ft_putendl_fd.c ft_putnbr_fd.c ft_split.c get_next_line.c get_next_line_utils.c \
				ft_strlen_until.c free_pp.c ft_strcmp.c

SOURCESBONUS =	ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c \
				ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c
				   		
OBJS		= $(SOURCES:.c=.o)

BOBJS		= $(SOURCESBONUS:.c=.o)
	
CC			= gcc
RM			= rm -f
CFLAGS		= -Wall -Wextra -Werror

NAME		= libft.a


$(NAME):	$(OBJS)
					ar rcs $(NAME) $(OBJS)

bonus:			$(OBJS) $(BOBJS)
					ar rcs $(NAME) $(OBJS) $(BOBJS)

all : 		$(NAME)

clean:
					$(RM) $(OBJS) $(BOBJS)

fclean:		clean
					$(RM) $(NAME)
re:			fclean 	$(NAME)

