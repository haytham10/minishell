/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmokhtar <hmokhtar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 20:12:00 by amsenhaj          #+#    #+#             */
/*   Updated: 2022/10/18 18:03:10 by hmokhtar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/minishell.h"

void	init_args(t_exe *exe)
{
	int		i;
	int		nb;
	t_env	*envr;

	envr = exe->envr;
	while (exe)
	{
		i = 0;
		nb = size_arg(exe->arg);
		exe->args = (char **)ft_malloc(sizeof(char **) * (nb + 2));
		if (!exe->args)
			return ;
		exe->args[0] = get_command(envr, exe->cmd);
		while (exe->arg->next)
		{
			exe->args[++i] = exe->arg->arg;
			exe->arg = exe->arg->next;
		}
		exe->args[++i] = exe->arg->arg;
		exe->args[++i] = NULL;
		exe->arg = exe->arg->head;
		exe = exe->next;
	}
}

int	size_arg(t_args *arg)
{
	int	i;

	i = 0;
	while (arg)
	{
		++i;
		arg = arg->next;
	}
	return (i);
}

void	get_status(t_env *envr, t_exe *exe)
{
	if (envr->status == 2)
		envr->status = 1;
	else if (envr->status == 3)
		envr->status = 131;
	else if ((ft_strcmp(exe->cmd, "ls") == 0) && envr->status == 256)
		envr->status = 1;
	else if (envr->status == 65280)
	{
		ft_error(exe->cmd, " : command not found");
		envr->status = 127;
	}
}

int	ft_error(char *s1, char *s2)
{
	write(2, s1, ft_strlen(s1));
	write(2, s2, ft_strlen(s2));
	write(2, "\n", 1);
	return (1);
}

void	execution(t_exe *exe, t_env *envr)
{
	t_pipe	pipe;

	signal(SIGQUIT, sighandler);
	pipe.tmp_fd_0 = dup(0);
	pipe.tmp_fd_1 = dup(1);
	pipe.nb_pipes = ft_lstsize(exe) - 1;
	init_args(exe);
	if (pipe.nb_pipes == 0)
	{
		no_pipe(exe, envr);
		get_status(envr, exe);
	}
	else
		with_pipe(envr, exe, &pipe);
	dup2(pipe.tmp_fd_0, 0);
	dup2(pipe.tmp_fd_1, 1);
}
