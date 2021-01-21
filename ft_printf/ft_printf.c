/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatis <tmatis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 20:29:25 by tmatis            #+#    #+#             */
/*   Updated: 2021/01/20 22:45:18 by tmatis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <unistd.h>
#include <stdio.h>

typedef struct s_parse
{
	int width;
	int pre;
	int conv;
}	t_parse;

static int ft_isnum(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

static int ft_strnlen(char *str, int size)
{
	int i;

	i = 0;
	while (i < size && str[i])
		i++;
	return (i);
}

static int ft_strlen(char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_atoi_basic(const char **str)
{
	int	n;

	n = 0;
	while (**str && ft_isnum(**str))
		n = n * 10 + (*(*str)++ - 48);
	return (n);
}

static void	ft_detect_conv(const char **format, t_parse *parse)
{
	if (**format == 's')
		parse->conv = 0;
	else if (**format == 'd')
		parse->conv = 1;
	else if (**format == 'x')
		parse->conv = 2;
	else
	{
		parse->conv = -1;
		return ;
	}
	(*format)++;
}

static void ft_detect_width(const char **format, t_parse *parse)
{
	parse->width = ft_atoi_basic(format);
}

static void ft_detect_pre(const char **format, t_parse *parse)
{
	if (**format == '.')
	{
		(*format)++;
		parse->pre = ft_atoi_basic(format);
	}
	else
		parse->pre = -1;
}

t_parse ft_parse(const char **format)
{
	t_parse parse;

	ft_detect_width(format, &parse);
	ft_detect_pre(format, &parse);
	ft_detect_conv(format, &parse);
	return (parse);
}

void ft_putxchar(char c, int x)
{
	while (x-- > 0)
		write(1, &c, 1);
}

int	ft_numlen(unsigned int i, int base)
{
	int len = 0;

	if (i == 0)
		return (1);
	while (i)
	{
		len++;
		i /= base;
	}
	return (len);
}

int ft_itoa_signed(int i, char *buff, char *base, int pre)
{
	int baselen = ft_strlen(base);
	int	numlen;
	int	numlenc;
	int	index = 0;
	unsigned int n;

	if (i < 0)
	{
		buff[index++] = '-';
		n = -i;
	}
	else
		n = i;
	numlen = ft_numlen(n, baselen);
	if (pre == 0 && n == 0)
		numlen = 0;
	if (pre > numlen)
		numlen = pre;
	numlenc = numlen;
	while (numlen)
	{
		buff[numlen + index - 1] = base[(n % baselen)];
		n /= baselen;
		numlen--;
	}
	return (numlenc + index);
}

int ft_itoa_unsigned(unsigned int n, char *buff, char *base, int pre)
{
	int baselen = ft_strlen(base);
	int	numlen;
	int	numlenc;

	numlen = ft_numlen(n, baselen);
	if (pre == 0 && n == 0)
		numlen = 0;
	if (pre > numlen)
		numlen = pre;
	numlenc = numlen;
	while (numlen)
	{
		buff[numlen - 1] = base[(n % baselen)];
		n /= baselen;
		numlen--;
	}
	return (numlenc);
}


int ft_int_conv(va_list va, t_parse parse)
{
	char buff[2000];
	int numlen = ft_itoa_signed(va_arg(va, int), buff, "0123456789", parse.pre);

	ft_putxchar(' ', parse.width - numlen);
	write(1, buff, numlen);
	if (parse.width > numlen)
		return (parse.width);
	else
		return (numlen);
}

int ft_hex_conv(va_list va, t_parse parse)
{
	char buff[2000];
	int numlen = ft_itoa_unsigned(va_arg(va, unsigned int), buff, "0123456789abcdef", parse.pre);

	ft_putxchar(' ', parse.width - numlen);
	write(1, buff, numlen);
	if (parse.width > numlen)
		return (parse.width);
	else
		return (numlen);
}


int ft_str_conv(va_list va, t_parse parse)
{
	int	strlen;
	char *str = va_arg(va, char *);

	if (!str)
		str = "(null)";
	if (parse.pre == -1)
		strlen = ft_strlen(str);
	else
		strlen = ft_strnlen(str, parse.pre);
	ft_putxchar(' ', parse.width - strlen);
	write(1, str, strlen);
	if (parse.width > strlen)
		return (parse.width);
	else
		return (strlen);
}

int	ft_doconv(va_list va, t_parse parse)
{
	if (parse.conv == 0)
		return (ft_str_conv(va, parse));
	if (parse.conv == 1)
		return (ft_int_conv(va, parse));
	if (parse.conv == 2)
		return (ft_hex_conv(va, parse));
	return (0);
}

int	ft_printf(const char *format, ...)
{
	va_list va;
	int	count;
	va_start(va, format);
	count = 0;
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			count += ft_doconv(va, ft_parse(&format));
		}
		else
		{
			write(1, format++, 1);
			count++;
		}
	}
	va_end(va);
	return (count);
}
