#include <stdio.h>
#include <stdlib.h>
#include "util.h"

static void zmalloc_oom_handler(size_t size) {
    fprintf(stderr, "zmalloc: Out of memory trying to allocate %zu bytes\n", size);
    fflush(stderr);
    abort();
}


void* zmalloc(size_t size)
{
	void* p;

	p = malloc(size);
	if (!p) {
		zmalloc_oom_handler(size);
	}

	return p;
}

void zfree(void* ptr)
{
	free(ptr);
}

