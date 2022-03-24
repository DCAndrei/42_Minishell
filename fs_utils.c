/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fs_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtrietz <mtrietz@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 10:15:15 by mtrietz           #+#    #+#             */
/*   Updated: 2022/03/17 15:21:07 by mtrietz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	set_envvar(t_list **sh_env, char *buf1, char *buf2);

int	pwd(int fd, char **cmd)
{
	char	buf[PATH_MAX + 1];
	int		err;

	err = chk_inval_opt(cmd);
	if (err)
		return (err);
	if (!getcwd(buf, PATH_MAX + 1))
		return (-1);
	ft_putendl_fd(buf, fd);
	return (0);
}

int	cd(t_list **sh_env, char **cmd)
{
	int		res;
	char	buf1[PATH_MAX + 1];
	char	buf2[PATH_MAX + 1];

	res = chk_inval_opt(cmd);
	if (res)
		return (res);
	if (ft_arrlen(cmd) > 2)
		return (errmsg(cmd[0], NULL, "too many arguments", 1));
	if (ft_arrlen(cmd) < 2)
		return (errmsg(cmd[0], NULL, "too few arguments", 1));
	if (!getcwd(buf1, PATH_MAX + 1))
		return (2);
	res = chdir(cmd[1]);
	if (!getcwd(buf2, PATH_MAX + 1))
		return (2);
	if (res)
		return (errmsg(cmd[0], cmd[1], strerror(errno), 1));
	set_envvar(sh_env, buf1, buf2);
	return (0);
}

static void	set_envvar(t_list **sh_env, char *buf1, char *buf2)
{
	char	*tmp;

	tmp = ft_strjoin("OLDPWD=", buf1);
	if (tmp)
	{
		env_set_value(sh_env, tmp);
		free(tmp);
	}
	tmp = ft_strjoin("PWD=", buf2);
	if (tmp)
	{
		env_set_value(sh_env, tmp);
		free(tmp);
	}
}
