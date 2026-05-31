#ifndef MM_IO_H
#define MM_IO_H

#include <stdio.h>
#include <string.h>
#include <zlib.h>

#if defined(_WIN32)
#include <fcntl.h>
#include <io.h>
#endif

static inline gzFile mm_gzopen_read(const char *fn)
{
	if (fn && strcmp(fn, "-") != 0)
		return gzopen(fn, "rb");
#if defined(_WIN32)
	_setmode(_fileno(stdin), _O_BINARY);
	return gzdopen(_fileno(stdin), "rb");
#else
	return gzdopen(fileno(stdin), "rb");
#endif
}

static inline void mm_set_stdout_binary_if_redirected(void)
{
#if defined(_WIN32)
	if (!_isatty(_fileno(stdout)))
		_setmode(_fileno(stdout), _O_BINARY);
#endif
}

#endif
