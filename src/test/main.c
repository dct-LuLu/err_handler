/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 08:21:48 by jaubry--          #+#    #+#             */
/*   Updated: 2025/10/09 13:51:23 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "xcerrcal.h"

#define BIN_ID 1

typedef enum e_bin_err
{
	ERR1 = 1,
	ERR2,
	ERR3,
	ERR4,
	ERR5,
	ERRS_NUM
}	t_bin_err;

#define ERR1_MSG "complex error %d"
#define ERR2_MSG "test 2"
#define ERR3_MSG "test 3"
#define ERR4_MSG "test 4"
#define ERR5_MSG "test 5"

void	register_errors(void)
{
	const char	*err_msgs[] = 
	{
		ERR1_MSG,
		ERR2_MSG,
		ERR3_MSG,
		ERR4_MSG,
		ERR5_MSG
	};
	bulk_register_error(ERRS_NUM - 1, BIN_ID, (const char **)err_msgs);
}


int	err5(void)
{
	errno = 1;
	return (error(pack_err(BIN_ID, ERR5), __FILE__, __LINE__, __func__));
}

int	err4(void)
{
	if (err5())
		return (error(pack_err(BIN_ID, ERR4), __FILE__, __LINE__, __func__));
	return (0);
}

int	err3(void)
{
	if (err4())
		return (error(pack_err(BIN_ID, ERR3), __FILE__, __LINE__, __func__));
	return (0);
}

int	err2(void)
{
	if (err3())
		return (error(pack_err(BIN_ID, ERR2), __FILE__, __LINE__, __func__));
	return (0);
}

int	err1(void)
{
	if (err2())
	{
		errno = 5;
		register_complex_err_msg(ERR1_MSG, 22);
		register_complex_err_msg(ERR1_MSG, 22);
		return (error(pack_err(BIN_ID, ERR1), __FILE__, __LINE__, __func__));
	}
	return (0);
}

int	main(void)
{
	register_errors();
	if (err1())
		error(pack_err(BIN_ID, ERR2), __FILE__, __LINE__, __func__);
	print_errs();
	return (0);
}

// ❯ ./test
// [src/test/main.c:90] in main()
// test 2

//     [src/test/main.c:81] in err1()
//     complex error 22
//     complex error 22:
//     Input/output error

//         [src/test/main.c:70] in err2()
//         test 2

//             [src/test/main.c:63] in err3()
//             test 3

//                 [src/test/main.c:56] in err4()
//                 test 4

//                     [src/test/main.c:50] in err5()
//                     test 5:
//                     Operation not permitted
