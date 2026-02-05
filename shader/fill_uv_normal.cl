// vim: ft=c

#include "include/gpu.cl"

void	fill_sphere_uv_normal(float3 hit_point, __constant t_sphere_gpu *sphere, __private float2 *uv, __private float3 *norm)
{
	*norm = normalize(hit_point - sphere->pos);
	uv->x = 0.5f + atan2(norm->z, norm->x) / (2.0f * M_PI);
	uv->y = 0.5f + asin(norm->y) / M_PI;
}

void	fill_plane_uv_normal(float3 hit_point, __constant t_plane_gpu *plane, __private float2 *uv, __private float3 *norm)
{
	float3	local_point;

	local_point = hit_point - plane->pos;
	uv->x = dot(local_point, plane->tangent) * plane->texture_scaling;
	uv->y = dot(local_point, plane->bitangent) * plane->texture_scaling;
	*norm = plane->normal;
}

void	fill_triangle_uv_normal(float3 hit_point, __constant t_triangle_gpu *t, __private float2 *uv, __private float3 *norm)
{
	float3	bary;
	float	d20;
	float	d21;

	hit_point = hit_point - t->p0.pos;
	d20 = dot(hit_point, t->edge_p1p0);
	d21 = dot(hit_point, t->edge_p2p0);
	bary.y = (t->d11 * d20 - t->d01 * d21) / t->denom;
	bary.z = (t->d00 * d21 - t->d01 * d20) / t->denom;
	bary.x = 1.0f - bary.y - bary.z;
	uv->x = bary.x * t->p0.uv.x
		+ bary.y * t->p1.uv.x
		+ bary.z * t->p2.uv.x;
	uv->y = bary.x * t->p0.uv.y
		+ bary.y * t->p1.uv.y
		+ bary.z * t->p2.uv.y;
	*norm = t->p0.norm * bary.x + t->p1.norm * bary.y + t->p2.norm * bary.z;
	*norm = normalize(*norm);
}

void	fill_skybox_uv(float3 dir, __private float2 *uv)
{
	uv->x = 0.5f + atan2(dir.z, dir.x) / (2.0f * M_PI);
	uv->y = 0.5f + asin(dir.y) / M_PI;
}
