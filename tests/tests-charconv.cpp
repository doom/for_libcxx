/*
** Created by doom on 02/11/18.
*/

#include <ut_config.h>
#include <string.h>
#include <charconv>

ut_test(to_chars)
{
    char buf[16];

    std::to_chars_result r1 = std::to_chars(buf, buf + 3, (int)123);
    ut_assert_ne(r1.ec, std::errc::value_too_large);
    ut_assert_eq(r1.ptr, buf + 3);
    ut_assert_memeq(buf, "123", 3);

    std::to_chars_result r2 = std::to_chars(buf, buf + 4, (int)-123);
    ut_assert_ne(r2.ec, std::errc::value_too_large);
    ut_assert_eq(r2.ptr, buf + 4);
    ut_assert_memeq(buf, "-123", 4);

    std::to_chars_result r3 = std::to_chars(buf, buf + 4, (int)11123);
    ut_assert_eq(r3.ec, std::errc::value_too_large);
    ut_assert_eq(r3.ptr, buf + 4);

    std::to_chars_result r4 = std::to_chars(buf, buf + 3, (unsigned int)123);
    ut_assert_ne(r4.ec, std::errc::value_too_large);
    ut_assert_eq(r4.ptr, buf + 3);
    ut_assert_memeq(buf, "123", 3);

    std::to_chars_result r5 = std::to_chars(buf, buf + 4, (unsigned int)11123);
    ut_assert_eq(r5.ec, std::errc::value_too_large);
    ut_assert_eq(r5.ptr, buf + 4);

    std::to_chars_result r6 = std::to_chars(buf, buf + 1, -0);
    ut_assert_ne(r6.ec, std::errc::value_too_large);
    ut_assert_eq(r6.ptr, buf + 1);
    ut_assert_memeq(buf, "0", 1);
}

ut_group(charconv,
    ut_get_test(to_chars)
);

void run_charconv_tests()
{
    ut_run_group(ut_get_group(charconv));
}
