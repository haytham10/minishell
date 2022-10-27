/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmokhtar <hmokhtar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 00:04:56 by hmokhtar          #+#    #+#             */
/*   Updated: 2022/10/11 00:08:59 by hmokhtar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/minishell.h"

int	arg_len(char **arg)
{
	int	i;

	i = 0;
	while (arg[i])
		i++;
	return (i);
}

int	add_env(t_list *list, char *name, char *value)
{
	list = list->head;
	while (list->next)
		list = list->next;
	list->next = ft_malloc(sizeof(t_list));
	if (!list->next)
		return (-1);
	list->next->head = list->head;
	list->next->name = name;
	list->next->value = value;
	list->next->next = NULL;
	return (0);
}

int	name_check(t_list *list, char *name, char *value)
{
	list = list->head;
	while (list)
	{
		if (strncmp(list->name, name, ft_strlen(name)) == 0)
		{
			free(list->name);
			free(list->value);
			list->value = value;
			list->name = name;
			return (0);
		}
		list = list->next;
	}
	return (-1);
}

char	*ft_strrcut(char *arg, char c)
{
	int		len;
	char	*str;
	int		i;
	int		j;

	j = -1;
	len = ft_strlen(arg);
	i = len;
	while (arg[--i] != c)
		;
	str = ft_malloc(len - i);
	if (!str)
		return (NULL);
	str[len - i - 1] = 0;
	while (arg[++i])
		str[++j] = arg[i];
	return (str);
}

char	*ft_strcut(char *arg, char c)
{
	int		i;
	int		len;
	char	*str;

	len = -1;
	while (arg[++len] != c)
		;
	str = ft_malloc(len + 1);
	if (!str)
		return (NULL);
	str[len] = 0;
	i = -1;
	while (++i < len)
		str[i] = arg[i];
	return (str);
}
