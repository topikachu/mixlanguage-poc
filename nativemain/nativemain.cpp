// nativemain.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <tchar.h>
#include <jni.h>
#include <stdio.h>
#include <stdlib.h>
#include "nativeapi.h"
#define LIB_CLASSPATH "..\\javalib\\target\\lib\\javalib-0.0.1-SNAPSHOT.jar"
#define JNA_CLASSPATH "..\\javalib\\target\\lib\\jna-4.0.0.jar"

int InitJNA (JNIEnv *env, JavaVM *jvm, const wchar_t *path)
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
	if ((mid = env->GetStaticMethodID( cls, "init", "(Ljava/lang/String;)V")) == 0) 
	{
		fprintf(stderr, "Can't find init method in class %s\n", "JSInterp");
		exit( -1);
	}
	/* create a new java string to be passes to the class */
	if ((jstr = env->NewString(( jchar *) path,_tcslen(path))) == 0) 
	{
		fprintf(stderr, "Out of memory\n");
		exit( -1);
	}






	/* call the main method with the required arguments */

	/* call the main method with the required arguments */
	env->CallStaticVoidMethod( cls, mid, jstr);

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
	if ((mid = env->GetStaticMethodID( cls, "run", "(Ljava/lang/String;)V")) == 0) 
	{
		fprintf(stderr, "Can't find run method in class %s\n", "JSInterp");
		exit( -1);
	}
	/* create a new java string to be passes to the class */
	if ((jstr = env->NewStringUTF( script)) == 0) 
	{
		fprintf(stderr, "Out of memory\n");
		exit( -1);
	}






	/* call the main method with the required arguments */

	/* call the main method with the required arguments */
	env->CallStaticVoidMethod( cls, mid, jstr);

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
	options[1].optionString = "-Djava.class.path="LIB_CLASSPATH";"JNA_CLASSPATH; /* user classes */


	/* Create the Java VM */
	if ((res = JNI_CreateJavaVM(&jvm,(void **)&env,&vm_args)) < 0) 
	{
		fprintf(stderr, "Can't create Java VM\n");
		return(1);
	}

	TCHAR path[MAX_PATH];
	GetModuleFileName(NULL, path, MAX_PATH);
	InitJNA(env,jvm,path);
	char const script[] = "nativelib.nativeadd(4,2);";
	CallJs(env,jvm,script);

	jvm->DestroyJavaVM();
	return 0;
}

