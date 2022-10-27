/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmokhtar <hmokhtar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 18:49:39 by amsenhaj          #+#    #+#             */
/*   Updated: 2022/10/18 18:03:32 by hmokhtar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/minishell.h"

void	display_prompt(void)
{
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	ft_signal(t_env	*envir)
{
	signal(SIGINT, sighandler);
	signal(SIGQUIT, SIG_IGN);
	handle_ctrl_c(4000, envir);
	handle_ctrl_c(5000, NULL);
	handle_ctrl_qu(5000, NULL);
}

void	sighandler(int signal)
{
	if (signal == SIGINT)
		handle_ctrl_c(signal, NULL);
	if (signal == SIGQUIT)
		handle_ctrl_qu(signal, NULL);
}

void	handle_ctrl_c(int signal, void *ptr)
{
	static pid_t	*saved = NULL;
	static t_env	*envir = NULL;
	int				i;

	i = -1;
	if (signal == 4000)
		envir = (t_env *)ptr;
	if (signal == 5000)
		saved = (pid_t *)ptr;
	if (signal == SIGINT)
	{
		if (saved == NULL)
		{
			display_prompt();
			envir->status = 1;
		}
		else
		{
			while (saved[++i])
				kill(saved[i], SIGTERM);
			printf("\n");
			saved = NULL;
		}
	}
}

void	handle_ctrl_qu(int signal, int *ptr)
{
	static int	*saved = NULL;
	int			i;

	i = 0;
	if (signal == 5000)
		saved = ptr;
	if (signal == SIGQUIT)
	{
		if (saved != NULL)
		{
			printf("Quit\n");
			while (saved[i])
			{
				kill(saved[i], SIGTERM);
				i++;
			}
			saved = NULL;
		}
	}
}
