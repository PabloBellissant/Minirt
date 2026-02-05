/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gpu.cl                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <mail@bellissantpablo.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 05:00:27 by pabellis          #+#    #+#             */
/*   Updated: 2026/01/09 05:00:27 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GPU_H
# define GPU_H

typedef float3 rgb3;

# define MAX_BOUNCE 4

typedef struct s_camera_gpu
{
	float3	pos;
	float3	rot;
	float3	camera_forward;
	float3	camera_right;
	float3	camera_up;
	float3	pixel_delta_u;
	float3	pixel_delta_v;
	float3	pixel00_loc;
	int		fov;
	int		frame;
	float	lens_radius;
	float	focus_dist;
}	t_camera_gpu;

typedef struct s_ray_gpu
{
	float3	origin;
	float3	dir;
	float3	inv_dir;
}	t_ray_gpu;

typedef struct s_texture_data
{
	int	index;
	int	offset;
	int	width;
	int	height;
	int	channels;
}	t_texture_data;

typedef struct s_hit_gpu
{
	float3		normal;
	float2		uv;
	int			mat_id;
	float3		hit_point;
	int			hit_obj;
	int			hit_type;
}			t_hit_gpu;

typedef struct s_hit_data
{
	float3	kd;
	float3	normal;
	float3	ks;
	float3	ke;
	float3	reflectivity;
	float	metalness;
	float	roughness;
	float	ns;
	float	ambient;
	float	opacity;
	float	ni;
}			t_hit_data;

typedef struct s_mat_gpu
{
	char				*name;
	float			ns;
	float3			kd;
	float3			ks;
	float3			ke;
	float			opacity;
	t_texture_data		kd_id;
	t_texture_data		normal_id;
	t_texture_data		roughness_id;
	t_texture_data		ambient_id;
	t_texture_data		opacity_id;
	t_texture_data		metalness_id;
	float			ni;
}	t_mat_gpu;

typedef struct s_light_gpu
{
	rgb3	rgb;
	float3	pos;
}			t_light_gpu;

typedef struct s_sphere_gpu
{
	float3	pos;
	int		mat;
	float	diameter;
}			t_sphere_gpu;

typedef struct s_vertex
{
	float3		pos;
	union
	{
		struct
		{
			float	u;
			float	v;
		};
		float2	uv;
	};
	float3		norm;
}	t_vertex;

typedef struct s_triangle_gpu
{
	t_vertex	p0;
	t_vertex	p1;
	t_vertex	p2;
	float3		edge_p1p0;
	float3		edge_p2p0;
	int			mat;
	float		d00;
	float		d01;
	float		d11;
	float		denom;
}	t_triangle_gpu;

typedef struct s_plane_gpu
{
	float3	pos;
	float3	normal;
	float3	tangent;
	float3	bitangent;
	int		mat;
	float	texture_scaling;
}			t_plane_gpu;

typedef struct s_cuboid
{
	float3	min;
	float3	max;
}	t_cuboid;

typedef enum e_bvh_ary_type
{
	BVH2 = 0,
	BVH4,
	BVH8
}	t_bvh_ary_type;

typedef struct s_bvh_gpu
{
	union
	{
		struct
		{
			float3	min;
			float3	max;
		};
		t_cuboid	cuboid;
	};
	union
	{
		int	next;
		int	object;
		int	children[8];
	};
	int			depth;
	int			skip;
	int			child_count;
	int			bvh_type;
}	t_bvh_gpu;

typedef struct s_objects
{
	__constant t_sphere_gpu		*spheres;
	__constant t_bvh_gpu		*sphere_bvh;
	__constant t_triangle_gpu	*triangles;
	__constant t_bvh_gpu		*triangle_bvh;
	__constant t_plane_gpu		*planes;
	__constant t_light_gpu		*lights;
	__constant t_mat_gpu		*mats;
	int							lights_count;
	int							planes_count;
}	t_objects;

typedef enum e_object_type
{
	UNDEFINED,
	AMBIENT,
	CAMERA,
	LIGHT,
	SPHERE,
	PLANE,
	TRIANGLE,
	SKYBOX,
	MATERIAL,
	OBJ_ENUM_SIZE
}	t_object_type;

typedef struct e_emissive
{
	int				obj_id;
	t_object_type	type;
}	t_emissive;

t_ray_gpu	calc_ray(__private t_camera_gpu *cam, int2 pos, uint *rng);
float	randomf(uint *rng);

t_hit_gpu	hit_register_gpu(__private t_ray_gpu *ray, __private t_objects *objects);

void	fill_sphere_uv_normal(float3 hit_point, __constant t_sphere_gpu *sphere, __private float2 *uv, __private float3 *norm);
void	fill_plane_uv_normal(float3 hit_point, __constant t_plane_gpu *plane, __private float2 *uv, __private float3 *norm);
void	fill_triangle_uv_normal(float3 hit_point, __constant t_triangle_gpu *t, __private float2 *uv, __private float3 *norm);
void	fill_skybox_uv(float3 dir, __private float2 *uv);

t_hit_data	sample_materials(__private t_hit_gpu *hit, __constant uchar *tex, __constant t_mat_gpu *mat, __private t_ray_gpu *ray);
t_hit_data	sample_refract(__private t_hit_gpu *hit, __constant uchar *tex, __constant t_mat_gpu *mat, __private t_ray_gpu *ray, float random);

rgb3	sample_texture(__constant uchar *textures, float2 uv, __constant t_texture_data *data);
float	sample_gray_level_texture(__constant uchar *textures, float2 uv, __constant t_texture_data *data);

rgb3	phong_shading(__private t_hit_data *hit_data, __private t_hit_gpu *hit, __private t_ray_gpu *ray, __private t_objects *objects, rgb3 ambient);


#endif
