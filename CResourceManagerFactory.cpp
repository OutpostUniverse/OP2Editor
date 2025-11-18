
#include "stdafx.h"
#include "CResourceManagerFactory.h"
#include "CResourceManager.h"



ULONG CResourceManagerFactory::AddRef()
{
	return ++m_cRef;
}

ULONG CResourceManagerFactory::Release()
{
	if(--m_cRef != 0)
		return m_cRef;
	delete this;
	return 0;
}

HRESULT CResourceManagerFactory::QueryInterface(REFIID riid, void** ppv)
{
	if(riid == IID_IUnknown)
		*ppv = (IUnknown*)this;
	else if(riid == IID_IClassFactory)
		*ppv = (IClassFactory*)this;
	else
	{
		*ppv = NULL;
		return E_NOINTERFACE;
	}
	AddRef();
	return S_OK;
}



HRESULT CResourceManagerFactory::CreateInstance(IUnknown *pUnknownOuter,
	REFIID riid, void** ppv)
{
	if(pUnknownOuter != NULL)
		return CLASS_E_NOAGGREGATION;

	// Initialize returned object pointer to NULL
	*ppv = NULL;

	CResourceManager *pResManager = new CResourceManager(NULL);
	if(pResManager == NULL)
		return E_OUTOFMEMORY;

	HRESULT hr = pResManager->QueryInterface(riid, ppv);
	pResManager->Release();
	return hr;
}

HRESULT CResourceManagerFactory::LockServer(BOOL bLock)
{
	if(bLock)
		g_cLocks++;
	else
		g_cLocks--;
	return S_OK;
}
