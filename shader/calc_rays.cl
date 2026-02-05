// vim: ft=c

#include "include/gpu.cl"

float2 random_in_unit_disk(uint *rng)
{
	float	r;
	float	theta;

	r = sqrt(randomf(rng));
	theta = 2.0f * M_PI_F * randomf(rng);
	return (float2)(r * cos(theta), r * sin(theta));
}

t_ray_gpu calc_ray(__private t_camera_gpu *cam, int2 pos, uint *rng)
{
	t_ray_gpu	ray;
	float3		x_offset;
	float3		y_offset;
	float3		pixel_center;
	float		jx;
	float		jy;
	float3		focal_point;
	float2		disk;
	float3		lens_offset;

	jx = randomf(rng) - 0.5f;
	jy = randomf(rng) - 0.5f;
	x_offset = cam->pixel_delta_u * ((float)pos.x + jx);
	y_offset = cam->pixel_delta_v * ((float)pos.y + jy);
	pixel_center = cam->pixel00_loc + x_offset + y_offset;
	ray.dir = normalize(pixel_center - cam->pos);
	focal_point = cam->pos + ray.dir * cam->focus_dist;
	disk = random_in_unit_disk(rng) * cam->lens_radius;
	lens_offset = cam->camera_right * disk.x + cam->camera_up * disk.y;
	ray.origin = cam->pos + lens_offset;
	ray.dir = normalize(focal_point - ray.origin);
	ray.inv_dir = 1.0f / ray.dir;
	return ray;
}
