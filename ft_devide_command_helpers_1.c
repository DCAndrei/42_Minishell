/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_devide_command_helpers_1.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acretu <acretu@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 21:35:20 by acretu            #+#    #+#             */
/*   Updated: 2022/03/16 13:12:29 by acretu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//q[2] = i q[3] = j

static char	*ft_iteration(char **tmp, int *j, int **q);

char	**ft_split_command(char *str)
{
	char	**ret;
	int		size;
	char	*tmp;
	int		*q;

	tmp = str;
	size = ft_com_size(str);
	ret = (char **)malloc(sizeof(char *) * (size + 1));
	if (ret == NULL)
		ft_pipe_fork_error('m');
	ret[size] = NULL;
	q = ft_calloc(4, sizeof(int));
	if (q == NULL)
		ft_pipe_fork_error('m');
	while (*tmp != '\0' && q[2] < size)
	{
		ret[q[2]] = ft_iteration(&tmp, &q[3], &q);
		tmp += q[3];
		q[2] += 1;
	}
	free (q);
	return (ret);
}

static char	*ft_iteration(char **tmp, int *j, int **q)
{
	char		*ret;

	while (ft_is_whitespace(**tmp) == 1 && **tmp != '\0')
		(*tmp) += 1;
	*j = 0;
	while ((ft_is_whitespace((*tmp)[*j]) == 0 && (*tmp)[*j] != '\0') \
	|| (ft_is_whitespace((*tmp)[*j]) == 1 && ((*q)[0] == 1 || (*q)[1] == 1)))
	{
		if ((*tmp)[*j] == '\'' && (*q)[0] == 1 && (*q)[1] == 0)
			(*q)[0] = 0;
		else if ((*tmp)[*j] == '\'' && (*q)[0] == 0 && (*q)[1] == 0)
			(*q)[0] = 1;
		else if ((*tmp)[*j] == '"' && (*q)[1] == 0 && (*q)[0] == 0)
			(*q)[1] = 1;
		else if ((*tmp)[*j] == '"' && (*q)[1] == 1 && (*q)[0] == 0)
			(*q)[1] = 0;
		*j += 1;
	}
	ret = ft_substr_f(*tmp, 0, *j + 1);
	ft_remove_quotes(&ret);
	return (ret);
}

static char	*ft_return_str(char *str, size_t *nb, size_t *i);
static void	ft_remove_help(char **str, size_t len, char **ret);

void	ft_remove_quotes(char **str)
{
	char		*ret;
	size_t		nb;
	size_t		i;
	size_t		len;

	if (*str == NULL)
		return ;
	nb = 0;
	i = 0;
	ret = ft_return_str(*str, &nb, &i);
	len = ft_strlen(*str) - nb;
	ft_remove_help(str, len, &ret);
	free (*str);
	*str = ret;
}

static char	*ft_return_str(char *str, size_t *nb, size_t *i)
{
	int		q[2];
	char	*ret;

	q[0] = 0;
	q[1] = 0;
	while (str[*i] != '\0')
	{
		if (str[*i] == '\'' && q[1] % 2 == 0)
		{
			*nb += 1;
			q[0] += 1;
		}
		else if (str[*i] == '"' && q[0] % 2 == 0)
		{
			*nb += 1;
			q[1] += 1;
		}
		*i += 1;
	}
	ret = (char *)malloc(sizeof(char) * (ft_strlen(str) - *nb + 1));
	if (ret == NULL)
		ft_pipe_fork_error('m');
	ret[ft_strlen(str) - *nb] = '\0';
	return (ret);
}

static void	ft_remove_help(char **str, size_t len, char **ret)
{
	int		q[2];
	size_t	nb;
	size_t	i;

	i = 0;
	nb = 0;
	q[0] = 0;
	q[1] = 0;
	while (nb < len && (*str)[i] != '\0')
	{
		if (((*str)[i] != '\'' && (*str)[i] != '"') || ((*str)[i] == '\'' \
		&& q[1] % 2 != 0) || ((*str)[i] == '"' && q[0] % 2 != 0))
		{
			(*ret)[nb] = (*str)[i];
			nb += 1;
		}
		else if ((*str)[i] == '\'' && q[1] % 2 == 0)
			q[0] += 1;
		else if ((*str)[i] == '"' && q[0] % 2 == 0)
			q[1] += 1;
		i += 1;
	}
}
