/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftprintf.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 13:43:29 by okraus            #+#    #+#             */
/*   Updated: 2023/01/26 17:27:14 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFTPRINTF_H

# define LIBFTPRINTF_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdint.h>
# include <stdarg.h>

typedef struct s_output
{
	char	*string;
	int		len;
	int		precision;
	int		padsize;
	int		dash;
	int		zero;
	int		period;
	int		hash;
	int		space;
	int		plus;
}			t_output;

int			ft_printf(char *s, ...);
void		ft_putstuff(va_list arg, char *s, int *i, t_output *t);
int			ft_putchar_fd(char c, int fd);
int			ft_putuns_fd(unsigned int u, int fd);
void		ft_putuns2_fd(unsigned int u, int fd);
void		ft_putnbr_fd(int n, int fd);
char		*ft_string_pointer(void *mem);
int			ft_putpointer_fd(void *mem, int fd);
int			ft_print_pointer_fd(void *mem, int fd);
size_t		ft_strlen(const char *s);
int			ft_putstring_fd(char *s, int fd);
int			ft_print_string_fd(char *s, int fd);
int			ft_putunsigned_fd(unsigned int u, int fd);
int			ft_print_unsigned_fd(unsigned int u, int fd);
char		*ft_string_unsigned(unsigned int u);
int			ft_putinteger_fd(int d, int fd, t_output *t);
int			ft_print_integer_fd(int d, int fd, t_output *t);
char		*ft_string_integer(int d);
int			ft_puthexabig_fd(unsigned int h, int fd, t_output *t);
int			ft_print_hexabig_fd(unsigned int h, int fd, t_output *t);
char		*ft_string_hexabig(unsigned int h);
int			ft_puthexasmall_fd(unsigned int h, int fd, t_output *t);
int			ft_print_hexasmall_fd(unsigned int h, int fd, t_output *t);
char		*ft_string_hexasmall(unsigned int h);
void		ft_initialise_struct(t_output *t);
void		ft_prefill_struct(t_output *t, const char *s);
int			ft_get_num(t_output *t, const char *s, int i);
char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_padint(char *s, t_output *t);
char		*ft_precint(char *s, t_output *t);

#endif
