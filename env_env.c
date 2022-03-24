/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtrietz <mtrietz@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 12:37:41 by mtrietz           #+#    #+#             */
/*   Updated: 2022/03/18 14:29:20 by mtrietz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env_env(t_list *sh_env, char *cmd[], int fd)
{
	if (ft_arrlen(cmd) != 1)
		return (errmsg(cmd[0], NULL, "No options or arguments allowed", 1));
	while (sh_env && sh_env->content)
	{
		ft_putendl_fd((char *) sh_env->content, fd);
		sh_env = sh_env->next;
	}
	return (0);
}
