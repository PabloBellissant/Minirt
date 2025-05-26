/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_register.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <mail@bellissantpablo.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 17:42:26 by pabellis          #+#    #+#             */
/*   Updated: 2025/05/25 17:42:29 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "struct.h"

bool	hit_register(t_ray *ray, t_scene *scene)
{
	int	i;

	(void) ray;
	i = 0;
	while (i < scene->object_count)
	{
		++i;
	}
	return (false);
}
