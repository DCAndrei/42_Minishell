/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_devide_command_helpers_3.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acretu <acretu@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 20:27:57 by acretu            #+#    #+#             */
/*   Updated: 2022/03/21 21:47:26 by acretu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_set_size_oo(int *start, t_each *ret, char **str, int c)
{
	int		size;

	if (c == 1)
		*start += 1;
	size = ft_len(&(*str)[*start + 1]) + 1;
	if (c == 1)
	{
		ret->r_o = -1;
		ret->r_oo = 1;
	}
	else
	{
		ret->r_o = 1;
		ret->r_oo = -1;
	}
	return (size);
}

int	ft_set_size_ii(int *start, t_each *ret, char **str, int c)
{
	int		size;

	if (c == 1)
		*start += 1;
	size = ft_len(&(*str)[*start + 1]) + 1;
	if (c == 1)
	{
		ret->r_ii = 1;
	}
	else
	{
		ret->r_i = 1;
	}
	return (size);
}

void	ft_heredoc_redirect(char **str, t_each *ret, int *size, int *start)
{
	if (ret->ii_file != NULL)
	{
		ft_gnl_built(ret->ii_file);
		free (ret->ii_file);
		ret->ii_file = NULL;
	}
	*size = ft_set_size_ii(start, ret, str, 1);
	ret->ii_file = ft_substr_f(*str, *start + 1, *size);
	ft_remove_ws(&ret->ii_file);
	ft_cut_string(str, *start - 1, *start + *size);
}
