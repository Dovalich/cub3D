# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nammari <nammari@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/01 15:32:48 by twagner           #+#    #+#              #
#    Updated: 2022/01/25 09:29:24 by nammari          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

################################################################################
#                               PARAMS & COLORS                                #
################################################################################
OS			=  $(shell uname -s)

ifneq (,$(findstring xterm,${TERM}))
	GREEN        := $(shell tput -Txterm setaf 2)
	YELLOW       := $(shell tput -Txterm setaf 3)
	BLUE         := $(shell tput -Txterm setaf 6)
	RESET		 := $(shell tput -Txterm sgr0)
else
	GREEN        := ""
	YELLOW       := ""
	BLUE         := ""
	RESET        := ""
endif

################################################################################
#                                 COMMANDS                                     #
################################################################################
RM			= rm -rf
CC			= gcc
AR			= ar rcs

################################################################################
#                                 SOURCES                                      #
################################################################################

SRCS_DIR = srcs/
OBJS_DIR = objs/

PARSER_FILES = $(addprefix parser/, parser.c params_controller.c \
				init_param_struct.c map_controller.c)

ERROR_FILES = $(addprefix error_handling/, error_messages.c)

RESSOURCE_FREE_FILES = $(addprefix resource_free/, free_resource.c)

SRCS_FILES = main.c $(PARSER_FILES) $(ERROR_FILES) $(RESSOURCE_FREE_FILES)

SRCS = $(addprefix $(SRCS_DIR), $(SRCS_FILES))

OBJS_FILES		= $(SRCS_FILES:.c=.o)
OBJS			= $(addprefix $(OBJS_DIR), $(OBJS_FILES))
OBJS_SUB_DIRS = $(addprefix objs/, parser error_handling resource_free)
################################################################################
#                           EXECUTABLES & LIBRARIES                            #
################################################################################
NAME		= cub3D
LFT			= libft.a

ifeq ($(OS), Linux)
	LMLX	= libmlx_Linux.a
else
	LMLX	= 
endif

################################################################################
#                                 DIRECTORIES                                  #
################################################################################
HEADERS		= includes/ 
LFTDIR		= libft/
LMLXDIR		= minilibx-linux/

################################################################################
#                                     FLAGS                                    #
################################################################################
CFLAGS		:= -Wall -Wextra -Werror
LFTFLAGS	:= -L. -lft
DEBUG		:= true

ifeq ($(DEBUG), true)
	CFLAGS	+= -fsanitize=address -g3 -O0
endif

ifeq ($(OPTI), false)
	CFLAGS	+= -O0
endif

ifeq ($(OS), Linux)
	LMLXFLAGS	:= -L. -lmlx_Linux -L/usr/lib -lXext -lX11 -lm
else
	LMLXFLAGS	:= -framework OpenGL -framework AppKit
endif

#LMLXFLAGS	:= -lmlx -framework OpenGL -framework AppKit
################################################################################
#                                    RULES                                     #
################################################################################


$(OBJS_DIR)%.o: $(SRCS_DIR)%.c $(HEADERS)
			@$(CC) -I$(HEADERS) -I$(LFTDIR) -I$(LMLXDIR) -c $(CFLAGS) -o $@ $< 

$(NAME):	$(OBJS) $(LMLX) $(LFT)
			@printf  "$(BLUE)Creating $(RESET) $(YELLOW)[$(NAME)]$(RESET)" 
			@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -I$(HEADERS) -I$(LMLXDIR) $(LMLXFLAGS) $(LFTFLAGS)
			@echo " : $(GREEN)OK !$(RESET)"

all:		$(NAME)

OBJ_MK:		
			mkdir $(OBJS_DIR)
			mkdir $(OBJS_SUB_DIRS)

clean:
			@printf "$(BLUE)Cleaning $(RESET) $(YELLOW)[objects & libraries]$(RESET)"
			@$(RM) $(OBJS) $(LFT) $(LMLX)
			@echo " : $(GREEN)OK !$(RESET)"

fclean:		clean
			@printf "$(BLUE)Cleaning $(RESET) $(YELLOW)[executable(s)]$(RESET)"
			@$(RM) $(NAME)
			@echo " : $(GREEN)OK !$(RESET)"

re:			fclean all

$(LFT):	
			@printf "$(BLUE)Compiling$(RESET) $(YELLOW)[$(LFT)]$(RESET)"
			@make -s -C $(LFTDIR)
			@make clean -s -C $(LFTDIR)
			@mv $(LFTDIR)$(LFT) .
			@echo " : $(GREEN)OK !$(RESET)"

$(LMLX):		
			@printf "$(BLUE)Compiling$(RESET) $(YELLOW)[$(LMLX)]$(RESET)"
			@make -s -C $(LMLXDIR)
			@mv $(LMLXDIR)$(LMLX) .
			@make clean -s -C $(LMLXDIR)
			@echo " : $(GREEN)OK !$(RESET)"

.PHONY:		all clean fclean c.o re