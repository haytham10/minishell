/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmokhtar <hmokhtar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 22:01:42 by amsenhaj          #+#    #+#             */
/*   Updated: 2022/10/11 00:20:21 by hmokhtar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/minishell.h"

int	ft_env(t_env *envr)
{
	t_list	*lst;

	lst = envr->l_envr;
	lst = lst->head;
	while (lst)
	{
		if (lst->value != NULL)
			printf("%s=%s\n", lst->name, lst->value);
		lst = lst->next;
	}
	envr->status = 0;
	return (0);
}
