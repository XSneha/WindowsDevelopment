//Shree Ganeshay Namha

//cl.exe /c /EHsc ClassFactoryDLLServerWithRegFile.cpp
//link.exe ClassFactoryDLLServerWithRegFile.obj /DLL /DEF:ClassFactoryDLLServerWithRegFile.def User32.lib GDI32.lib Kernel32.lib /SUBSYSTEM:WINDOWS

#include<Windows.h>
#include"ClassFactoryDLLServerWithRegFile.h"

//co-class : com class / concret class 
class CSumSubtract : public ISum, ISubstract
{
private :
	long m_cRef;

public :
	//constructor 
	CSumSubtract(void);

	//desructor
	~CSumSubtract(void);

	//IUnkown methods
	HRESULT __stdcall QueryInterface(REFIID, void**);
	ULONG __stdcall AddRef(void);
	ULONG __stdcall Release(void);

	//Isum method
	HRESULT __stdcall SumOfTwoIntegers(int, int, int*);

	//Isbtract method
	HRESULT __stdcall SubstractionOfTwoIntegers(int, int, int*);
};

//class factory class 
class CSumSubtractClassFactory : public IClassFactory
{
private :
	long m_cRef;

public:
	//constructor
	CSumSubtractClassFactory(void);

	//destructor
	~CSumSubtractClassFactory(void);

	//IUnkown methods
	HRESULT __stdcall QueryInterface(REFIID, void**);
	ULONG __stdcall AddRef(void);
	ULONG __stdcall Release(void);

	//IClassFactory methods
	HRESULT __stdcall CreateInstance(IUnknown*, REFIID, void**);
	HRESULT __stdcall LockServer(BOOL );

};

//global - gl: global long
long glNumberOfActiveComponents;
long glNumberOfServerLocks;

//dll main
BOOL WINAPI DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpReveresed) {
	//code
	switch (dwReason) {
	case DLL_PROCESS_ATTACH:
		break;
	case DLL_THREAD_ATTACH:
		break;
	case DLL_THREAD_DETACH:
		break;
	case DLL_PROCESS_DETACH:
		break;
	default:
		break;
	}

	return TRUE;
}

//CSumSubstract implementation

//constructor
CSumSubtract::CSumSubtract(void) 
{
	//code
	m_cRef = 1;
	InterlockedIncrement(&glNumberOfActiveComponents);
}

//destuctor
CSumSubtract::~CSumSubtract(void) {
	//code
	InterlockedDecrement(&glNumberOfActiveComponents);
}

//IUnknown method implementations
HRESULT CSumSubtract::QueryInterface(REFIID riid, void** ppv) {
	//code
	//Nothing in Com is as importanat as IUnkowns QueryInterface
	if (riid == IID_IUnknown) {
		*ppv = static_cast<ISum *>(this);
	}
	else if (riid == IID_ISum) {
		*ppv = static_cast<ISum *>(this);
	}
	else if (riid == IID_ISubstract) {
		*ppv = static_cast<ISubstract *>(this);
	}
	else {
		*ppv = NULL;
		return E_NOINTERFACE;
	}
	reinterpret_cast<IUnknown*>(*ppv)->AddRef();
	return S_OK;
}

ULONG CSumSubtract::AddRef(void) {
	//code
	InterlockedIncrement(&m_cRef);
	return m_cRef;
}

ULONG CSumSubtract::Release(void) {
	InterlockedDecrement(&m_cRef);
	if (m_cRef == 0) {
		delete(this);
		return 0;
	}
	return m_cRef;
}

//Isum implementation
HRESULT CSumSubtract::SumOfTwoIntegers(int num1, int num2, int* pSum) {
	//code
	*pSum = num1 + num2;
	return S_OK;
}

//Isubstract implementation
HRESULT CSumSubtract::SubstractionOfTwoIntegers(int num1, int num2, int* pSubtract) {
	//code
	*pSubtract = num1 - num2;
	return S_OK;
}

//CSumSubtractClassFactory implementation
//constuctor
CSumSubtractClassFactory::CSumSubtractClassFactory(void) {
	//code
	m_cRef = 1;
}

//destructor
CSumSubtractClassFactory :: ~CSumSubtractClassFactory(void) {
	//code
}

//IUnknown method implementation
HRESULT CSumSubtractClassFactory::QueryInterface(REFIID riid, void** ppv) {
	//code
	if (riid == IID_IUnknown) {
		*ppv = static_cast<IClassFactory*>(this);
	}
	else if (riid == IID_IClassFactory) {
		*ppv = static_cast<IClassFactory*>(this);
	}
	else {
		*ppv = NULL;
		return E_NOINTERFACE;
	}
	reinterpret_cast<IUnknown*>(*ppv)->AddRef();
	return S_OK;
}


ULONG CSumSubtractClassFactory::AddRef(void) {
	//code
	InterlockedIncrement(&m_cRef);
	return m_cRef;
}

ULONG CSumSubtractClassFactory::Release(void) {
	InterlockedDecrement(&m_cRef);
	if (m_cRef == 0) {
		delete(this);
		return 0;
	}
	return m_cRef;
}


//IClassFactory Methods implementaion
HRESULT CSumSubtractClassFactory::CreateInstance(IUnknown* pUnkOuter, REFIID riid, void**ppv) {
	//variable declerations
	CSumSubtract* pCSumSubtract = NULL;
	HRESULT hr;
	//code
	if (pUnkOuter != NULL) {
		return CLASS_E_NOAGGREGATION;
	}
	pCSumSubtract = new CSumSubtract;
	if (pCSumSubtract == NULL) {
		return E_OUTOFMEMORY;
	}
	hr = pCSumSubtract->QueryInterface(riid,ppv);
	pCSumSubtract->Release();
	return hr;
}

HRESULT CSumSubtractClassFactory::LockServer(BOOL fLock) {
	//code
	if (fLock) {
		InterlockedIncrement(&glNumberOfServerLocks);
	}
	else {
		InterlockedDecrement(&glNumberOfServerLocks);
	}
	return S_OK;
}

//exportable com dll methods
EXTERN_C HRESULT __stdcall DllGetClassObject(REFCLSID rClsID,REFIID riid,void ** ppv) {
	//variable declerations 
	CSumSubtractClassFactory* pCSumSubtractClassFactory = NULL;
	HRESULT hr;
	//code
	if (rClsID != CLSID_SumSubstract) {
		return CLASS_E_CLASSNOTAVAILABLE;
	}
	pCSumSubtractClassFactory = new CSumSubtractClassFactory;
	if (pCSumSubtractClassFactory == NULL) {
		return E_OUTOFMEMORY;
	}
	hr = pCSumSubtractClassFactory->QueryInterface(riid, ppv);
	pCSumSubtractClassFactory->Release();
	return hr;
}

EXTERN_C HRESULT __stdcall DllCanUnloadNow(void) {
	//code
	if (glNumberOfActiveComponents == 0 && glNumberOfServerLocks == 0) {
		return S_OK;
	}
	else {
		return S_FALSE;
	}
}
