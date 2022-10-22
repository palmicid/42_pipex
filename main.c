/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruangde <pruangde@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 00:05:12 by pruangde          #+#    #+#             */
/*   Updated: 2022/10/08 00:06:27 by pruangde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child_proc(int *fd, char **av, char **envp)
{
	int	cx_exe;
	int	fdin;
	char **cmd;

	fdin = open("filein", O_RDONLY, 0777);
	if (fdin == -1)
		do_error();
	dup2(fdin, STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	cx_cmdpath();
	cx_exe = execve()

}

int	main(int ac, char **av, char **envp)
{
	int	fd[2];
	int	pid;

	if (ac == 5)
	{
		if (pipe(fd) == -1)
			return (2);
		pid = fork();
		if (pid == 0)
		{
			child_proc(av, envp);
		}
		cx_error();
		parent_proc(av, envp);
	}
	else
	{
		ft_putchar_fd("Expect => ./pipex file1 cmd1 cmd2 file2", STDOUT_FILENO);
		return (1);
	}
	return (0);
}
