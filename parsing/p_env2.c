/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_env2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmokhtar <hmokhtar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 08:32:02 by amsenhaj          #+#    #+#             */
/*   Updated: 2022/10/18 13:49:31 by hmokhtar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	size_buffer_env(char *buffer)
{
	int	i;

	i = 0;
	while (((buffer[i] <= 9 && buffer[i] >= 13)
			|| buffer[i] != 32) && buffer[i] && buffer[i] != '\"' \
				&& buffer[i] != '$')
		i++;
	return (i);
}

char	*get_name(char	*str)
{
	char	*name;
	int		i;

	name = NULL;
	i = 0;
	if (*str == '$')
	{
		name = (char *)ft_malloc(2);
		name[0] = '$';
		name[1] = 0;
	}
	else
	{
		name = (char *)ft_malloc(size_buffer_env(str) + 1);
		while (((*str <= 9 && *str >= 13) || *str != 32)
			&& *str && *str != '\"' && *str != '$' \
			&& *str != '\'' && *str != '+')
		{
			name[i] = *str;
			i++;
			str++;
		}
		name[i] = 0;
	}
	return (name);
}

int	status_size(int nb)
{
	int	i;

	i = 0;
	if (nb == 0)
		return (1);
	while (nb > 0)
	{
		nb = nb / 10;
		i++;
	}
	return (i);
}

char	*get_value(char *name, t_exe *exec)
{
	t_list	*tmp;

	tmp = exec->envr->l_envr;
	while (tmp != NULL)
	{
		if (ft_strcmp(name, tmp->name))
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}

char	*get_env(char *buffer, t_exe *exec, int *i)
{
	char	*value;
	char	*name;

	name = get_name(++buffer);
	value = get_value(name, exec);
	if (value)
	{
		while (*value)
		{
			exec->arg->arg[*i] = *value;
			value++;
			*i = *i + 1;
		}
	}
	if (buffer[0] == '$')
		buffer = buffer + 1;
	else
	{
		while (((*buffer <= 9 && *buffer >= 13) || *buffer != 32)
			&& *buffer != '\0' && *buffer != '$' && *buffer != '\'' \
				&& *buffer != '\"')
			buffer++;
	}
	free(name);
	return (buffer);
}
