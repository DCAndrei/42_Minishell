/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_helpers_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acretu <acretu@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 13:04:23 by acretu            #+#    #+#             */
/*   Updated: 2022/03/22 11:02:07 by acretu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_parent_proc(t_status *sh, t_each **c, int i)
{
	ft_close_all_pipes(sh->pipes->pipes, sh->max);
	signal(SIGINT, handle_sigint_parent);
	signal(SIGQUIT, handle_sigquit_parent);
	i = 0;
	while (i < sh->max)
	{
		sh->v_exit = 0;
		waitpid(sh->pipes->pid[i], &sh->w_status, 0);
		if (i == (sh->max - 1) && ((WIFEXITED(sh->w_status) || \
		WIFSIGNALED(sh->w_status))))
		{
			if (WIFEXITED(sh->w_status))
				sh->v_exit = WEXITSTATUS(sh->w_status);
			if (WIFSIGNALED(sh->w_status))
				sh->v_exit = 128 + WTERMSIG(sh->w_status);
		}
		i++;
	}
	ft_free_full_struct(&c);
	ft_free_double(&sh->envp_2);
	ft_free_pipes(&sh->pipes, sh->max);
}

void	ft_pipeline(t_status *sh, t_each **c)
{
	int		i;

	if (ft_exec_built_in(sh, c) == 1)
	{
		sh->pipes = ft_create_pipes(sh->max);
		i = 0;
		while (i < sh->max)
		{
			if (pipe(sh->pipes->pipes[i]) == -1)
				ft_pipe_fork_error('p');
			i += 1;
		}
		i = 0;
		while (i < sh->max)
		{
			sh->pipes->pid[i] = fork();
			if (sh->pipes->pid[i] == -1)
				ft_pipe_fork_error('p');
			if (sh->pipes->pid[i] == 0)
				ft_exec_pipe(c, sh, i);
			i += 1;
		}	
		ft_parent_proc(sh, c, i);
	}
}

void	ft_built_redir(t_status *sh, t_each **c)
{
	if (c[0]->r_ii > 0)
		ft_gnl_built(c[0]->ii_file);
	sh->fd_stdout = dup(1);
	if (sh->fd_stdout == -1)
		ft_pipe_fork_error('d');
	ft_modify_fd(c, sh, 0);
	if (sh->fd_out > 0)
	{
		if (dup2(sh->fd_out, STDOUT_FILENO) == -1)
			ft_pipe_fork_error('d');
		close (sh->fd_out);
	}
	sh->v_exit = ft_return_built(sh->built, sh, c[0], &c);
	if (dup2(sh->fd_stdout, STDOUT_FILENO) == -1)
		ft_pipe_fork_error('d');
	close (sh->fd_stdout);
}

void	ft_execute_command(t_each **c, t_status *sh, int i)
{
	ft_free_double(&sh->envp_2);
	ft_free_pipes(&sh->pipes, sh->max);
	ft_lstclear(&sh->sh_env, free);
	if (access(c[i]->cmmd[0], F_OK) == 0 && \
	ft_strchr(c[i]->cmmd[0], '/') != NULL)
	{
		if (c[i]->lst_red != 0)
		{
			if (execve(c[i]->cmmd[0], c[i]->cmmd, c[i]->env) == -1)
				ft_cmd_error(c, i);
		}
		else
			exit (0);
	}
	else
	{
		if (ft_check_path(c[i]->cmmd, c[i]->env) == 1)
			ft_cmd_error(c, i);
		if (c[i]->lst_red != 0)
			ft_execute(c, i);
		else
			exit (0);
	}
}
