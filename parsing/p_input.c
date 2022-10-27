/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_input.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmokhtar <hmokhtar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 13:21:25 by amsenhaj          #+#    #+#             */
/*   Updated: 2022/10/18 17:51:40 by hmokhtar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*dup_last_str(char	*last)
{
	char	*duplicate;
	int		i;

	i = 0;
	duplicate = ft_malloc(ft_strlen(last) + 2);
	if (!duplicate)
		return (NULL);
	while (last[i])
	{
		duplicate[i] = last[i];
		i++;
	}
	duplicate[i] = '\n';
	duplicate[i + 1] = 0;
	free(last);
	return (duplicate);
}

char	*other(char *str, t_exe *exe)
{
	if (*str == '$')
	{
		free(str);
		str = ft_strdup(get_value(++str, exe));
		if (str == NULL)
			str = ft_strdup("\n");
	}
	return (str);
}

char	*p_input2_2(char *docstr, t_exe *exe)
{
	char	*buffer;
	char	*last_str;

	last_str = readline("\033[92mheredoc> \033[97m");
	if (last_str == NULL)
		return (NULL);
	last_str = other(last_str, exe);
	if (ft_strcmp(last_str, docstr))
		return (free(last_str), NULL);
	while (1)
	{
		buffer = readline("\033[92mheredoc> \033[97m");
		if (buffer == NULL)
			return (dup_last_str(last_str));
		buffer = other(buffer, exe);
		if (ft_strcmp(buffer, docstr))
			break ;
		last_str = ft_strjoin(last_str, buffer);
		free(buffer);
	}
	return (free(buffer), dup_last_str(last_str));
}

char	*p_input2(char *buffer, t_exe *exe)
{
	char	*str;
	char	*d_str;
	int		i;

	while ((*buffer >= 9 && *buffer <= 13) || *buffer == 32)
		buffer++;
	i = 0;
	str = buffer;
	d_str = ft_malloc(size_buffer2(str) + 1);
	if (!d_str)
		return (NULL);
	while (i < size_buffer2(str))
	{
		d_str[i++] = *buffer;
		buffer++;
	}
	d_str[i] = 0;
	exe->stdin2 = p_input2_2(d_str, exe);
	free(d_str);
	return (buffer);
}

char	*p_input(char *buffer, t_exe *exe)
{
	if (*buffer == '<')
		buffer = p_input2(++buffer, exe);
	else
	{
		while ((*buffer >= 9 && *buffer <= 13) || *buffer == 32)
			buffer++;
		buffer = only_arg(buffer, exe);
		exe->stdin = join_arg(exe->arg->arg, NULL);
		exe->arg->arg = NULL;
	}
	return (buffer);
}
