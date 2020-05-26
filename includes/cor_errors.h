/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cor_errors.h                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mmarcell <mmarcell@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/25 18:15:55 by mmarcell      #+#    #+#                 */
/*   Updated: 2020/05/25 18:15:55 by mmarcell      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef COR_ERRORS_H
# define COR_ERRORS_H

#include "corewar.h"

//TODO create error enum so exit_with_message can print the right message given
//its first param. 
//	0 -> usage
//	1 -> invalid option - general
//	2 -> invalid option - n flag
//	3 -> magic number incorrect
//	4 -> invalid playername
//	5 -> champion file does not exist
//	6 -> champion file too big
//	7 -> champion file too small
//	8 -> champion file incorrect format
//	9 -> champion program size too big

# define USAGE		"usage of corewar"
# define INV_OPT	"invalid options given"
# define INV_OPT_N
# define INV_MAGIC
# define INV_FILE_NAME
# define FILE_NOT_EXIST
# define FILE_TOO_BIG
# define FILE_TOO_SMALL
# define FILE_INCORRECT_FORMAT
# define CHAMP_TOO_BIG

// enum	e_errors
// {
// 	usage,
// 	inv_opt_general,
// 	inv_opt_n,
// 	some_other_error,
// 	inv_file_name,
// 	file_not_exist,
// 	file_too_big,
// 	file_too_small,
// 	file_incorrect_format,
// 	champ_too_big
// };

#endif
