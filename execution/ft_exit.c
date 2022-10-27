/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmokhtar <hmokhtar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 08:29:55 by amsenhaj          #+#    #+#             */
/*   Updated: 2022/09/29 23:40:38 by hmokhtar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/minishell.h"

int	str_isdigit(char *s)
{
	int	i;

	i = -1;
	while (s[++i])
	{
		if (s[i] < '0' || s[i] > '9')
			return (0);
	}
	return (1);
}

unsigned long long	ft_cnv(char *str)
{
	int					i;
	int					sign;
	unsigned long long	result;

	i = 0;
	sign = 1;
	result = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + str[i] - '0';
		i++;
	}
	return (sign * result);
}

int	ft_exit_hahia(t_exe *exe, t_env *env)
{
	if (!exe->args[1])
		return (write(1, "exit\n", 5), ft_exit(exe, env));
	if (str_isdigit(exe->args[1]) && !exe->args[2] && \
			ft_cnv(exe->args[1]) <= ULLONG_MAX)
	{
		env->status = ft_cnv(exe->args[1]) % 256;
		return (write(1, "exit\n", 5), ft_exit(exe, env));
	}
	if (!str_isdigit(exe->args[1]))
	{
		env->status = 255;
		printf("exit\nexit: %s: numeric argument required", exe->args[1]);
		ft_exit(exe, env);
	}
	else
	{
		env->status = 1;
		printf("exit\nminishell: exit: too many arguments\n");
	}
	return (6);
}
