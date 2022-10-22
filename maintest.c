/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maintest.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruangde <pruangde@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 16:45:41 by pruangde          #+#    #+#             */
/*   Updated: 2022/10/13 22:30:03 by pruangde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdio.h>
#include <string.h>
#include <sys/errno.h>
/*
int	main(int ac, char **av, char **envp)
{
	int	i = 0;
	int	j = 0;
	char	**split_path;
	char	*path_program;

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
		{
			split_path[i] = ft_strtrim(split_path[i], "PATH=");
		}
		printf("%s\n", split_path[i]);
		path_program = ft_strjoin(split_path[i], "/norminette");
		if (access(path_program, F_OK))
			break ;
		i++;
	}
	return (0);
}
*/
/*
int	main(void)
{
	printf("start\n");
	int	stat;
	int	exit_stat;
	int	fd[2];
	int	filein;
	int	fileout;

	if (pipe(fd) == -1)
		return (0);
	int	pid = fork();
	if (pid == 0)
	{
		dup2(fd[1], STDOUT_FILENO);
		write(1, "QWERTY\0", 7);
		write(1, "TEST\0", 5);
		close(fd[0]);
		close(fd[1]);
		exit(EXIT_SUCCESS);
	}
	else
	{
		waitpid(pid, &stat, 0);
		int	op = open("fileout", O_RDWR);
		dup2(fd[0], STDIN_FILENO);
		dup2(op, STDOUT_FILENO);
		int i = 0;
		char	*str;
		str = (char *)ft_calloc(11, sizeof(char));
		while (i < 2)
		{
			read(STDIN_FILENO, str, 7);
			printf("%s\n", str);
			i++;
		}
		close(fd[0]);
		close(fd[1]);
		close(op);
		// printf("parent = %d\n", errno);
		// printf("%s\n", strerror(errno));
	}

	printf("Finish Test\n");
	return (0);
}
*/

int	main(int ac, char **av, char **envp)
{
	char	*cmd[] = {"/la", "-bbbqwertyuio", 0};
	int		fdin;
	int		fdout;
	int		child_stat;
	int		pid;

	pid = fork();
	printf("%d\n", pid);
	if (pid == 0)
	{
		fdin = open("file", O_RDONLY);

		//fdout = open("fileout", O_RDWR | O_TRUNC, 0777);

		// dup2(fdin, STDIN_FILENO);
		// dup2(fdout, STDOUT_FILENO);
		
		// cmd[0] = findpath(cmd[0], envp);
		// printf("cmd = %s\n", cmd[0]);
		execve(cmd[0], cmd, NULL);
		printf("%d\n", errno);
		close(fdin);
		close(fdout);
		ft_putstr_fd(strerror(errno), 2);
		exit(errno);
	}
	printf("dp u wait???\n");
	waitpid(pid, &child_stat, 0);
	printf("its back with %d\n", child_stat);
	ft_putstr_fd(strerror(child_stat), 2);
	exit(errno);
	printf("stat = %d", child_stat);

}
