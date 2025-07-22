/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 06:30:19 by jaubry--          #+#    #+#             */
/*   Updated: 2024/08/21 08:24:22 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	Function that returns 1 if the char is in the standart ascii table 
	(not extended)
*/
int	ft_isascii(int c)
{
	return (c >= 0 && c <= 127);
}
