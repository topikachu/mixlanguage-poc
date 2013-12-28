
#ifndef _NATIVEAPI_H
#define _NATIVEAPI_H

#define NATIVELIB_API __declspec(dllexport)

#ifdef __cplusplus
extern "C" {
#endif
NATIVELIB_API int nativeadd(int a,int b);


#ifdef __cplusplus
}
#endif
#endif