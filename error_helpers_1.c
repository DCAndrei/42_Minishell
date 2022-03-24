/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_helpers_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtrietz <mtrietz@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 09:41:14 by acretu            #+#    #+#             */
/*   Updated: 2022/03/22 14:47:09 by mtrietz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_file_error(char *file, t_each **c, t_status *sh)
{
	char	*str;

	str = ft_strdup(file);
	ft_free_double(&sh->envp_2);
	ft_free_pipes(&sh->pipes, sh->max);
	ft_lstclear(&sh->sh_env, free);
	ft_free_full_struct(&c);
	errmsg(str, NULL, strerror(errno), errno);
	free(str);
	rl_clear_history();
	exit (errno);
}

void	ft_file_error_no_exit(char *file, t_status *sh)
{
	char	*str;

	str = ft_strdup(file);
	sh->v_exit = errmsg(str, NULL, strerror(errno), errno);
	free (str);
}

void	ft_pipe_fork_error(char c)
{
	if (c == 'p')
		perror(SHELLNAME);
	else if (c == 'f')
		perror(SHELLNAME);
	else if (c == 'd')
		perror(SHELLNAME);
	else if (c == 'm')
		perror(SHELLNAME);
	rl_clear_history();
	exit(errno);
}

void	ft_cmd_error(t_each **c, int i)
{
	if (c[i]->cmmd[0] == NULL)
		exit (1);
	if (ft_strchr(c[i]->cmmd[0], '/'))
	{
		errmsg(c[i]->cmmd[0], NULL, "No such file or directory", 1);
		ft_free_full_struct(&c);
		rl_clear_history();
		exit (1);
	}
	else
	{
		errmsg(c[i]->cmmd[0], NULL, "command not found", 127);
		ft_free_full_struct(&c);
		rl_clear_history();
		exit (127);
	}
}

void	ft_error(int fd)
{
	dup2(fd, STDOUT_FILENO);
	perror(SHELLNAME);
	rl_clear_history();
	exit(127);
}
