#include<iostream>
#include <map>
#include <string>
#include<Windows.h>
#include<signal.h>
#include<jni.h>
#include"jni_WindowsProcessManager.h"

std::map<int, std::string> proccesses;

void pushProcess(int  PID, std::string name) {
	proccesses[PID] = name;
}

//return the hashmap std::map<int, std::string> 
JNIEXPORT void JNICALL Java_jni_WindowsProcessManager_getStoredProcesses(JNIEnv* env, jobject thisObject) {
	jclass windowsProcessManagerClass = env->FindClass("jni/WindowsProcessManager");
	jclass hashmapclass = env->FindClass("java/util/HashMap");
	jmethodID hashmapclass_initmeth = env->GetMethodID(hashmapclass, "<init>", "()V");
	jobject processesObject = env->NewObject(hashmapclass, hashmapclass_initmeth);
	jmethodID putmeth = env->GetMethodID(hashmapclass, "put",
		"(Ljava/lang/Object;Ljava/lang/Object;)Ljava/lang/Object;");
	try {
		for (std::map<int, std::string>::iterator p = proccesses.begin(); p != proccesses.end(); ++p)
		{
			std::cout << "PID : " << (*p).first << "\t Process -> " << (*p).second << std::endl;
			int pid = (*p).first;
			std::string pid_str = std::to_string(pid);
			std::string name_str = (*p).second;
			jstring keyJava = env->NewStringUTF(pid_str.c_str());
			jstring valueJava = env->NewStringUTF(name_str.c_str());
			env->CallObjectMethod(processesObject, putmeth, keyJava, valueJava);
		}

		jfieldID employees = env->GetFieldID(windowsProcessManagerClass, "processes", "Ljava/util/HashMap;");
		env->SetObjectField(thisObject, employees, processesObject);

	}
	catch (const std::exception& exc)
	{
		std::cerr << exc.what();
	}
}

JNIEXPORT jboolean JNICALL Java_jni_WindowsProcessManager_stopProcess(JNIEnv* env, jobject thisObject,jint PID) {
    std::cout << "passed value   " << PID << std::endl;
            HANDLE tmpHandle = OpenProcess(PROCESS_ALL_ACCESS, TRUE, PID);
            if (NULL != tmpHandle)
            {
                std::cout << "Terminating process   " << PID << std::endl;
                if (TerminateProcess(tmpHandle, 0)) {
                    CloseHandle(tmpHandle);
                    proccesses.erase(PID);
                    return true;
                }
            }
            return false;
}

void listProcess() {
    for (std::map<int, std::string>::iterator p = proccesses.begin(); p != proccesses.end(); ++p)
    {
        std::cout << "PID : " << (*p).first << "\t Process -> " << (*p).second << std::endl;
    }
}