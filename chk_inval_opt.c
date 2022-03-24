/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chk_inval_opt.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtrietz <mtrietz@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 10:48:20 by mtrietz           #+#    #+#             */
/*   Updated: 2022/03/21 20:48:55 by mtrietz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	chk_inval_opt(char **cmd)
{
	char	*cmd_name;

	if (!cmd)
		return (0);
	cmd_name = *cmd;
	while (*cmd)
	{
		if (ft_strchr(*cmd, '-'))
		{
			write(2, "minishell: ", 11);
			write(2, cmd_name, ft_strlen(cmd_name));
			write(2, " : ", 3);
			write(2, *cmd, ft_strlen(*cmd));
			write(2, " : ", 3);
			write(2, "Invalid option.\n", 16);
			return (2);
		}	
		cmd++;
	}
	return (0);
}
