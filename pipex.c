/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonslee <yoonslee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 14:59:01 by yoonslee          #+#    #+#             */
/*   Updated: 2023/02/21 14:00:51 by yoonslee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PIPEX_H"

/*
1. First check if the argument count 
2. check if every argv is correct
*/
int argv_is_correct(char **argv,t_pipex *pipex)
{
	pipex.fd[0] = open(argv[1], O_RDONLY);
		perror("failed to open file")
	
}

int	main(int argc, char *argv[], char **env)
{
	t_pipex	*pipex;

	if (argc != 5)
	{
		write(1, "arguments number is incorrect!\n", 31);
		exit(1);
	}
	argv_is_correct(argv, pipex);
		
}
