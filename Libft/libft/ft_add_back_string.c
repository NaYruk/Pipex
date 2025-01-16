/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_back_string.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcmilliot <marcmilliot@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 18:33:19 by marcmilliot       #+#    #+#             */
/*   Updated: 2025/01/16 18:33:50 by marcmilliot      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_add_back_string(char *str, char *to_add)
{
	int		i;
	int		j;
	char	*new_str;

	new_str = NULL;
	if (!str)
		return (0);
	new_str = malloc(sizeof(char) * (ft_strlen(str)) + ft_strlen(to_add) + 1);
	if (!new_str)
		return (0);
	i = -1;
	j = -1;
	while (str[++i] != '\0')
		new_str[i] = str[i];
	while (to_add[++j] != '\0')
		new_str[i++] = to_add[j];
	new_str[i] = '\0';
	return (new_str);
}
