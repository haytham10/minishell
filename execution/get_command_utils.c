/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_command_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmokhtar <hmokhtar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 20:54:39 by amsenhaj          #+#    #+#             */
/*   Updated: 2022/10/18 15:59:39 by hmokhtar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/minishell.h"

char	*ft_strjoin_2(char *s1, char *s2)
{
	int		i;
	char	*tmp;

	i = -1;
	tmp = (char *)ft_malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!tmp)
		return (NULL);
	if (s1)
	{
		while (s1[++i])
			tmp[i] = s1[i];
	}
	if (s2)
	{
		while (*s2)
		{
			tmp[i] = *s2;
			s2++;
			i++;
		}
	}
	tmp[i] = 0;
	return (tmp);
}

char	*ft_strdup(char *str)
{
	int		i;
	char	*s;

	i = 0;
	s = ft_malloc(ft_strlen((char *)str) + 1);
	if (!s || !str)
		return (NULL);
	while (str[i])
	{
		s[i] = str[i];
		i++;
	}
	s[i] = '\0';
	return (s);
}
