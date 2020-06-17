/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlintill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 13:34:15 by rlintill          #+#    #+#             */
/*   Updated: 2019/09/07 11:26:13 by rlintill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strcat(char *dest, const char *str)
{
	unsigned	i;
	unsigned	j;

	i = 0;
	j = 0;
	while (dest[i] != '\0')
		i++;
	while (str[j] != '\0')
	{
		dest[i + j] = str[j];
		j++;
	}
	dest[i + j] = '\0';
	return (dest);
}
