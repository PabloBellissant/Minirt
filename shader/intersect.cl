// vim: ft=c

#include "include/gpu.cl"
#include "fill_uv_normal.cl"

#define TRIANGLE_EPSILON 1e-6f
#define WIDE_BVH_STACK_SIZE 64

int	intersect_triangle(__private t_ray_gpu *ray, __constant t_triangle_gpu *tr, float *t)
{
	float3	h;
	float	f;
	float3	s;
	float	u;
	float	v;

	h = cross(ray->dir, tr->edge_p2p0);
	f = dot(tr->edge_p1p0, h);
	if (fabs(f) < TRIANGLE_EPSILON)
		return (0);
	f = 1.0f / f;
	s = ray->origin - tr->p0.pos;
	u = f * dot(s, h);
	if (u < 0.0f || u > 1.0f)
		return (0);
	s = cross(s, tr->edge_p1p0);
	v = f * dot(ray->dir, s);
	if (v < 0.0f || u + v > 1.0f)
		return (0);
	*t = f * dot(tr->edge_p2p0, s);
	return (*t > TRIANGLE_EPSILON);
}

int intersect_sphere(__private t_ray_gpu *ray, __constant t_sphere_gpu *sp, float *t)
{
	float3 oc;
	float b;
	float c;
	float discriminant;
	float sqrt_d;
	float t_min;
	float t_max;

	oc = ray->origin - sp->pos;

	b = 2.0f * (ray->dir.x * oc.x + ray->dir.y * oc.y + ray->dir.z * oc.z);
	c = oc.x * oc.x + oc.y * oc.y + oc.z * oc.z - ((sp->diameter / 2.0f) * (sp->diameter / 2.0f));

	discriminant = b * b - 4.0f * c;
	if (discriminant < 0.0f)
		return 0;

	sqrt_d = sqrt(discriminant);
	t_min = (-b - sqrt_d) / (2.0f);
	t_max = (-b + sqrt_d) / (2.0f);

	*t = min(t_min, t_max);
	if (*t <= 0.0f)
		*t = max(t_min, t_max);
	return (*t > 0.01f);
}

#define PLANE_EPSILON 1e-5f

int	intersect_plane(__private t_ray_gpu *ray, __constant t_plane_gpu *plane, float *t)
{
	float	denom;

	denom = dot(ray->dir, plane->normal);
	if (fabs(denom) < PLANE_EPSILON)
		return (0);
	*t = dot(plane->pos - ray->origin, plane->normal) / denom;
	return (*t >= PLANE_EPSILON);
}

bool	hit_box(__private t_ray_gpu *ray, __constant t_bvh_gpu *bvh)
{
	float	t_min;
	float	t_max;
	float3	min_val;
	float3	max_val;

	min_val = (bvh->min - ray->origin) * ray->inv_dir;
	max_val = (bvh->max - ray->origin) * ray->inv_dir;
	t_min = min(min_val.x, max_val.x);
	t_max = max(min_val.x, max_val.x);
	t_min = max(min(min_val.y, max_val.y), t_min);
	t_max = min(max(min_val.y, max_val.y), t_max);
	if (t_min > t_max)
		return (false);
	t_min = max(min(min_val.z, max_val.z), t_min);
	t_max = min(max(min_val.z, max_val.z), t_max);
	if (t_min > t_max)
		return (false);
	if (t_max < 0.0f)
		return (false);
	return (true);
}

int hit_sphere_bvh(__private t_ray_gpu *ray, __constant t_bvh_gpu *bvh, __constant t_sphere_gpu *spheres, float *t)
{
	int		node;
	int		nearest;
	float	distance;

	if (bvh[0].depth == 0 && bvh[0].object == -1)
		return (-1);
	nearest = -1;
	if (bvh[0].bvh_type == BVH2)
	{
		node = 0;
		while (node != -1)
		{
			if (hit_box(ray, &bvh[node]))
			{
				if (bvh[node].depth == 0)
				{
					if (intersect_sphere(ray, &spheres[bvh[node].object], &distance) != 0)
					{
						if (distance < *t)
						{
							*t = distance;
							nearest = bvh[node].object;
						}
					}
					node = bvh[node].skip;
				}
				else
					++node;
			}
			else
				node = bvh[node].skip;
		}
	}
	else
	{
		int		stack[WIDE_BVH_STACK_SIZE];
		int		sp;
		int		i;
		int		child;
		int		leaf;

		sp = 0;
		stack[sp++] = 0;
		while (sp > 0)
		{
			node = stack[--sp];
			if ((node < 0) || !hit_box(ray, &bvh[node]))
				continue ;
			if (bvh[node].depth == 0)
			{
				i = 0;
				while (i < bvh[node].child_count)
				{
					leaf = bvh[node].children[i];
					if (leaf < 0)
					{
						leaf = -1 - leaf;
						if (intersect_sphere(ray, &spheres[leaf], &distance))
						{
							if (distance < *t)
							{
								*t = distance;
								nearest = leaf;
							}
						}
					}
					++i;
				}
			}
			else
			{
				i = 0;
				while (i < bvh[node].child_count)
				{
					child = bvh[node].children[i];
					if (child >= 0 && sp < WIDE_BVH_STACK_SIZE)
						stack[sp++] = child;
					++i;
				}
			}
		}
	}
	return (nearest);
}

