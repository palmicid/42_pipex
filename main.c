/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruangde <pruangde@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 00:05:12 by pruangde          #+#    #+#             */
/*   Updated: 2022/10/27 04:06:02 by pruangde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child_proc_cmd1(char **av, char **envp, int *fd)
{
	int	filein;
	char	**cmd;
	
	filein = open(av[1], O_RDONLY, 0777);
	if (filein == -1)
		do_error_exit(0, av[1]);
	dup2(filein, STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[0]);
	close(fd[1]);
	close(filein);
	cmd = cx_cmdpath(av[2], envp);
	if (errno == 127)
	{
		p2p_free(cmd);
		do_error_exit("command not found", av[2]);
	}
	if (execve(cmd[0], cmd, envp) != 0)
	{
		p2p_free(cmd);
		do_error_exit(0, 0);
	}
}

void	parent_proc_cmd2(char **av, char **envp, int *fd)
{
	int	fileout;
	char **cmd;
	
	fileout = open(av[4], O_RDWR | O_CREAT | O_TRUNC, 0777);
	if (fileout == -1)
		do_error_exit(0, av[4]);
	dup2(fd[0], STDIN_FILENO);
	dup2(fileout, STDOUT_FILENO);
	close(fd[0]);
	close(fd[1]);
	close(fileout);
	cmd = cx_cmdpath(av[3], envp);
	if (errno == 127)
	{
		p2p_free(cmd);
		do_error_exit("command not found", av[3]);
	}
	if (execve(cmd[0], cmd, envp) != 0)
	{
		p2p_free(cmd);
		do_error_exit(0, 0);
	}
}

int	main(int ac, char **av, char **envp)
{
	int	fd[2];
	int	pid;
	int	child_stat;
	int	err_stat = 0;

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
		child_proc_cmd1(av, envp, fd);

	//wait and get errno from child
	waitpid(pid, &child_stat, 0);
	if (WIFEXITED(child_stat))
		err_stat = WEXITSTATUS(child_stat);
	errno = err_stat;
	
	// parent process last cmd
	parent_proc_cmd2(av, envp, fd);

}
