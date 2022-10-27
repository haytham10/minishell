/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmokhtar <hmokhtar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 20:39:44 by amsenhaj          #+#    #+#             */
/*   Updated: 2022/10/17 16:12:11 by hmokhtar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/minishell.h"

static char	**our_path(t_list *l_envr)
{
	char	**path;

	path = NULL;
	l_envr = l_envr->head;
	while (l_envr)
	{
		if (!ft_strncmp(l_envr->name, "PATH", ft_strlen(l_envr->name)))
		{
			path = ft_split(l_envr->value, ':');
			break ;
		}
		l_envr = l_envr->next;
	}
	return (path);
}

static char	*check_command(char **path, char *str_cmd)
{
	int		i;
	char	*tmp;

	i = -1;
	if (path)
	{
		while (path[++i])
		{
			tmp = ft_strjoin_2(path[i], str_cmd);
			if (access(tmp, X_OK) == 0)
				return (tmp);
			else
				free(tmp);
		}
	}
	return (NULL);
}

static char	**free_path(char **path)
{
	size_t	i;

	i = 0;
	if (path)
	{
		while (path[i])
		{
			free(path[i]);
			i++;
		}
		free(path);
	}
	return (NULL);
}

char	*get_command(t_env *envr, char *command)
{
	char	**path;
	char	*str_cmd;
	char	*cmd;

	cmd = command;
	path = our_path(envr->l_envr);
	str_cmd = ft_strjoin_2("/", cmd);
	cmd = check_command(path, str_cmd);
	if (!cmd)
		cmd = ft_strdup(command);
	free(str_cmd);
	free_path(path);
	return (cmd);
}
