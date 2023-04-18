/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_errors.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 10:19:59 by tdubois           #+#    #+#             */
/*   Updated: 2023/04/18 17:24:02 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_ERRORS_H
# define PARSER_ERRORS_H

typedef enum e_parsing_error
{
	PARSING_SUCCESS,
	PARSING_FAILURE,
	PARSING_FILE_END_ERR,
}	t_parsing_error;

//**** FILENAME ERRORS *******************************************************//

static const char	g_empty_filename_error_msg[] = \
	"Error"																"\n"
	""																	"\n"
	"Invalid path `%s'"													"\n"
	"Expected non empty filename"										"\n";

static const char	g_filename_extension_error_msg[] = \
	"Error"																"\n"
	""																	"\n"
	"Invalid file name `%s'"											"\n"
	"Expected file ending in `.rt'"										"\n";

static const char	g_filename_too_short_error_msg[] = \
	"Error"																"\n"
	""																	"\n"
	"Invalid file name `%s'"											"\n"
	"Expected non empty filename before extension"						"\n";

//**** IO ERRORS *************************************************************//

static const char	g_file_opening_error_msg[] = \
	"Error"																"\n"
	""																	"\n"
	"couldn't open `%s': %s"											"\n";

static const char	g_reading_error_msg[] = \
	"Error"																"\n"
	""																	"\n"
	"file `%s':"														"\n"
	""																	"\n"
	"  couldn't read line %i: %s"										"\n";

//**** DIRECTIVE RELATED SYNTAX ERRORS ***************************************//

static const char	g_missing_camera_error_msg[] = \
	"Error"																"\n"
	""																	"\n"
	"file `%s':"														"\n"
	""																	"\n"
	"  missing camera directive"										"\n"
	""																	"\n"
	"Usage: C <pos> <orientation> <fov>"								"\n";

static const char	g_unknown_directive_identifier_error_msg[] = \
	"Error"																"\n"
	""																	"\n"
	"file `%s', line %i: %s"											"\n"
	""																	"\n"
	"  Unknown identifier `%s'"											"\n"
	"  Expected indentifier in list:"									"\n"
	"    C, A, L, sp, pl, cy"											"\n";

static const char	g_too_many_ambient_lightning_directives_error[] = \
	"Error"																"\n"
	""																	"\n"
	"file `%s', line %i: %s"											"\n"
	""																	"\n"
	"  too many ambient lightning directives"							"\n"
	"  expected only one"												"\n";

static const char	g_too_many_spotlights_error[] = \
	"Error"																"\n"
	""																	"\n"
	"file `%s', line %i: %s"											"\n"
	""																	"\n"
	"too many spot light directives"									"\n"
	"expected only one"													"\n";

//**** GENERAL FIELD RELATED SYNTAX ERRORS ***********************************//

static const char	g_unexpected_trailing_chars_err[] = \
	"Error"																"\n"
	""																	"\n"
	"file `%s', line %i: %s"											"\n"
	""																	"\n"
	"while parsing %s field: %s"										"\n"
	"  unexpected trailing chars: %s"									"\n";

static const char	g_too_many_fields_error[] = \
	"Error"																"\n"
	""																	"\n"
	"file `%s', line %i: %s"											"\n"
	""																	"\n"
	"unexpected fields: %s %s"												"\n";

static const char	g_missing_field_error[] = \
	"Error"																"\n"
	""																	"\n"
	"file `%s', line %i: %s"											"\n"
	""																	"\n"
	"missing field `%s'"												"\n";

static const char	g_usage_footer_msg[] = \
	""																	"\n"
	"Usage: %s"															"\n";

//**** BRIGHTNESS FIELD RELATED SYNTAX ERRORS ********************************//

static const char	g_invalid_brightness_format_err[] = \
	"Error"																"\n"
	""																	"\n"
	"file `%s', line %i: %s"											"\n"
	""																	"\n"
	"while parsing brightness field: %s"								"\n"
	"  invalid format"													"\n"
	"  expected floating point number in range [0.0, 1.0]"				"\n";

