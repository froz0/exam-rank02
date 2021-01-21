/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatis <tmatis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 14:03:31 by tmatis            #+#    #+#             */
/*   Updated: 2021/01/20 16:07:09 by tmatis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

int ft_gnl(char **line);

int	main(void)
{
	int r;
	char *line;

	while ((r = ft_gnl(&line)))
	{
		printf("%i: %s\n", r, line);
		free(line);
	}
	printf("%i: %s\n", r, line);
	free(line);
}
