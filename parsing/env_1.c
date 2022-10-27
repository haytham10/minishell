/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmokhtar <hmokhtar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 21:07:51 by amsenhaj          #+#    #+#             */
/*   Updated: 2022/10/11 00:08:59 by hmokhtar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*first_env(void)
{
	t_list	*node;

	node = ft_malloc(sizeof(t_list));
	if (!node)
		return (NULL);
	node->name = NULL;
	node->value = NULL;
	node->head = node;
	node->next = NULL;
	return (node);
}

void	init_env(char	**env, t_env	*envr)
{
	envr->envr = env;
	envr->l_envr = first_env();
	envr->status = 0;
}
