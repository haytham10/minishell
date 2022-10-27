/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmokhtar <hmokhtar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 23:57:57 by hmokhtar          #+#    #+#             */
/*   Updated: 2022/10/18 09:31:48 by hmokhtar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/minishell.h"

void	change_env(t_env *env, char *name, char *value)
{
	t_list	*tmp;

	tmp = env->l_envr;
	while (tmp)
	{
		if (strcmp(tmp->name, name) == 0)
		{
			free(tmp->value);
			tmp->value = ft_strdup(value);
			return ;
		}
		tmp = tmp->next;
	}
}

void	change_pwd(t_env *env, t_exe *exe)
{
	char	*pwd;
	char	*oldpwd;

	oldpwd = get_value("PWD", exe);
	pwd = getcwd(NULL, 0);
	change_env(env, "OLDPWD", oldpwd);
	change_env(env, "PWD", pwd);
	free(pwd);
}

int	cd(t_exe *exe, t_env *env)
{
	int	i;

	if (arg_len(exe->args) > 2)
		return (ft_error("cd:", "too many arguments"));
	if (exe->args[1] == NULL || strcmp(exe->args[1], " \t\n\v\f\r") == 0)
		i = chdir(get_value("HOME", exe));
	else if (ft_strncmp(exe->args[1], "-", 1) == 0)
	{
		if (ft_strcmp(get_value("OLDPWD", exe), get_value("PWD", exe)))
			return (ft_error("cd : ", "OLDPWD not set"));
		i = chdir(get_value("OLDPWD", exe));
	}
	else
		i = chdir(exe->args[1]);
	if (i == -1)
	{
		env->status = 1;
		return (ft_error(exe->args[1], ": no such file or directory"));
	}
	else
	{
		change_pwd(env, exe);
		env->status = 0;
	}
	return (0);
}
