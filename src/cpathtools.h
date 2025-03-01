#ifndef CPATHTOOLS_H
#define CPATHTOOLS_H
#ifdef __cplusplus
extern C
{
#endif

// https://gcc.gnu.org/wiki/Visibility
#if defined _WIN32 || defined __CYGWIN__
  #ifdef BUILDING_DLL
    #ifdef __GNUC__
      #define DLL_PUBLIC(T) __attribute__ ((dllexport)) T
    #else
      #define DLL_PUBLIC(T) __declspec(dllexport) T // Note: actually gcc seems to also supports this syntax.
    #endif
  #else
    #ifdef __GNUC__
      #define DLL_PUBLIC(T) __attribute__ ((dllimport)) T
    #else
      #define DLL_PUBLIC(T) __declspec(dllimport) T // Note: actually gcc seems to also supports this syntax.
    #endif
  #endif
  #define DLL_LOCAL(T) T
#else
  #if __GNUC__ >= 4
    #define DLL_PUBLIC(T) __attribute__ ((visibility ("default"))) T
    #define DLL_LOCAL(T)  __attribute__ ((visibility ("hidden"))) T
  #else
    #define DLL_PUBLIC(T) T
    #define DLL_LOCAL(T) T
  #endif
#endif

DLL_PUBLIC(char *) GetPath(char *__path, long long __depth);

#ifdef __cplusplus
}
#endif
#endif /* !CPATHTOOLS_H */
