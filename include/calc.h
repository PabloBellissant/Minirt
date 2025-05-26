/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <mail@bellissantpablo.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 17:50:50 by pabellis          #+#    #+#             */
/*   Updated: 2025/05/25 17:50:55 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CALC_H
# define CALC_H

# include <stdbool.h>
# include "struct.h"

bool	hit_register(t_ray *ray, t_scene *scene);
t_color	ray_path(t_ray *ray, t_scene *scene);

#endif
