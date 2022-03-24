/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtrietz <mtrietz@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 13:18:10 by mtrietz           #+#    #+#             */
/*   Updated: 2022/03/22 12:10:29 by mtrietz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_error(t_list **sh_env, char *cmd[]);
static void	search_and_del(t_list **sh_env, char *searchstr);

int	env_unset(t_list **sh_env, char *cmd[])
{
	int		i;
	int		exit_code;
	char	*searchstr;

	exit_code = check_error(sh_env, cmd);
	if (exit_code)
		return (exit_code);
	i = 1;
	while (cmd[i])
	{
		if (!ft_is_bashname(cmd[i]))
			exit_code = errmsg(cmd[0], cmd[i], "not a valid identifier", 1);
		else
		{
			searchstr = ft_strjoin(cmd[i], "=");
			search_and_del(sh_env, searchstr);
			free(searchstr);
		}
		i++;
	}
	return (exit_code);
}

static int	check_error(t_list **sh_env, char *cmd[])
{
	int		err;

	if (!sh_env || ft_lstsize(*sh_env) == 0)
		return (51);
	if (!cmd[0] || !cmd[1])
		return (52);
	err = chk_inval_opt(cmd);
	if (err)
		return (err);
	return (0);
}

static void	search_and_del(t_list **sh_env, char *searchstr)
{
	t_list	*last;
	t_list	*curr;
	t_list	*tmp;

	curr = *sh_env;
	last = *sh_env;
	while (curr)
	{
		if (!ft_strncmp(curr->content, searchstr, ft_strlen(searchstr)))
		{
			tmp = curr;
			if (curr == *sh_env)
				*sh_env = curr->next;
			else
				last->next = curr->next;
			ft_lstdelone(tmp, free);
			break ;
		}
		last = curr;
		curr = curr->next;
	}
}
