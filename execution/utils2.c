/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmokhtar <hmokhtar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 20:17:06 by amsenhaj          #+#    #+#             */
/*   Updated: 2022/10/18 15:52:35 by hmokhtar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/minishell.h"

int	init_pipe(t_pipe *pipee)
{
	int	i;

	i = -1;
	pipee->fd_pipe = ft_malloc(sizeof(int) * pipee->nb_pipes * 2);
	if (!pipee->fd_pipe)
		return (1);
	while (++i < pipee->nb_pipes)
		if (pipe(pipee->fd_pipe + i * 2) == -1)
			return (1);
	pipee->pid = ft_malloc(sizeof(int) * (pipee->nb_pipes + 2));
	if (!pipee->pid)
		return (1);
	pipee->pid[pipee->nb_pipes + 1] = 0;
	return (0);
}

void	close_fd_pipe(t_pipe *pipee)
{
	int	i;

	i = -1;
	while (++i < pipee->nb_pipes * 2)
		close(pipee->fd_pipe[i]);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (s1[i] != s2[i] || !s1[i] || !s2[i])
			return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
		i++;
	}
	return (0);
}

void	fd_close(int fd_0, int fd_1, t_exe *exe)
{
	if (exe->stdin != 0 || exe->stdin2 != 0)
		close(fd_0);
	if (exe->stdout != 0 || exe->stdout2 != 0)
		close(fd_1);
}

int	ft_lstsize(t_exe *lst)
{
	int	i;

	i = 0;
	while (lst != NULL)
	{
		lst = lst->next;
		++i;
	}
	return (i);
}
