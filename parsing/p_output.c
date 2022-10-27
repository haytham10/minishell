/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_output.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmokhtar <hmokhtar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 03:00:30 by hmokhtar          #+#    #+#             */
/*   Updated: 2022/10/18 15:47:14 by hmokhtar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*p_output2(char *buffer, t_exe *exe)
{
	while ((*buffer >= 9 && *buffer <= 13) || *buffer == 32)
		buffer++;
	buffer = only_arg(buffer, exe);
	exe->stdout2 = join_arg(exe->arg->arg, NULL);
	exe->arg->arg = NULL;
	return (buffer);
}

char	*p_output(char *buffer, t_exe *exe)
{
	if (*buffer == '>')
		buffer = p_output2(++buffer, exe);
	else
	{
		while ((*buffer >= 9 && *buffer <= 13) || *buffer == 32)
			buffer++;
		buffer = only_arg(buffer, exe);
		exe->stdout = join_arg(exe->arg->arg, NULL);
		exe->arg->arg = NULL;
	}
	return (buffer);
}
