/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_commands_3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acretu <acretu@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 09:26:09 by acretu            #+#    #+#             */
/*   Updated: 2022/03/21 15:21:20 by acretu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_variable(char *var, char *envp[], int v_exit)
{
	int		i;
	char	*ret;
	char	*tmp;

	ret = NULL;
	if (var == NULL)
		return (NULL);
	else if (var[0] == '?')
		return (ft_itoa(v_exit));
	tmp = ft_strjoin_ch(var, '=');
	i = 0;
	while (envp[i] != NULL && ft_strnstr(envp[i], tmp, ft_strlen(tmp)) == NULL)
		i += 1;
	free (tmp);
	if (envp[i] == NULL)
		return (NULL);
	else
		ret = ft_substr_f(envp[i], ft_strlen(var) + 1, \
			ft_strlen(envp[i]) - ft_strlen(var));
	return (ret);
}

char	*ft_extract_command(char *str)
{
	char	*ret;
	int		i;

	i = 0;
	while (ft_is_whitespace(str[i]) == 0 && str[i] != '\0')
		i += 1;
	ret = ft_substr_f(str, 0, i + 1);
	return (ret);
}

void	ft_init_structure(t_each *var)
{
	var->cmmd = NULL;
	var->env = NULL;
	var->r_i = -1;
	var->r_o = -1;
	var->r_ii = -1;
	var->r_oo = -1;
	var->i_file = NULL;
	var->ii_file = NULL;
	var->o_file = NULL;
	var->pipes = 0;
	var->max_pipes = 0;
	var->lst_red = -1;
}

int	ft_find_dolar(char *str, int *in_quotes)
{
	int		i;
	int		q[2];

	q[0] = 0;
	q[1] = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\'' && q[1] % 2 == 0)
			q[0] += 1;
		else if (str[i] == '"' && q[0] % 2 == 0)
			q[1] += 1;
		if (str[i] == '$' && q[1] % 2 != 0)
		{
			*in_quotes = 1;
			return (i);
		}
		if (str[i] == '$' && q[1] % 2 == 0 && q[0] % 2 == 0 && \
		(ft_isalnum(str[i + 1]) == 1 || str[i + 1] == '?'))
			return (i);
		i += 1;
	}
	return (-1);
}

int	ft_is_shell(char c)
{
	if (ft_isalnum(c) == 1 || c == '_')
		return (1);
	return (0);
}