int hit_triangle_bvh(__private t_ray_gpu *ray, __constant t_bvh_gpu *bvh, __constant t_triangle_gpu *triangles, float *t)
{
	int		node;
	int		nearest;
	float	distance;

	if (bvh[0].depth == 0 && bvh[0].object == -1)
		return (-1);
	nearest = -1;
	if (bvh[0].bvh_type == BVH2)
	{
		node = 0;
		while (node != -1)
		{
			if (hit_box(ray, &bvh[node]))
			{
				if (bvh[node].depth == 0)
				{
				if (intersect_triangle(ray, &triangles[bvh[node].object], &distance) != 0)
					{
						if (distance < *t)
						{
							*t = distance;
							nearest = bvh[node].object;
						}
					}
					node = bvh[node].skip;
				}
				else
					++node;
			}
			else
				node = bvh[node].skip;
		}
	}
	else
	{
		int		stack[WIDE_BVH_STACK_SIZE];
		int		sp;
		int		i;
		int		child;
		int		leaf;

		sp = 0;
		stack[sp++] = 0;
		while (sp > 0)
		{
			node = stack[--sp];
			if ((node < 0) || !hit_box(ray, &bvh[node]))
				continue ;
			if (bvh[node].depth == 0)
			{
				i = 0;
				while (i < bvh[node].child_count)
				{
					leaf = bvh[node].children[i];
					if (leaf < 0)
					{
						leaf = -1 - leaf;
						if (intersect_triangle(ray, &triangles[leaf],
								&distance))
						{
							if (distance < *t)
							{
								*t = distance;
								nearest = leaf;
							}
						}
					}
					++i;
				}
			}
			else
			{
				i = 0;
				while (i < bvh[node].child_count)
				{
					child = bvh[node].children[i];
					if (child >= 0 && sp < WIDE_BVH_STACK_SIZE)
						stack[sp++] = child;
					++i;
				}
			}
		}
	}
	return (nearest);
}

int	hit_plane_gpu(__private t_ray_gpu *ray, __constant t_plane_gpu *planes, int planes_count, float *t)
{
	int		i;
	int		nearest;
	float	distance;

	nearest = -1;
	i = 0;
	while (i < planes_count)
	{
		if (intersect_plane(ray, &planes[i], &distance) != 0)
		{
			if (distance < *t)
			{
				*t = distance;
				nearest = i;
			}
		}
		++i;
	}
	return (nearest);
}

t_hit_gpu	hit_register_gpu(__private t_ray_gpu *ray, __private t_objects *objects)
{
	int			hit_triangle;
	int			hit_plane;
	t_hit_gpu	hit;
	float		t;

	t = FLT_MAX;
	hit.hit_obj = hit_sphere_bvh(ray, objects->sphere_bvh, objects->spheres, &t);
	hit_plane = hit_plane_gpu(ray, objects->planes, objects->planes_count, &t);
	hit_triangle = hit_triangle_bvh(ray, objects->triangle_bvh, objects->triangles, &t);
	if (hit_triangle != -1)
	{
		hit.hit_obj = hit_triangle;
		hit.hit_point = ray->origin + (ray->dir * t);
		fill_triangle_uv_normal(hit.hit_point, &objects->triangles[hit.hit_obj], &hit.uv, &hit.normal);
		hit.mat_id = objects->triangles[hit.hit_obj].mat; 
		hit.hit_type = TRIANGLE;
	}
	else if (hit_plane != -1)
	{
		hit.hit_obj = hit_plane;
		hit.hit_point = ray->origin + (ray->dir * t);
		fill_plane_uv_normal(hit.hit_point, &objects->planes[hit.hit_obj], &hit.uv, &hit.normal);
		hit.mat_id = objects->planes[hit.hit_obj].mat; 
		hit.hit_type = PLANE;
	}
	else if (hit.hit_obj != -1)
	{
		hit.hit_point = ray->origin + (ray->dir * t);
		fill_sphere_uv_normal(hit.hit_point, &objects->spheres[hit.hit_obj], &hit.uv, &hit.normal);
		hit.mat_id = objects->spheres[hit.hit_obj].mat; 
		hit.hit_type = SPHERE;
	}
	else
	{
		hit.hit_type = SKYBOX;
		fill_skybox_uv(ray->dir, &hit.uv);
		hit.normal = ray->dir;
	}
	hit.uv.x -= floor(hit.uv.x);
	hit.uv.y -= floor(hit.uv.y);
	hit.uv.y = 1.0f - hit.uv.y;
	return (hit);
}
