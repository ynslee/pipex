/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonslee <yoonslee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 12:35:37 by yoonslee          #+#    #+#             */
/*   Updated: 2022/12/12 18:46:36 by yoonslee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>
# include "./libft/libft.h"

int			ft_printstr(char *str);
int			ft_printnbr(int n);
int			ft_printnbr_unsigned(unsigned int n);
int			ft_printchr(int c);
int			ft_check(char c, va_list ap);
int			ft_printf(const char *str, ...);
int			ft_printhex_small(unsigned int n);
int			ft_printhex_big(unsigned int n);
int			ft_printptr(unsigned long long n);

#endif