/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 10:53:16 by tdubois           #+#    #+#             */
/*   Updated: 2023/04/26 17:46:49 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <minirt/parser/parser_int.h>

//**** PARSER DIRECTIVES *****************************************************//

static const t_directive	g_directives[] = {
{
	.identifier = "C",
	.usage = "C <position> <orientation vector> <fov>"
},
};

//**** PARSER ERRORS *********************************************************//

//---- filename errors -------------------------------------------------------//

static const char			g_file_err[] = \
	"Error"																"\n"
	"<%s>: %s"															"\n";

#endif//PARSER_H
