/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_options.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmokhtar <hmokhtar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 09:10:48 by amsenhaj          #+#    #+#             */
/*   Updated: 2022/10/17 20:31:12 by hmokhtar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

void	ft_skip_par(char *str, int *i)
{
	int	cp;

	cp = 0;
	if (str[*i] == 40)
	{
		cp++;
		(*i)++;
		while (str[*i] && cp > 0)
		{
			if (str[*i] == 41)
				cp--;
			if (str[*i] == 40)
				cp++;
			(*i)++;
		}
	}
}

int	ft_strchr(char *s, int c)
{
	int		i;

	i = 0;
	while (s[i])
	{
		if (ft_skip_quote(s, &i) == -1)
			return (-1);
		ft_skip_par(s, &i);
		if (s[i] == (char)c)
		{
			if (s[i + 1] == (char)c)
			{
				i += 2;
				continue ;
			}
			return (i);
		}
		i++;
	}
	return (-1);
}

int	ft_check_options(char *buffer)
{
	int	i;

	i = 0;
	while (buffer[i])
	{
		if (ft_skip_quote(buffer, &i) == -1)
			return (1);
		if (ft_strchr(TABLE, buffer[i]) != -1 && buffer[i + 1] == ' ')
		{
			i++;
			while (buffer[i] && buffer[i] == ' ')
				i++;
			if (ft_strchr(TABLE, buffer[i]) != -1)
			{
				printf ("MiniShell: syntax error near ");
				printf("unexpected token `%c'\n", buffer[i]);
				return (1);
			}
		}
		else
			i++;
	}
	return (0);
}
