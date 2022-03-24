/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acretu <acretu@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 12:24:07 by acretu            #+#    #+#             */
/*   Updated: 2022/03/22 12:43:28 by acretu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exec_built_in(t_status *sh, t_each **c)
{
	sh->built = ft_is_builtin(c[0]->cmmd[0]);
	if (sh->built == 7 && sh->max == 1)
	{
		sh->v_exit = exit_cmd(&sh->sh_env, c[0]->cmmd, &c, sh->v_exit);
		ft_free_full_struct(&c);
		return (0);
	}
	else if (sh->built != 0 && sh->max == 1)
	{
		ft_built_redir(sh, c);
		ft_free_full_struct(&c);
		return (0);
	}
	return (1);
}

static void	ft_fd_handle_2(t_status *sh, t_each **c, int i);

void	ft_fd_handle(t_status *sh, t_each **c, int i)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (c[i]->r_ii > 0 && c[i]->lst_red == 1)
		ft_get_lines(c[i]->ii_file, sh, c);
	if (sh->max == 1)
	{
		close (sh->pipes->pipes[0][0]);
		close (sh->pipes->pipes[0][1]);
	}
	else
		ft_fd_handle_2(sh, c, i);
	ft_modify_fd(c, sh, i);
	if (sh->fd_out > 0)
	{
		if (dup2(sh->fd_out, STDOUT_FILENO) == -1)
			ft_pipe_fork_error('d');
		close (sh->fd_out);
	}
}

static void	ft_fd_handle_2(t_status *sh, t_each **c, int i)
{
	ft_close_pipes(sh->pipes->pipes, sh->max, i);
	if (i == 0)
	{
		close (sh->pipes->pipes[0][0]);
		dup2(sh->pipes->pipes[1][1], STDOUT_FILENO);
		close (sh->pipes->pipes[1][1]);
	}
	else if (i == sh->max - 1)
	{
		if (c[i]->r_ii <= 0)
			dup2(sh->pipes->pipes[i][0], STDIN_FILENO);
		close (sh->pipes->pipes[i][0]);
	}
	else
	{
		if (c[i]->r_ii <= 0)
			dup2(sh->pipes->pipes[i][0], STDIN_FILENO);
		close (sh->pipes->pipes[i][0]);
		dup2(sh->pipes->pipes[i + 1][1], STDOUT_FILENO);
		close(sh->pipes->pipes[i + 1][1]);
	}
}

void	ft_exec_pipe(t_each **c, t_status *sh, int i)
{
	ft_fd_handle(sh, c, i);
	if (sh->fd_in > 0)
	{
		if (dup2(sh->fd_in, STDIN_FILENO) == -1)
			ft_pipe_fork_error('d');
		close (sh->fd_in);
	}
	if (ft_is_builtin(c[i]->cmmd[0]) != 0)
	{
		sh->v_exit = ft_return_built(ft_is_builtin(c[i]->cmmd[0]), \
		sh, c[i], &c);
		ft_free_full_struct(&c);
		ft_free_pipes(&sh->pipes, sh->max);
		ft_free_double(&sh->envp_2);
		ft_lstclear(&sh->sh_env, free);
		exit (sh->v_exit);
	}
	if (c[i]->cmmd[0] == NULL)
		exit (0);
	ft_execute_command(c, sh, i);
}
