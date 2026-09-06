/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   populate_mat_edit.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 17:04:02 by jaubry--          #+#    #+#             */
/*   Updated: 2026/02/19 20:44:11 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
	UI, top-to-bottom order is:

	1. **Base colors and opacity**
	   - `Kd` – Diffuse Color (base/albedo)  
	   - `Ka` – Ambient Color  
	   - `d` – Dissolve/Opacity  

	2. **Specular and shininess**
	   - `Ks` – Specular Color  
	   - `Ns` – Shininess/Specular Exponent  

	3. **PBR core controls**
	   - `Pr` – Roughness  
	   - `Pm` – Metallness  

	4. **Optical/advanced**
	   - `Ni` – Index of Refraction  
*/

int	add_ka_edit(t_data *data, t_hbranch *obj_edit, int *y_size, t_mat *mat);
int	add_kd_edit(t_data *data, t_hbranch *obj_edit, int *y_size, t_mat *mat);
int	add_d_edit(t_data *data, t_hbranch *obj_edit, int *y_size, t_mat *mat);

int	add_ks_edit(t_data *data, t_hbranch *obj_edit, int *y_size, t_mat *mat);
int	add_ns_edit(t_data *data, t_hbranch *obj_edit, int *y_size, t_mat *mat);

int	add_pr_edit(t_data *data, t_hbranch *obj_edit, int *y_size, t_mat *mat);
int	add_pm_edit(t_data *data, t_hbranch *obj_edit, int *y_size, t_mat *mat);

int	add_ni_edit(t_data *data, t_hbranch *obj_edit, int *y_size, t_mat *mat);

#define MAT_FIELDS 8

/*
	**`Ns` (Shininess/Specular Exponent)** - **0 to 1000**
		- 0 = very rough/dull surface
		- 1000 = mirror-like polish

	**`Ka` (Ambient Color)** - **0.0 to 1.0** per RGB channel
		- RGB values between 0.0 and 1.0

	**`Kd` (Diffuse Color)** - **0.0 to 1.0** per RGB channel
		- RGB values between 0.0 and 1.0

	**`Ks` (Specular Color)** - **0.0 to 1.0** per RGB channel
		- RGB values between 0.0 and 1.0

	**`Ni` (Index of Refraction)** - **0.001 to 10** (typical: 1.0 to 3.0)
		- 1.0 = air/vacuum
		- 1.33 = water
		- 1.5-1.9 = glass
		- 2.4 = diamond

	**`d` (Dissolve/Opacity)** - **0.0 to 1.0**
		- 0.0 = fully transparent
		- 1.0 = fully opaque

	**`Pr` (Roughness)** - **0.0 to 1.0**
		- 0.0 = perfectly smooth
		- 1.0 = completely rough

	**`Pm` (Metallness)** - **0.0 to 1.0**
		- 0.0 = non-metallic/dielectric
		- 1.0 = fully metallic
*/
int	populate_mat_edit(t_data *data, t_hbranch *obj_edit,
		int *y_size, t_mat *mat)
{
	static int	(*mat_edit_func[MAT_FIELDS])(t_data *, t_hbranch *,
			int *, t_mat *)
		= {
		add_kd_edit, add_ka_edit, add_d_edit,
		add_ks_edit, add_ns_edit,
		add_pr_edit, add_pm_edit,
		add_ni_edit
	};
	size_t		i;

	if (!mat)
		return (0);
	i = 0;
	while (i < MAT_FIELDS)
	{
		if (mat_edit_func[i](data, obj_edit, y_size, mat) != 0)
			return (1);
		i++;
	}
	return (0);
}
