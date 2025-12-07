/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sample_materials.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <pabellis@student.forty2.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 08:17:01 by pabellis          #+#    #+#             */
/*   Updated: 2025/12/02 08:17:04 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

float	sample_binary_texture(const t_texture *texture_list, int id, t_vec2 uv);
t_vec3	apply_normal_map(t_vec3 normal, t_vec3 nmap, t_vec3 tangent, t_vec3 bitangent);

void	sample_materials(t_hit *hits, int pixel, t_texture *tex, t_mat *mat)
{
	t_vec3	tangent;
	t_vec3	bitangent;
	t_rgb	nmap;

	mat = mat + hits[pixel].mat_id;
	hits[pixel].hit_rgb = sample_texture(tex, mat->kd_id, hits[pixel].uv);
	hits[pixel].hit_roughness = sample_binary_texture(tex, mat->roughness_id, hits[pixel].uv);
	hits[pixel].hit_ambient = sample_binary_texture(tex, mat->ambient_id, hits[pixel].uv);
	hits[pixel].hit_opacity = sample_binary_texture(tex, mat->opacity_id, hits[pixel].uv);
	nmap = sample_texture(tex, mat->normal_id, hits[pixel].uv);
	tangent = get_tangent(hits[pixel].normal);
	bitangent = get_bitangent(hits[pixel].normal, tangent);
	hits[pixel].normal = apply_normal_map(hits[pixel].normal, nmap, tangent, bitangent);
	hits[pixel].ks = mat->ks;
	hits[pixel].ke = mat->ke;
	hits[pixel].ns = mat->ns;
}
