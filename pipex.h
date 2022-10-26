/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruangde <pruangde@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 00:08:00 by pruangde          #+#    #+#             */
/*   Updated: 2022/10/08 00:21:36 by pruangde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <stdio.h>
# include <string.h>

// pipex_utils_1
char    **cx_cmdpath(char *cmd, char **envp);
char    *findpath(char *prog_name, char **envp);
void    p2p_free(char **ptr2d);
void    do_error_exit(char *msg, char *str);

// void    printtest(char *str, int n, int fd);
// void    printp2p(char **p2p);

#endif
