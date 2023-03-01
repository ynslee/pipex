/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonslee <yoonslee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 14:59:12 by yoonslee          #+#    #+#             */
/*   Updated: 2023/03/01 14:11:00 by yoonslee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>//perror, strerror
# include <sys/wait.h>//wait, waitpid
# include <fcntl.h>
# include <errno.h>
# include <string.h>
# include "libft/libft.h"

typedef struct s_pipex{
	char	*cmd1;
	char	*cmd2;
	char	**path;
	char	*cmd1_path;
	char	*cmd2_path;
	char	**cmd1_argv;
	char	**cmd2_argv;
	char	*env;
	int		fd[2];
	int		read[0];
	int		write[1];
	int		infile;
	int		outfile;
	int		pid1;
	int		pid2;
}			t_pipex;

#endif