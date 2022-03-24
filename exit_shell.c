/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acretu <acretu@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 18:58:32 by mtrietz           #+#    #+#             */
/*   Updated: 2022/03/21 15:52:44 by acretu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exit_cmd(t_list **sh_env, char *cmd[], t_each ***c, int v_exit)
{
	int	errnum;

	write(1, "exit\n", 5);
	if (cmd[1])
	{
		if (!ft_isstrnum(cmd[1]))
			return (errmsg(cmd[0], cmd[1], "numeric argument required", 2));
		if (cmd[2])
			return (errmsg(cmd[0], NULL, "too many arguments", 1));
		errnum = ft_atoi(cmd[1]);
		exit_shell(sh_env, errnum, c);
	}
	else
		exit_shell(sh_env, v_exit, c);
	return (0);
}

void	exit_shell(t_list **sh_env, int exit_no, t_each ***c)
{
	ft_lstclear(sh_env, free);
	rl_clear_history();
	ft_free_full_struct(c);
	exit(exit_no);
}
