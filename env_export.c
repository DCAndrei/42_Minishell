/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtrietz <mtrietz@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 14:29:59 by mtrietz           #+#    #+#             */
/*   Updated: 2022/03/13 07:39:45 by mtrietz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		check_error(char *cmd[]);
static t_list	*env_get_entry(t_list *sh_env, char *searchstr);
static void		put_value(t_list **sh_env, char *cmd, char **searchstr);
static void		search_and_update(t_list **sh_env, char **cmd, int *exit_code);

int	env_export(t_list **sh_env, char *cmd[])
{
	int		i;
	int		exit_code;

	exit_code = 0;
	i = check_error(cmd);
	if (i)
		return (i);
	if (ft_arrlen(cmd) == 1)
	{	
		env_print(*sh_env, 1);
		return (0);
	}
	search_and_update(sh_env, cmd, &exit_code);
	return (exit_code);
}

static t_list	*env_get_entry(t_list *sh_env, char *searchstr)
{
	while (sh_env)
	{
		if (!ft_strncmp(sh_env->content, searchstr, ft_strlen(searchstr)))
			return (sh_env);
		sh_env = sh_env->next;
	}
	return (NULL);
}

static int	check_error(char *cmd[])
{
	int		err;

	if (!cmd[0])
		return (52);
	err = chk_inval_opt(cmd);
	if (err)
		return (err);
	return (0);
}

static void	put_value(t_list **sh_env, char *cmd, char **searchstr)
{
	t_list	*entry;
	char	*s_str;
	char	*tmp;

	s_str = ft_strjoin(*searchstr, "=");
	free(*searchstr);
	entry = env_get_entry(*sh_env, s_str);
	free(s_str);
	if (entry)
	{
		tmp = entry->content;
		entry->content = ft_strdup(cmd);
		free(tmp);
	}
	else
		ft_lstadd_back(sh_env, ft_lstnew(ft_strdup(cmd)));
}

static void	search_and_update(t_list **sh_env, char **cmd, int *exit_code)
{
	int		i;
	char	*searchstr;

	i = 0;
	while (cmd[++i])
	{
		if (!ft_strchr(cmd[i], '='))
			continue ;
		searchstr = ft_get_key(cmd[i], '=');
		if (!ft_is_bashname(searchstr))
		{
			*exit_code = 1;
			ft_putstr_fd(SHELLNAME, 2);
			ft_putstr_fd(": export: \'", 2);
			ft_putstr_fd(cmd[i], 2);
			ft_putendl_fd("\': not a valid identifier", 2);
			free(searchstr);
			continue ;
		}
		put_value(sh_env, cmd[i], &searchstr);
	}
}