static const char	g_invalid_brightness_range_err[] = \
	"Error"																"\n"
	""																	"\n"
	"file `%s', line %i: %s"											"\n"
	""																	"\n"
	"while parsing brightness field: %s"								"\n"
	"  invalid range"													"\n"
	"  expected floating point number in range [0.0, 1.0]"				"\n";

//**** COLOR FIELD RELATED SYNTAX ERRORS *************************************//

static const char	g_too_many_color_channels_error[] = \
	"Error"																"\n"
	""																	"\n"
	"file `%s', line %i: %s"											"\n"
	""																	"\n"
	"while parsing color field: %s"										"\n"
	"  too many color channels"											"\n"
	"  consider removing `,%s'"											"\n";

static const char	g_invalid_color_channel_range_error[] = \
	"Error"																"\n"
	""																	"\n"
	"file `%s', line %i: %s"											"\n"
	""																	"\n"
	"while parsing color field: %s"										"\n"
	"  invalid range for channel: %s"									"\n"
	"  expected three comma separated r,g,b channels in range [0, 255]"	"\n";

static const char	g_color_channel_trailing_non_digit_error[] = \
	"Error"																"\n"
	""																	"\n"
	"file `%s', line %i: %s"											"\n"
	""																	"\n"
	"while parsing color field: %s"										"\n"
	"  invalid format, unexpected chars: %s"							"\n"
	"  expected three comma separated r,g,b channels in range [0, 255]"	"\n";

static const char	g_missing_color_channel_error[] = \
	"Error"																"\n"
	""																	"\n"
	"file `%s', line %i: %s"											"\n"
	""																	"\n"
	"while parsing color field: %s"										"\n"
	"  missing channel"													"\n"
	"  expected three comma separated r,g,b channels in range [0, 255]"	"\n";

static const char	g_empty_color_channel_error[] = \
	"Error"																"\n"
	""																	"\n"
	"file `%s', line %i: %s"											"\n"
	""																	"\n"
	"while parsing color field: %s"										"\n"
	"  empty channel"													"\n"
	"  expected three comma separated r,g,b channels in range [0, 255]"	"\n";

static const char	g_color_channel_leading_non_digit_error[] = \
	"Error"																"\n"
	""																	"\n"
	"file `%s', line %i: %s"											"\n"
	""																	"\n"
	"while parsing color field: %s"										"\n"
	"  invalid format: %s"												"\n"
	"  expected three comma separated r,g,b channels in range [0, 255]"	"\n";

//**** POSITION FIELD RELATED SYNTAX ERRORS **********************************//

static const char	g_too_many_coords_error[] = \
	"Error"																"\n"
	""																	"\n"
	"file `%s', line %i: %s"											"\n"
	""																	"\n"
	"while parsing position field: %s"									"\n"
	"  too many coordinates"											"\n"
	"  consider removing `,%s'"											"\n";

static const char	g_missing_coord_error[] = \
	"Error"																"\n"
	""																	"\n"
	"file `%s', line %i: %s"											"\n"
	""																	"\n"
	"while parsing position field: %s"									"\n"
	"  missing coordinate"												"\n"
	"  expected three comma separated x,y,z floating point coordinates"	"\n";

static const char	g_empty_coord_error[] = \
	"Error"																"\n"
	""																	"\n"
	"file `%s', line %i: %s"											"\n"
	""																	"\n"
	"while parsing position field: %s"									"\n"
	"  empty coordinate"												"\n"
	"  expected three comma separated x,y,z floating point coordinates"	"\n";

static const char	g_coord_trailing_non_digit_error[] = \
	"Error"																"\n"
	""																	"\n"
	"file `%s', line %i: %s"											"\n"
	""																	"\n"
	"while parsing position field: %s"									"\n"
	"  invalid format, unexpected chars: %s"							"\n"
	"  expected three comma separated x,y,z floating point coordinates"	"\n";

static const char	g_coord_leading_non_digit_error[] = \
	"Error"																"\n"
	""																	"\n"
	"file `%s', line %i: %s"											"\n"
	""																	"\n"
	"while parsing position field: %s"									"\n"
	"  invalid format: %s"												"\n"
	"  expected three comma separated x,y,z floating point coordinates"	"\n";

#endif//PARSER_ERRORS_H
