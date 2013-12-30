
#ifndef _NATIVEAPI_H
#define _NATIVEAPI_H

#include <jni.h>

#ifdef __cplusplus
extern "C" {
#endif
JNIEXPORT jint JNICALL Java_net_topikachu_mixpoc_NativeLib_nativeadd
  (JNIEnv *, jobject, jint, jint);


#ifdef __cplusplus
}
#endif
#endif