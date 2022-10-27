/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmokhtar <hmokhtar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 13:24:56 by amsenhaj          #+#    #+#             */
/*   Updated: 2022/10/17 18:00:10 by hmokhtar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*handle(char *buffer, t_exe *exe)
{
	if (*buffer == '>')
		buffer = p_output(++buffer, exe);
	else if (*buffer == '<')
		buffer = p_input(++buffer, exe);
	if (exe->cmd == NULL)
		buffer = p_cmd(buffer, exe);
	if (!exe->option && *buffer + 1 == '-')
		buffer = p_option(buffer, exe);
	else if (*buffer == '|')
		buffer = p_pipe(++buffer, exe);
	else if (((*buffer <= 9 && *buffer >= 13) || *buffer != 32) && *buffer)
		buffer = only_arg(buffer, exe);
	return (buffer);
}

void	parsing(char *buffer, t_exe *exe)
{
	init_arg(exe);
	while (*buffer)
	{
		while ((*buffer >= 9 && *buffer <= 13) || *buffer == 32)
			buffer++;
		if ((*buffer <= 9 && *buffer >= 13) || \
			(*buffer != 32 && *buffer))
			buffer = handle(buffer, exe);
	}
	exe->arg = exe->arg->head;
	exe = exe->head;
}
