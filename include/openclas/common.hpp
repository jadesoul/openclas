/*
 * Copyright (c) 2007-2010 Tao Wang <dancefire@gmail.org>
 * See the file "LICENSE.txt" for usage and redistribution license requirements
 *
 *	$Id: common.hpp 93M 2012-06-24 01:12:16Z (local) $
 */
#pragma once
#ifndef _OPENCLAS_COMMON_HPP_
#define _OPENCLAS_COMMON_HPP_

//	workaround for remove VC max(a,b) macro function definition,
//	which is make std::number_limites<T>::max(), std::max() and std::min() not working.
#ifdef _MSC_VER

#define NOMINMAX

#	ifdef max
#		undef max
#	endif

#	ifdef min
#		undef min
#	endif

#endif	//	max,min

// #define BOOST_HAS_CPP_0X
// #define BOOST_HAS_TR1_TUPLE
// #undef BOOST_HAS_INCLUDE_NEXT
// #include <boost/tr1/detail/config.hpp>
// #include <boost/tr1/tuple.hpp>

#include <boost/config.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/shared_array.hpp>
#include <boost/scoped_array.hpp>

namespace openclas {
	using boost::shared_ptr;
	using boost::shared_array;
	using boost::scoped_array;
}

//	 _OPENCLAS_COMMON_HPP_
#endif
