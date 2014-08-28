#ifndef cpp0x_compiler_macros_h
#define cpp0x_compiler_macros_h

// ----------------------------------------------------------------------
// Define gcc version test:
// ----------------------------------------------------------------------

#if defined __GNUC_PATCHLEVEL__
  # define GCC_VERSION (10000 * __GNUC__ \
                       + 1000 * __GNUC_MINOR__ \
                       +        __GNUC_PATCHLEVEL__)

#elif defined __GNUC_MINOR__
  # define GCC_VERSION (10000 * __GNUC__ \
                       + 1000 * __GNUC_MINOR__)

#elif defined __GNUC__
  # define GCC_VERSION (10000 * __GNUC__)

#else
  # define GCC_VERSION 0

#endif

# define GCC_IS_AT_LEAST(major, minor, patch) \
  (GCC_VERSION >= ((10000*(major)) + (1000*(minor)) + (patch)))

#endif /* cpp0x_compiler_macros_h */

// Local Variables:
// mode: c++
// End:
