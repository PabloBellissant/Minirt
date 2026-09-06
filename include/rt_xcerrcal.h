/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_xcerrcal.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 21:37:36 by jaubry--          #+#    #+#             */
/*   Updated: 2026/02/07 04:46:32 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_XCERRCAL_H
# define RT_XCERRCAL_H

# define RT_ID 5

typedef enum e_rt_err
{
	RT_E_ARGC = 1,
	RT_E_GRAPHICS,
	RT_E_PARSING,
	RT_E_ARGS,
	RT_E_AMBIENT,
	RT_E_CAMERA,
	RT_E_LIGHT,
	RT_E_OBJ,
	RT_E_PLANE,
	RT_E_SKY,
	RT_E_SPHERE,
	RT_E_TEX,
	RT_E_OBJ_FAIL,
	RT_E_OBJ_NO_MAT,
	RT_E_NO_TEX,
	RT_E_NO_PARSER,
	RT_E_UNKNOW_MAT,
	RT_E_UNKNOW_TEX,
	RT_E_UNKNOW_NMAP,
	RT_E_UNKNOW_ROUGHNESS,
	RT_E_UNKNOW_AMBIENT,
	RT_E_UNKNOW_OPACITY,
	RT_E_FB_DOUBLE,
	RT_E_FB_NO,
	RT_E_VERTEX,
	RT_E_NORMAL,
	RT_E_UV,
	RT_E_FACE,
	RT_E_UNDEFINED_TYPE,
	RT_E_KERNEL,
	RT_ERRS_NUM
}	t_rt_err;

# define RT_E_MSG_ARGC "Wrong argument count, expected 1 argument in format: \
\"%s <file.rt>\", got %d"
# define RT_E_MSG_GRAPHICS "Initialize of graphics component failed"
# define RT_E_MSG_PARSING "Failed to correctly parse \"%s\" file"
# define RT_E_MSG_ARGS "Wrong argument name, argument must end with \".rt\", \
got \"%s\""

# define RT_E_MSG_AMBIENT "Ambient syntax invalid, expecting format: \
\"A ratio[0:1] R,G,B[0:255]\""
# define RT_E_MSG_CAMERA "Camera syntax invalid, expecting format: \
\"C posX,Y,Z rotX,Y,Z FOV[0:180]\""
# define RT_E_MSG_LIGHT "Light syntax invalid, expecting format: \
\"L posX,Y,Z brightness[0:1] R,G,B[0:255]\""
# define RT_E_MSG_OBJ "Object syntax invalid, expecting format: \
\"obj 'path.obj' posX,Y,Z\""
# define RT_E_MSG_PLANE "Plane syntax invalid, expecting format: \
\"pl posX,Y,Z normX,Y,Z[-1:1] R,G,B[0:255]\""
# define RT_E_MSG_SKY "Skybox syntax invalid, expecting format: \
\"sky [path.ppm]\""
# define RT_E_MSG_SPHERE "Sphere syntax invalid, expecting format: \
\"sp posX,Y,Z diameter R,G,B[0:255]\""
# define RT_E_MSG_TEX "Texture syntax invalid, expecting format: \
\"tex 'name' 'path'\""
# define RT_E_MSG_OBJ_FAIL ".obj extraction failed on \"%s\" file"
# define RT_E_MSG_OBJ_NO_MAT "No materials defined before face definition"
# define RT_E_MSG_NO_TEX "Cannot parse \"%s\" texture"
# define RT_E_MSG_NO_PARSER "Cannot parse this texture"

# define RT_E_MSG_UNKNOW_MAT "Unknow material \"%s\""

# define RT_E_MSG_UNKNOW_TEX "Unknow texture \"%s\""
# define RT_E_MSG_UNKNOW_NMAP "Unknow normal map \"%s\""
# define RT_E_MSG_UNKNOW_ROUGHNESS "Unknow roughness map \"%s\""
# define RT_E_MSG_UNKNOW_AMBIENT "Unknow ambient map \"%s\""
# define RT_E_MSG_UNKNOW_OPACITY "Unknow opacity map \"%s\""
# define RT_E_MSG_FB_DOUBLE "Cannot instance type \"%s\" twice"
# define RT_E_MSG_FB_NO "Cannot find needed type \"%s\""
# define RT_E_MSG_UNDEFINED_TYPE "Cannot recognize type \"%c\""
# define RT_E_MSG_KERNEL "Cannot start kernel."

# define RT_E_MSG_VERTEX "Cannot apply vertex"
# define RT_E_MSG_NORMAL "Cannot apply normal"
# define RT_E_MSG_UV "Cannot apply uv"
# define RT_E_MSG_FACE "Failed to parse face"

void	register_rt_errors(void);

#endif//RT_XCERRCAL_H
