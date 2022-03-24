/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_devide_command.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acretu <acretu@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 09:33:41 by acretu            #+#    #+#             */
/*   Updated: 2022/03/21 20:31:18 by acretu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_check_i(char **str, t_each *ret, int *n);
static void	ft_check_o(char **str, t_each *ret, int *n, int *m);
static void	ft_test(char **file, int start, int size, char **str);
static int	ft_test_2(char **file, int start, int size, char **str);

t_each	*ft_devide_comm(char **str, char **envp_2)
{
	t_each	*ret;
	int		t[3];

	ret = (t_each *)malloc(sizeof(t_each) * 1);
	if (ret == NULL)
		ft_pipe_fork_error('m');
	ft_init_structure(ret);
	ret->env = ft_copy_array(envp_2);
	t[0] = 0;
	t[1] = 0;
	t[2] = 0;
	ft_check_i(str, ret, &t[0]);
	ft_check_o(str, ret, &t[1], &t[2]);
	ft_remove_ws(&ret->i_file);
	ft_remove_ws(&ret->o_file);
	ft_remove_ws(str);
	ret->cmmd = ft_split_command(*str);
	return (ret);
}

static void	ft_check_i(char **str, t_each *ret, int *n)
{
	int		start;
	int		size;

	while (ft_return_position(*str, '<') != NULL)
	{
		start = ft_return_position(*str, '<') - *str;
		if ((*str)[start + 1] == '<')
		{
			ft_heredoc_redirect(str, ret, &size, &start);
		}
		else
		{
			size = ft_set_size_ii(&start, ret, str, 0);
			if (*n == 0)
			{
				ft_test(&ret->i_file, start, size, str);
				*n = ft_test_file(ret->i_file, 1);
			}
			ft_cut_string(str, start, start + size);
		}
	}
}

static void	ft_check_o(char **str, t_each *ret, int *n, int *m)
{
	int		start;
	int		size;

	while (ft_return_position(*str, '>') != NULL)
	{
		start = ft_return_position(*str, '>') - *str;
		if ((*str)[start + 1] == '>')
		{
			size = ft_set_size_oo(&start, ret, str, 1);
			if (*m == 0 && *n == 0)
			{
				ft_test(&ret->o_file, start, size, str);
				*m = ft_test_file(ret->o_file, 3);
			}
			ft_cut_string(str, start - 1, start + size);
		}
		else
		{
			size = ft_set_size_oo(&start, ret, str, 0);
			if (*n == 0 && *m == 0)
				*n = ft_test_2(&ret->o_file, start, size, str);
			ft_cut_string(str, start, start + size);
		}
	}
}

static void	ft_test(char **file, int start, int size, char **str)
{
	if (*file != NULL)
		free (*file);
	*file = ft_substr_f(*str, start + 1, size);
	ft_remove_ws(file);
}

static int	ft_test_2(char **file, int start, int size, char **str)
{
	if (*file != NULL)
		free (*file);
	*file = ft_substr_f(*str, start + 1, size);
	ft_remove_ws(file);
	return (ft_test_file(*file, 2));
}
