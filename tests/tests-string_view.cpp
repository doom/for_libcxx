/*
** Created by doom on 21/10/18.
*/

#include <ut_config.h>
#include <string_view>

ut_test(empty)
{
    constexpr std::string_view sv;

    static_assert(sv.empty());
    static_assert(sv.size() == 0);
    static_assert(sv.data() == nullptr);
}

ut_test(from_c_string)
{
    constexpr std::string_view sv1("0123456789");

    static_assert(!sv1.empty());
    static_assert(sv1.size() == 10);
    static_assert(sv1 == "0123456789");
}

ut_test(from_char_array)
{
    constexpr std::string_view sv1("0123456789", 5);

    static_assert(!sv1.empty());
    static_assert(sv1.size() == 5);
    static_assert(sv1 == "01234");
}

ut_test(substr)
{
    constexpr std::string_view sv1("0123456789");
    constexpr auto sv2 = sv1.substr();
    static_assert(sv2 == sv1);

    constexpr auto sv3 = sv1.substr(2, 4);
    static_assert(sv3 == "2345");

    constexpr auto sv4 = sv1.substr(3);
    static_assert(sv4 == "3456789");

    constexpr auto sv5 = sv1.substr(0, sv1.size());
    static_assert(sv5 == sv1);

    constexpr auto sv6 = sv1.substr(0, 2000);
    static_assert(sv6 == sv1);
}

ut_test(remove_suffix)
{
    constexpr auto result = []() constexpr {
        std::string_view sv1("0123456789abc");
        sv1.remove_suffix(3);
        return sv1;
    }();
    static_assert(result == "0123456789");
}

ut_test(remove_prefix)
{
    constexpr auto result = []() constexpr {
        std::string_view sv1("abc0123456789");
        sv1.remove_prefix(3);
        return sv1;
    }();
    static_assert(result == "0123456789");
}

ut_test(ordering)
{
    constexpr std::string_view sv1("0123456789");
    constexpr std::string_view sv2("0123466789");

    static_assert(sv1 <= sv1);
    static_assert(sv1 >= sv1);
    static_assert(sv1 < sv2);
    static_assert(sv2 > sv1);
}

ut_test(front_back)
{
    constexpr std::string_view sv1("0123456789");
    static_assert(sv1.front() == '0');
    static_assert(&sv1.front() == sv1.data());
    static_assert(sv1.back() == '9');
    static_assert(&sv1.back() == sv1.data() + sv1.size() - 1);
}

ut_test(find)
{
    constexpr std::string_view sv1("0123456789");

    constexpr auto pos1 = sv1.find("ab");
    static_assert(pos1 == std::string_view::npos);

    constexpr auto pos2 = sv1.find("45");
    static_assert(pos2 == 4);

    constexpr auto pos3 = sv1.find("0123456789");
    static_assert(pos3 == 0);

    constexpr auto pos4 = sv1.find("89");
    static_assert(pos4 == 8);

    constexpr auto pos5 = sv1.find("");
    static_assert(pos5 == 0);

    constexpr auto pos6 = sv1.find('1');
    static_assert(pos6 == 1);

    constexpr auto pos7 = sv1.find('a');
    static_assert(pos7 == std::string_view::npos);

    constexpr auto pos8 = sv1.find('1', 2);
    static_assert(pos8 == std::string_view::npos);
}

ut_test(rfind)
{
    constexpr std::string_view sv1("0123456789");

    constexpr auto pos1 = sv1.rfind("ab");
    static_assert(pos1 == std::string_view::npos);

    constexpr auto pos2 = sv1.rfind("45");
    static_assert(pos2 == 4);

    constexpr auto pos3 = sv1.rfind("0123456789");
    static_assert(pos3 == 0);

    constexpr auto pos4 = sv1.rfind("89");
    static_assert(pos4 == 8);

    constexpr auto pos5 = sv1.rfind("");
    static_assert(pos5 == sv1.size() - 1);

    constexpr auto pos6 = sv1.rfind('1');
    static_assert(pos6 == 1);

    constexpr auto pos7 = sv1.rfind('a');
    static_assert(pos7 == std::string_view::npos);
}

ut_test(find_first_of)
{
    constexpr std::string_view sv1("h3ll0");

    constexpr auto pos1 = sv1.find_first_of("0123456789");
    static_assert(pos1 == 1);

    constexpr auto pos2 = sv1.find_first_of("hello");
    static_assert(pos2 == 0);

    constexpr auto pos3 = sv1.find_first_of("wxcv");
    static_assert(pos3 == std::string_view::npos);

    constexpr auto pos4 = sv1.find_first_of("");
    static_assert(pos4 == std::string_view::npos);
}

ut_test(find_last_of)
{
    constexpr std::string_view sv1("h3ll0");

    constexpr auto pos1 = sv1.find_last_of("0123456789");
    static_assert(pos1 == 4);

    constexpr auto pos2 = sv1.find_last_of("hello");
    static_assert(pos2 == 3);

    constexpr auto pos3 = sv1.find_last_of("wxcv");
    static_assert(pos3 == std::string_view::npos);

    constexpr auto pos4 = sv1.find_last_of("");
    static_assert(pos4 == std::string_view::npos);

    constexpr auto pos5 = sv1.find_last_of("0123456789", 0);
    static_assert(pos5 == std::string_view::npos);
}

ut_group(string_view,
         ut_get_test(empty),
         ut_get_test(from_c_string),
         ut_get_test(from_char_array),
         ut_get_test(substr),
         ut_get_test(remove_prefix),
         ut_get_test(remove_suffix),
         ut_get_test(substr),
         ut_get_test(ordering),
         ut_get_test(front_back),
         ut_get_test(find),
         ut_get_test(rfind),
         ut_get_test(find_first_of),
         ut_get_test(find_last_of)
);

void run_string_view_tests()
{
    ut_run_group(ut_get_group(string_view));
}
