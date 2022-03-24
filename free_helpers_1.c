/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_helpers_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acretu <acretu@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 09:28:45 by acretu            #+#    #+#             */
/*   Updated: 2022/03/20 14:43:38 by acretu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_pipes(t_pipes **pipes, int size)
{
	int		i;

	if (*pipes == NULL)
		return ;
	free ((*pipes)->pid);
	i = 0;
	while (i < size)
	{
		free ((*pipes)->pipes[i]);
		i += 1;
	}
	free ((*pipes)->pipes);
	free (*pipes);
	*pipes = NULL;
}
