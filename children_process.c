/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children_process.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonslee <yoonslee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 16:56:26 by yoonslee          #+#    #+#             */
/*   Updated: 2023/03/02 17:08:51 by yoonslee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	first_child_process(t_pipex *pipex)
{
	pipex->pid1 = fork();
	if (pipex->pid1 < 0)
		exit(1);
	if (pipex->pid1 == 0)
	{
		if (dup2(pipex->fd[1], STDOUT_FILENO) == -1)
			exit(1);
		if (dup2(pipex->infile, STDIN_FILENO) == -1)
			exit(1);
		close(pipex->infile);
		close(pipex->fd[1]);
		close(pipex->fd[0]);
		close(pipex->outfile);
		if (!pipex->cmd1_path)
		{
			ft_putstr_fd("Error; cmd1 not found\n", 2);
			exit(1);
		}
		if (execve(pipex->cmd1_path, pipex->cmd1_argv, pipex->envp) < 0)
		{
			perror("error, child1 execve failed");
			exit(1);
		}
	}
}

void	second_child_process(t_pipex *pipex)
{
	pipex->pid2 = fork();
	if (pipex->pid2 < 0)
		error_msg(pipex, 3);
	if (pipex->pid2 == 0)
	{
		if (dup2(pipex->fd[0], STDIN_FILENO) == -1)
			exit(1);
		if (dup2(pipex->outfile, STDOUT_FILENO) == -1)
			exit(1);
		close(pipex->infile);
		close(pipex->fd[1]);
		close(pipex->fd[0]);
		close(pipex->outfile);
		if (!pipex->cmd2_path)
		{
			ft_putstr_fd("Error; cmd2 not found\n", 2);
			exit(1);
		}
		if (execve(pipex->cmd2_path, pipex->cmd2_argv, pipex->envp) < 0)
		{
			perror("error, child1 execve failed");
			exit(1);
		}
	}
}
