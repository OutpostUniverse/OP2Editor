
extern int g_cLocks;


class CResourceManagerFactory : public IClassFactory
{
public:
	// IUnknown
	ULONG __stdcall AddRef();
	ULONG __stdcall Release();
	HRESULT __stdcall QueryInterface(REFIID riid, void** ppv);

	// IClassFactory
	HRESULT __stdcall CreateInstance(IUnknown* pUnknownOuter,
		REFIID riid, void** ppv);
	HRESULT __stdcall LockServer(BOOL bLock);

	CResourceManagerFactory() : m_cRef(1) { g_cLocks++; }
	~CResourceManagerFactory() { g_cLocks--; }

private:
	ULONG m_cRef;
};
