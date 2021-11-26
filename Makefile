NAME	=	libftprintf.a

SRCS	=	ft_printf.c	ft_printf_utils.c

OBJS	=	$(SRCS:.c=.o)

OBJDIR	:=	./.objs

FLAGS	:=	-Wall -Werror -Wextra

%.o	:		%.c
			gcc $(FLAGS) -c $<	-o $@

all	:		$(NAME)

$(NAME): 	$(OBJS)
			ar rcs $(NAME) $?

bonus	: 	$(NAME) $(BONUSES:.c=.o)
			ar rcs $(NAME) $?

re	:		fclean all

so:
	clang -nostartfiles -fPIC $(FLAGS) $(SRCS)
	clang -nostartfiles -shared -o libft.so $(OBJS)

clean:
			rm -rf $(OBJS) $(BONUSES:.c=.o)

fclean:		clean
			rm -rf $(NAME)

.PHONY	:	all clean fclean re bonus
