/*
** Created by doom on 16/10/18.
*/

#ifndef FOR_LIBCXX_CONFIG_HPP
#define FOR_LIBCXX_CONFIG_HPP

#ifdef FOR_LIBCXX_NO_EXCEPTIONS
#define FOR_LIBCXX_THROW(e)
#define FOR_LIBCXX_TRY          if (true)
#define FOR_LIBCXX_CATCH(e)     else
#else
#define FOR_LIBCXX_THROW(e)     throw e
#define FOR_LIBCXX_TRY          try
#define FOR_LIBCXX_CATCH(e)     catch
#endif

#endif /* !FOR_LIBCXX_CONFIG_HPP */
