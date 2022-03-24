/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errmsg.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtrietz <mtrietz@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 10:18:58 by mtrietz           #+#    #+#             */
/*   Updated: 2022/03/20 08:20:54 by mtrietz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*join_and_free(char *msg, char *str)
{
	char	*tmp;

	if (!msg)
		msg = ft_strjoin("", str);
	else
	{
		tmp = msg;
		msg = ft_strjoin(tmp, str);
		free(tmp);
	}
	return (msg);
}

int	errmsg(char *cmdname, char *cmdarg, char *errmsg, int errcode)
{
	char	*msg;

	msg = join_and_free((char *) NULL, SHELLNAME);
	msg = join_and_free(msg, ": ");
	msg = join_and_free(msg, cmdname);
	msg = join_and_free(msg, ": ");
	if (cmdarg)
	{
		msg = join_and_free(msg, cmdarg);
		msg = join_and_free(msg, ": ");
	}
	msg = join_and_free(msg, errmsg);
	msg = join_and_free(msg, "\n");
	write(2, msg, ft_strlen(msg));
	free(msg);
	return (errcode);
}
