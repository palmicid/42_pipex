/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruangde <pruangde@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 03:49:55 by pruangde          #+#    #+#             */
/*   Updated: 2022/10/27 11:00:26 by pruangde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**cx_cmdpath(char *cmd, char **envp)
{
	char	**ret_cmd;

	ret_cmd = ft_split(cmd, ' ');
	if (!ret_cmd)
		return (NULL);
	ret_cmd[0] = findpath(ret_cmd[0], envp);
	return (ret_cmd);
}

char	*findpath(char *prog_name, char **envp)
{
	char	**split_path;
	char	*sl_progname;
	char	*prog2exe;

	sl_progname = findnadd_slash(prog_name);
	split_path = path_split(envp);
	prog2exe = search_path(split_path, prog_name, sl_progname);
	return (prog2exe);
}

char	*search_path(char **split_path, char *prog_name, char *sl_progname)
{
	int		i;
	char	*path_program;

	i = 0;
	while (split_path[i])
	{
		if (i == 0)
			split_path[i] = sp_strtrim(split_path[i], "PATH=");
		path_program = ft_strjoin(split_path[i], sl_progname);
		if (access(path_program, F_OK) == 0)
		{
			p2p_free(split_path);
			free(prog_name);
			free(sl_progname);
			return (path_program);
		}
		free(path_program);
		i++;
	}
	p2p_free(split_path);
	free(sl_progname);
	if (access(prog_name, F_OK) != 0)
		errno = 127;
	return (prog_name);
}

char	*findnadd_slash(char *prog_name)
{
	char	*sl_progname;

	if (prog_name[0] == '/')
		sl_progname = ft_strjoin("", prog_name);
	else
		sl_progname = ft_strjoin("/", prog_name);
	return (sl_progname);
}

char	**path_split(char **envp)
{
	int		i;
	char	**split_path;

	i = 0;
	while (envp[i])
	{
		if (ft_strnstr(envp[i], "PATH=", 5))
			split_path = ft_split(envp[i], ':');
		i++;
	}
	return (split_path);
}
