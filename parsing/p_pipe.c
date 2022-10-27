/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_pipe.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmokhtar <hmokhtar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 02:47:09 by hmokhtar          #+#    #+#             */
/*   Updated: 2022/10/18 15:47:54 by hmokhtar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*next_cmd(char *buffer, t_exe *exe)
{
	exe = new_exe(exe);
	init_arg(exe);
	while (*buffer)
	{
		while ((*buffer >= 9 && *buffer <= 13) || *buffer == 32)
			buffer++;
		if ((*buffer <= 9 && *buffer >= 13) || (*buffer != 32 && *buffer))
			buffer = handle(buffer, exe);
	}
	exe->arg = exe->arg->head;
	exe = exe->head;
	return (buffer);
}

char	*p_pipe(char *buffer, t_exe *exe)
{
	while ((*buffer >= 9 && *buffer <= 13) || (*buffer == 32 && *buffer))
		buffer++;
	if (*buffer != '\0')
		buffer = next_cmd(buffer, exe);
	return (buffer);
}
