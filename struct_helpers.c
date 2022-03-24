/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acretu <acretu@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 11:29:06 by acretu            #+#    #+#             */
/*   Updated: 2022/03/21 14:23:05 by acretu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_sh_init(t_status *sh, char *envp[])
{
	if (sh->sh_env == NULL)
	{
		sh->sh_env = env_init(envp);
		sh->v_exit = 0;
	}
	if (sh->v_exit == 0)
		sh->v_exit = 0;
	sh->w_status = 0;
	sh->fd_in = 0;
	sh->fd_out = 0;
	sh->pipes = NULL;
	sh->envp_2 = NULL;
	sh->fd_stdout = 0;
}
