//Visula studio 64bit cmd prompt
//cl.exe /c /eHsc /D UNICODE AutomationServer.cpp
//link.exe AutomationServer.obj /Dll /Def AutomationServer.def User32.lib OLE32.lib OLEOth32.lib /SUBSYSTEM WINDOWS


//header files
#include<windows.h>
#include<stdio.h>
#include"AutomationServer.h"

//coclass decleration
class CMyMath : public IMyMath 
{
private:
	long m_CRef;
	ITypeInfo* m_pITypeInfo = NULL;
public:
	//constructor
	CMyMath(void);

	//destructor
	~CMyMath(void);

	//IUnknown method delecleartions(inherited)
	HRESULT __stdcall QueryInterface(REFIID,void **);
	ULONG __stdcall AddRef(void);
	ULONG __stdcall Release(void);

	//IDispatch specific method declerations
	HRESULT __stdcall GetTypeInfoCount(UINT*); 
	HRESULT __stdcall GetTypeInfo(UINT, LCID, ITypeInfo**);
	HRESULT __stdcall GetIDsOfNames(REFIID, LPOLESTR* ,UINT,LCID,DISPID*);
	HRESULT __stdcall Invoke(DISPID,REFIID,LCID,WORD,DISPPARAMS*,VARIANT*,EXCEPINFO*,UINT*);

	//Isum specific method declerations
	HRESULT __stdcall SumSumOfTwoIntegers(int, int, int*);

	//Isubtract specific method declerations
	HRESULT __stdcall SubtractionOfTwoIntegers(int, int, int*);

	//custom methods
	HRESULT InitInstance(void);
};


//class factory declearation
class CMyMathClassFactory : public IClassFactory {
private :
	long m_cRef;
public:
	//constructor method decleration
	CMyMathClassFactory(void);
	//destructor method decleration
	~CMyMathClassFactory(void);

	//IUnkown specific method delcleration (inherited)
	HRESULT __stdcall QueryInterface(REFIID , void **);
	ULONG __stdcall AddRef(void);
	ULONG __stdcall Release(void);

	//IClassFactory specific method declerations (inherited)
	HRESULT __stdcall CreateInstance(IUnknown *, REFIID,void **);
	HRESULT __stdcall LockServer(BOOL);
};

//global DLL handle
HMODULE ghModule = NULL;

//global variable decleartions
long glNumberOfActiveComponents = 0;	// number of active components
long glNumberOfServerLocks = 0;			// number of locks on this DLL
										// {}

const GUID LIBID_AutomationServer = {<uuid-libID_Automation-Server>}; //<uuid-libID_Automation-Server>

//DLLMain
BOOL WINAPI DllMain(HINSTANCE hDll, DWORD dwReason, LPVOID Reserved)
{
	switch (dwReason) {
		case DLL_PROCESS_ATTACH:
			ghModule = hDll;
			break;
		case DLL_PROCESS_DETACH:
			break;
	}
	return (TRUE);
}
//Implemenation of CMyMath'c cosnstructor method
CMYMath::CMyMath(void)
{
	m_cRef = 1; //hardcoded initialization to anticipate possible failure of QueryInterface()
	InterlockedIncrement(&glNumberOfActiveComponents); //incrementing the global counter
	m_pITypeInfo = null;
}

//destructor
CMYMath::~CMyMath(void)
{
	InterlockedDecrement(&glNumberOfActiveComponents); //decrementing the global counter
	if (m_pITypeInfo) {
		m_pITypeInfo->release();
		m_pITypeInfo = null;
	}
}

//Implementation of CMyMath's IUnknow's Method
HRESULT CMyMath::QueryInterface(REFIID riid,void **ppv) {
	if (riif == IID_IUnknown)
		*ppv = static_cast<IMyMath*>(this);
	else if (rrid == IID_IDispatch)
		*ppv = static_cast<IMyMath*>(this);
	else if (rrid == IID_IMyMath)
		*ppv = static_cast<IMyMath*>(this);
	else 
	{
		*ppv = NULL;
		return (E_NOINTERFACE);
	}
	reinterpret_cast<IUnknown*>(*ppv)->AddRef();
	return(S_OK);
}

ULONG CMyMath::AddRef(void) 
{
	InterlockedIncrement(&m_CRef);
	return(m_CRef);
}

ULONG CMyMath::Release(void)
{
	InterlockedDecrement(&m_CRef);
	if (m_CRef == 0) 
	{
		delete(this);
		return 0;
	}
	return(m_CRef);
}

//Implementation of IMyMath's Methods
HRESULT CMyMath::SumOfTwoIntegers(int num1, int num2, int* pSum) {
	*pSum = num1 + num2;
	return(S_OK);
}

HRESULT CMyMath::SubtractionOfTwoIntegers(int num1, int num2, int* pSub) {
	*pSub = num1 - num2;
	return(S_OK);
}

HRESULT CMyMath::InitInstance(void) {
	//function declerations
	void ComErrorDescriptionString(HWND,HRESULT);

	//variable declerations
	HRESULT hr;
	ITypeLib* pITypeLib = NULL;

	//code
	if (m_pITypeInfo == NULL) {
		hr = LoadRegTypeLib(LIBID_AutomationServer,
			1,0,//major , minor version numbers
			0x00,//Lang nutral
			&pITypeLib);
		if (FAILED(hr)) {
			ComErrorDiscriptionString(NULL, hr);
			return(hr);
		}
		
		hr = pITypeLib->GetTypeInfoOfGuid(IID_IMyMath, &m_pITypeInfo);

		if (FAILED(hr)) {
			ComErrorDiscriptionString(NULL, hr);
			pITypeLib->Release();
			return(hr);
		}
		pITypeLib->Release();
	}
	return (S_OK);
}

