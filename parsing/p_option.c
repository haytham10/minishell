/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_option.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmokhtar <hmokhtar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 17:02:57 by hmokhtar          #+#    #+#             */
/*   Updated: 2022/10/11 00:08:59 by hmokhtar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

int	size_cmd(char *buffer)
{
	int	i;

	i = 0;
	while (((buffer[i] <= 9 && buffer[i] >= 13) || buffer[i] != 32)
		&& buffer[i])
		i++;
	return (i);
}

char	*p_option(char *buffer, t_exe *exec)
{
	char	*str;
	int		i;

	i = 0;
	str = buffer;
	exec->option = (char *)ft_malloc(size_cmd(str) + 1);
	if (!exec->option)
		return (NULL);
	while (i < size_cmd(str))
	{
		exec->option[i] = *buffer;
		i++;
		buffer++;
	}
	exec->option[i] = 0;
	return (buffer);
}
