/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_position.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 13:27:59 by tdubois           #+#    #+#             */
/*   Updated: 2023/04/18 13:41:57 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt/parser/parser.h>
#include <libft/libft.h>
#include <stdio.h>

//############################################################################//
//#### DECLARATIONS ##########################################################//

t_parsing_error			parse_position(
							t_line_info const *line_info,
							char const *field_name,
							char *field,
							void *ret_ptr);

static t_parsing_error	parse_coords(
							t_line_info const *line_info,
							char const *field,
							char *field_cpy,
							t_vec3 *ret_pos);

static t_parsing_error	parse_coord(
							t_line_info const *line_info,
							char const *field,
							char **field_cpy,
							float *ret_coord);

static t_parsing_error	check_missing_or_empty_coord(
							t_line_info const *line_info,
							char const *field,
							char const *nptr);

static t_parsing_error	check_leading_non_digit(
							t_line_info const *line_info,
							char const *field,
							char const *nptr);

//############################################################################//
//#### DEFINITIONS ###########################################################//

t_parsing_error	parse_position(
					t_line_info const *line_info,
					char const *field_name,
					char *field,
					void *ret_ptr)
{
	t_vec3 *const	ret_pos = ret_ptr;
	t_parsing_error	err;
	char			*field_cpy;

	(void) field_name;
	field_cpy = ft_strdup(field);
	if (field_cpy == NULL)
		return (PARSING_FAILURE);
	err = parse_coords(line_info, field, field_cpy, ret_pos);
	ft_memdel(&field_cpy);
	return (err);
}

static t_parsing_error	parse_coords(
							t_line_info const *line_info,
							char const *field,
							char *field_cpy,
							t_vec3 *ret_pos)
{
	if (parse_coord(
			line_info, field, &field_cpy, &ret_pos->x) == PARSING_FAILURE)
		return (PARSING_FAILURE);
	if (parse_coord(
			line_info, field, &field_cpy, &ret_pos->y) == PARSING_FAILURE)
		return (PARSING_FAILURE);
	if (parse_coord(
			line_info, field, &field_cpy, &ret_pos->z) == PARSING_FAILURE)
		return (PARSING_FAILURE);
	if (field_cpy != NULL)
	{
		printf(g_too_many_coords_error, line_info->basename,
			line_info->line_nbr, line_info->line, field, field_cpy);
		return (PARSING_FAILURE);
	}
	return (PARSING_SUCCESS);
}

static t_parsing_error	parse_coord(
							t_line_info const *line_info,
							char const *field,
							char **field_cpy,
							float *ret_coord)
{
	char	*nptr;
	char	*endptr;

	nptr = ft_strsep(field_cpy, ",");
	if (check_missing_or_empty_coord(
			line_info, field, nptr) == PARSING_FAILURE)
		return (PARSING_FAILURE);
	if (check_leading_non_digit(line_info, field, nptr) == PARSING_FAILURE)
		return (PARSING_FAILURE);
	*ret_coord = ft_strtof(nptr, &endptr);
	if (endptr[0] != '\0')
	{
		printf(g_coord_trailing_non_digit_error, line_info->basename,
			line_info->line_nbr, line_info->line, field, nptr);
		return (PARSING_FAILURE);
	}
	return (PARSING_SUCCESS);
}

static t_parsing_error	check_missing_or_empty_coord(
							t_line_info const *line_info,
							char const *field,
							char const *nptr)
{
	if (nptr == NULL)
	{
		printf(g_missing_coord_error, line_info->basename,
			line_info->line_nbr, line_info->line, field);
		return (PARSING_FAILURE);
	}
	if (nptr[0] == '\0')
	{
		printf(g_empty_coord_error, line_info->basename,
			line_info->line_nbr, line_info->line, field);
		return (PARSING_FAILURE);
	}
	return (PARSING_SUCCESS);
}

static t_parsing_error	check_leading_non_digit(
							t_line_info const *line_info,
							char const *field,
							char const *nptr)
{
	if (!ft_isdigit(nptr[0]) && nptr[0] != '-')
	{
		printf(g_coord_leading_non_digit_error, line_info->basename,
			line_info->line_nbr, line_info->line, field, nptr);
		return (PARSING_FAILURE);
	}
	return (PARSING_SUCCESS);
}
