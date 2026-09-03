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

inline float3 quat_rotate(float4 q, float3 v)
{
	float3	t;

    t = 2.0f * cross(q.xyz, v);
    return (v + q.w * t + cross(q.xyz, t));
}

int hit_sphere(__private t_ray_gpu *ray, __constant t_bvh_node_gpu *bvh)
{
	float3	oc;
	float	b;
	float	c;
	float	discriminant;
	float	sqrt_d;
	float	t_min;
	float	t_max;
	
	oc = ray->origin - bvh->bounds.sphere.pos;
	b = 2.0f * (ray->dir.x * oc.x + ray->dir.y * oc.y + ray->dir.z * oc.z);
	c = oc.x * oc.x + oc.y * oc.y + oc.z * oc.z - ((bvh->bounds.sphere.radius) * (bvh->bounds.sphere.radius));
	discriminant = b * b - 4.0f * c;
	if (discriminant < 0.0f)
		return (0);
	sqrt_d = sqrt(discriminant);
	t_min = (-b - sqrt_d) / (2.0f);
	t_max = (-b + sqrt_d) / (2.0f);
	if (t_min > 0.0f)
		return (1);
	if (t_max > 0.0f)
		return (1);
	return 0;
}

bool	hit_obb(__private t_ray_gpu *ray, __constant t_bvh_node_gpu *bvh)
{
	float	t_min;
	float	t_max;
	float3	min_val;
	float3	max_val;
	float4	qinv = (float4)(-bvh->bounds.obb.q.x, -bvh->bounds.obb.q.y, -bvh->bounds.obb.q.z, bvh->bounds.obb.q.w);
	float3	local_origin = quat_rotate(qinv, ray->origin - bvh->bounds.obb.center);
	float3	local_dir    = quat_rotate(qinv, ray->dir);
	float3	inv_dir      = 1.0f / local_dir;
	float3	minb = -bvh->bounds.obb.half_extents;
	float3	maxb =  bvh->bounds.obb.half_extents;

	min_val = (minb - local_origin) * inv_dir;
	max_val = (maxb - local_origin) * inv_dir;
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

bool	hit_aabb(__private t_ray_gpu *ray, __constant t_bvh_node_gpu *bvh)
{
	float	t_min;
	float	t_max;
	float3	min_val;
	float3	max_val;

	min_val = (bvh->bounds.aabb.min - ray->origin) * ray->inv_dir;
	max_val = (bvh->bounds.aabb.max - ray->origin) * ray->inv_dir;
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

int hit_bvh_sphere(__private t_ray_gpu *ray, __constant t_bvh_node_gpu *bvh, __constant t_triangle_gpu *triangles, __constant t_sphere_gpu *spheres, float *t)
{
	int		node;
	int		nearest;
	float	distance;

	nearest = -1;
	node = 0;
	while (node != -1)
	{
		if (hit_sphere(ray, &bvh[node]))
		{
			if (bvh[node].children[0] <= 0)
			{
				if ((bvh[node].type == TRIANGLE && intersect_triangle(ray, &triangles[bvh[node].object_id], &distance))
					|| (bvh[node].type == SPHERE && intersect_sphere(ray, &spheres[bvh[node].object_id], &distance)))
				{
					if (distance < *t)
					{
						*t = distance;
						nearest = node;
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
	return (nearest);
}

int hit_bvh_aabb(__private t_ray_gpu *ray, __constant t_bvh_node_gpu *bvh, __constant t_triangle_gpu *triangles, __constant t_sphere_gpu *spheres, float *t)
{
	int		node;
	int		nearest;
	float	distance;

	nearest = -1;
	node = 0;
	while (node != -1)
	{
		if (hit_aabb(ray, &bvh[node]))
		{
			if (bvh[node].children[0] <= 0)
			{
				if ((bvh[node].type == TRIANGLE && intersect_triangle(ray, &triangles[bvh[node].object_id], &distance))
					|| (bvh[node].type == SPHERE && intersect_sphere(ray, &spheres[bvh[node].object_id], &distance)))
				{
					if (distance < *t)
					{
						*t = distance;
						nearest = node;
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
	return (nearest);
}

int hit_bvh_obb(__private t_ray_gpu *ray, __constant t_bvh_node_gpu *bvh, __constant t_triangle_gpu *triangles, __constant t_sphere_gpu *spheres, float *t)
{
	int		node;
	int		nearest;
	float	distance;

	nearest = -1;
	node = 0;
	while (node != -1)
	{
		if (hit_obb(ray, &bvh[node]))
		{
			if (bvh[node].children[0] <= 0)
			{
				if ((bvh[node].type == TRIANGLE && intersect_triangle(ray, &triangles[bvh[node].object_id], &distance))
					|| (bvh[node].type == SPHERE && intersect_sphere(ray, &spheres[bvh[node].object_id], &distance)))
				{
					if (distance < *t)
					{
						*t = distance;
						nearest = node;
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

t_hit_gpu	hit_register_gpu(__private t_ray_gpu *ray, __private t_objects *objects, int type)
{
	int			hit_plane;
	t_hit_gpu	hit;
	float		t;

	t = FLT_MAX;
	hit.hit_obj = -1;
	if (type == 0)
		hit.hit_obj = hit_bvh_sphere(ray, objects->bvh, objects->triangles, objects->spheres, &t);
	else if (type == 1)
		hit.hit_obj = hit_bvh_aabb(ray, objects->bvh, objects->triangles, objects->spheres, &t);
	else
		hit.hit_obj = hit_bvh_obb(ray, objects->bvh, objects->triangles, objects->spheres, &t);
	hit_plane = hit_plane_gpu(ray, objects->planes, objects->planes_count, &t);
	if (hit_plane != -1)
	{
		hit.hit_obj = hit_plane;
		hit.hit_point = ray->origin + (ray->dir * t);
		fill_plane_uv_normal(hit.hit_point, &objects->planes[hit.hit_obj], &hit.uv, &hit.normal);
		hit.mat_id = objects->planes[hit.hit_obj].mat; 
		hit.hit_type = PLANE;
	}
	else if (hit.hit_obj != -1)
	{
		hit.hit_type = objects->bvh[hit.hit_obj].type;
		hit.hit_obj = objects->bvh[hit.hit_obj].object_id;
		hit.hit_point = ray->origin + (ray->dir * t);
		if (hit.hit_type == SPHERE)
		{
			fill_sphere_uv_normal(hit.hit_point, &objects->spheres[hit.hit_obj], &hit.uv, &hit.normal);
			hit.mat_id = objects->spheres[hit.hit_obj].mat; 
		}
		else
		{
			fill_triangle_uv_normal(hit.hit_point, &objects->triangles[hit.hit_obj], &hit.uv, &hit.normal);
			hit.mat_id = objects->triangles[hit.hit_obj].mat;
		}
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
