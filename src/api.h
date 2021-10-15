#pragma once

#if defined _WIN32 || defined __CYGWIN__
#  define TorqueLimitTest_DLLIMPORT __declspec(dllimport)
#  define TorqueLimitTest_DLLEXPORT __declspec(dllexport)
#  define TorqueLimitTest_DLLLOCAL
#else
// On Linux, for GCC >= 4, tag symbols using GCC extension.
#  if __GNUC__ >= 4
#    define TorqueLimitTest_DLLIMPORT __attribute__((visibility("default")))
#    define TorqueLimitTest_DLLEXPORT __attribute__((visibility("default")))
#    define TorqueLimitTest_DLLLOCAL __attribute__((visibility("hidden")))
#  else
// Otherwise (GCC < 4 or another compiler is used), export everything.
#    define TorqueLimitTest_DLLIMPORT
#    define TorqueLimitTest_DLLEXPORT
#    define TorqueLimitTest_DLLLOCAL
#  endif // __GNUC__ >= 4
#endif // defined _WIN32 || defined __CYGWIN__

#ifdef TorqueLimitTest_STATIC
// If one is using the library statically, get rid of
// extra information.
#  define TorqueLimitTest_DLLAPI
#  define TorqueLimitTest_LOCAL
#else
// Depending on whether one is building or using the
// library define DLLAPI to import or export.
#  ifdef TorqueLimitTest_EXPORTS
#    define TorqueLimitTest_DLLAPI TorqueLimitTest_DLLEXPORT
#  else
#    define TorqueLimitTest_DLLAPI TorqueLimitTest_DLLIMPORT
#  endif // TorqueLimitTest_EXPORTS
#  define TorqueLimitTest_LOCAL TorqueLimitTest_DLLLOCAL
#endif // TorqueLimitTest_STATIC