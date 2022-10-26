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

    ret_cmd = ft_split(cmd, ' ');
    if (!ret_cmd)
        return (NULL);
    ret_cmd[0] = findpath(ret_cmd[0], envp);
    return (ret_cmd);
}

char    *findpath(char *prog_name, char **envp)
{
    int     i;
    char    **split_path;
    char    *path_program;
    char    *sl_progname;

    sl_progname = ft_strjoin("/", prog_name);
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
        path_program = ft_strjoin(split_path[i], sl_progname);
        if (access(path_program, F_OK) == 0)
        {
            p2p_free(split_path);
            free(prog_name);
            free(sl_progname);
            return (path_program);
        }
        i++;
    }
    free(sl_progname);
    free(path_program);
    errno = 127;
    return (prog_name);
}

void    p2p_free(char **ptr2d)
{
    int i;

    i = 0;
    while (ptr2d[i])
    {
        free(ptr2d[i]);
        i++;
    }
    free(ptr2d);
    ptr2d = NULL;
}

// void    for_dup2_inout(int *fd, int fdin, int fdout)
// {
//     if (dup2(fdin, STDIN_FILENO))
//         do_error_exit
// }

void    do_error_exit(char *msg, char *str)
{
    if (msg && str)
    {
        ft_putstr_fd("zsh: ", STDERR_FILENO);
        ft_putstr_fd(msg, STDERR_FILENO);
        ft_putstr_fd(": ", STDERR_FILENO);
        ft_putstr_fd(str, STDERR_FILENO);
        ft_putchar_fd('\n', STDERR_FILENO);
    }
    else if (str)
    {
        ft_putstr_fd("zsh: ", STDERR_FILENO);
        ft_putstr_fd(strerror(errno), STDERR_FILENO);
        ft_putstr_fd(": ", STDERR_FILENO);
        ft_putstr_fd(str, STDERR_FILENO);
        ft_putchar_fd('\n', STDERR_FILENO);
    }
    else
    {
        ft_putstr_fd("zsh: ", STDERR_FILENO);
        ft_putstr_fd(strerror(errno), STDERR_FILENO);
        ft_putchar_fd('\n', STDERR_FILENO);
    }
    // if ok move this comment out
    exit(errno);
}

// just for test
// void    printtest(char *str, int n, int fd)
// {
//     ft_putstr_fd(str, fd);
//     ft_putstr_fd(" = ", fd);
//     ft_putnbr_fd(n, fd);
//     ft_putchar_fd('\n', fd);
// }

// void printp2p(char **p2p)
// {
//     int i = 0;

//     while (p2p[i])
//     {
//         ft_putstr_fd(p2p[i], STDERR_FILENO);
//         ft_putstr_fd("\n",2);
//         i++;
//     }
// }
