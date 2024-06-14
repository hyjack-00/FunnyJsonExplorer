#include <cstdio>

#define RELEASE


// Helper macro to extract file name from full path
#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)

// If RELEASE is defined, disable debug printing
#ifdef RELEASE
    #define DEBUG_PRINT(fmt, ...) (void)0
#else
    #define DEBUG_PRINT(fmt, ...) \
        do { \
            printf("DEBUG %s : %d : %s(): " fmt "\n", __FILENAME__, __LINE__, __func__, __VA_ARGS__); \
        } while (0)
#endif
