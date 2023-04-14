/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsep.test.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 13:04:10 by tdubois           #+#    #+#             */
/*   Updated: 2023/04/07 13:34:14 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"

#include "greatest.h"

#include <stddef.h>
#include <string.h>

TEST	test1(void)
{
	char 	buf[] = "abc|def|||ghijk";
	char	*str = buf;
	char	*tok = NULL;

	tok = ft_strsep(&str, "|");
	ASSERT_STR_EQ("abc", tok);
	ASSERT_STR_EQ("def|||ghijk", str);

	tok = ft_strsep(&str, "|");
	ASSERT_STR_EQ("def", tok);
	ASSERT_STR_EQ("||ghijk", str);

	tok = ft_strsep(&str, "|");
	ASSERT_STR_EQ("", tok);
	ASSERT_STR_EQ("|ghijk", str);

	tok = ft_strsep(&str, "|");
	ASSERT_STR_EQ("", tok);
	ASSERT_STR_EQ("ghijk", str);

	tok = ft_strsep(&str, "|");
	ASSERT_STR_EQ("ghijk", tok);
	ASSERT_EQ(NULL, str);

	tok = ft_strsep(&str, "|");
	ASSERT_EQ(NULL, tok);
	ASSERT_EQ(NULL, str);

	PASS();
}

TEST	test2(void)
{
	char 	buf[] = "|abc|";
	char	*str = buf;
	char	*tok = NULL;

	tok = ft_strsep(&str, "|");
	ASSERT_STR_EQ("", tok);
	ASSERT_STR_EQ("abc|", str);

	tok = ft_strsep(&str, "|");
	ASSERT_STR_EQ("abc", tok);
	ASSERT_STR_EQ("", str);

	tok = ft_strsep(&str, "|");
	ASSERT_STR_EQ("", tok);
	ASSERT_EQ(NULL, str);

	tok = ft_strsep(&str, "|");
	ASSERT_EQ(NULL, tok);
	ASSERT_EQ(NULL, str);

	PASS();
}

SUITE(ft_strsep__suite)
{
	RUN_TEST(test1);
	RUN_TEST(test2);
}
