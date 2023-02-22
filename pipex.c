/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonseonlee <yoonseonlee@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 14:59:01 by yoonslee          #+#    #+#             */
/*   Updated: 2023/02/22 22:16:30 by yoonseonlee      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
/*
1. First check if the argument count 
2. check if every argv is correct
*/
int argv_is_correct(char **argv,t_pipex *pipex)
{
	pipex.fd[0] = open(argv[1], O_RDONLY);
	if(pipex.fd[0] == -1)
		perror("failed to open file")
	pipex.fd[1] = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC)
	
}

int	main(int argc, char *argv[], char **env)
{
	t_pipex	*pipex;

	if (argc != 5)
		return(ft_printf("incorrect amount of arguments!\n"));
	argv_is_correct(argv, pipex);
		
}
