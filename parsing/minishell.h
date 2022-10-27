/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmokhtar <hmokhtar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 13:29:29 by amsenhaj          #+#    #+#             */
/*   Updated: 2022/10/27 19:39:47 by hmokhtar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <limits.h>
# include <readline/readline.h>
# include <readline/history.h>

# define TABLE "|&<>"
# define WHITESPACE " \n\r\v\t\f"

typedef struct s_list
{
	char			*name;
	char			*value;
	struct s_list	*head;
	struct s_list	*next;
}	t_list;

typedef struct s_env
{
	char			**envr;
	t_list			*l_envr;
	int				status;
	int				*child_pid;
}	t_env;

typedef struct s_args
{
	char			*arg;
	struct s_args	*head;
	struct s_args	*next;
}	t_args;

typedef struct s_exe
{
	char			*cmd; // command name (ls, pwd, ...), or path to executable file (/bin/ls, /usr/bin/pwd, ...)
	char			*option;
	t_args			*arg; // Linked list of arguments (ls -l -a, pwd -L, ...)
	char			**args; // Array of arguments (ls -l -a, pwd -L, ...), used for execve function
	char			*stdin; // Input redirection (ls < file.txt, pwd < file.txt, ...)
	char			*stdout; // Output redirection (ls > file.txt, pwd > file.txt, ...)
	char			*stdin2; // Input redirection (ls << file.txt, pwd << file.txt, ...)
	char			*stdout2; // Output redirection (ls >> file.txt, pwd >> file.txt, ...)
	t_env			*envr; // Linked list of environment variables (PATH, HOME, ...)
	struct s_exe	*next;
	struct s_exe	*head;
}	t_exe;

typedef struct s_pipe
{
	int		nb_pipes;
	int		*fd_pipe;
	int		*pid;
	int		tmp_fd_0;
	int		tmp_fd_1;
	t_env	*envr;
}	t_pipe;

int					ft_strlen(char *str);
char				*join_arg2(char *tmp, char *ptr, int *i);
char				*join_arg(char *s1, char *s2);
int					size_buffer(char *buffer);
char				*p_arg(char *buffer, t_exe *exe);
void				new_arg(t_exe *exec);
char				*only_arg(char *buffer, t_exe *exe);
void				init_arg(t_exe *exe);
t_list				*first_env(void);
void				init_env(char **env, t_env *envr);
void				ft_malloc_env(t_env *envr, char *env);
int					fill_name(t_env *envr, char *env);
void				fill_value(t_env *envr, char *env, int i);
void				next_env(t_env *envr);
void				fill_env(char **env, t_env *envr);
t_exe				*new_exe(t_exe *exe);
t_exe				*init_exe(void);
void				free_args(t_args *args, t_exe *exec);
void				free_exec(t_exe *exec);
void				free_kolchi(t_exe *exec);
int					ft_exit(t_exe *exec, t_env *envr);
int					ft_strcmp(char *s1, char *s2);
char				*p_cmd(char *buffer, t_exe *exe);
char				*ft_itoa(int nb);
int					size_buffer_env(char *buffer);
char				*get_name(char	*str);
int					status_size(int nb);
int					ft_parentheses(char *buffer);
char				*get_value(char *name, t_exe *exec);
char				*get_env(char *buffer, t_exe *exec, int *i);
char				*one_dollar(char *buffer, t_exe *exec, int *i);
char				*new_status(char *buffer, t_exe *exec, int *i);
char				*p_env_2(char *buffer, t_exe *exec, int size);
int					last_size_env(char	*buffer, t_exe *exec);
char				*p_env(char *buffer, t_exe *exec);
char				*ft_strjoin(char *s1, char *s2);
char				*dup_last_str(char	*last);
int					size_buffer2(char *buffer);
char				*p_input2_2(char *docstrm, t_exe *exe);
char				*p_input2(char *buffer, t_exe *exe);
char				*p_input(char *buffer, t_exe *exe);
int					size_cmd(char *buffer);
char				*p_option(char *buffer, t_exe *exec);
char				*p_output2(char *buffer, t_exe *exe);
char				*p_output(char *buffer, t_exe *exe);
char				*next_cmd(char *buffer, t_exe *exe);
char				*p_pipe(char *buffer, t_exe *exe);
int					size_line_quotes(char *str);
char				*p_quotes(char *buffer, t_exe *exec);
int					check_others(char *buffer);
int					f_size_quote2(char *str, t_exe *exe);
int					buffer_size_q(char *buffer, t_exe *exe);
char				*skip_buffer(t_exe *exe, char *buffer, int *i);
char				*p_quote2_2(char *buffer, t_exe *exe, int size);
char				*p_quotes2(char *buffer, t_exe *exe);
char				*handle(char *buffer, t_exe *exe);
void				parsing(char *buffer, t_exe *exe);
int					cd(t_exe *exe, t_env *env);
int					echo(t_exe *exe, t_env *env);
int					ft_env(t_env *envr);
void				create_env(t_env *envr);
void				init_args(t_exe *exe);
int					size_arg(t_args *arg);
void				get_status(t_env *envr, t_exe *exe);
int					ft_error(char *s1, char *s2);
void				execution(t_exe *exe, t_env *envr);
int					export(t_exe *exe, t_env *env);
char				**ft_split(const char *str, char charset);
void				*free_tab(char **tab);
char				*ft_strjoin_2(char *s1, char *s2);
char				*ft_strdup(char *str);
char				*get_command(t_env *envr, char *command);
int					builtins(t_exe *exe, t_env *env);
void				no_pip_child(t_exe *exe, t_env *env, int *fd);
int					open_fd(t_exe *exe, int **fd);
int					no_pipe(t_exe *exe, t_env *env);
int					pwd(t_env *env);
int					check_the_first(t_env *envr);
void				check_lst(t_env *envr, char *name);
int					unset(t_exe *exe, t_env *env);
int					arg_len(char **arg);
int					add_env(t_list *list, char *name, char *value);
int					name_check(t_list *list, char *name, char *value);
char				*ft_strrcut(char *arg, char c);
char				*ft_strcut(char *arg, char c);
int					init_pipe(t_pipe *pipee);
void				close_fd_pipe(t_pipe *pipee);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
void				fd_close(int fd_0, int fd_1, t_exe *exe);
int					ft_lstsize(t_exe *lst);
int					fd_open2(t_exe *exe, int *fd_pipe);
int					fd_open(t_exe *exe, int fd_0, int fd_1, int *fd);
int					child_process(t_exe *exe, int fd_0, int fd_1, \
						t_pipe *pipee);
void				parent_process(t_exe *exe, t_pipe *pipee);
int					with_pipe(t_env *envr, t_exe *exe, t_pipe *pipe);
void				ft_signal(t_env	*envir);
void				sighandler(int signal);
void				handle_ctrl_c(int signal, void *ptr);
void				handle_ctrl_qu(int signal, int *ptr);
int					check_parenthesis(char *buffer);
int					ft_strchr(char *s, int c);
int					ft_check_options(char *buffer);
int					ft_valid_options_mini(char c, char get, int *cp);
int					ft_valid_options(char *str);
int					ft_skip_quote(char *buffer, int *i);
void				ft_skip_par(char *str, int *i);
int					ft_w9f(char *str);
char				*ft_lkmala(char *tmp, char *s1, char *s2);
char				*ft_tani(char *str);
void				free_all(char *buffer, t_exe *exec);
char				*my_strchr(char *str, char c);
int					check_valid(char *arg);
int					ft_isalnum(char c);
int					ft_isalpha(char c);
int					ft_isdigit(char c);
int					str_isdigit(char *s);
int					ft_exit_hahia(t_exe *exe, t_env *env);
unsigned long long	ft_cnv(char *str);
void				*ft_malloc(size_t size);
void				haaan(int signal, int *ptr);
#endif