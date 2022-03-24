/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipes_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acretu <acretu@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 22:26:32 by acretu            #+#    #+#             */
/*   Updated: 2022/03/19 18:04:26 by acretu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_pipes	*ft_create_pipes(int size)
{
	int		i;
	t_pipes	*ret;

	ret = (t_pipes *)malloc(sizeof(t_pipes) * 1);
	if (ret == NULL)
		ft_pipe_fork_error('m');
	ret->pid = (int *)ft_calloc(size, sizeof(int));
	ret->pipes = (int **)malloc(sizeof(int *) * size);
	if (ret->pipes == NULL)
		ft_pipe_fork_error('m');
	i = 0;
	while (i < size)
	{
		ret->pipes[i] = (int *)malloc(sizeof(int) * 2);
		if (ret->pipes[i] == NULL)
			ft_pipe_fork_error('m');
		ret->pipes[i][0] = 0;
		ret->pipes[i][1] = 0;
		i += 1;
	}
	return (ret);
}

void	ft_close_pipes(int **pipes, int size, int pos)
{
	int		i;

	i = 0;
	while (i < size)
	{
		if (i != pos)
		{
			close (pipes[i][0]);
		}
		if (i != pos + 1)
		{
			close (pipes[i][1]);
		}
		i += 1;
	}
}

void	ft_close_all_pipes(int **pipes, int size)
{
	int		i;

	i = 0;
	while (i < size)
	{
		close (pipes[i][0]);
		close (pipes[i][1]);
		i += 1;
	}
}
