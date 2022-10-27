/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmokhtar <hmokhtar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 14:35:36 by hmokhtar          #+#    #+#             */
/*   Updated: 2022/10/11 00:08:59 by hmokhtar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**fill_it(char **env)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	env[0] = "SHLVL=1";
	env[1] = ft_strjoin_2("PWD=", pwd);
	env[2] = "_=/usr/bin/env";
	env[3] = NULL;
	free(pwd);
	return (env);
}

void	create_env(t_env *envr)
{
	char	**env;
	int		i;
	int		j;

	i = 1;
	env = (char **)ft_malloc(sizeof(char *) * 4);
	env = fill_it(env);
	envr->envr = env;
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
	free(env[1]);
	free(env);
}
