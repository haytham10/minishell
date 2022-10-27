/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   with_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmokhtar <hmokhtar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 23:55:34 by hmokhtar          #+#    #+#             */
/*   Updated: 2022/10/18 15:54:10 by hmokhtar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/minishell.h"

int	fd_open2(t_exe *exe, int *fd_pipe)
{
	int	pid;

	if (exe->stdin2 != 0)
	{
		if (pipe(fd_pipe) == -1)
			return (-1);
		pid = fork();
		if (!pid)
		{
			write(fd_pipe[1], exe->stdin2, ft_strlen(exe->stdin2));
			close(fd_pipe[1]);
			close(fd_pipe[0]);
			exit(0);
		}
		close(fd_pipe[1]);
		waitpid(pid, 0, 0);
		dup2(fd_pipe[0], 0);
		close(fd_pipe[0]);
	}
	return (0);
}

int	fd_open(t_exe *exe, int fd_0, int fd_1, int *fd)
{
	if (exe->stdin != 0)
	{
		fd[0] = open(exe->stdin, O_RDONLY);
		if (fd[0] < 0)
			return (ft_error(exe->stdin, ": No such file or dirctory"), -1);
		dup2(fd[0], 0);
	}
	else if (exe->stdin2 != 0)
	{
		if (fd_open2(exe, fd) == -1)
			return (-1);
	}
	else
		dup2(fd_0, 0);
	if (exe->stdout != 0)
		fd[1] = open(exe->stdout, O_WRONLY | O_TRUNC | O_CREAT, 0666);
	else if (exe->stdout2 != 0)
		fd[1] = open(exe->stdout2, O_WRONLY | O_APPEND | O_CREAT, 0666);
	else
		dup2(fd_1, 1);
	return (0);
}

int	child_process(t_exe *exe, int fd_0, int fd_1, t_pipe *pipee)
{
	int	*fd;

	fd = ft_malloc(sizeof(int) * 2);
	if (!fd)
		return (-1);
	if (fd_open(exe, fd_0, fd_1, fd) == -1)
		return (-1);
	if (fd[1] != 0)
		dup2(fd[1], 1);
	close_fd_pipe(pipee);
	fd_close(fd[0], fd[1], exe);
	free(fd);
	exe->envr->status = builtins(exe, exe->envr);
	if (exe->envr->status == 6)
	{
		exe->envr->status = execve(exe->args[0], exe->args, pipee->envr->envr);
		if (exe->envr->status == 65280)
			exe->envr->status = 127;
	}
	exit(exe->envr->status);
}

void	parent_process(t_exe *exe, t_pipe *pipee)
{
	int		i;

	i = -1;
	while (++i <= pipee->nb_pipes)
	{
		pipee->pid[i] = fork();
		if (pipee->pid[i] == -1)
			ft_error("Error: fork mistake", "\n");
		if (!pipee->pid[i])
		{
			if (i == 0)
				child_process(exe, pipee->tmp_fd_0, \
							pipee->fd_pipe[i * 2 + 1], pipee);
			else if (i == pipee->nb_pipes)
				child_process(exe, pipee->fd_pipe[(i - 1) * 2], \
							pipee->tmp_fd_1, pipee);
			else
				child_process(exe, pipee->fd_pipe[(i - 1) * 2], \
							pipee->fd_pipe[i * 2 + 1], pipee);
		}
		exe = exe->next;
	}
}

int	with_pipe(t_env *envr, t_exe *exe, t_pipe *pipe)
{
	int			i;
	t_exe		*tmp;

	i = -1;
	tmp = exe;
	pipe->envr = envr;
	init_pipe(pipe);
	envr->child_pid = pipe->pid;
	parent_process(tmp, pipe);
	close_fd_pipe(pipe);
	while (++i <= pipe->nb_pipes)
	{
		handle_ctrl_c(5000, envr->child_pid);
		waitpid(pipe->pid[i], &envr->status, 0);
		get_status(tmp->envr, tmp);
		tmp = tmp->next;
	}
	free(pipe->pid);
	pipe->pid = NULL;
	free(pipe->fd_pipe);
	pipe->fd_pipe = NULL;
	return (0);
}
