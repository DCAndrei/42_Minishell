/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_handle_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acretu <acretu@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 15:48:21 by acretu            #+#    #+#             */
/*   Updated: 2022/03/21 22:00:08 by acretu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_return_fd(t_each **elem, t_status *sh, int i);

void	ft_modify_fd(t_each **elem, t_status *sh, int i)
{
	if (elem[i]->r_i > 0)
	{
		sh->fd_in = open(elem[i]->i_file, O_RDONLY, 0777);
	}
	if (elem[i]->r_o > 0)
	{
		sh->fd_out = open(elem[i]->o_file, O_WRONLY | O_TRUNC | O_CREAT, 0777);
	}
	if (elem[i]->r_oo > 0)
	{
		sh->fd_out = open(elem[i]->o_file, O_WRONLY | O_APPEND | O_CREAT, 0777);
	}
	ft_return_fd(elem, sh, i);
}

int	ft_modify_fd_2(t_each *elem, int *fd_in, int *fd_out)
{
	if (elem->r_i > 0)
	{
		*fd_in = open(elem->i_file, O_RDONLY, 0777);
	}
	if (elem->r_o > 0)
	{
		*fd_out = open(elem->o_file, O_WRONLY | O_TRUNC | O_CREAT, 0777);
	}
	if (elem->r_oo > 0)
	{
		*fd_out = open(elem->o_file, O_WRONLY | O_APPEND | O_CREAT, 0777);
	}
	if (*fd_in < 0)
		return (1);
	if (*fd_out < 0)
		return (2);
	return (0);
}

int	ft_test_file(char *str, int type)
{
	int		fd;

	fd = 0;
	if (str == NULL)
		return (1);
	if (type == 1)
		fd = open(str, O_RDONLY, 0777);
	else if (type == 2)
		fd = open(str, O_WRONLY | O_TRUNC | O_CREAT, 0777);
	else
		fd = open(str, O_WRONLY | O_APPEND | O_CREAT, 0777);
	if (fd < 0)
		return (type);
	else
		close (fd);
	return (0);
}

static void	ft_return_fd(t_each **elem, t_status *sh, int i)
{
	if (sh->max == 1 && ft_is_builtin(elem[i]->cmmd[0]))
	{
		if (sh->fd_in < 0)
			ft_file_error_no_exit(elem[i]->i_file, sh);
		if (sh->fd_out < 0)
			ft_file_error_no_exit(elem[i]->o_file, sh);
	}
	else
	{
		if (sh->fd_in < 0)
		{
			ft_file_error(elem[i]->i_file, elem, sh);
		}
		if (sh->fd_out < 0)
		{
			ft_file_error(elem[i]->o_file, elem, sh);
		}
	}
}
