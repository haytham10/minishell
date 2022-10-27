/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_cmd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsenhaj <amsenhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 01:52:08 by hmokhtar          #+#    #+#             */
/*   Updated: 2022/09/27 07:43:37 by amsenhaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*p_cmd(char *buffer, t_exe *exe)
{
	buffer = only_arg(buffer, exe);
	if (exe->arg->arg == NULL)
		return (buffer);
	if (ft_strcmp(exe->arg->arg, ""))
	{
		free(exe->arg->arg);
		exe->arg->arg = NULL;
		while ((*buffer >= 9 && *buffer <= 13) || *buffer == 32)
			buffer++;
		buffer = p_cmd(buffer, exe);
	}
	else
	{
		exe->cmd = join_arg(exe->arg->arg, NULL);
		exe->arg->arg = NULL;
	}
	return (buffer);
}
