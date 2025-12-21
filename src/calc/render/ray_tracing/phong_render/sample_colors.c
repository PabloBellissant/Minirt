/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sample_colors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <mail@bellissantpablo.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 02:08:32 by pabellis          #+#    #+#             */
/*   Updated: 2025/12/20 21:52:51 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bvh.h"
#include "colors_types.h"
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

t_rgb	sample_texture(const t_texture *texture_list, int id, t_vec2 uv);

float	sample_binary_texture(const t_texture *texture_list, int id, t_vec2 uv);

t_vec3	apply_normal_map(t_vec3 normal, t_vec3 nmap, t_vec3 tangent, t_vec3 bitangent);

t_rgb	get_f0(float metalness, float ior, t_rgb ks);

t_vec3	vec3_inv(t_vec3 vec);

void	sample_colors(t_data *data, int pixel, t_texture *tex, t_mat *mat)
{
	t_vec3			tangent;
	t_vec3			bitangent;
	t_rgb			nmap;

	mat = mat + data->buffers.hits[pixel].mat_id;
	if (data->params.texture)
		data->buffers.hits[pixel].hit_rgb = sample_texture(tex, mat->kd_id, data->buffers.hits[pixel].uv);
	else
	 	data->buffers.hits[pixel].hit_rgb = rgb(0.7, 0.7, 0.7);
	if (data->params.ambient)
		data->buffers.hits[pixel].hit_ambient = sample_binary_texture(tex, mat->ambient_id, data->buffers.hits[pixel].uv);
	else
		data->buffers.hits[pixel].hit_ambient = 1.0f;
	if (data->params.normal_map)
	{
		nmap = sample_texture(tex, mat->normal_id, data->buffers.hits[pixel].uv);
		tangent = get_tangent(data->buffers.hits[pixel].normal);
		bitangent = get_bitangent(data->buffers.hits[pixel].normal, tangent);
		data->buffers.hits[pixel].normal = apply_normal_map(data->buffers.hits[pixel].normal, nmap, tangent, bitangent);
	}
	data->buffers.hits[pixel].ks = mat->ks;
	data->buffers.hits[pixel].ke = mat->ke;
	data->buffers.hits[pixel].ns = mat->ns;
}

void	sample_colors_loop(t_data *data, t_texture *tex, t_mat *mat, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		sample_colors(data, i, tex, mat);
		++i;
	}
}


