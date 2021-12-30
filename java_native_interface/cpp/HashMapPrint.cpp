#include<jni.h>
#include<iostream>
#include"com_HashMapPrint.h"
JNIEXPORT jint JNICALL Java_com_HashMapPrint_hashMapPrintCPP(JNIEnv* env, jobject thisObject) {

	
	jclass hashMapPrintClass = env->FindClass("com/HashMapPrint");
	jclass hashmapclass = env->FindClass("java/util/HashMap");
	jmethodID hashmapclass_initmeth = env->GetMethodID(hashmapclass, "<init>", "()V");
	jobject employeesObject = env->NewObject(hashmapclass, hashmapclass_initmeth);
	jmethodID putmeth = env->GetMethodID(hashmapclass, "put",
		"(Ljava/lang/Object;Ljava/lang/Object;)Ljava/lang/Object;");
	try {		
		jstring keyJava = env->NewStringUTF("1");
		jstring valueJava = env->NewStringUTF("karthikeyan");
		env->CallObjectMethod(employeesObject, putmeth, keyJava, valueJava);
		keyJava = env->NewStringUTF("2");
		valueJava = env->NewStringUTF("Naveen");
		env->CallObjectMethod(employeesObject, putmeth, keyJava, valueJava);
		jfieldID employees = env->GetFieldID(hashMapPrintClass, "employees", "Ljava/util/HashMap;");
		env->SetObjectField(thisObject, employees, employeesObject);

		jmethodID printMethod = env->GetMethodID(hashMapPrintClass, "print", "()V");
		env->CallObjectMethod(thisObject, printMethod);
		
	}
	catch (const std::exception& exc)
	{
		std::cerr << exc.what();
	}
	return (jint)10;
}

JNIEXPORT jstring JNICALL Java_com_HashMapPrint_passAndReturn(JNIEnv* env,jobject thisObject,jstring message) {
	return message;
}