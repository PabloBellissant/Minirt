// vim: ft=c

# include "include/gpu.cl"

bool	hit_aabb(__private t_ray_gpu *ray, __constant t_bvh_node_gpu *bvh);
bool	hit_obb(__private t_ray_gpu *ray, __constant t_bvh_node_gpu *bvh);
int		hit_sphere(__private t_ray_gpu *ray, __constant t_bvh_node_gpu *bvh);

int hit_bvh_depth_sphere(__private t_ray_gpu *ray, __constant t_bvh_node_gpu *bvh)
{
	int	node;
	int	hit_count;

	if (bvh[0].children[0] <= 0 && bvh[0].object_id == -1)
		return (-1);
	node = 0;
	hit_count = 0;
	while (node != -1)
	{
		if (bvh[node].children[0] > 0 && hit_sphere(ray, &bvh[node]))
		{
			++hit_count;
			++node;
		}
		else
			node = bvh[node].skip;
	}
	return (hit_count);
}

int hit_bvh_depth_aabb(__private t_ray_gpu *ray, __constant t_bvh_node_gpu *bvh)
{
	int	node;
	int	hit_count;

	if (bvh[0].children[0] <= 0 && bvh[0].object_id == -1)
		return (-1);
	node = 0;
	hit_count = 0;
	while (node != -1)
	{
		if (bvh[node].children[0] > 0 && hit_aabb(ray, &bvh[node]))
		{
			++hit_count;
			++node;
		}
		else
			node = bvh[node].skip;
	}
	return (hit_count);
}

int hit_bvh_depth_obb(__private t_ray_gpu *ray, __constant t_bvh_node_gpu *bvh)
{
	int	node;
	int	hit_count;

	if (bvh[0].children[0] <= 0 && bvh[0].object_id == -1)
		return (-1);
	node = 0;
	hit_count = 0;
	while (node != -1)
	{
		if (bvh[node].children[0] > 0 && hit_obb(ray, &bvh[node]))
		{
			++hit_count;
			++node;
		}
		else
			node = bvh[node].skip;
	}
	return (hit_count);
}

int hit_bvh_depth(__private t_ray_gpu *ray, __constant t_bvh_node_gpu *bvh, int bvh_type)
{
	if (bvh_type == 0)
		return (hit_bvh_depth_sphere(ray, bvh));
	if (bvh_type == 1)
		return (hit_bvh_depth_aabb(ray, bvh));
	return (hit_bvh_depth_obb(ray, bvh));
}

typedef struct s_palette
{
	int		color_count;
	float3	color[4];
}	t_palette;

inline t_palette get_palette(int idx)
{
	const t_palette palettes[10] = {
		{
			.color_count = 2,
			.color = {
				(float3)(0.0f, 0.0f, 0.0f),
				(float3)(1.0f, 1.0f, 1.0f)
			}
		},
		{
			.color_count = 4,
			.color = {
				(float3)(0.0f, 0.0f, 0.5f),
				(float3)(0.0f, 0.8f, 1.0f),
				(float3)(1.0f, 1.0f, 0.0f),
				(float3)(1.0f, 0.0f, 0.0f)
			}
		},
		{
			.color_count = 4,
			.color = {
				(float3)(0.0f, 0.0f, 0.0f),
				(float3)(0.3f, 0.0f, 0.4f),
				(float3)(0.9f, 0.3f, 0.0f),
				(float3)(1.0f, 0.9f, 0.2f)
			}
		},
		{
			.color_count = 3,
			.color = {
				(float3)(0.1f, 0.0f, 0.4f),
				(float3)(0.0f, 0.7f, 0.5f),
				(float3)(0.9f, 0.9f, 0.2f)
			}
		},
		{
			.color_count = 3,
			.color = {
				(float3)(0.4f, 0.0f, 0.6f),
				(float3)(0.9f, 0.2f, 0.6f),
				(float3)(1.0f, 0.8f, 0.2f)
			}
		},
		{
			.color_count = 3,
			.color = {
				(float3)(0.0f, 0.0f, 0.0f),
				(float3)(0.7f, 0.1f, 0.0f),
				(float3)(1.0f, 0.9f, 0.3f)
			}
		},
		{
			.color_count = 3,
			.color = {
				(float3)(0.0f, 0.1f, 0.3f),
				(float3)(0.0f, 0.6f, 0.7f),
				(float3)(0.9f, 1.0f, 1.0f)
			}
		},
		{
			.color_count = 4,
			.color = {
				(float3)(0.0f, 0.0f, 0.0f),
				(float3)(0.6f, 0.0f, 0.0f),
				(float3)(1.0f, 0.5f, 0.0f),
				(float3)(1.0f, 1.0f, 1.0f)
			}
		},
		{
			.color_count = 3,
			.color = {
				(float3)(0.0f, 0.0f, 0.0f),
				(float3)(0.0f, 0.4f, 0.1f),
				(float3)(0.6f, 0.9f, 0.4f)
			}
		},
		{
			.color_count = 2,
			.color = {
				(float3)(0.15f, 0.15f, 0.15f),
				(float3)(0.9f, 0.9f, 0.9f)
			}
		}
	};
	return palettes[idx];
}

float3	heatmap(float v, int color_id)
{
	int		idx;
	float	scaled;
	float	t;
	v = clamp(v, 0.0f, 1.0f);
	color_id %= 10;
	t_palette p = get_palette(color_id);

	if (p.color_count <= 1)
		return (p.color[0]);

	scaled = v * (p.color_count - 1);
	idx = (int)scaled;
	t = scaled - idx;

	idx = clamp(idx, 0, p.color_count - 2);
	return (p.color[idx] + t * (p.color[idx + 1] - p.color[idx]));
}

__kernel void	heat(t_camera_gpu cam,
				   __constant t_bvh_node_gpu *bvh,
				   int bvh_type,
				   __global float3 *img,
				   int max_depth,
				   int color_offset)
{
	int2		pos;
	t_ray_gpu	ray;
	int			pixel;

	pos.x = get_global_id(0);
	pos.y = get_global_id(1);
	if (pos.x >= (int) get_global_size(0) || pos.y >= (int) get_global_size(1))
		return ;
	pixel = pos.y * get_global_size(0) + pos.x;
	uint		rng = cam.frame * get_global_size(1) * get_global_size(0) + pixel;
	ray = calc_ray(&cam, pos, &rng);
	int	hit_depth;
	hit_depth = hit_bvh_depth(&ray, bvh, bvh_type);
	if (hit_depth <= 1)
		return ;
	img[pixel] += heatmap((float) hit_depth / (max_depth * max_depth), color_offset);
}
