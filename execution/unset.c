/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmokhtar <hmokhtar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 21:50:24 by amsenhaj          #+#    #+#             */
/*   Updated: 2022/10/16 10:33:34 by hmokhtar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/minishell.h"

int	check_exist(char *arg, t_list *env)
{
	env = env->head;
	while (env)
	{
		if (ft_strncmp(env->name, arg, ft_strlen(arg)) == 0)
			return (0);
		env = env->next;
	}
	return (-1);
}

int	delete_node(char *arg, t_list *env)
{
	t_list	*tmp;

	tmp = env;
	if (ft_strncmp(tmp->name, arg, ft_strlen(arg)) == 0)
	{
		env->head = tmp->next;
		return (0);
	}
	while (tmp)
	{
		if (ft_strncmp(tmp->next->name, arg, ft_strlen(arg)) == 0)
		{
			free(tmp->next->name);
			free(tmp->next->value);
			free(tmp->next);
			tmp->next = tmp->next->next;
			return (0);
		}
		tmp = tmp->next;
	}
	free(tmp);
	return (-1);
}

int	unset(t_exe *exe, t_env *env)
{
	int	i;

	i = 1;
	while (exe->args[i])
	{
		if (check_valid(exe->args[i]) == -1)
			return (printf("BashAllah: unset: `%s': not a valid identifier\n", \
				exe->args[i]), -1);
		if (check_exist(exe->args[i], env->l_envr) == -1)
			return (-1);
		i++;
	}
	i = 1;
	while (exe->args[i])
	{
		if (delete_node(exe->args[i], env->l_envr) == -1)
			return (printf("BashAllah: unset: `%s': not a valid identifier\n", \
				exe->args[i]), -1);
		i++;
	}
	return (0);
}
