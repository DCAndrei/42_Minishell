/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_helpers_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtrietz <mtrietz@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 12:01:55 by acretu            #+#    #+#             */
/*   Updated: 2022/03/22 14:54:13 by mtrietz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_iteration_lines(char *limiter, int *fd)
{
	char	*line;
	int		i;

	close (fd[0]);
	i = 0;
	while (i < 10000000)
		i += 1;
	write(1, "> ", 2);
	line = get_next_line(STDIN_FILENO);
	while (line != NULL)
	{
		if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0)
		{
			free(line);
			close(fd[1]);
			free (limiter);
			rl_clear_history();
			exit(EXIT_SUCCESS);
		}
		write(fd[1], line, ft_strlen(line));
		free(line);
		write(1, "> ", 2);
		line = get_next_line(STDIN_FILENO);
	}
}

void	ft_get_lines(char *limiter, t_status *sh, t_each **c)
{
	int		fd[2];
	int		pid;
	char	*limit;

	limit = ft_strdup(limiter);
	if (pipe(fd) == -1)
		ft_pipe_fork_error('p');
	pid = fork();
	if (pid == 0)
	{
		ft_free_full_struct(&c);
		ft_free_pipes(&sh->pipes, sh->max);
		ft_lstclear(&sh->sh_env, free);
		ft_free_double(&sh->envp_2);
		ft_iteration_lines(limit, fd);
	}
	else
	{
		free (limit);
		close (fd[1]);
		if (dup2(fd[0], STDIN_FILENO) == -1)
			ft_pipe_fork_error('d');
		close (fd[0]);
		waitpid(pid, NULL, 0);
	}
}

void	ft_gnl_built(char *limiter)
{
	char	*line;

	write(1, "> ", 2);
	line = get_next_line(STDIN_FILENO);
	while (line != NULL)
	{
		if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0)
		{
			free(line);
			return ;
		}
		free(line);
		write(1, "> ", 2);
		line = get_next_line(STDIN_FILENO);
	}
}
