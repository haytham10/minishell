/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmokhtar <hmokhtar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 13:13:10 by amsenhaj          #+#    #+#             */
/*   Updated: 2022/10/18 16:01:13 by hmokhtar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	norm_fix(char **env, t_env *envir)
{
	if (env[0] == NULL)
	{
		envir->l_envr = first_env();
		create_env(envir);
	}
	else
	{
		init_env(env, envir);
		fill_env(env, envir);
	}
}

void	free_all(char *buffer, t_exe *exec)
{
	free_kolchi(exec);
	free(buffer);
	return ;
}

void	sir_lfo9(t_env *envir, t_exe *exe)
{
	char	*buffer;

	while (1)
	{
		ft_signal(envir);
		exe = init_exe();
		exe->envr = envir;
		buffer = readline("\033[92m😎 Bash@Allah $> \033[97m");
		if (!buffer)
			ft_exit(exe, envir);
		if (buffer[0] != 0)
			add_history(buffer);
		if (check_parenthesis(buffer) || check_others(buffer) || \
			ft_check_options(buffer) || ft_valid_options(buffer) || !buffer[0])
		{
			free_all(buffer, exe);
			continue ;
		}
		parsing(buffer, exe);
		if (exe->cmd != NULL)
			execution(exe, envir);
		free_all(buffer, exe);
	}
}

int	main(int ac, char **av, char **env)
{
	t_env	envir;
	t_exe	*exec;

	exec = NULL;
	if (ac != 1 || !av)
		return ((write(1, "\033[91mError🙂3awd jreb\n", 25)), 1);
	norm_fix(env, &envir);
	sir_lfo9(&envir, exec);
	return (0);
}
