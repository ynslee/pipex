/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonslee <yoonslee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 14:59:01 by yoonslee          #+#    #+#             */
/*   Updated: 2023/03/02 17:09:42 by yoonslee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
1. First check if the argument count 
2. check open file, close file
3. split the cmd1 cmd2 to use with execve later on
4. find envp paths to execute commands
5. make a pipe to use child functions
5. write infile and execute child1 process/use dup2 to change stdin
6. read child1 process result and execute child2 process/use dup2 to change stdout
7. check if everything is closed
opens argv[4] in write-only mode with create and truncate options and sets file permissions to 0644
execve is a system call in Unix and Unix-like operating systems, which is used to execute a new program within the current process.

When a program executes execve, it replaces the current program code and memory space with the new program's code and memory space. The new program becomes the current process, and it starts executing from its main function.

The execve system call takes three arguments: the first argument is the path to the new program, the second argument is an array of strings that represent the program's arguments, and the third argument is an array of strings that represent the program's environment variables.

The execve system call is commonly used in Unix systems to implement the functionality of shell commands such as ls, grep, cat, and many others. When you run a command in the shell, the shell uses execve to execute the corresponding program, and the program replaces the shell process.
*/

// char	**split_command(char *argv)
// {
// 	char	**cmd;
// 	int		i;

// 	// cmd = ft_split(argv, ' ');
// 	i = 0;
// 	if (ft_strchr(argv[i], 39) != 0)
// 		has_single_quote(argv)
// 		while (argv[i])
// 		{
// 			if (argv[i] = 39)
// 				break;
// 			i++;
// 		}
// 			while
// 	return (cmd);
// }

// char *has_single_quote(char *argv)
// {
// 	char	*cmd;
// 	int		i;
// 	int		j;

// 	i = 0;
// 	while (!argv[i])
// 	{
// 		j++;
// 		if (argv[i] == 39)
// 			break ;
// 		i++;
// 	}
// 	while (!argv[j])
// 	{
// 		if (argv[j] == 39)
// 			break ;
// 		j++;
// 	}
// 	cmd = ft_substr(argv, i, j - i + 1);
// }

int	argv_check(char **argv, t_pipex *pipex)
{
	pipex->infile = open(argv[1], O_RDONLY);
	if (pipex->infile == -1)
		perror("Infile error!");
	pipex->outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (pipex->outfile == -1)
		perror("Outfile error!");
	// pipex->cmd1_argv = split_command(argv[2]);
	// if (!pipex->cmd1_argv)
	// 	// exit(1);
	// pipex->cmd2_argv = split_command(argv[3]);
	// if (!pipex->cmd2_argv)
	// 	// exit(1);
	pipex->cmd1_argv = ft_split(argv[2], ' ');
	if (!pipex->cmd1_argv)
		error_msg(pipex, 5);
	pipex->cmd2_argv = ft_split(argv[3], ' ');
	if (!pipex->cmd2_argv)
		error_msg(pipex, 5);
	return (0);
}

void	find_path(t_pipex *pipex, char **envp)
{
	int		i;
	char	*path;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			break ;
		else
			i++;
	}
	if (!envp[i])
		error_msg(pipex, 2);
	path = ft_substr(envp[i], 5, ft_strlen(envp[i]));
	if (!path)
		error_msg(pipex, 5);
	pipex->path = ft_split(path, ':');
	if (!pipex->path)
		error_msg(pipex, 5);
}

char	*get_path(t_pipex *pipex, char **cmd)
{
	int		i;
	char	*path_tmp;
	char	*path_env;

	i = 0;
	while (pipex->path[i])
	{
		path_tmp = ft_strjoin(pipex->path[i], "/");
		if (!path_tmp)
			error_msg(pipex, 5);
		path_env = ft_strjoin(path_tmp, cmd[0]);
		free(path_tmp);
		if (!path_env)
			error_msg(pipex, 5);
		if (access(path_env, X_OK) == 0)
			return (path_env);
		free(path_env);
		i++;
	}
	return (NULL);
}

int	main(int argc, char *argv[], char **envp)
{
	t_pipex	*pipex;

	if (argc != 5)
		return (ft_printf("Wrong amount of arguments!\n"));
	else
	{
		pipex = ft_calloc(1, sizeof(t_pipex));
		pipex->envp = envp;
		if (!pipex)
			error_msg(pipex, 5);
		argv_check(argv, pipex);
		find_path(pipex, envp);
		if (pipe(pipex->fd) == -1)
			return (ft_printf("problem when making a pipe!\n"));
		pipex->cmd1_path = get_path(pipex, pipex->cmd1_argv);
		pipex->cmd2_path = get_path(pipex, pipex->cmd2_argv);
		first_child_process(pipex);
		second_child_process(pipex);
		close_all(pipex);
		waitpid(pipex->pid1, NULL, 0);
		waitpid(pipex->pid2, NULL, 0);
		free_all(pipex);
	}
	return (0);
}


