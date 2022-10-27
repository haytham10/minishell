/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_quotes.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmokhtar <hmokhtar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 03:04:29 by amsenhaj          #+#    #+#             */
/*   Updated: 2022/10/11 00:08:59 by hmokhtar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	size_line_quotes(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] && str[i] != '\'')
		i++;
	return (i);
}

char	*p_quotes(char *buffer, t_exe *exec)
{
	char	*str;
	int		i;

	while (*buffer == '\'')
		++buffer;
	i = 0;
	str = buffer;
	exec->arg->arg = (char *)ft_malloc(size_line_quotes(str) + 1);
	if (!exec->arg->arg)
		return (NULL);
	while (i < size_line_quotes(str))
	{
		exec->arg->arg[i] = *buffer;
		i++;
		++buffer;
	}
	exec->arg->arg[i] = 0;
	if (*buffer == 0)
		return (buffer);
	return (++buffer);
}
