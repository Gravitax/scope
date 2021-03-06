/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3d_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 01:18:43 by gedemais          #+#    #+#             */
/*   Updated: 2022/05/26 16:16:30 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_vec.h"

t_vec3d	zero_vector(void)
{
	return ((t_vec3d){0.0f, 0.0f, 0.0f, 0.0f});
}

float	vec_norm(t_vec3d vec)
{
	return (sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z));
}

t_vec3d	vec_normalize(t_vec3d vec)
{
	float	l;

	l = vec_norm(vec);
	return ((t_vec3d){vec.x /= l, vec.y /= l, vec.z /= l, vec.w /= l});
}

float	vec_dot(t_vec3d a, t_vec3d b)
{
	float	ret;

	ret = 0.0f;
	ret += a.x * b.x;
	ret += a.y * b.y;
	ret += a.z * b.z;
	return (ret);
}

float	vec3d_dist(t_vec3d o, t_vec3d v)
{
	return (sqrt((o.x - v.x) * (o.x - v.x)
		+ (o.y - v.y) * (o.y - v.y)
		+ (o.z - v.z) * (o.z - v.z)));
}
