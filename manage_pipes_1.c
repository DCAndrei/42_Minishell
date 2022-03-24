/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_pipes_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acretu <acretu@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 21:32:09 by acretu            #+#    #+#             */
/*   Updated: 2022/03/21 21:04:12 by acretu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_execute(t_each **c, int i)
{
	char	*path;

	path = ft_get_path(c[i]->cmmd[0], c[i]->env);
	if (execve(path, c[i]->cmmd, c[i]->env) == -1)
	{
		free(path);
		ft_cmd_error(c, i);
	}
}
