// vim: ft=c

#include "include/gpu.cl"

rgb3	sample_texture(__constant uchar *textures, float2 uv, __constant t_texture_data *data)
{
	int		x;
	int		y;
	uchar3	color;
	int		offset;

	x = (int)(uv.x * (float)(data->width));
	y = (int)(uv.y * (float)(data->height));
	offset = data->offset;
	offset += y * (data->width * data->channels) + x * data->channels;
	color.x = textures[offset];
	color.y = textures[offset + 1];
	color.z = textures[offset + 2];
	return ((rgb3) (color.x / 255.0f, color.y / 255.0f, color.z / 255.0f));
}

float	sample_gray_level_texture(__constant uchar *textures, float2 uv, __constant t_texture_data *data)
{
	int		x;
	int		y;
	uchar	pixel;
	int		offset;

	x = (int)(uv.x * (float)(data->width));
	y = (int)(uv.y * (float)(data->height));
	offset = data->offset;
	offset += y * data->width + x;
	pixel = textures[offset];
	return ((float) pixel / 255.0f);
}
