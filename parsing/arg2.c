/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmokhtar <hmokhtar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 08:29:08 by amsenhaj          #+#    #+#             */
/*   Updated: 2022/10/18 14:43:38 by hmokhtar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

char	*join_arg2(char *tmp, char *ptr, int *i)
{
	int	j;

	j = 0;
	while (ptr[j])
	{
		tmp[*i] = ptr[j];
		j++;
		*i = *i + 1;
	}
	return (tmp);
}

char	*join_arg(char *s1, char *s2)
{
	char	*tmp;
	int		i;

	i = 0;
	if (!s1)
		return (s2);
	tmp = ft_malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!tmp)
		return (NULL);
	if (s1)
	{
		while (s1[i])
		{
			tmp[i] = s1[i];
			i++;
		}
	}
	if (s2)
		tmp = join_arg2(tmp, s2, &i);
	tmp[i] = 0;
	return (free(s1), free(s2), tmp);
}

char	*ft_itoa(int nb)
{
	char	*str;
	int		size;
	int		i;

	i = 0;
	size = status_size(nb);
	str = ft_malloc(size + 1);
	if (!str)
		return (NULL);
	if (nb == 0)
		str[i++] = '0';
	while (nb > 0)
	{
		str[size - i - 1] = (nb % 10) + '0';
		nb = nb / 10;
		i++;
	}
	str[i] = 0;
	return (str);
}

char	*ft_strjoin(char *s1, char *s2)
{
	int		i;
	char	*str;

	i = 0;
	str = (char *)ft_malloc(ft_strlen(s1) + ft_strlen(s2) + 2);
	if (!str)
		return (NULL);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = '\n';
	i++;
	while (*s2)
	{
		str[i] = *s2;
		i++;
		s2++;
	}
	str[i] = 0;
	free(s1);
	return (str);
}
