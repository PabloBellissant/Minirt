/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glb.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <mail@bellissantpablo.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 03:59:01 by pabellis          #+#    #+#             */
/*   Updated: 2025/05/16 03:59:06 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GLB_H
# define GLB_H

# include "struct.h"

t_object	*glb_parser(char *str);
t_object	get_object_data(int elem, char *str);

#endif
