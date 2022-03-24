/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_commands_1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtrietz <mtrietz@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 10:31:27 by acretu            #+#    #+#             */
/*   Updated: 2022/03/16 08:15:27 by mtrietz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//ft_split_line - will split a line based on the "|" into an array of strings,
//each representing a command in the pipeline

#include "minishell.h"

static int	ft_number_commands(char *line_read);
static int	ft_find_delimiter(char *line_read);
static void	split_loop(char *line_read, char ***com, int size);

int	ft_split_line(char *line_read, char ***com)
{
	int		size;

	size = ft_number_commands(line_read);
	(*com) = (char **)malloc(sizeof(char *) * (size + 1));
	if ((*com) == NULL)
		ft_pipe_fork_error('m');
	(*com)[size] = NULL;
	split_loop(line_read, com, size);
	return (0);
}

static void	split_loop(char *line_read, char ***com, int size)
{
	int		delimiter;
	int		i;

	i = 0;
	while (i < size && *line_read != '\0')
	{
		delimiter = ft_find_delimiter(line_read);
		if (delimiter != -1)
		{
			(*com)[i] = ft_substr_f(line_read, 0, delimiter + 1);
			line_read += delimiter + 1;
		}
		else
		{
			(*com)[i] = ft_substr_f(line_read, 0, ft_strlen(line_read) + 1);
			line_read += ft_strlen(line_read) + 1;
		}
		ft_remove_ws(&((*com)[i]));
		i += 1;
	}
}

static int	ft_number_commands(char *line_read)
{
	int		i;
	int		q[2];
	int		nr_com;

	i = 0;
	q[0] = 0;
	q[1] = 0;
	while (ft_is_whitespace(line_read[i]) == 1)
		i += 1;
	if (line_read[i] == '\0')
		return (0);
	nr_com = 1;
	i = 0;
	while (line_read[i] != '\0')
	{
		if (line_read[i] == '\'' && q[1] % 2 == 0)
			q[0] += 1;
		else if (line_read[i] == '"' && q[0] % 2 == 0)
			q[1] += 1;
		if (line_read[i] == '|' && q[0] % 2 == 0 && q[1] % 2 == 0)
				nr_com += 1;
		i += 1;
	}
	return (nr_com);
}

static int	ft_find_delimiter(char *line_read)
{
	int		i;
	int		q[2];

	i = 0;
	q[0] = 0;
	q[1] = 0;
	while (line_read[i] != '\0')
	{
		if (line_read[i] == '\'' && q[1] % 2 == 0)
			q[0] += 1;
		else if (line_read[i] == '"' && q[0] % 2 == 0)
			q[1] += 1;
		if (line_read[i] == '|' && q[0] % 2 == 0 && q[1] % 2 == 0)
			return (i);
		i += 1;
	}
	return (-1);
}
