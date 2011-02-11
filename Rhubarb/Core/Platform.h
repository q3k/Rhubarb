// Platform-specific stuff
// (mostly dirty fixes to get this to play nice with gcc

#pragma once

#include <string.h>

#ifndef _WIN32
	#define memcpy_s(a, b, c, d) memcpy(a, c, d)
	#define strncpy_s(a, b, c, d) strncpy(a, c, d)
#endif
