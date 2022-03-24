/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_commands_1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acretu <acretu@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 14:49:43 by acretu            #+#    #+#             */
/*   Updated: 2022/03/21 19:01:14 by acretu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_modify_string(int start, int end, char **str, t_status *sh);
static void	ft_expand_checker(int *end, int i, int in_quotes, t_line *line);
static void	ft_check_string(char **middle, char **second, char **str, int end);
static void	ft_replace(char **middle, char **second);

int	ft_expand_var(t_line *line, t_status *sh)
{
	int		i;
	int		begin;
	int		end;
	int		in_quotes;

	i = 0;
	while (line->commands[i] != NULL)
	{
		begin = 0;
		while (begin != -1)
		{
			in_quotes = 0;
			begin = ft_find_dolar(line->commands[i], &in_quotes);
			if (begin != -1)
			{
				end = begin + 1;
				ft_expand_checker(&end, i, in_quotes, line);
				ft_modify_string(begin, end, &line->commands[i], sh);
			}
		}
		i += 1;
	}
	return (0);
}

static int	ft_modify_string(int start, int end, char **str, t_status *sh)
{
	char	*first;
	char	*second;
	char	*middle;
	char	*var;

	first = ft_substr_f(*str, 0, start + 1);
	middle = ft_substr_f(*str, start + 1, end - start);
	second = NULL;
	ft_check_string(&middle, &second, str, end);
	var = ft_variable(middle, sh->envp_2, sh->v_exit);
	free (middle);
	if (var == NULL)
		middle = ft_strdup(first);
	else
		middle = ft_strjoin(first, var);
	free (first);
	if (var != NULL)
		free (var);
	first = ft_strjoin(middle, second);
	free (middle);
	free (second);
	free (*str);
	*str = first;
	return (0);
}

static void	ft_expand_checker(int *end, int i, int in_quotes, t_line *line)
{
	if (line->commands[i][*end] != '?')
	{
		if (in_quotes == 0)
			while (ft_is_whitespace(line->commands[i][*end]) == 0 && \
			line->commands[i][*end] != '\0' && \
			ft_is_shell(line->commands[i][*end]) == 1)
				*end += 1;
		else
			while (ft_is_whitespace(line->commands[i][*end]) == 0 && \
			line->commands[i][*end] != '\0' && \
			(line->commands[i][*end] != '"' && line->commands[i][*end] != '\''))
				*end += 1;
	}
	else
		*end += 1;
}

static void	ft_check_string(char **middle, char **second, char **str, int end)
{
	char		*tmp;
	char		c;

	if (ft_isdigit((*middle)[0]) == 1)
	{
		tmp = ft_substr_f(*str, end, ft_strlen(*str) - end + 2);
		*second = ft_strjoin(middle[1], tmp);
		free (tmp);
		c = (*middle)[0];
		free (*middle);
		if (c != '0')
		{
			*middle = ft_calloc(2, sizeof(char));
			(*middle)[0] = c;
		}
		else
			ft_replace(middle, second);
	}
	else
		*second = ft_substr_f(*str, end, ft_strlen(*str) - end + 2);
}

static void	ft_replace(char **middle, char **second)
{
	*middle = ft_strdup(*second);
	free (*second);
	*second = ft_strjoin("minishell", *middle);
	free (*middle);
	*middle = NULL;
}
