SRCS		= ft_memset.c \
			  ft_bzero.c \
			  ft_memcpy.c \
			  ft_memccpy.c \
			  ft_memmove.c \
			  ft_memchr.c \
			  ft_memcmp.c \
			  ft_strlen.c \
			  ft_isalpha.c \
			  ft_isdigit.c \
			  ft_isalnum.c \
			  ft_isascii.c \
			  ft_isprint.c \
			  ft_toupper.c \
			  ft_tolower.c \
			  ft_strchr.c \
			  ft_strrchr.c \
			  ft_strncmp.c \
			  ft_strcmp.c \
			  ft_strlcpy.c \
			  ft_strlcat.c \
			  ft_strnstr.c \
			  ft_atoi.c \
			  ft_calloc.c \
			  ft_strdup.c \
			  ft_substr.c \
			  ft_strjoin.c \
			  ft_strtrim.c \
			  ft_split.c \
			  ft_itoa.c \
			  ft_strmapi.c \
			  ft_putchar_fd.c \
			  ft_putstr_fd.c \
			  ft_putendl_fd.c \
			  ft_putnbr_fd.c \
			  ft_get_next_line.c \
			  ft_realloc.c \
			  ft_strcpy.c \
			  ft_lstnew.c \
			  ft_lstadd_front.c \
			  ft_lstsize.c \
			  ft_lstlast.c \
			  ft_lstadd_back.c \
			  ft_lstdelone.c \
			  ft_lstclear.c \
			  ft_lstiter.c \
			  ft_lstmap.c \
			  ft_strchr_index.c\
			  ft_get_trimed_right.c\
			  ft_is_space.c

BSRCS		= ft_lstnew.c \
			  ft_lstadd_front.c \
			  ft_lstsize.c \
			  ft_lstlast.c \
			  ft_lstadd_back.c \
			  ft_lstdelone.c \
			  ft_lstclear.c \
			  ft_lstiter.c \
			  ft_lstmap.c

OBJS		= $(SRCS:.c=.o)

BOBJS		= $(BSRCS:.c=.o)

NAME		= libft.a

HEADERS		= .

CFLAGS		= -Wall -Wextra -Werror

RM			= rm -f

CC			= gcc

AR			= ar rcs

.c.o:
			$(CC) $(CFLAGS) -c $< -o $(<:.c=.o) -I$(HEADERS)

$(NAME):	$(OBJS)
			$(AR) $(NAME) $(OBJS)

all:		$(NAME)

bonus:		$(NAME) $(BOBJS)
			@touch bonus
			$(AR) $(NAME) $(BOBJS)

clean:
			$(RM) $(OBJS) $(BOBJS) bonus

fclean:		clean
			$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean c.o re
