/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmokhtar <hmokhtar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 23:57:23 by hmokhtar          #+#    #+#             */
/*   Updated: 2022/09/29 23:33:44 by hmokhtar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/minishell.h"

static void	output2(t_exe *exe, int len)
{
	int	i;

	i = 0;
	if (exe->option)
		printf("%s ", exe->option);
	while (++i < len - 1)
		printf("%s ", exe->args[i]);
	if (exe->args[i])
		printf("%s", exe->args[i]);
	printf("\n");
}

static	int	ft_bzaf(char *str)
{
	int	i;

	i = 1;
	if (str[0] == '-')
	{
		i++;
		while (str[i])
		{
			if (str[i] != 'n')
				return (1);
			i++;
		}
		if (str[i] == 0)
			return (0);
	}
	return (2);
}

int	echo(t_exe *exe, t_env *env)
{
	int	i;
	int	len;

	i = 1;
	len = arg_len(exe->args);
	if (ft_strcmp(exe->args[0], "/bin/echo") && !exe->args[1])
		return (write(1, "\n", 1), 0);
	if (ft_strcmp(exe->args[i], "-n") || !ft_bzaf(exe->args[i]))
	{
		i++;
		while (exe->args[i] && (ft_strcmp(exe->args[i], "-n") && \
			!ft_bzaf(exe->args[i])))
			i++;
		while (exe->args[i])
		{
			printf("%s ", exe->args[i]);
			i++;
		}
	}
	else
		output2(exe, len);
	env->status = 0;
	return (0);
}
