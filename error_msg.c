/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonslee <yoonslee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 15:34:50 by yoonslee          #+#    #+#             */
/*   Updated: 2023/03/02 16:07:33 by yoonslee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
error codes:
2. didn't find path
3. fork failed
5. allocation failure
*/
void	error_msg(t_pipex *pipex, int error_code)
{
	if (error_code == 2)
		ft_putstr_fd("Error; didn't find path (HOW IS THIS POSSIBLE?)\n", 2);
	if (error_code == 3)
		ft_putstr_fd("Error; fork failed\n", 2);
	if (error_code == 5)
		ft_putstr_fd("Error; allocation failure", 2);
	// free everything you have malloced
	if (pipex)
		
	exit (error_code);
}
