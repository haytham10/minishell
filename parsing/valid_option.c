/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_option.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmokhtar <hmokhtar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 09:18:12 by amsenhaj          #+#    #+#             */
/*   Updated: 2022/10/17 20:27:37 by hmokhtar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_valid_options_mini(char c, char get, int *cp)
{
	if (ft_strchr(TABLE, c) != -1)
	{
		if (get != c)
		{
			printf ("BashAllah: syntax error near unexpected token `%c'\n", c);
			return (1);
		}
		if (get == c)
		{
			(*cp)++;
			if (*cp == 2)
			{
				printf ("BashAllah: syntax error near ");
				printf("unexpected token `%c'\n", c);
				return (1);
			}
		}
	}
	if (get == '&' && *cp == 0)
	{
		printf ("BashAllah: syntax error near unexpected token `&'\n");
		return (1);
	}
	return (0);
}

int	ft_valid_options(char *str)
{
	int		i;
	int		cp;
	char	get;

	i = 0;
	cp = 0;
	while (str[i])
	{
		if (ft_skip_quote(str, &i) == -1)
			return (1);
		if (ft_strchr(TABLE, str[i]) != -1)
		{
			get = str[i++];
			if (ft_valid_options_mini(str[i], get, &cp))
				return (1);
		}
		else
		{
			cp = 0;
			i++;
		}
	}
	return (0);
}
