/*
** Created by doom on 20/10/18.
*/

#include <ut_config.h>
#include <details/char_traits.hpp>

ut_test(char_assign)
{
    char c = 'a';
    std::char_traits<char>::assign(c, 'b');
    ut_assert_eq(c, 'b');

    char buf[10];
    std::char_traits<char>::assign(buf, 10, 'z');
    ut_assert_memeq(buf, "zzzzzzzzzz", 10);
}

ut_test(char_eq)
{
    static_assert(std::char_traits<char>::eq('a', 'a'));
    static_assert(!std::char_traits<char>::eq('a', 'A'));
}

ut_test(char_lt)
{
    static_assert(std::char_traits<char>::lt('a', 'b'));
    static_assert(!std::char_traits<char>::lt('b', 'a'));
}

ut_test(char_move)
{
    char dest[10];
    const char *src = "0123456789";

    std::char_traits<char>::move(dest, src, 10);
    ut_assert_memeq(dest, src, 10);
}

ut_test(char_copy)
{
    char dest[10];
    const char *src = "0123456789";

    std::char_traits<char>::copy(dest, src, 10);
    ut_assert_memeq(dest, src, 10);
}

ut_test(char_compare)
{
    constexpr int diff = std::char_traits<char>::compare("salut", "tulas", 5);
    static_assert(diff < 0);

    const char *s1 = "salut";
    const char *s2 = "tulas";
    int diff2 = std::char_traits<char>::compare(s1, s2, 5);
    ut_assert_lt(diff2, 0);
}

ut_test(char_length)
{
    constexpr auto len = std::char_traits<char>::length("salut");
    static_assert(len == 5);
    const char *s = "hello world";
    auto len2 = std::char_traits<char>::length(s);
    ut_assert_eq(len2, 11);
}

ut_test(char_find)
{
    const char *s = "0123456789";
    auto r2 = std::char_traits<char>::find(s, 10, '8');
    ut_assert_eq(*r2, '8');
    ut_assert_eq(r2, s + 8);
}

ut_group(char_traits,
         ut_get_test(char_assign),
         ut_get_test(char_eq),
         ut_get_test(char_lt),
         ut_get_test(char_move),
         ut_get_test(char_copy),
         ut_get_test(char_compare),
         ut_get_test(char_length),
         ut_get_test(char_find)
);

void run_char_traits_tests()
{
    ut_run_group(ut_get_group(char_traits));
}
