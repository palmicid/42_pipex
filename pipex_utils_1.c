/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruangde <pruangde@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 03:49:55 by pruangde          #+#    #+#             */
/*   Updated: 2022/10/16 03:50:27 by pruangde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char    **cx_cmdpath(char *cmd, char **envp)
{
    char    **ret_cmd;
    char    *sl_cmd;
//cmd == "ls -la"
    sl_cmd = ft_strjoin("/", cmd);
    ret_cmd = ft_split(sl_cmd, ' ');
    if (!ret_cmd)
        return (NULL);
    ret_cmd[0] = findpath(ret_cmd[0], envp);
    free(sl_cmd);
    return (ret_cmd);
}

char    *findpath(char *prog_name, char **envp)
{
    int     i;
    char    **split_path;
    char    *path_program;

    i = 0;
    while (envp[i])
    {
        if (ft_strnstr(envp[i], "PATH", 4))
            split_path = ft_split(envp[i], ':');
        i++;
    }
    i = 0;
    while (split_path[i])
    {
        if (i == 0)
            split_path[i] = ft_strtrim(split_path[i], "PATH=");
        path_program = ft_strjoin(split_path[i], prog_name);
        if (access(path_program, F_OK) == 0)
            break ;
        i++;
    }
    return (path_program);
}

void    do_error(void)
{
    strerror(errno);
    exit(EXIT_FAILURE);
}
