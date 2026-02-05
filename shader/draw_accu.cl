// vim: ft=c

# include "include/gpu.cl"

typedef union	u_color
{
	int	rgb;
	struct
	{
		uchar	b;
		uchar	g;
		uchar	r;
	};
}	t_color;

__kernel void	draw_accu(__global float3 *accu, __global int *img, int sample_count)
{
	int2	pos;
	int		pixel;
	t_color	color;
	float3	accu_divide;

	pos.x = get_global_id(0);
	pos.y = get_global_id(1);
	if (pos.x >= (int) get_global_size(0) || pos.y >= (int) get_global_size(1))
		return ;
	pixel = pos.y * get_global_size(0) + pos.x;
	accu_divide = (accu[pixel] / sample_count) * 255.0f;
	accu_divide = clamp(accu_divide, 0, 255);
	color.r = accu_divide[0];
	color.g = accu_divide[1];
	color.b = accu_divide[2];
	img[pixel] = color.rgb;
}
