/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_quotes2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmokhtar <hmokhtar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 03:03:05 by hmokhtar          #+#    #+#             */
/*   Updated: 2022/10/11 00:08:59 by hmokhtar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	f_size_quote2(char *str, t_exe *exe)
{
	char	*name;
	int		i;

	i = 0;
	if ((str[1] == '?' && str[2] == '\0')
		|| (str[2] >= 9 && str[2] <= 13) || str[2] == 32)
		i = status_size(exe->envr->status);
	else
	{
		while ((*str <= 9 && *str >= 13) || (*str != 32
				&& *str && *str != '\"' && *str != '\''))
		{
			if (*str == '$')
			{
				if (((str[1] >= 9 && str[1] <= 13) || str[1] == 32)
					|| str[1] == '\0' || str[1] == '\"' || str[1] == '\'')
					i++;
				name = get_name(++str);
				i = i + ft_strlen(get_value(name, exe));
				free(name);
			}
			str++;
		}
	}
	return (i);
}

int	buffer_size_q(char *buffer, t_exe *exe)
{
	int	i;

	i = 0;
	if (buffer == NULL)
		return (0);
	while (*buffer && *buffer != '\"')
	{
		if (*buffer == '$')
		{
			i = i + f_size_quote2(buffer, exe);
			while (((*buffer <= 9 && *buffer >= 13)
					|| *buffer != 32) && *buffer && *buffer != '\"' \
						&& *buffer != '\'')
				buffer++;
		}
		else
		{
			i++;
			buffer++;
		}
	}
	return (i);
}

char	*skip_buffer(t_exe *exe, char *buffer, int *i)
{
	if ((buffer[1] >= 9 && buffer[1] <= 13) || buffer[1] == 32
		|| buffer[1] == '\0' || buffer[1] == '\"' || buffer[1] == '\'')
		buffer = one_dollar(buffer, exe, i);
	else if ((buffer[1] == '?' && buffer[2] == '\0')
		|| (buffer[2] >= 9 && buffer[2] <= 13)
		|| buffer[2] == 32 || buffer[2] == '\"' || buffer[2] == '\'')
		buffer = new_status(buffer, exe, i);
	else
		buffer = get_env(buffer, exe, i);
	return (buffer);
}

char	*p_quote2_2(char *buffer, t_exe *exe, int size)
{
	int		i;

	i = 0;
	while (i < size)
	{
		if (*buffer == '$')
			buffer = skip_buffer(exe, buffer, &i);
		else
		{
			exe->arg->arg[i] = *buffer;
			i++;
			buffer++;
		}
	}
	exe->arg->arg[i] = 0;
	return (buffer);
}

char	*p_quotes2(char *buffer, t_exe *exe)
{
	int	size;

	while (*buffer == '\"')
		++buffer;
	size = buffer_size_q(buffer, exe);
	if (size != 0)
	{
		exe->arg->arg = ft_malloc(size + 1);
		if (!exe->arg->arg)
			return (NULL);
		buffer = p_quote2_2(buffer, exe, size);
	}
	else
	{
		while (*buffer != '\"' && *buffer)
			buffer++;
		exe->arg->arg = NULL;
	}
	if (*buffer == 0)
		return (buffer);
	return (++buffer);
}
