#ifndef CPATHTOOLS_H
#define CPATHTOOLS_H
#ifdef __cplusplus
extern C
{
#endif

#ifdef CPATHTOOLSEXPORT
#define __EXPORT(T) __declspec(dllexport) T
#else
#define __EXPORT(T) __declspec(dllimport) T
#endif

__EXPORT(char *) GetPath(char *__path, long long __depth);

#ifdef __cplusplus
}
#endif
#endif /* !CPATHTOOLS_H */
