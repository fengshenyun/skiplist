#ifndef _UTIL__H__
#define _UTIL__H__

#if DEBUG

#define Log_Debug(format, ...) \
	do \
	{ \
		printf(format, ##__VA_ARGS__); \
	} while (0)

#define Log_Error(format, ...) \
	do \
	{ \
		printf(format, ##__VA_ARGS__); \
	} while (0)

#else

#define Log_Debug(format, ...)	

#define Log_Error(format, ...) \
	do \
	{ \
		printf(format, ##__VA_ARGS__); \
	} while (0)

#endif

void* zmalloc(size_t size);
void zfree(void* ptr);



#endif
