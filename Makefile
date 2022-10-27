# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hmokhtar <hmokhtar@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/18 23:34:02 by amsenhaj          #+#    #+#              #
#    Updated: 2022/10/18 15:53:00 by hmokhtar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
RM = rm -rf
CC = cc

CFLAGS = -g -Wall -Werror -Wextra

FILES = ./parsing/arg.c \
		./parsing/arg2.c \
		./parsing/check_parenthesis.c \
		./parsing/env_1.c \
		./parsing/env_2.c \
		./parsing/exe.c \
		./parsing/exit.c \
		./parsing/main.c \
		./parsing/p_cmd.c \
		./parsing/p_env.c \
		./parsing/p_env2.c \
		./parsing/p_input.c \
		./parsing/p_option.c \
		./parsing/p_output.c \
		./parsing/p_pipe.c \
		./parsing/p_quotes.c \
		./parsing/p_quotes2.c \
		./parsing/parsing.c \
		./parsing/check_others.c \
		./parsing/check_options.c \
		./parsing/valid_option.c \
		./parsing/wa7d_l3iba.c \
		./parsing/env3.c \
		./parsing/utils.c \
		./execution/cd.c \
		./execution/echo.c \
		./execution/env.c \
		./execution/execution.c \
		./execution/export.c \
		./execution/ft_split.c \
		./execution/get_command.c \
		./execution/get_command_utils.c \
		./execution/no_pipe.c \
		./execution/pwd.c \
		./execution/unset.c \
		./execution/utils.c \
		./execution/utils2.c \
		./execution/utils3.c \
		./execution/with_pipe.c \
		./execution/ft_signal.c \
		./execution/mini_utils.c \
		./execution/ft_exit.c \
		
INCLUDE = ./parsing/minishell.h
		
OBJS = $(FILES:.c=.o)

all: $(NAME)

$(NAME): $(OBJS) $(INCLUDE)
	@echo "\n"
	@echo "\033[0;32mCompiling minishell..."
	@$(CC)  $(OBJS) -o $(NAME) -L$(shell brew --prefix readline)/lib -lreadline
	@echo "\n\033[0mSalina lcompilation !"

%.o:%.c $(INCLUDE)
	@printf "\033[0;33mHadchi Kayder Khdmto, Sbeeer... %-33.33s\r" $@
	@$(CC) $(CFLAGS) -c $< -o $@ -I$(shell brew --prefix readline)/include

update:
	$(shell cd ~/goinfre && brew update)

install:
	$(shell cd ~/goinfre && brew install readline)

clean:
	@echo "\nRemoving binaries..."
	@$(RM) $(OBJS)
	@echo "\033[0m"
			
fclean:
	@echo "\033[0;31mM7INA .o..."
	@$(RM) $(OBJS)
	@echo "\nM7INA KOLCHI..."
	@$(RM) $(NAME)
	@echo "\033[0m"

re: fclean all



