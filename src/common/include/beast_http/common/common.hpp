#pragma once

// clang-format off
#ifndef BEAST_HTTP_BEGIN_NAMESPACE
#define BEAST_HTTP_BEGIN_NAMESPACE \
	namespace beast_http           \
	{                              \
	inline namespace v0            \
	{

#define BEAST_HTTP_END_NAMESPACE   \
	}                              \
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
