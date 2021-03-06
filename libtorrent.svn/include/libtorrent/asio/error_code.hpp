//
// error_code.hpp
// ~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2007 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef ASIO_ERROR_CODE_HPP
#define ASIO_ERROR_CODE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include "asio/detail/push_options.hpp"

#include "asio/detail/push_options.hpp"
#include <boost/config.hpp>
#include <string>
#include "asio/detail/pop_options.hpp"

#if defined(GENERATING_DOCUMENTATION)
# define ASIO_WIN_OR_POSIX(e_win, e_posix) implementation_defined
#elif defined(BOOST_WINDOWS) || defined(__CYGWIN__)
# define ASIO_WIN_OR_POSIX(e_win, e_posix) e_win
#else
# define ASIO_WIN_OR_POSIX(e_win, e_posix) e_posix
#endif

namespace asio {

/// Available error code categories.
enum error_category
{
  /// Native error codes.
  native_ecat = ASIO_WIN_OR_POSIX(0, 0),

  /// Error codes from NetDB functions.
  netdb_ecat = ASIO_WIN_OR_POSIX(native_ecat, 1),

  /// Error codes from getaddrinfo.
  addrinfo_ecat = ASIO_WIN_OR_POSIX(native_ecat, 2),

  /// Miscellaneous error codes.
  misc_ecat = ASIO_WIN_OR_POSIX(3, 3),

  /// SSL error codes.
  ssl_ecat = ASIO_WIN_OR_POSIX(4, 4)
};

/// Class to represent an error code value.
class error_code
{
public:
  /// The underlying representation of an error code.
  typedef int value_type;

  /// Default constructor.
  error_code()
    : value_(0),
      category_(native_ecat)
  {
  }

  /// Construct with specific error code and category.
  error_code(value_type v, error_category c)
    : value_(v),
      category_(c)
  {
  }

  /// Get the error value.
  value_type value() const
  {
    return value_;
  }

  /// Get the error category.
  error_category category() const
  {
    return category_;
  }

  /// Get the message associated with the error.
  std::string message() const;

  struct unspecified_bool_type_t
  {
  };

  typedef unspecified_bool_type_t* unspecified_bool_type;

  /// Operator returns non-null if there is a non-success error code.
  operator unspecified_bool_type() const
  {
    if (value_ == 0)
      return 0;
    else
      return reinterpret_cast<unspecified_bool_type>(1);
  }

  /// Operator to test if the error represents success.
  bool operator!() const
  {
    return value_ == 0;
  }

  /// Equality operator to compare two error objects.
  friend bool operator==(const error_code& e1, const error_code& e2)
  {
    return e1.value_ == e2.value_ && e1.category_ == e2.category_;
  }

  /// Inequality operator to compare two error objects.
  friend bool operator!=(const error_code& e1, const error_code& e2)
  {
    return e1.value_ != e2.value_ || e1.category_ != e2.category_;
  }

private:
  // The value associated with the error code.
  value_type value_;

  // The category associated with the error code.
  error_category category_;
};

} // namespace asio

#undef ASIO_WIN_OR_POSIX

#include "asio/error.hpp"

#include "asio/detail/pop_options.hpp"

#endif // ASIO_ERROR_CODE_HPP
