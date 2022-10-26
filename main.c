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

int	main(int ac, char **av, char **envp)
{
	int	fd[2];
	int	pid;
	int	child_stat;
	int	err_stat_cmd1;

	int test = open("testout", O_RDWR | O_CREAT | O_TRUNC, 0777);
	if (ac != 5)
	{
		perror("expect -> ./pipex filein cmd1 cmd2 fileout");
		exit(EXIT_FAILURE);
	}
	if (pipe(fd) == -1)
		do_error_exit(0, 0);
	pid = fork();
	// child process CMD1
	if (pid == 0)
	{
		int	filein = open(av[1], O_RDONLY);
		if (filein == -1)
			do_error_exit(0, av[1]);
		if (dup2(filein, STDIN_FILENO) == -1)
			do_error_exit(0, 0);
		if (dup2(fd[1], STDOUT_FILENO) == -1)
			do_error_exit(0, 0);
		char	**cmd = cx_cmdpath(av[2], envp);
		close(fd[0]);
		close(fd[1]);
		close(filein);
		if (errno == 127)
			do_error_exit("command not found", cmd[0]);
		if (execve(cmd[0], cmd, envp) == -1)
			do_error_exit(0, 0);
	}
	//wait and get errno from child
	waitpid(pid, &child_stat, 0);
	if (WIFEXITED(child_stat) == 1)
		err_stat_cmd1 = WEXITSTATUS(child_stat);
	errno = err_stat_cmd1;
	
	// parent process last cmd
	int	fileout = open(av[4], O_RDWR | O_CREAT | O_TRUNC, 0777);
	if (fileout == -1)
		do_error_exit(0, av[4]);
	if (dup2(fd[0], STDIN_FILENO) == -1)
		do_error_exit(0, 0);
	if (dup2(fileout, STDOUT_FILENO) == -1)
		do_error_exit(0, 0);
	char	**cmd = cx_cmdpath(av[3], envp);
	close(fd[0]);
	close(fd[1]);
	close(fileout);
	if (errno == 127)
		do_error_exit("command not found", cmd[0]);
	if (execve(cmd[0], cmd, envp) == -1)
		do_error_exit(0, cmd[0]);
}
