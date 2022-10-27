/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsenhaj <amsenhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 01:44:57 by amsenhaj          #+#    #+#             */
/*   Updated: 2022/09/21 13:12:35 by amsenhaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

void	free_args(t_args *args, t_exe *exec)
{
	t_args	*tmp;

	if (exec->args != NULL)
	{
		free(exec->args[0]);
		free(exec->args);
	}
	if (args->head != NULL)
		args = args->head;
	while (args != NULL)
	{
		tmp = args;
		if (args->arg != NULL)
			free(args->arg);
		args = args->next;
		free(tmp);
	}
}

void	free_exec(t_exe *exec)
{
	t_exe	*tmp;

	if (exec->head != NULL)
		exec = exec->head;
	while (exec != NULL)
	{
		tmp = exec;
		if (exec->arg != NULL)
			free_args(exec->arg, exec);
		if (exec->cmd != NULL)
			free(exec->cmd);
		if (exec->option != NULL)
			free(exec->option);
		if (exec->stdin != NULL)
			free(exec->stdin);
		if (exec->stdin2 != NULL)
			free(exec->stdin2);
		if (exec->stdout != NULL)
			free(exec->stdout);
		if (exec->stdout2 != NULL)
			free(exec->stdout2);
		exec = exec->next;
		free(tmp);
	}
}

void	free_kolchi(t_exe *exec)
{
	if (exec != NULL)
		free_exec(exec);
}

int	ft_exit(t_exe *exec, t_env *envr)
{
	int		status;
	t_list	*node;

	status = envr->status;
	envr->l_envr = envr->l_envr->head;
	while (envr->l_envr)
	{
		node = envr->l_envr;
		free(node->name);
		free(node->value);
		free(node);
		envr->l_envr = envr->l_envr->next;
	}
	free_kolchi(exec);
	exit(status);
}
