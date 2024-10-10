#pragma once

// clang-format off
#ifndef BEAST_HTTP_UNROLL_LOOP
#	if defined(_MSC_VER) && !defined(__clang__)
#		define BEAST_HTTP_UNROLL_LOOP(N) __pragma(loop(unroll, N))
#	else
#		define BEAST_HTTP_STRINGIFY(X)	 #X
#		define BEAST_HTTP_TOSTRING(X)	 BEAST_HTTP_STRINGIFY(X)
#		define BEAST_HTTP_UNROLL_LOOP(N) _Pragma(BEAST_HTTP_TOSTRING(GCC unroll N))
#	endif
#endif

#ifndef BEAST_HTTP_BEGIN_NAMESPACE
#define BEAST_HTTP_BEGIN_NAMESPACE \
	namespace beast_http \
	{                         \
	inline namespace v0       \
	{

#define BEAST_HTTP_END_NAMESPACE   \
	}                         \
	}
#endif

#ifndef BEAST_HTTP_EXPORT
#	if  defined(BEAST_HTTP_LIBRARY_STATIC)
#		define BEAST_HTTP_EXPORT
#	elif defined(BEAST_HTTP_LIBRARY_SHARED)
#		if defined(_WIN32)
#			define BEAST_HTTP_EXPORT __declspec(dllexport)
#		else
#			define BEAST_HTTP_EXPORT __attribute__((visibility("default")))
#		endif
#	else // import
#		if defined(_WIN32)
#			define BEAST_HTTP_EXPORT __declspec(dllimport)
#		else
#			define BEAST_HTTP_EXPORT
#		endif
#	endif
#endif
// clang-format on

BEAST_HTTP_BEGIN_NAMESPACE

namespace detail
{

[[noreturn]] inline void unreachable()
{
    // Uses compiler specific extensions if possible.
    // Even if no extension is used, undefined behavior is still raised by
    // an empty function body and the noreturn attribute.
#if defined(_MSC_VER) && !defined(__clang__) // MSVC
    __assume(false);
#else // GCC, Clang
    __builtin_unreachable();
#endif
}

} // namespace detail

BEAST_HTTP_END_NAMESPACE
