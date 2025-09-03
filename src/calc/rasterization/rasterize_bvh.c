/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rasterize_bvh.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <pabellis@student.forty2.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 23:47:07 by pabellis          #+#    #+#             */
/*   Updated: 2025/09/03 23:37:17 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bvh.h"
#include "minirt.h"
#include "render.h"
#include "mlx_wrapper.h"

int rasterize_bvh(t_bvh *bvh, t_img_data *img, t_camera *camera)
{
    t_vec3 vertices[8];

    vertices[0] = bvh->pos;
    vertices[1] = vec3(bvh->pos.x + bvh->size.x, bvh->pos.y, bvh->pos.z);
    vertices[2] = vec3(bvh->pos.x + bvh->size.x, bvh->pos.y + bvh->size.y, bvh->pos.z);
    vertices[3] = vec3(bvh->pos.x, bvh->pos.y + bvh->size.y, bvh->pos.z);
    vertices[4] = vec3(bvh->pos.x, bvh->pos.y, bvh->pos.z + bvh->size.z);
    vertices[5] = vec3(bvh->pos.x + bvh->size.x, bvh->pos.y, bvh->pos.z + bvh->size.z);
    vertices[6] = vec3(bvh->pos.x + bvh->size.x, bvh->pos.y + bvh->size.y, bvh->pos.z + bvh->size.z);
    vertices[7] = vec3(bvh->pos.x, bvh->pos.y + bvh->size.y, bvh->pos.z + bvh->size.z);

    t_vec2i projected[8];
    int i;

    i = 0;
    while (i < 8)
    {
        projected[i] = projection_matrix(&vertices[i], camera);
        ++i;
    }

    ft_mlx_line_put(img, projected[0], projected[1], 0x00FFFF);
    ft_mlx_line_put(img, projected[1], projected[2], 0x00FFFF);
    ft_mlx_line_put(img, projected[2], projected[3], 0x00FFFF);
    ft_mlx_line_put(img, projected[3], projected[0], 0x00FFFF);

    ft_mlx_line_put(img, projected[4], projected[5], 0x00FFFF);
    ft_mlx_line_put(img, projected[5], projected[6], 0x00FFFF);
    ft_mlx_line_put(img, projected[6], projected[7], 0x00FFFF);
    ft_mlx_line_put(img, projected[7], projected[4], 0x00FFFF);

    ft_mlx_line_put(img, projected[0], projected[4], 0x00FFFF);
    ft_mlx_line_put(img, projected[1], projected[5], 0x00FFFF);
    ft_mlx_line_put(img, projected[2], projected[6], 0x00FFFF);
    ft_mlx_line_put(img, projected[3], projected[7], 0x00FFFF);

	if (bvh->depth != 0)
	{
		rasterize_bvh(bvh->next_a, img, camera);
		rasterize_bvh(bvh->next_b, img, camera);
	}
    return (0);
}
