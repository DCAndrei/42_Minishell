/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_set_value.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtrietz <mtrietz@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 07:00:16 by mtrietz           #+#    #+#             */
/*   Updated: 2022/03/14 10:38:51 by mtrietz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*env_set_value(t_list **sh_env, char *varstr)
{
	char	*cmd[3];

	cmd[0] = ft_strdup("export");
	cmd[1] = varstr;
	cmd[2] = NULL;
	env_export(sh_env, cmd);
	free(cmd[0]);
	return (NULL);
}
