// nativemain.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <tchar.h>
#include <jni.h>
#include <stdio.h>
#include <stdlib.h>
#include "nativeapi.h"
#define LIB_CLASSPATH "..\\javalib\\target\\lib\\javalib-0.0.1-SNAPSHOT.jar"
//#define JNA_CLASSPATH "..\\javalib\\target\\lib\\jna-4.0.0.jar"
#define RHINO_CLASSPATH "..\\javalib\\target\\lib\\js-1.7R2.jar"
#define USER_CLASSPATH LIB_CLASSPATH";"RHINO_CLASSPATH
int registerJniMethod (JNIEnv *env, JavaVM *jvm, const wchar_t *path)
{


	jclass         cls;
	/* locate and load the class file */
	if ((cls = env->FindClass( "net/topikachu/mixpoc/NativeLib")) == 0) 
	{
		fprintf(stderr, "Can't find class %s\n", "JSInterp");
		exit( -1);
	}
	static JNINativeMethod methods[] = {
		{"nativeadd",    "(II)I",                    Java_net_topikachu_mixpoc_NativeLib_nativeadd},

	};

	env->RegisterNatives( cls,
		methods, sizeof(methods)/sizeof(methods[0]));

	return 0;
}



int CallJs(JNIEnv *env, JavaVM *jvm, const char *script)
{
	jclass         cls;
	jmethodID      mid;
	jstring         jstr;


	/* locate and load the class file */
	if ((cls = env->FindClass( "net/topikachu/mixpoc/JSInterp")) == 0) 
	{
		fprintf(stderr, "Can't find class %s\n", "JSInterp");
		exit( -1);
	}

	/* locate the main method */
	if ((mid = env->GetStaticMethodID( cls, "run", "(Lnet/topikachu/mixpoc/NativeLib;Ljava/lang/String;)V")) == 0) 
	{
		fprintf(stderr, "Can't find run method in class %s\n", "JSInterp");
		exit( -1);
	}


	jclass		clsNativeLib	;
	/* locate and load the class file */
	if ((clsNativeLib = env->FindClass( "net/topikachu/mixpoc/NativeLib")) == 0) 
	{
		fprintf(stderr, "Can't find class %s\n", "NativeLib");
		exit( -1);
	}



	jmethodID nativeLibCntr
		= env->GetMethodID(clsNativeLib,"<init>","()V");

	jobject nativeLibInstance 
		= env->NewObject(clsNativeLib,nativeLibCntr);

	/* create a new java string to be passes to the class */
	if ((jstr = env->NewStringUTF( script)) == 0) 
	{
		fprintf(stderr, "Out of memory\n");
		exit( -1);
	}






	/* call the main method with the required arguments */

	/* call the main method with the required arguments */
	env->CallStaticVoidMethod( cls, mid, nativeLibInstance, jstr);


	if ( NULL != nativeLibInstance )
	{
		/* we know myObj is a valid local ref, so use it */
		jclass myClazz = env->GetObjectClass( nativeLibInstance);

		/* uses of myObj and myClazz, etc. but no new local refs */

		/* Without the following calls, we would leak */
		env->DeleteLocalRef(  nativeLibInstance ); 
		env->DeleteLocalRef(  clsNativeLib );
	}
	return 0;
}


int _tmain(int argc, _TCHAR* argv[])
{



	JNIEnv         *env;
	JavaVM         *jvm;
	JavaVMInitArgs    vm_args;
	JavaVMOption   options[2];
	jint         res;



	/* IMPORTANT: specify vm_args version # if you use JDK1.1.2 and beyond */
	vm_args.version = JNI_VERSION_1_6;
	vm_args.nOptions =2;
	vm_args.options=options;
	options[0].optionString = "-Djava.compiler=NONE"; /* disable JIT */
	options[1].optionString = "-Djava.class.path="USER_CLASSPATH; /* user classes */


	/* Create the Java VM */
	if ((res = JNI_CreateJavaVM(&jvm,(void **)&env,&vm_args)) < 0) 
	{
		fprintf(stderr, "Can't create Java VM\n");
		return(1);
	}

	TCHAR path[MAX_PATH];
	GetModuleFileName(NULL, path, MAX_PATH);
	registerJniMethod(env,jvm,path);
	char const script[] = "var i=1;\nvar j=2;\nnativelib.nativeadd(i,j);\n";
	CallJs(env,jvm,script);

	jvm->DestroyJavaVM();
	return 0;
}

