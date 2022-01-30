#define _WIN32_DCOM
#include <iostream>
#include<map>
#include <comdef.h>
#include <Wbemidl.h>
#include<Windows.h>
#include "process_manager.h"
#pragma comment(lib, "wbemuuid.lib")
#include<jni.h>
#include"jni_WindowsProcessManager.h"
JNIEXPORT void JNICALL Java_jni_WindowsProcessManager_fetchProcesses(JNIEnv* env, jobject thisObject)
{
	HRESULT hres;

	// Step 1: --------------------------------------------------
	// Initialize COM. ------------------------------------------

	hres = CoInitializeEx(0, COINIT_MULTITHREADED);
	if (FAILED(hres))
	{
		std::cout << "Failed to initialize COM library. Error code = 0x"
			<< std::hex << hres << std::endl;
		                 // Program has failed.
	}

	// Step 2: --------------------------------------------------
	// Set general COM security levels --------------------------

	hres = CoInitializeSecurity(
		NULL,
		-1,                          // COM authentication
		NULL,                        // Authentication services
		NULL,                        // Reserved
		RPC_C_AUTHN_LEVEL_DEFAULT,   // Default authentication 
		RPC_C_IMP_LEVEL_IMPERSONATE, // Default Impersonation  
		NULL,                        // Authentication info
		EOAC_NONE,                   // Additional capabilities 
		NULL                         // Reserved
	);


	if (FAILED(hres))
	{
		std::cout << "Failed to initialize security. Error code = 0x"
			<< std::hex << hres << std::endl;
		CoUninitialize();
		// Program has failed.
	}

	// Step 3: ---------------------------------------------------
	// Obtain the initial locator to WMI -------------------------

	IWbemLocator* pLoc = NULL;

	hres = CoCreateInstance(
		CLSID_WbemLocator,
		0,
		CLSCTX_INPROC_SERVER,
		IID_IWbemLocator, (LPVOID*)&pLoc);

	if (FAILED(hres))
	{
		std::cout << "Failed to create IWbemLocator object."
			<< " Err code = 0x"
			<< std::hex << hres << std::endl;
		CoUninitialize();
		// Program has failed.
	}

	// Step 4: -----------------------------------------------------
	// Connect to WMI through the IWbemLocator::ConnectServer method

	IWbemServices* pSvc = NULL;

	// Connect to the root\cimv2 namespace with
	// the current user and obtain pointer pSvc
	// to make IWbemServices calls.
	hres = pLoc->ConnectServer(
		_bstr_t(L"ROOT\\CIMV2"), // Object path of WMI namespace
		NULL,                    // User name. NULL = current user
		NULL,                    // User password. NULL = current
		0,                       // Locale. NULL indicates current
		0,                    // Security flags.
		0,                       // Authority (for example, Kerberos)
		0,                       // Context object 
		&pSvc                    // pointer to IWbemServices proxy
	);

	if (FAILED(hres))
	{
		std::cout << "Could not connect. Error code = 0x"
			<< std::hex << hres << std::endl;
		pLoc->Release();
		CoUninitialize();
		// Program has failed.
	}

	std::cout << "Connected to ROOT\\CIMV2 WMI namespace" << std::endl;


	// Step 5: --------------------------------------------------
	// Set security levels on the proxy -------------------------

	hres = CoSetProxyBlanket(
		pSvc,                        // Indicates the proxy to set
		RPC_C_AUTHN_WINNT,           // RPC_C_AUTHN_xxx
		RPC_C_AUTHZ_NONE,            // RPC_C_AUTHZ_xxx
		NULL,                        // Server principal name 
		RPC_C_AUTHN_LEVEL_CALL,      // RPC_C_AUTHN_LEVEL_xxx 
		RPC_C_IMP_LEVEL_IMPERSONATE, // RPC_C_IMP_LEVEL_xxx
		NULL,                        // client identity
		EOAC_NONE                    // proxy capabilities 
	);

	if (FAILED(hres))
	{
		std::cout << "Could not set proxy blanket. Error code = 0x"
			<< std::hex << hres << std::endl;
		pSvc->Release();
		pLoc->Release();
		CoUninitialize();
		// Program has failed.
	}

	BSTR MethodName = SysAllocString(L"GetOwner");
	BSTR ClassName = SysAllocString(L"Win32_Process");

	// get the object containing our desired method
	IWbemClassObject* pClass = NULL;
	hres = pSvc->GetObject(ClassName, 0, NULL, &pClass, NULL);
	if (FAILED(hres))
	{
		printf("GetObject hres = %08x\n", hres);
		pSvc->Release();
		pLoc->Release();
		CoUninitialize();
	}

	// get the desired method
	// in our case, we only need pmethodGetOwner since GetOwner really only has output
	IWbemClassObject* pmethodGetOwner = NULL;
	hres = pClass->GetMethod(MethodName, 0, NULL, &pmethodGetOwner);
	if (FAILED(hres))
	{
		printf("GetMethod hres = %08x\n", hres);
		pSvc->Release();
		pLoc->Release();
		CoUninitialize();
	}

	// spawn the instance of the method
	IWbemClassObject* pInInst = NULL;
	hres = pmethodGetOwner->SpawnInstance(0, &pInInst);
	if (FAILED(hres))
	{
		printf("SpawnInstance hres = %08x\n", hres);
		pSvc->Release();
		pLoc->Release();
		CoUninitialize();
	}

	// Step 6: --------------------------------------------------
	// Use the IWbemServices pointer to make requests of WMI ----

	// For example, get the name of the operating system
	IEnumWbemClassObject* pEnumerator = NULL;
	hres = pSvc->ExecQuery(
		bstr_t("WQL"),
		bstr_t("SELECT * FROM Win32_Process"),
		WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY,
		NULL,
		&pEnumerator);

	if (FAILED(hres))
	{
		std::cout << "Query for operating system name failed."
			<< " Error code = 0x"
			<< std::hex << hres << std::endl;
		pSvc->Release();
		pLoc->Release();
		CoUninitialize();
		// Program has failed.
	}

	// Step 7: -------------------------------------------------
	// Get the data from the query in step 6 -------------------

	IWbemClassObject* pclsObj = NULL;
	ULONG uReturn = 0;
	int processCount = 1;
	while (pEnumerator)
	{
		HRESULT hr = pEnumerator->Next(WBEM_INFINITE, 1, &pclsObj, &uReturn);

		if (0 == uReturn)
		{
			break;
		}

		VARIANT vtProp;
		VARIANT vtProcName;
		VARIANT vtDomain;
		VARIANT vtUsername;
		VARIANT vtPrcessID;
		VARIANT pHandle;

		// Get the value of the Name property
		hr = pclsObj->Get(L"Name", 0, &vtProcName, 0, 0);
		if (FAILED(hr))
		{
			printf("Failed to get the process's name\n");
			pclsObj->Release();
			continue;
		}

		// Get the PATH to the object in question
		// the result in vtProp is similar to '\\name_of_computer\ROOT\CIMV2:Win32_Process.Handle="pid_of_process"'
		/*hr = pclsObj->Get(L"__PATH", 0, &vtProp, 0, 0);
		if (FAILED(hres))
		{
			printf("Failed to get the path to the object\n");
			pclsObj->Release();
			continue;
		}*/

		// Execute Method against the object defined by the __PATH variable
		/*hr = pSvc->ExecMethod(vtProp.bstrVal, MethodName, 0, NULL, NULL, &pmethodGetOwner, NULL);
		if (FAILED(hr))
		{
			wprintf(L"Failed to execute the method against %s\n", vtProp.bstrVal);
			pclsObj->Release();
			continue;
		}*/

		// extract the results
		/*hr = pmethodGetOwner->Get(L"User", 0, &vtUsername, NULL, 0);
		if (FAILED(hr))
		{
			printf("Failed to get the owner's name\n");
			pclsObj->Release();
			continue;
		}

		hr = pmethodGetOwner->Get(L"Domain", 0, &vtDomain, NULL, 0);
		if (FAILED(hr))
		{
			printf("Failed to get the owner's domain\n");
			pclsObj->Release();
			continue;
		}*/

		hr = pclsObj->Get(L"ProcessId", 0, &vtPrcessID, 0, 0);
		//wprintf (L"%d",vtPrcessID);
		if (FAILED(hr))
		{
			printf("Failed to get the PrcessID \n");
			pclsObj->Release();
			continue;
		}

		hr = pclsObj->Get(L"Handle", 0, &pHandle, 0, 0);
		//wprintf (L"%d",vtPrcessID);
		if (FAILED(hr))
		{
			printf("Failed to get the Process Handle \n");
			pclsObj->Release();
			continue;
		}
		// print the output to screen
		//wprintf(L"Process: %s Domain %s User: %s \n", V_BSTR(&vtProcName), V_BSTR(&vtDomain), V_BSTR(&vtUsername));
		//cout<<(V_UINT(&vtPrcessID));
		//wprintf(L"PID : % u Process No %d \t PID : %u \t Process: %s \n", V_INT(&pHandle),processCount, V_INT(&vtPrcessID), V_BSTR(&vtProcName));
			//wprintf(L"PID : %u \t Process: %s \t\t\t Domain %s \t\t User: %s \n", V_INT(&vtPrcessID), V_BSTR(&vtProcName, V_BSTR(&vtDomain), V_BSTR(&vtUsername)));
		int pid = V_INT((&vtPrcessID));
		std::string process_name = (const char*)_bstr_t(V_BSTR(&vtProcName));
		pushProcess(pid, process_name);
		//cout << HANDLE(&pHandle);
		// release/cleanup resources we used this go around
		VariantClear(&vtProcName);
		VariantClear(&vtProp);
		VariantClear(&vtDomain);
		VariantClear(&vtUsername);
		VariantClear(&vtPrcessID);
		pclsObj->Release();
		processCount++;
	}
	
	// Cleanup
	// ========

	pSvc->Release();
	pLoc->Release();
	pEnumerator->Release();
	CoUninitialize();
   // Program successfully completed.

}


//int main() {
//	fetchProcesses();
//	listProcess();
//	bool e = true;
//	while (e) {
//		cout << "Type PID to stop" << endl;
//		int pid;
//		cin >> pid;
//		//stopProcess(std::strtoul(pid.c_str(), NULL, 16));
//		stopProcess(pid);
//		listProcess();
//	}
//}