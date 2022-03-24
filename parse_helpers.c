/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acretu <acretu@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 11:57:48 by acretu            #+#    #+#             */
/*   Updated: 2022/03/22 13:08:14 by acretu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	get_cmline(t_line *line, t_list **sh_env, int v_exit, t_each ***c);
static void	ft_heredoc_fd(t_line *line, t_each ***c, t_status *sh);

int	ft_check_line(t_line *line, t_status *sh, t_each ***c)
{
	int		i;

	get_cmline(line, &sh->sh_env, sh->v_exit, c);
	sh->envp_2 = ft_lst2arr(sh->sh_env);
	line->tmp_v = ft_check_pipe_error(line->line);
	if (line->tmp_v != 0)
		return (line->tmp_v);
	ft_split_line(line->line, &line->commands);
	i = 0;
	while (line->commands[i] != NULL)
	{
		if (line->tmp_v == 0)
			line->tmp_v = ft_check_quotes(line->commands[i]);
		i += 1;
	}
	if (line->tmp_v != 0)
		ft_free_double(&line->commands);
	return (line->tmp_v);
}

void	ft_create_cmds(t_line *line, t_each ***c, t_status *sh)
{
	int		i;
	t_each	*tmp;

	ft_expand_var(line, sh);
	sh->max = 0;
	while (line->commands[sh->max] != NULL)
		sh->max += 1;
	*c = (t_each **)malloc(sizeof(t_each *) * (sh->max + 1));
	if (*c == NULL)
		ft_pipe_fork_error('m');
	(*c)[sh->max] = NULL;
	i = 0;
	while (line->commands[i] != NULL)
	{
		tmp = ft_devide_comm(&line->commands[i], sh->envp_2);
		tmp->pipes = i;
		tmp->max_pipes = sh->max;
		if (tmp->r_ii > 0)
			tmp->lst_red = 1;
		(*c)[i] = tmp;
		i += 1;
	}
	ft_heredoc_fd(line, c, sh);
}

static void	get_cmline(t_line *line, t_list **sh_env, int v_exit, t_each ***c)
{
	line->commands = NULL;
	line->line = NULL;
	line->line = readline ("minishell$ ");
	if (line->line == NULL)
	{
		rl_replace_line ("exit", 0);
		rl_redisplay();
		write(1, "\n", 1);
		exit_shell(sh_env, v_exit, c);
	}
}

void	ft_line_fail(t_line *line, t_status *sh)
{
	if (line->line != NULL && line->line[0] != '\0')
		add_history(line->line);
	free (line->line);
	ft_free_double(&sh->envp_2);
	sh->v_exit = line->tmp_v;
}

static void	ft_heredoc_fd(t_line *line, t_each ***c, t_status *sh)
{
	int		t;
	int		i;

	i = sh->max;
	t = 0;
	while (i-- > 0)
	{
		if ((*c)[i]->lst_red == 1 && t == 0)
			t = 1;
		else if ((*c)[i]->lst_red == 1)
			(*c)[i]->lst_red = 0;
	}
	i = 0;
	while (i < sh->max)
	{
		if ((*c)[i]->r_ii > 0 && (*c)[i]->lst_red == 0)
			ft_gnl_built((*c)[i]->ii_file);
		i += 1;
	}
	if (line->line != NULL && line->line[0] != '\0')
		add_history(line->line);
	if (line->line != NULL)
		free (line->line);
	ft_free_double(&(line)->commands);
	ft_free_double(&(sh)->envp_2);
}
