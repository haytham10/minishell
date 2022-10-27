/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmokhtar <hmokhtar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 12:57:49 by amsenhaj          #+#    #+#             */
/*   Updated: 2022/10/18 12:49:02 by hmokhtar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	size_buffer(char *buffer)
{
	int	i;

	i = 0;
	while (((buffer[i] <= 9 && buffer[i] >= 13) || buffer[i] != 32)
		&& buffer[i] && buffer[i] != '$' && buffer[i] != '\"' \
			&& buffer[i] != '\'' && buffer[i] != '|')
		i++;
	return (i);
}

char	*p_arg(char *buffer, t_exe *exe)
{
	char	*str;
	int		i;

	i = 0;
	str = buffer;
	exe->arg->arg = (char *)ft_malloc(size_buffer(str) + 1);
	if (!exe->arg->arg)
		return (NULL);
	while (i < size_buffer(str))
	{
		exe->arg->arg[i] = *buffer;
		i++;
		buffer++;
	}
	exe->arg->arg[i] = 0;
	return (buffer);
}

void	new_arg(t_exe *exec)
{
	t_args	*tmp;

	tmp = ft_malloc(sizeof(t_args));
	if (!tmp)
		return ;
	tmp->head = exec->arg->head;
	tmp->next = NULL;
	tmp->arg = NULL;
	exec->arg->next = tmp;
	exec->arg = tmp;
}

char	*only_arg(char *buffer, t_exe *exe)
{
	char	*tmp;

	tmp = NULL;
	if (exe->arg->arg != NULL)
		new_arg(exe);
	while (((*buffer <= 9 && *buffer >= 13) || *buffer != 32) \
		&& *buffer != '\0' && *buffer != '|')
	{
		if (*buffer == '\"')
			buffer = p_quotes2(++buffer, exe);
		else if (*buffer == '\'')
			buffer = p_quotes(++buffer, exe);
		else if (*buffer == '$')
			buffer = p_env(buffer, exe);
		else if (((*buffer <= 9 && *buffer >= 13) || (*buffer != 32)) \
			&& *buffer)
			buffer = p_arg(buffer, exe);
		tmp = join_arg(tmp, exe->arg->arg);
	}
	exe->arg->arg = tmp;
	return (buffer);
}

void	init_arg(t_exe *exe)
{
	t_args	*tmp;

	tmp = ft_malloc(sizeof(t_args));
	if (!tmp)
		return ;
	tmp->head = tmp;
	tmp->next = NULL;
	tmp->arg = NULL;
	exe->arg = tmp;
}
