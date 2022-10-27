/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wa7d_l3iba.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmokhtar <hmokhtar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 11:44:14 by amsenhaj          #+#    #+#             */
/*   Updated: 2022/10/11 00:08:59 by hmokhtar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tani(char *s1, char *s2, char *s)
{
	free(s1);
	free(s2);
	free(s);
}

int	ft_w9f(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '|' && str[i + 1])
			return (0);
		i++;
	}
	return (1);
}

char	*ft_lkmala(char *tmp, char *s1, char *s2)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	tmp = ft_malloc (strlen(s1) + strlen(s2) + 2);
	if (!tmp)
		return (NULL);
	while (s1[i])
	{
		tmp[j] = s1[i];
		i++;
		j++;
	}
	i = 0;
	tmp[j++] = ' ';
	tmp[j++] = '|';
	tmp[j++] = ' ';
	while (s2[i])
	{
		tmp[j++] = s2[i];
		i++;
	}
	tmp[j] = 0;
	return (tmp);
}

char	*ft_tani(char *str)
{
	char	**s;
	char	*s1;
	char	*s2;
	char	*tmp;

	s = ft_split(str, '|');
	tmp = NULL;
	s1 = s[0];
	s2 = s[1];
	if (s2)
	{
		tmp = ft_lkmala(tmp, s1, s2);
		free(str);
		free_tab(s);
		return (tmp);
	}
	free(str);
	free_tab(s);
	return (str);
}
