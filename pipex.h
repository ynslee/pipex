/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonslee <yoonslee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 14:59:12 by yoonslee          #+#    #+#             */
/*   Updated: 2023/02/24 11:36:56 by yoonslee         ###   ########.fr       */
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
# include "libft/ft_printf.h"

typedf	strcut s_pipex{
	char	*cmd1;
	char	*cmd2;
	char	*path;
	char	*cmd_path;
	char	**cmd1_argv;
	char	**cmd2_argv;
	char	**envp;
	int 	fd[2];
	int		infile;
	int		outfile;
	int		pid1;
	int 	pid2;
}			t_pipex;

#endif