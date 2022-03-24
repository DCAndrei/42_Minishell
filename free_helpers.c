/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acretu <acretu@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 12:43:09 by acretu            #+#    #+#             */
/*   Updated: 2022/03/21 16:13:45 by acretu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//frees an 2d array, without freeing the adress of the array itself
//frees only the elements of the array

void	ft_free_db_array(char **str)
{
	int		size;
	int		i;

	if (*str == NULL)
		return ;
	i = 0;
	size = 0;
	while (str[size] != NULL)
		size += 1;
	while (i <= size)
	{
		free (str[i]);
		i += 1;
	}
}

void	ft_free_double(char ***str)
{
	int		i;

	if (*str == NULL)
		return ;
	i = 0;
	while ((*str)[i] != NULL)
	{
		free ((*str)[i]);
		i += 1;
	}
	free ((*str)[i]);
	free (*str);
	*str = NULL;
}

static void	ft_free_helper(char ***elem);

void	ft_free_full_struct(t_each ***elem)
{
	int		i;

	i = 0;
	if (*elem == NULL)
		return ;
	while ((*elem)[i] != NULL)
	{
		ft_free_helper(&(*elem)[i]->cmmd);
		if ((*elem)[i]->i_file != NULL)
			free ((*elem)[i]->i_file);
		if ((*elem)[i]->ii_file != NULL)
			free ((*elem)[i]->ii_file);
		if ((*elem)[i]->o_file != NULL)
			free ((*elem)[i]->o_file);
		ft_free_helper(&(*elem)[i]->env);
		free ((*elem)[i]);
		i += 1;
	}
	free ((*elem)[i]);
	free (*elem);
	*elem = NULL;
}

static void	ft_free_helper(char ***elem)
{
	int		i;

	i = 0;
	if (*elem != NULL)
	{
		while ((*elem)[i] != NULL)
		{
			free ((*elem)[i]);
			i += 1;
		}
		free ((*elem)[i]);
		free (*elem);
		*elem = NULL;
	}
}

void	ft_free_gnl(char **val)
{
	char		*tmp;

	tmp = *val;
	free (tmp);
	*val = NULL;
}
