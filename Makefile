# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aperrein <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/06 12:51:34 by aperrein          #+#    #+#              #
#    Updated: 2023/03/16 13:29:56 by aperrein         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAMEC	=	client

NAME	=	server

OBJ_DIR =	OBJ/

SRCS	=	server.c

SRCC	=	client.c

OBJS	=	$(SRCS:.c=.o)

OBJC	=	$(SRCC:.c=.o)

OBJ	=	$(addprefix $(OBJ_DIR), $(OBJS)) $(addprefix $(OBJ_DIR), $(OBJC))

RM	=	rm -f

CFLAGS	=	-Wall -Werror -Wextra

all     :       $(OBJ_DIR) $(NAME)
	
$(OBJ_DIR)%.o:	%.c
		gcc $(CFLAGS) -c $< -o $@

$(OBJ_DIR) :
		mkdir $(OBJ_DIR)


$(NAME)	:	make_lib $(OBJ)
		gcc $(CFLAGS) -o $(NAME) $(OBJ_DIR)$(OBJS) libft/libft.a
		gcc $(CFLAGS) -o $(NAMEC) $(OBJ_DIR)$(OBJC) libft/libft.a

make_lib :
		@make -s -C libft/

clean	:
		$(RM) $(OBJ)

fclean	:	clean
		$(RM) $(NAME) $(NAMEC)

re 	:	fclean $(NAME)
