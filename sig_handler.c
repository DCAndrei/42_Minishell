/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtrietz <mtrietz@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 20:29:08 by mtrietz           #+#    #+#             */
/*   Updated: 2022/03/14 11:54:54 by mtrietz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_sigint_rl(int signum)
{
	signum += 0;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	handle_sigint_parent(int signum)
{
	signum += 0;
	write(1, "\n", 1);
}

void	handle_sigquit_parent(int signum)
{
	signum += 0;
	write(1, "Quit\n", 5);
}
