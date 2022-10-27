/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_env.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmokhtar <hmokhtar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 03:10:07 by amsenhaj          #+#    #+#             */
/*   Updated: 2022/10/11 00:08:59 by hmokhtar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*one_dollar(char *buffer, t_exe *exec, int *i)
{
	exec->arg->arg[*i] = '$';
	*i = *i + 1;
	buffer++;
	return (buffer);
}

char	*new_status(char *buffer, t_exe *exec, int *i)
{
	char	*status;
	char	*tmp;

	status = ft_itoa(exec->envr->status);
	tmp = status;
	while (*status)
	{
		exec->arg->arg[*i] = *status;
		status++;
		*i = *i + 1;
	}
	free(tmp);
	buffer = buffer + 2;
	return (buffer);
}

char	*p_env_2(char *buffer, t_exe *exec, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		if ((buffer[1] >= 9 && buffer[1] <= 13)
			|| buffer[1] == 32 || buffer[1] == '\0')
			buffer = one_dollar(buffer, exec, &i);
		else if (buffer[1] == '?' && (buffer[2] == '\0'
				|| (buffer[2] >= 9 && buffer[2] <= 13) || buffer[2] == 32))
			buffer = new_status(buffer, exec, &i);
		else
			buffer = get_env(buffer, exec, &i);
	}
	exec->arg->arg[i] = 0;
	return (buffer);
}

int	last_size_env(char	*buffer, t_exe *exec)
{
	char	*name;
	int		i;

	i = 0;
	if ((buffer[1] == '?' && buffer[2] == '\0')
		|| (buffer[2] >= 9 && buffer[2] <= 13) || buffer[2] == 32)
		i = status_size(exec->envr->status);
	else
	{
		while ((*buffer <= 9 && *buffer >= 13) || (*buffer != 32
				&& *buffer && *buffer != '\'' && *buffer != '\"'))
		{
			if (*buffer == '$')
			{
				if ((buffer[1] >= 9 && buffer[1] <= 13)
					|| buffer[1] == 32 || buffer[1] == '\0')
					i++;
				name = get_name(++buffer);
				i = i + ft_strlen(get_value(name, exec));
				free(name);
			}
			buffer++;
		}
	}
	return (i);
}

char	*p_env(char *buffer, t_exe *exec)
{
	int	size;

	size = last_size_env(buffer, exec);
	if (size != 0)
	{
		exec->arg->arg = ft_malloc(size + 1);
		if (!exec->arg->arg)
			return (NULL);
		buffer = p_env_2(buffer, exec, size);
	}
	else
	{
		if (buffer[0] == '$' && buffer[1] == '$')
			buffer = buffer + 2;
		else
		{
			while (*buffer && ((*buffer <= 9 && *buffer >= 13)
					|| *buffer != 32) && *buffer != '\'' && *buffer != '\"')
				buffer++;
		}
		exec->arg->arg = NULL;
	}
	return (buffer);
}
