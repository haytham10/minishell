/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_others.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmokhtar <hmokhtar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 15:50:18 by amsenhaj          #+#    #+#             */
/*   Updated: 2022/10/18 15:46:01 by hmokhtar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_verif(char c, char const *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	int		i;
	int		start;
	int		end;

	start = 0;
	if (!s1)
		return (NULL);
	while (s1[start] && ft_verif(s1[start], set))
		start++;
	end = strlen(s1);
	while (end > start && ft_verif(s1[end - 1], set))
		end--;
	str = (char *)ft_malloc(sizeof(char) * (end - start + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (start < end)
	{
		str[i] = s1[start];
		i++;
		start++;
	}
	str[i] = 0;
	return (str);
}

static	int	check_lpipes(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '|' && str[i + 1] == '|')
			return (-1);
		i++;
	}
	return (0);
}

int	check_others(char *buffer)
{
	int		j;
	char	*str;

	str = ft_strtrim(buffer, "\t\n\v\f\r ");
	j = ft_strlen (str);
	if (check_lpipes(str))
		return (write(1, "BashAllah: syntax error\n", 24), free(str), 1);
	if (str[0] == ';' || str[j - 1] == ';')
		return (write(1, "BashAllah: syntax error\n", 24), free(str), 1);
	if (str[j - 1] == '\\')
		return (write(1, "BashAllah: syntax error\n", 24), free(str), 1);
	if (str[0] == '|' || str[j - 1] == '|')
		return (write(1, "BashAllah: syntax error\n", 24), free(str), 1);
	if (str[j - 1] == '<')
		return (write(1, "syntax error near unexpected token `newline'\n", 45), \
			free(str), 1);
	if (str[j - 1] == '>')
		return (write(1, "syntax error near unexpected token `newline'\n", 45), \
			free(str), 1);
	free(str);
	return (0);
}
