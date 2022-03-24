/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtsin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acretu <acretu@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 16:28:07 by acretu            #+#    #+#             */
/*   Updated: 2022/03/22 12:38:18 by acretu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_builtin(char *str)
{
	if (str == NULL)
		return (0);
	if (ft_strncmp(str, "echo", 5) == 0)
		return (1);
	else if (ft_strncmp(str, "cd", 3) == 0)
		return (2);
	else if (ft_strncmp(str, "pwd", 4) == 0)
		return (3);
	else if (ft_strncmp(str, "export", 7) == 0)
		return (4);
	else if (ft_strncmp(str, "unset", 6) == 0)
		return (5);
	else if (ft_strncmp(str, "env", 4) == 0)
		return (6);
	else if (ft_strncmp(str, "exit", 5) == 0)
		return (7);
	else
		return (0);
}

int	ft_return_built(int i, t_status *sh, t_each *elem, t_each ***c)
{
	int		v_exit;

	v_exit = 0;
	if (i == 1)
		v_exit = echo(elem->cmmd, STDOUT_FILENO, sh, elem);
	else if (i == 2)
		v_exit = cd(&sh->sh_env, elem->cmmd);
	else if (i == 3)
		v_exit = pwd(1, elem->cmmd);
	else if (i == 4)
		v_exit = env_export(&sh->sh_env, elem->cmmd);
	else if (i == 5)
		v_exit = env_unset(&sh->sh_env, elem->cmmd);
	else if (i == 6)
		v_exit = env_env(sh->sh_env, elem->cmmd, 1);
	else if (i == 7)
		exit_cmd(&sh->sh_env, elem->cmmd, c, 0);
	return (v_exit);
}
