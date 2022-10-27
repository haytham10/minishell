/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmokhtar <hmokhtar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 17:02:46 by hmokhtar          #+#    #+#             */
/*   Updated: 2022/10/18 15:46:21 by hmokhtar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_exe	*new_exe(t_exe *exe)
{
	t_exe	*tmp;

	tmp = ft_malloc(sizeof(t_exe));
	if (!tmp)
		return (NULL);
	tmp->head = exe->head;
	tmp->next = NULL;
	tmp->arg = NULL;
	tmp->cmd = NULL;
	tmp->option = NULL;
	tmp->stdin = NULL;
	tmp->stdout = NULL;
	tmp->envr = exe->envr;
	tmp->stdin2 = NULL;
	tmp->stdout2 = NULL;
	exe->next = tmp;
	return (tmp);
}

t_exe	*init_exe(void)
{
	t_exe	*tmp;

	tmp = ft_malloc(sizeof(t_exe));
	if (!tmp)
		return (NULL);
	tmp->cmd = NULL;
	tmp->option = NULL;
	tmp->args = NULL;
	tmp->arg = NULL;
	tmp->stdin = NULL;
	tmp->stdout = NULL;
	tmp->stdin2 = NULL;
	tmp->stdout2 = NULL;
	tmp->head = tmp;
	tmp->next = NULL;
	return (tmp);
}
