# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nammari <nammari@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/01 15:32:48 by twagner           #+#    #+#              #
#    Updated: 2022/01/31 17:17:02 by nammari          ###   ########.fr        #
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
SRCS_DIR_BONUS = srcs_bonus/
OBJS_DIR_BONUS = objs_bonus/


PARSER_FILES = $(addprefix parser/, parser.c params_controller.c \
				init_param_struct.c map_controller.c)

PARSER_FILES_BONUS = $(addprefix parser_bonus/, parser_bonus.c \
					params_controller_bonus.c init_param_struct_bonus.c \
					map_controller_bonus.c)

PROGRAM_EXIT_FILES = $(addprefix program_exit/, exit_functions.c \
				free_resource.c)

PROGRAM_EXIT_FILES_BONUS = $(addprefix program_exit_bonus/, \
				exit_functions_bonus.c free_resource_bonus.c)

EXECUTION_FILES = $(addprefix execution/, draw_frame.c events.c \
					game_initialisation.c raycaster.c movement_and_rotation.c \
					texture.c)

EXECUTION_FILES_BONUS = $(addprefix execution_bonus/, draw_frame_bonus.c \
				events_bonus.c game_initialisation_bonus.c raycaster_bonus.c \
				movement_and_rotation_bonus.c texture_bonus.c)

TMP_TEST_FILES = $(addprefix tmp_test_functions/, tmp_test_fun.c)


SRCS_FILES = main.c $(PARSER_FILES) $(PROGRAM_EXIT_FILES) $(EXECUTION_FILES) \
				$(TMP_TEST_FILES)

SRCS_FILES_BONUS = main_bonus.c $(PARSER_FILES_BONUS) $(PROGRAM_EXIT_FILES_BONUS) \
					$(EXECUTION_FILES_BONUS) 

SRCS = $(addprefix $(SRCS_DIR), $(SRCS_FILES))

SRCS_BONUS = $(addprefix $(SRCS_DIR_BONUS), $(SRCS_FILES_BONUS))

OBJS_FILES		= $(SRCS_FILES:.c=.o)
OBJS_FILES_BONUS = $(SRCS_FILES_BONUS:.c=.o)
OBJS			= $(addprefix $(OBJS_DIR), $(OBJS_FILES))
OBJS_BONUS		= $(addprefix $(OBJS_DIR_BONUS), $(OBJS_FILES_BONUS))
OBJS_SUB_DIRS = $(addprefix objs/, parser program_exit execution tmp_test_functions)
OBJS_SUB_DIRS_BONUS = $(addprefix objs_bonus/, parser_bonus program_exit_bonus execution_bonus)

################################################################################
#                           EXECUTABLES & LIBRARIES                            #
################################################################################
NAME		= cub3D
NAME_BONUS	= cub3D_bonus
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
BONUSFLAGS	:=
DEBUG		:= false

ifeq ($(DEBUG), true)
	CFLAGS	+= -fsanitize=address -g3 -O0
endif

ifeq ($(OPTI), false)
	CFLAGS	+= -O0
endif

ifeq ($(OS), Linux)
	LMLXFLAGS	:= -L. -lmlx_Linux -L/usr/lib -lXext -lX11 -lm
else
	LMLXFLAGS	:= -lmlx -framework OpenGL -framework AppKit
endif

################################################################################
#                                    RULES                                     #
################################################################################
$(OBJS_DIR)%.o: $(SRCS_DIR)%.c $(HEADERS)
			@$(CC) -I$(HEADERS) -I$(LFTDIR) -I$(LMLXDIR) -c $(CFLAGS) $(BONUSFLAGS) -o $@ $< 

$(NAME):	$(OBJS_DIR) $(OBJS) $(LMLX) $(LFT)
			@printf  "$(BLUE)Creating $(RESET) $(YELLOW)[$(NAME)]$(RESET)" 
			@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -I$(HEADERS) -I$(LMLXDIR) $(LMLXFLAGS) $(LFTFLAGS)
			@echo " : $(GREEN)OK !$(RESET)"

all:		$(NAME) $(NAME_BONUS)

bonus:		$(NAME_BONUS)

$(OBJS_DIR_BONUS)%.o: $(SRCS_DIR_BONUS)%.c $(HEADERS)
			@$(CC) -I$(HEADERS) -I$(LFTDIR) -I$(LMLXDIR) -c $(CFLAGS) -o $@ $<


$(NAME_BONUS):	$(OBJS_DIR_BONUS) $(OBJS_BONUS) $(LMLX) $(LFT)
			@printf  "$(BLUE)Creating $(RESET) $(YELLOW)[$(NAME_BONUS)]$(RESET)" 
			@$(CC) $(CFLAGS) $(OBJS_BONUS) -o $(NAME_BONUS) -I$(HEADERS) -I$(LMLXDIR) $(LMLXFLAGS) $(LFTFLAGS)
			@echo " : $(GREEN)OK !$(RESET)"


$(OBJS_DIR):
			@printf "$(BLUE)Creating $(RESET) $(YELLOW)[$(OBJS_DIR)]$(RESET)"	
			@mkdir $(OBJS_DIR)
			@mkdir $(OBJS_SUB_DIRS)
			@echo " : $(GREEN)OK !$(RESET)"

$(OBJS_DIR_BONUS):
			@printf "$(BLUE)Creating $(RESET) $(YELLOW)[$(OBJS_DIR_BONUS)]$(RESET)"	
			@mkdir $(OBJS_DIR_BONUS)
			@mkdir $(OBJS_SUB_DIRS_BONUS)
			@echo " : $(GREEN)OK !$(RESET)"

clean:
			@printf "$(BLUE)Cleaning $(RESET) $(YELLOW)[objects & libraries]$(RESET)"
			@$(RM) $(OBJS_DIR) $(OBJS_DIR_BONUS) $(LFT) $(LMLX)
			@echo " : $(GREEN)OK !$(RESET)"

fclean:		clean
			@printf "$(BLUE)Cleaning $(RESET) $(YELLOW)[executable(s)]$(RESET)"
			@$(RM) $(NAME) $(NAME_BONUS)
			@echo " : $(GREEN)OK !$(RESET)"
			@printf "$(BLUE)Removing $(RESET) $(YELLOW)[$(OBJS_DIR)]$(RESET)"
			@$(RM) $(OBJS_DIR)
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