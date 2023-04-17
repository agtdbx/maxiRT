/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_errors.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 10:19:59 by tdubois           #+#    #+#             */
/*   Updated: 2023/04/17 17:40:31 by tdubois          ###   ########.fr       */
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
	"Error"													"\n"
	""														"\n"
	"Invalid path `%s'"										"\n"
	"Expected non empty filename"							"\n";

static const char	g_filename_extension_error_msg[] = \
	"Error"													"\n"
	""														"\n"
	"Invalid file name `%s'"								"\n"
	"Expected file ending in `.rt'"							"\n";

static const char	g_filename_too_short_error_msg[] = \
	"Error"													"\n"
	""														"\n"
	"Invalid file name `%s'"								"\n"
	"Expected non empty filename before extension"			"\n";

//**** IO ERRORS *************************************************************//

static const char	g_file_opening_error_msg[] = \
	"Error"													"\n"
	""														"\n"
	"couldn't open `%s': %s"								"\n";

static const char	g_reading_error_msg[] = \
	"Error"													"\n"
	""														"\n"
	"file `%s':"											"\n"
	""														"\n"
	"  couldn't read line %i: %s"							"\n";

//**** DIRECTIVE RELATED SYNTAX ERRORS ***************************************//

static const char	g_missing_camera_error_msg[] = \
	"Error"													"\n"
	""														"\n"
	"file `%s':"											"\n"
	""														"\n"
	"  missing camera directive"							"\n"
	""														"\n"
	"Usage: C <pos> <orientation> <fov>"					"\n";

static const char	g_unknown_directive_identifier_error_msg[] = \
	"Error"													"\n"
	""														"\n"
	"file `%s', line %i: %s"								"\n"
	""														"\n"
	"  Unknown identifier `%s'"								"\n"
	"  Expected indentifier in list:"						"\n"
	"    C, A, L, sp, pl, cy"								"\n";

static const char	g_too_many_ambient_lightning_directives_error[] = \
	"Error"													"\n"
	""														"\n"
	"file `%s', line %i: %s"								"\n"
	""														"\n"
	"  too many ambient lightning directives"				"\n"
	"  expected only one"									"\n";

//**** GENERAL FIELD RELATED SYNTAX ERRORS ***********************************//

static const char	g_unexpected_trailing_chars_err[] = \
	"Error"													"\n"
	""														"\n"
	"file `%s', line %i: %s"								"\n"
	""														"\n"
	"while parsing %s field: %s"							"\n"
	"  unexpected trailing chars: %s"						"\n";

static const char	g_usage_footer_msg[] = \
	""														"\n"
	"Usage: %s"												"\n";

//**** BRIGHTNESS FIELD RELATED SYNTAX ERRORS ********************************//

static const char	g_invalid_brightness_format_err[] = \
	"Error"													"\n"
	""														"\n"
	"file `%s', line %i: %s"								"\n"
	""														"\n"
	"while parsing brightness field: %s"					"\n"
	"  invalid format"										"\n"
	"  expected floating point number in range [0.0, 1.0]"	"\n";

static const char	g_invalid_brightness_range_err[] = \
	"Error"													"\n"
	""														"\n"
	"file `%s', line %i: %s"								"\n"
	""														"\n"
	"while parsing brightness field: %s"					"\n"
	"  invalid range"										"\n"
	"  expected floating point number in range [0.0, 1.0]"	"\n";


#endif//PARSER_ERRORS_H
