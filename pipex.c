/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonslee <yoonslee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 14:59:01 by yoonslee          #+#    #+#             */
/*   Updated: 2023/02/23 15:58:29 by yoonslee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
1. First check if the argument count 
2. check open file, close file
3. split the cmd1 cmd2 to use with execve later on
4. find env paths to execute commands
5. make a pipe to use child functions
5. write infile and execute child1 process/use dup2 to change stdin
6. read child1 process result and execute child2 process/use dup2 to change stdout
7. check if everything is closed
opens argv[4] in write-only mode with create and truncate options and sets file permissions to 0644
*/

int argv_check(char **argv, t_pipex *pipex)
{
	pipex.fd[0] = open(argv[1], O_RDONLY);
	if (pipex.fd[0] == -1)
		perror("Infile error!");
	pipex.fd[1] = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (pipex.fd[1] == -1)
		perror("Outfile error!");
	pipex->cmd1_argv = ft_split(argv[2], ' ');
	if (!pipex->cmd1_argv)
		exit(1);
	pipex->cmd1 = ft_strjoin("/", pipex->cmd1_argv[0]);
	pipex->cmd2_argv = ft_split(argv[3], ' ');
	if (!pipex->cmd2_argv)
		exit(1);
	pipex->cmd2 = ft_strjoin("/", pipex->cmd2_argv[0]);
	return (0);
}

char	*find_path(char **env)
{
	int		i;
	char	*path;
	char	**env_path;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
			break ;
		else
			i++;
	}
	path = ft_substr(env[i], 5, ft_strlen(env[i]));
	if (!path)
		return (NULL);
	return (path);
}

int	get_cmd_path(t_pipex *pipex)
{
	
	
}

int	main(int argc, char *argv[], char **env)
{
	t_pipex	*pipex;

	if (argc != 5)
		return (ft_printf("Wrong amoung=t of arguments!\n"));
	pipex = calloc(1, sizeof(t_pipex)); // change it to ft_calloc later.
	if (!pipex)
		return (ft_printf("error in allocating pipex"));
	argv_check(argv, pipex);
	pipex->env = find_path(env);
	pipex->cmd_paths = ft_split(pipex->env, ':');
	get_cmd_path(pipex);
	
	return (0);
}
