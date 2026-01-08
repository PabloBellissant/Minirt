/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sample_materials.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <mail@bellissantpablo.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 02:08:32 by pabellis          #+#    #+#             */
/*   Updated: 2025/12/16 02:08:32 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bvh.h"
#include "colors_types.h"
#include "libft.h"
#include "minirt.h"
#include "rasterizer.h"
#include "render.h"
#include "rgb_special1.h"
#include "vec3_operations.h"
#include "vec3_scalar.h"
#include "vec3_special1.h"
#include "vec3_special2.h"
#include "vectors_types.h"
#include <errno.h>
#include <stdint.h>
#include "calc.h"

t_vec3	apply_normal_map(t_vec3 normal, t_vec3 nmap, 
	t_vec3 tangent, t_vec3 bitangent)
{
    t_vec3	world_normal;
	t_vec3	n;

	n = vec3_sub_scalar(vec3_scale(nmap, 2.0f), 1);
	world_normal = vec3_add(vec3_add(
		vec3_scale(tangent, n.x),
		vec3_scale(bitangent, -n.y)),
		vec3_scale(normal, n.z));
    return (vec3_normalize(world_normal));
}

t_vec3	vec3_inv(t_vec3 vec);

void	apply_hit_data(
	t_hit *hit, t_mat *mat, t_texture *tex, t_hit_mat_data *data);

void	sample_materials(t_buffers *buffers, int pixel, t_texture *tex, t_mat *mat)
{
	t_rgb			f0;
	t_ray			*ray;
	t_hit_mat_data	hit_data;

	hit_data.mat = mat + buffers->hits[pixel].mat_id;
	ray = &buffers->rays[buffers->hits[pixel].id];
	apply_hit_data(&buffers->hits[pixel], hit_data.mat, tex, &hit_data);
	buffers->hits[pixel].ks = hit_data.mat->ks;
	buffers->hits[pixel].ns = hit_data.mat->ns;
	f0 = get_f0(hit_data.metalness, hit_data.mat->ni, buffers->hits[pixel].ks);
	buffers->hits[pixel].reflectivity = get_reflect(ray->dir, buffers->hits[pixel].normal, hit_data.roughness, f0);
	buffers->hits[pixel].reflectivity = vec3_clamp(buffers->hits[pixel].reflectivity, 0.0f, 1.0f);
	if (ray->iteration > MAX_ITER || vec3_length(buffers->hits[pixel].reflectivity) < 0.05f)
		buffers->hits[pixel].hit = false;
	else
	{
		ray->refract.through_power[ray->refract.count] = vec3_scale(ray->through_power, 1.0f - hit_data.hit_opacity);
		if (vec3_length(ray->refract.through_power[ray->refract.count]) > 0.05)
		{
			ray->refract.dir[ray->refract.count] = ray->dir;
			ray->refract.origin[ray->refract.count] = ray->origin;
			ray->through_power = vec3_sub(ray->through_power, ray->refract.through_power[ray->refract.count]);
			refract(&ray->refract.origin[ray->refract.count], &ray->refract.dir[ray->refract.count], &buffers->hits[pixel], hit_data.mat->ni);
			++ray->refract.count;
		}
		ray->origin = buffers->hits[pixel].hit_point;
		ray->dir = vec3_reflect(ray->dir, buffers->hits[pixel].normal);
		ray->inv_dir = vec3_inv(ray->dir);
		ray->iteration++;
	}
}

void	sample_materials_loop(t_buffers *buffers, t_texture *tex, t_mat *mat, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		sample_materials(buffers, i, tex, mat);
		++i;
	}
}


