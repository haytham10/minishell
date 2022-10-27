/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmokhtar <hmokhtar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 21:05:38 by amsenhaj          #+#    #+#             */
/*   Updated: 2022/10/11 00:08:59 by hmokhtar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_malloc_env(t_env	*envr, char	*env)
{
	int	nb_name;
	int	nb_value;
	int	i;

	nb_name = 0;
	nb_value = 0;
	i = 0;
	while (env[i] != '=')
	{
		nb_name++;
		i++;
	}
	i++;
	while (env[i])
	{
		nb_value++;
		i++;
	}
	envr->l_envr->name = ft_malloc(nb_name + 1);
	if (!envr->l_envr->name)
		return ;
	envr->l_envr->value = ft_malloc(nb_value + 1);
	if (!envr->l_envr->value)
		return ;
}

int	fill_name(t_env	*envr, char	*env)
{
	int	i;

	i = 0;
	while (env[i] != '=')
	{
		envr->l_envr->name[i] = env[i];
		i++;
	}
	envr->l_envr->name[i] = 0;
	return (i + 1);
}

void	fill_value(t_env *envr, char *env, int i)
{
	int	j;

	j = 0;
	while (env[i])
	{
		envr->l_envr->value[j] = env[i];
		i++;
		j++;
	}
	envr->l_envr->value[j] = 0;
}

void	next_env(t_env	*envr)
{
	t_list	*node;

	node = ft_malloc(sizeof(t_list));
	if (!node)
		return ;
	node->name = NULL;
	node->value = NULL;
	node->head = envr->l_envr->head;
	node->next = NULL;
	envr->l_envr->next = node;
	envr->l_envr = node;
}

void	fill_env(char	**env, t_env	*envr)
{
	int	i;
	int	j;

	i = 1;
	ft_malloc_env(envr, env[0]);
	j = fill_name(envr, env[0]);
	fill_value(envr, env[0], j);
	while (env[i])
	{
		next_env(envr);
		ft_malloc_env(envr, env[i]);
		j = fill_name(envr, env[i]);
		fill_value(envr, env[i], j);
		i++;
	}
	envr->l_envr = envr->l_envr->head;
}
