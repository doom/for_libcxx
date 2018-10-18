/*
** Created by doom on 16/10/18.
*/

#ifndef FOR_LIBCXX_CONFIG_HPP
#define FOR_LIBCXX_CONFIG_HPP

#ifdef FOR_LIBCXX_NO_EXCEPTIONS
#define FOR_LIBCXX_THROW(e)
#else
#define FOR_LIBCXX_THROW(e)     throw e
#endif

#endif /* !FOR_LIBCXX_CONFIG_HPP */