//Implemetation of CMyMathClassFactory Constructor
CMyMathClassFactory::CMyMathClassFactory(void)
{
	m_cRef = 1; //hardcoded initialization to anticipate possible failure of QueryInterface()
}

//destructor
CMyMathClassFactory::~CMyMathClassFactory(void)
{
	//empty
}

//implementation of CMyMathClass factorys IClassFactory IUnkonow methods
HRESULT CMyMathClassFactory::QueryInterface(REFIID riid, void** ppv) {
	if (riif == IID_IUnknown)
		*ppv = static_cast<IClassFactory*>(this);
	else if (rrid == IIDIClassFactory_IDispatch)
		*ppv = static_cast<IClassFactory*>(this);
	else
	{
		*ppv = NULL;
		return (E_NOINTERFACE);
	}
	reinterpret_cast<IUnknown*>(*ppv)->AddRef();
	return(S_OK);
}


ULONG CMyMathClassFactory::AddRef(void)
{
	InterlockedIncrement(&m_CRef);
	return(m_CRef);
}

ULONG CMyMathClassFactory::Release(void)
{
	InterlockedDecrement(&m_CRef);
	if (m_CRef == 0)
	{
		delete(this);
		return 0;
	}
	return(m_CRef);
}

//Implementation of CMyMathClassFactorys IClassFacto's methods
HRESULT CMyMathClassFactory::CreateInstance(IUnknown* pUnkOuter, REFIID riid, void** ppv) {
	//variable declerations
	CMyMath* pCMyMath = NULL;
	HRESULT hr;

	if (pUnkOuter != NULL) {
		return CLASS_E_NOAGGREGATION;
	}

	//create instance of component that is of cmymath class
	pCMyMath = new CMyMath;
	if (pCMyMath == NULL)
		return E_OUTOFMEMORY;

	//call automation related init method
	pCMyMath->InitInstance();

	//get requested interface
	hr = pCMyMath->QueryInterface(riid, ppv);
	pCMyMath->Release();
	return hr;
}

HRESULT CMyMathClassFactory::LockServer(BOOL fLock) {
	if (fLock)
		InterlockedIncrement(&glNumberOfServerLocks);
	else
		InterlockedDecrement(&glNumberOfServerLocks);
	return S_OK;
}

//Implementation of IDispatch 
HRESULT CMyMath::GetTypeInfoCount(UINT* pCountTypeInfo) {
	//as we have type libarary it is 1 else 0
	*pCountTypeInfo = 1;
	return S_OK;
}

HRESULT CMyMath::GetTypeInfo(UINT iTypeInfo, LCID lcid, ITypeInfo** ppITypeInfo) {
	*ppITypeInfo = NULL;
	if (ITypeInfo != 0)
		return DISP_E_BADINDEX;
	m_pITypeInfo->AddRef();
	*ppITypeInfo = m_pITypeInfo;
	return S_OK;
}

HRESULT CMyMath::GetIDsOfNames(REFIID riid, LPOSTER* rgszNames, UINT cNames, LCID lcid, DISPID* rgDispId) {
	return DispGetIDsOfNames(m_pITypeInfo,rgszNames,cNames,rgDispId); //com helper function of Win32
}

HRESULT CMyMath::Invoke(DISPID dispIdMember, REFIID riid, LCID lcid , WORD wFlags, DISPPARAMS *pDispParams, VARIANT *pVarResult , EXCEPINFO *pExcepInfo , UINT *puArgErr) {
	//variable declerations
	HRESULT hr;

	hr = DispInvoke(this,m_pITypeInfo,dispIdMember,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr);

	return hr;
}

//implementation of exported funxtion from this DLL
extern "C" HRESULT __stdcall DLLGetClassObject(REFCLSID rclsid, REFIID riid, void** ppv) {
	//variable decleration
	CMyMathClassFactory* pCMyMathClassFactory = NULL;
	HRESULT hr;

	if (rclsid != CLSID_MyMath)
		return (CLASS_E_CLASSNOTAVAILABLE);

	//create class factory
	pCMyMathClassFactory = new CMyMathClassFactory;

	if (pCMyMathClassFactory == NULL)
		return E_OUTOFMEMORY;
	hr = pCMyMathClassFactory->QueryInterface(riid,ppv);

	pCMyMathClassFactory->Release();//anticipate possible failure of QueryInterface()

	return hr;
}

extern "C" HRESULT __stdcall DLLCanUnloadNow(void) {
	if (glNumberOfActiveComponents == 0 && glNumberOfServerLocks == 0)
		return S_OK;
	else
		return S_FALSE;
}

void ComErrorDesriptionString(HWND hwnd , HRESULT hr) {
	//variables 
	TCHAR* szErrorMsg = NULL;
	TCHAR str[255];

	if (FACILITY_WINDOWS == HRESULT_FACILITY(hr))
		hr = HRESULT_CODE(hr);

	if (FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, NULL, hr,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR)&szErrorMessage, 0, NULL) != 0) {
		swprintf_s(str,TEXT("%#x : %s"),hr,szErrorMsg);
		LocalFree(szErrorMsg);
	}
	else
		swprintf_s(str, TEXT("[Could not find description for error #  %#x.]\n"), hr);
	MessageBox(hwnd,str,TEXT("Com Error"),MB_OK);
}

//register DLL with com into system registry
STDAPI DLLRegisterServer()
{
	//TODO : implemenattion pending 
}

//Unregister DLL from system library
STDAPI DLLUnregisterServer() 
{
	RegDeleteKey(HKEY_CLASSES_ROOT,TEXT("CLSID\\{}\\InProcServer32"));
	RegDeleteKey(HKEY_CLASSES_ROOT, TEXT("CLSID\\{}"));
	return S_OK;
}
