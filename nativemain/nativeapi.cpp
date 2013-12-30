#include "stdafx.h"
#include "nativeapi.h"

JNIEXPORT jint JNICALL Java_net_topikachu_mixpoc_NativeLib_nativeadd
  (JNIEnv *, jobject, jint a, jint b)
{
	return a+b;
}

