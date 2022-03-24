/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acretu <acretu@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 07:00:36 by mtrietz           #+#    #+#             */
/*   Updated: 2022/03/21 12:36:42 by acretu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	echo(char **cmd, int fd, t_status *sh, t_each *elem)
{
	int	i;

	if (sh->fd_in < 0 || sh->fd_out < 0)
		return (sh->v_exit);
	i = 1;
	if (!cmd[1])
	{
		write(fd, "\n", 1);
		return (0);
	}
	if (cmd[1] && !ft_strcmp(cmd[1], "-n"))
		i = 2;
	while (cmd[i])
	{
		ft_putstr_fd(cmd[i], fd);
		i++;
		if (cmd[i] && (elem->r_o < 0 || elem->r_oo < 0))
			write(fd, " ", 1);
	}
	if (cmd[1] && ft_strcmp(cmd[1], "-n"))
		write(fd, "\n", 1);
	return (0);
}
