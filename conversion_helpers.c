/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversion_helpers.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acretu <acretu@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 21:27:25 by acretu            #+#    #+#             */
/*   Updated: 2022/03/22 12:04:00 by acretu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_first_check(char **str, int *size, int *i);
static int	ft_second_check(char **str, int *size, int *i);

int	ft_check_pipe_error(char *str)
{
	int		i;
	int		size;

	if (str == NULL)
		return (2);
	i = 0;
	size = 0;
	if (ft_first_check(&str, &size, &i) == -1)
		return (258);
	if (ft_second_check(&str, &size, &i) == -1)
		return (258);
	return (0);
}

static int	ft_first_check(char **str, int *size, int *i)
{
	if (*str == NULL || (*str)[0] == '\0')
		return (0);
	while (ft_is_whitespace((*str)[*i]) == 1)
		*i += 1;
	if ((*str)[*i] == '|')
	{
		write(2, "minishell: syntax error near unexpected token `|'\n", 50);
		return (-1);
	}
	*size = ft_strlen(*str) - 1;
	while (ft_is_whitespace((*str)[*size]) == 1 && *size > 0)
		*size -= 1;
	if ((*str)[*size] == '|')
	{
		write(2, "minishell: syntax error near unexpected token `|'\n", 50);
		return (-1);
	}
	return (0);
}

static int	ft_second_check(char **str, int *size, int *i)
{
	int		q[2];

	q[0] = 0;
	q[1] = 0;
	while ((*str)[*i] != '\0' && *i < *size)
	{
		if ((*str)[*i] == '\'' && q[1] % 2 == 0)
			q[0] += 1;
		if ((*str)[*i] == '"' && q[0] % 2 == 0)
			q[1] += 1;
		if ((*str)[*i] == '|' && q[0] % 2 == 0 && q[1] % 2 == 0)
		{
			*i += 1;
			while (ft_is_whitespace((*str)[*i]) == 1 && (*str)[*i] != '\0')
				*i += 1;
			if ((*str)[*i] == '|')
			{
				write(2, "minishell: syntax error near unexpected token \
`|'\n", 50);
				return (-1);
			}
		}
		*i += 1;
	}
	return (0);
}

static void	ft_iteration(char *str, int *size, int *i, int **q);

int	ft_check_quotes(char *str)
{
	int		i;
	int		size;
	int		*q;

	i = 0;
	size = 0;
	q = (int *)malloc(sizeof(int) * 2);
	if (q == NULL)
		ft_pipe_fork_error('m');
	q[0] = 0;
	q[1] = 0;
	while (str[i] != '\0')
	{
		ft_iteration(str, &size, &i, &q);
		if ((q[0] % 2 != 0 || q[1] % 2 != 0) && str[i] == '\0')
		{
			write(2, "minishell: error: unclosed quotes\n", 34);
			free (q);
			return (3);
		}
	}
	free (q);
	return (0);
}

static void	ft_iteration(char *str, int *size, int *i, int **q)
{
	while (ft_is_whitespace(str[*i]) == 1 && str[*i] != '\0')
		*i += 1;
	while (ft_is_whitespace(str[*i]) == 0 && str[*i] != '\0')
	{
		if (str[*i] == '\'' && (*q)[1] % 2 == 0)
			(*q)[0] += 1;
		else if (str[*i] == '"' && (*q)[0] % 2 == 0)
			(*q)[1] += 1;
		*i += 1;
	}
	if ((*q)[0] % 2 == 0 && (*q)[1] % 2 == 0)
		*size += 1;
}
