/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmokhtar <hmokhtar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 12:49:47 by hmokhtar          #+#    #+#             */
/*   Updated: 2022/10/18 18:22:38 by hmokhtar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (!s1)
		return (1);
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
			return (0);
		i++;
	}
	return (1);
}

int	size_buffer2(char *buffer)
{
	int	i;

	i = 0;
	while (((buffer[i] <= 9 && buffer[i] >= 13) || buffer[i] != 32)
		&& buffer[i] && buffer[i] != '\"' \
			&& buffer[i] != '\'' && buffer[i] != '|')
		i++;
	return (i);
}
