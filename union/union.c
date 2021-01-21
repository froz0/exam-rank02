/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   union.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatis <tmatis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 12:51:55 by tmatis            #+#    #+#             */
/*   Updated: 2021/01/20 12:59:19 by tmatis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

static	int ft_isinside(char c)
{
	static char	inside[2000];
	int			i;

	i = 0;
	while (inside[i])
	{
		if (inside[i] == c)
			return (1);
		i++;
	}
	inside[i] = c;
	return (0);
}
int main(int argc, char **argv)
{
	char	*str1;
	char	*str2;
	if (argc == 3)
	{
		str1 = argv[1];
		str2 = argv[2];
		while (*str1)
		{
			if (!ft_isinside(*str1))
				write(1, str1, 1);
			str1++;
		}
		while (*str2)
		{
			if (!ft_isinside(*str2))
				write(1, str2, 1);
			str2++;
		}
	}
	write(1, "\n", 1);
}
