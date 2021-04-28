/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_codes.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncatrien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 11:37:57 by ncatrien          #+#    #+#             */
/*   Updated: 2021/04/28 07:22:10 by ncatrien         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODES_H
# define CODES_H

/* error messages */

# define E_NUM_ELEMT "Invalid number of elements for the object"
# define E_ALREADY_EXISTS "The object must be defined only once;\
 already defined"
# define E_INVAL "Invalid value(s)"
# define E_MEM "Memory problem (not enough space?)"
# define E_NORES "No resolution defined"
# define E_NOAMB "No ambient light defined"
# define E_NOCAM "No camera defined"
# define E_BADLINE "Invalid line type"
# define E_NOT_NORMED "Orientation vector is not normalized"
# define E_IMG_SIZE_MAX "The defined resolution is too high"

/* exit codes */
# define EXIT_FAIL_MLX (2)
# define EXIT_FAIL_BMP (3)

/* key codes */

# define K_ESC (53)
# define K_C (8)

#endif
