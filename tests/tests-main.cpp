/*
** Created by doom on 09/10/18.
*/

void run_type_traits_tests();
void run_utility_tests();
void run_optional_tests();
void run_iterator_tests();
void run_initializer_list_tests();
void run_char_traits_tests();
void run_string_view_tests();
void run_charconv_tests();
void run_algorithm_tests();
void run_functional_tests();
void run_memory_tests();
void run_vector_tests();
void run_tuple_tests();
void run_numeric_tests();
void run_array_tests();

int main()
{
    run_type_traits_tests();
    run_utility_tests();
    run_optional_tests();
    run_iterator_tests();
    run_initializer_list_tests();
    run_char_traits_tests();
    run_string_view_tests();
    run_charconv_tests();
    run_algorithm_tests();
    run_functional_tests();
    run_memory_tests();
    run_vector_tests();
    run_tuple_tests();
    run_numeric_tests();
    run_array_tests();
}
