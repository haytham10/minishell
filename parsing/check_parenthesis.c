/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_parenthesis.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsenhaj <amsenhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 20:39:43 by amsenhaj          #+#    #+#             */
/*   Updated: 2022/09/27 17:47:59 by amsenhaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

static	int	check_parenthesis_mini(char *buffer, int *i, int *j)
{
	int	str;

	str = 0;
	while (buffer[*i] && *j > 0)
	{
		if (buffer[*i] == '&' || buffer[*i] == '|')
			str++;
		if (buffer[*i] == 40)
			(*j)++;
		if (buffer[*i] == 41)
			(*j)--;
		if (*j)
			(*i)++;
	}
	if (str)
		return (1);
	return (0);
}

static int	check_parenthesis_norm(char *buffer, int *i, int *j)
{
	if (buffer[*i] == 40)
	{
		(*j)++;
		(*i)++;
		if (!check_parenthesis_mini(buffer, i, j))
		{
			printf ("MiniShell: syntax error near ");
			printf("unexpected token `%c'\n", buffer[*i]);
			return (1);
		}
	}
	if (*j != 0)
	{
		printf ("MiniShell: syntax error near ");
		printf("unexpected token `%c'\n", buffer[*i]);
		return (1);
	}
	return (0);
}

int	ft_skip_quote(char *buffer, int *i)
{
	char	index;

	if (buffer[*i] == '\"' || buffer[*i] == '\'')
	{
		index = buffer[(*i)++];
		while (buffer[*i] && buffer[*i] != index)
			(*i)++;
		if (!buffer[*i])
		{
			printf("MiniShell: syntax error unclosed ");
			printf("quote near `%c'\n", buffer[*i]);
			return (-1);
		}
	}
	return (0);
}

int	check_parenthesis(char *buffer)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (buffer[i])
	{
		if (ft_skip_quote(buffer, &i) == -1)
			return (1);
		if (buffer[i] == 41)
		{
			printf ("MiniShell: syntax error near ");
			printf("unexpected token `%c'\n", buffer[i]);
			return (1);
		}
		if (check_parenthesis_norm(buffer, &i, &j))
			return (1);
		i++;
	}
	return (0);
}
