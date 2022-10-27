/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   no_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmokhtar <hmokhtar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 20:14:39 by hmokhtar          #+#    #+#             */
/*   Updated: 2022/10/18 18:21:55 by hmokhtar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/minishell.h"

int	builtins(t_exe *exe, t_env *env)
{
	if (ft_strncmp(exe->cmd, "echo", 5) == 0)
		return (echo(exe, env));
	if (ft_strncmp(exe->cmd, "cd", 3) == 0)
		return (cd(exe, env));
	if (ft_strncmp(exe->cmd, "pwd", 4) == 0)
		return (pwd(env));
	if (ft_strncmp(exe->cmd, "export", 7) == 0)
		return (export(exe, env));
	if (ft_strncmp(exe->cmd, "unset", 6) == 0)
		return (unset(exe, env));
	if (ft_strncmp(exe->cmd, "env", 4) == 0)
		return (ft_env(env));
	if (ft_strncmp(exe->cmd, "exit", 5) == 0)
		return (ft_exit_hahia(exe, env), env->status);
	return (6);
}

void	no_pip_child(t_exe *exe, t_env *env, int *fd)
{
	if (exe->stdout != 0 || exe->stdout2 != 0)
		dup2(fd[1], 1);
	if (exe->stdin != 0 || exe->stdin2 != 0)
		dup2(fd[0], 0);
	env->status = builtins(exe, env);
	env->child_pid = (int *)ft_malloc(sizeof(int) * 2);
	if (!env->child_pid)
		return ;
	if (env->status == 6)
	{
		env->child_pid[0] = fork();
		env->child_pid[1] = 0;
		handle_ctrl_c(5000, env->child_pid);
		handle_ctrl_qu(5000, env->child_pid);
		if (!env->child_pid[0])
		{
			env->status = execve(exe->args[0],
					exe->args, env->envr);
			exit(env->status);
		}
		waitpid(env->child_pid[0], &env->status, 0);
	}
	if (ft_strcmp(exe->cmd, "ls") && env->status == 256)
		env->status = 1;
	fd_close(fd[0], fd[1], exe);
}

int	open_fd(t_exe *exe, int **fd)
{
	if (exe->stdin != 0)
	{
		(*fd)[0] = open(exe->stdin, O_RDONLY);
		if ((*fd)[0] == -1)
			return (ft_error(exe->stdin, " : No such file or directory"), -1);
		if (exe->stdin != 0)
			dup2((*fd)[0], 0);
	}
	else if (exe->stdin2 != 0)
	{
		if (pipe(*(fd) + 2) == -1)
			return (-1);
		if (!fork())
		{
			write((*fd)[3], exe->stdin2, ft_strlen(exe->stdin2));
			close((*fd)[3]);
			close((*fd)[2]);
			exit(0);
		}
		close((*fd)[3]);
		wait(0);
		dup2((*fd)[2], 0);
		close((*fd)[2]);
	}
	return (0);
}

int	no_pipe(t_exe *exe, t_env *env)
{
	int	*fd;

	fd = ft_malloc(sizeof(int) * 4);
	if (!fd)
		return (ft_error("Error", "fd ft_malloc failed"));
	if (open_fd(exe, &fd) == -1)
		return (-1);
	if (exe->stdout != 0)
		fd[1] = open(exe->stdout, O_WRONLY | O_TRUNC | O_CREAT, S_IRWXU);
	else if (exe->stdout2 != 0)
		fd[1] = open(exe->stdout2, O_WRONLY | O_APPEND | O_CREAT, S_IRWXU);
	no_pip_child(exe, env, fd);
	free(env->child_pid);
	env->child_pid = NULL;
	free(fd);
	return (0);
}
