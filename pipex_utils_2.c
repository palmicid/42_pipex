/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruangde <pruangde@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 04:51:50 by pruangde          #+#    #+#             */
/*   Updated: 2022/10/27 11:00:35 by pruangde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	p2p_free(char **ptr2d)
{
	int	i;

	i = 0;
	while (ptr2d[i])
	{
		free(ptr2d[i]);
		i++;
	}
	free(ptr2d);
	ptr2d = NULL;
}

void	do_error_exit(char *msg, char *str)
{
	if (msg && str)
	{
		ft_putstr_fd("zsh: ", STDERR_FILENO);
		ft_putstr_fd(msg, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		sp_putstrlen_fd(str, STDERR_FILENO);
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
	exit(errno);
}

int	find_space(char *str)
{
	int	i;

	i = 0;
	while (str[i] && (str[i] != ' '))
		i++;
	return (i);
}

void	sp_putstrlen_fd(char *str, int fd)
{
	int	len;

	len = find_space(str);
	write(fd, str, len);
}

char	*sp_strtrim(char *s1, char *set)
{
	char	*strim;
	size_t	st;
	size_t	ed;

	if (!s1 || !set)
		return (NULL);
	st = 0;
	ed = ft_strlen(s1);
	while (ft_strchr(set, s1[st]) && s1[st])
		st++;
	while (ft_strchr(set, s1[ed]) && ed >= st)
		ed--;
	strim = ft_substr(s1, st, (ed - st) + 1);
	free(s1);
	return (strim);
}
