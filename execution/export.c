/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmokhtar <hmokhtar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 00:00:11 by hmokhtar          #+#    #+#             */
/*   Updated: 2022/09/28 23:43:00 by hmokhtar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/minishell.h"

int	print_env(t_list *env, t_env *eenv)
{
	env = env->head;
	while (env)
	{
		if (env->name)
		{
			printf("declare -x %s", env->name);
			if (env->value)
				printf("=\"%s\"", env->value);
			printf("\n");
		}
		env = env->next;
	}
	eenv->status = 0;
	return (0);
}

void	kmala(t_env *env, t_exe *exe, int i)
{
	if (my_strchr(exe->args[i], '='))
	{
		if (name_check(env->l_envr, ft_strcut(exe->args[i], '='), \
			ft_strrcut(exe->args[i], '=')) == -1)
			add_env(env->l_envr, ft_strcut(exe->args[i], '='), \
			ft_strrcut(exe->args[i], '='));
	}
	else
	{
		if (name_check(env->l_envr, ft_strdup(exe->args[i]), NULL) == -1)
			add_env(env->l_envr, ft_strdup(exe->args[i]), NULL);
	}
}

int	export(t_exe *exe, t_env *env)
{
	int	i;

	i = 0;
	if (exe->args[1] == NULL)
		return (print_env(env->l_envr, env));
	while (exe->args[++i])
	{
		if (check_valid(exe->args[i]) == 0)
			kmala(env, exe, i);
		else
		{
			ft_error(exe->args[i], " : is not a valid identifier");
			env->status = 1;
			return (-1);
		}
	}
	env->status = 0;
	return (0);
}
