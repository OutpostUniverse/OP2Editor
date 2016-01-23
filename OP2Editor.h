/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Fri Nov 11 16:06:01 2005
 */
/* Compiler settings for E:\op2\OP2Editor\OP2Editor.idl:
    Oicf (OptLev=i2), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
*/
//@@MIDL_FILE_HEADING(  )


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 440
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __OP2Editor_h__
#define __OP2Editor_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __StreamReader_FWD_DEFINED__
#define __StreamReader_FWD_DEFINED__
typedef interface StreamReader StreamReader;
#endif 	/* __StreamReader_FWD_DEFINED__ */


#ifndef __SeekableStreamReader_FWD_DEFINED__
#define __SeekableStreamReader_FWD_DEFINED__
typedef interface SeekableStreamReader SeekableStreamReader;
#endif 	/* __SeekableStreamReader_FWD_DEFINED__ */


#ifndef __StreamWriter_FWD_DEFINED__
#define __StreamWriter_FWD_DEFINED__
typedef interface StreamWriter StreamWriter;
#endif 	/* __StreamWriter_FWD_DEFINED__ */


#ifndef __ArchiveReader_FWD_DEFINED__
#define __ArchiveReader_FWD_DEFINED__
typedef interface ArchiveReader ArchiveReader;
#endif 	/* __ArchiveReader_FWD_DEFINED__ */


#ifndef __ArchiveWriter_FWD_DEFINED__
#define __ArchiveWriter_FWD_DEFINED__
typedef interface ArchiveWriter ArchiveWriter;
#endif 	/* __ArchiveWriter_FWD_DEFINED__ */


#ifndef __TileSet_FWD_DEFINED__
#define __TileSet_FWD_DEFINED__
typedef interface TileSet TileSet;
#endif 	/* __TileSet_FWD_DEFINED__ */


#ifndef __TileSetSource_FWD_DEFINED__
#define __TileSetSource_FWD_DEFINED__
typedef interface TileSetSource TileSetSource;
#endif 	/* __TileSetSource_FWD_DEFINED__ */


#ifndef __TileSetManager_FWD_DEFINED__
#define __TileSetManager_FWD_DEFINED__
typedef interface TileSetManager TileSetManager;
#endif 	/* __TileSetManager_FWD_DEFINED__ */


#ifndef __TileGroup_FWD_DEFINED__
#define __TileGroup_FWD_DEFINED__
typedef interface TileGroup TileGroup;
#endif 	/* __TileGroup_FWD_DEFINED__ */


#ifndef __MapFile_FWD_DEFINED__
#define __MapFile_FWD_DEFINED__
typedef interface MapFile MapFile;
#endif 	/* __MapFile_FWD_DEFINED__ */


#ifndef __IResourceManager_FWD_DEFINED__
#define __IResourceManager_FWD_DEFINED__
typedef interface IResourceManager IResourceManager;
#endif 	/* __IResourceManager_FWD_DEFINED__ */


#ifndef __ResourceManager_FWD_DEFINED__
#define __ResourceManager_FWD_DEFINED__

#ifdef __cplusplus
typedef class ResourceManager ResourceManager;
#else
typedef struct ResourceManager ResourceManager;
#endif /* __cplusplus */

#endif 	/* __ResourceManager_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef __StreamReader_INTERFACE_DEFINED__
#define __StreamReader_INTERFACE_DEFINED__

/* interface StreamReader */
/* [helpstring][nonextensible][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_StreamReader;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("70AC9DEE-CE0F-4145-A140-6AE1BA658B1E")
    StreamReader : public IUnknown
    {
    public:
        virtual /* [helpstring][local] */ HRESULT STDMETHODCALLTYPE Read( 
            /* [in] */ int numBytes,
            /* [in] */ int pBuffer,
            /* [retval][out] */ int __RPC_FAR *numBytesRead) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Status( 
            /* [retval][out] */ int __RPC_FAR *status) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct StreamReaderVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            StreamReader __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            StreamReader __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            StreamReader __RPC_FAR * This);
        
        /* [helpstring][local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Read )( 
            StreamReader __RPC_FAR * This,
            /* [in] */ int numBytes,
            /* [in] */ int pBuffer,
            /* [retval][out] */ int __RPC_FAR *numBytesRead);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Status )( 
            StreamReader __RPC_FAR * This,
            /* [retval][out] */ int __RPC_FAR *status);
        
        END_INTERFACE
    } StreamReaderVtbl;

    interface StreamReader
    {
        CONST_VTBL struct StreamReaderVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define StreamReader_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define StreamReader_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define StreamReader_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define StreamReader_Read(This,numBytes,pBuffer,numBytesRead)	\
    (This)->lpVtbl -> Read(This,numBytes,pBuffer,numBytesRead)

#define StreamReader_get_Status(This,status)	\
    (This)->lpVtbl -> get_Status(This,status)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][local] */ HRESULT STDMETHODCALLTYPE StreamReader_Read_Proxy( 
    StreamReader __RPC_FAR * This,
    /* [in] */ int numBytes,
    /* [in] */ int pBuffer,
    /* [retval][out] */ int __RPC_FAR *numBytesRead);


void __RPC_STUB StreamReader_Read_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE StreamReader_get_Status_Proxy( 
    StreamReader __RPC_FAR * This,
    /* [retval][out] */ int __RPC_FAR *status);


void __RPC_STUB StreamReader_get_Status_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __StreamReader_INTERFACE_DEFINED__ */


#ifndef __SeekableStreamReader_INTERFACE_DEFINED__
#define __SeekableStreamReader_INTERFACE_DEFINED__

/* interface SeekableStreamReader */
/* [helpstring][nonextensible][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_SeekableStreamReader;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("57B5FDD0-8E6E-4134-94DE-6949BD2EB3CB")
    SeekableStreamReader : public StreamReader
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_ReadOffset( 
            /* [retval][out] */ int __RPC_FAR *readOffset) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_StreamSize( 
            /* [retval][out] */ int __RPC_FAR *streamSize) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Seek( 
            /* [in] */ int offset) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct SeekableStreamReaderVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            SeekableStreamReader __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            SeekableStreamReader __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            SeekableStreamReader __RPC_FAR * This);
        
        /* [helpstring][local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Read )( 
            SeekableStreamReader __RPC_FAR * This,
            /* [in] */ int numBytes,
            /* [in] */ int pBuffer,
            /* [retval][out] */ int __RPC_FAR *numBytesRead);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Status )( 
            SeekableStreamReader __RPC_FAR * This,
            /* [retval][out] */ int __RPC_FAR *status);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ReadOffset )( 
            SeekableStreamReader __RPC_FAR * This,
            /* [retval][out] */ int __RPC_FAR *readOffset);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_StreamSize )( 
            SeekableStreamReader __RPC_FAR * This,
            /* [retval][out] */ int __RPC_FAR *streamSize);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Seek )( 
            SeekableStreamReader __RPC_FAR * This,
            /* [in] */ int offset);
        
        END_INTERFACE
    } SeekableStreamReaderVtbl;

    interface SeekableStreamReader
    {
        CONST_VTBL struct SeekableStreamReaderVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define SeekableStreamReader_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define SeekableStreamReader_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define SeekableStreamReader_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define SeekableStreamReader_Read(This,numBytes,pBuffer,numBytesRead)	\
    (This)->lpVtbl -> Read(This,numBytes,pBuffer,numBytesRead)

#define SeekableStreamReader_get_Status(This,status)	\
    (This)->lpVtbl -> get_Status(This,status)


#define SeekableStreamReader_get_ReadOffset(This,readOffset)	\
    (This)->lpVtbl -> get_ReadOffset(This,readOffset)

#define SeekableStreamReader_get_StreamSize(This,streamSize)	\
    (This)->lpVtbl -> get_StreamSize(This,streamSize)

#define SeekableStreamReader_Seek(This,offset)	\
    (This)->lpVtbl -> Seek(This,offset)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE SeekableStreamReader_get_ReadOffset_Proxy( 
    SeekableStreamReader __RPC_FAR * This,
    /* [retval][out] */ int __RPC_FAR *readOffset);


void __RPC_STUB SeekableStreamReader_get_ReadOffset_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE SeekableStreamReader_get_StreamSize_Proxy( 
    SeekableStreamReader __RPC_FAR * This,
    /* [retval][out] */ int __RPC_FAR *streamSize);


void __RPC_STUB SeekableStreamReader_get_StreamSize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE SeekableStreamReader_Seek_Proxy( 
    SeekableStreamReader __RPC_FAR * This,
    /* [in] */ int offset);


void __RPC_STUB SeekableStreamReader_Seek_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __SeekableStreamReader_INTERFACE_DEFINED__ */


#ifndef __StreamWriter_INTERFACE_DEFINED__
#define __StreamWriter_INTERFACE_DEFINED__

/* interface StreamWriter */
/* [helpstring][nonextensible][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_StreamWriter;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("B83597A2-3471-48db-B9BC-EB4749BA1AAA")
    StreamWriter : public IUnknown
    {
    public:
        virtual /* [helpstring][local] */ HRESULT STDMETHODCALLTYPE Write( 
            /* [in] */ int numBytes,
            /* [in] */ int pBuffer,
            /* [retval][out] */ int __RPC_FAR *numBytesWritten) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Status( 
            /* [retval][out] */ int __RPC_FAR *status) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct StreamWriterVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            StreamWriter __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            StreamWriter __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            StreamWriter __RPC_FAR * This);
        
        /* [helpstring][local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Write )( 
            StreamWriter __RPC_FAR * This,
            /* [in] */ int numBytes,
            /* [in] */ int pBuffer,
            /* [retval][out] */ int __RPC_FAR *numBytesWritten);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Status )( 
            StreamWriter __RPC_FAR * This,
            /* [retval][out] */ int __RPC_FAR *status);
        
        END_INTERFACE
    } StreamWriterVtbl;

    interface StreamWriter
    {
        CONST_VTBL struct StreamWriterVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define StreamWriter_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define StreamWriter_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define StreamWriter_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define StreamWriter_Write(This,numBytes,pBuffer,numBytesWritten)	\
    (This)->lpVtbl -> Write(This,numBytes,pBuffer,numBytesWritten)

#define StreamWriter_get_Status(This,status)	\
    (This)->lpVtbl -> get_Status(This,status)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][local] */ HRESULT STDMETHODCALLTYPE StreamWriter_Write_Proxy( 
    StreamWriter __RPC_FAR * This,
    /* [in] */ int numBytes,
    /* [in] */ int pBuffer,
    /* [retval][out] */ int __RPC_FAR *numBytesWritten);


void __RPC_STUB StreamWriter_Write_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE StreamWriter_get_Status_Proxy( 
    StreamWriter __RPC_FAR * This,
    /* [retval][out] */ int __RPC_FAR *status);


void __RPC_STUB StreamWriter_get_Status_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __StreamWriter_INTERFACE_DEFINED__ */


#ifndef __ArchiveReader_INTERFACE_DEFINED__
#define __ArchiveReader_INTERFACE_DEFINED__

/* interface ArchiveReader */
/* [helpstring][nonextensible][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_ArchiveReader;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("CE02B285-D2F4-4707-B6D3-39CB6697357C")
    ArchiveReader : public IUnknown
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_NumFiles( 
            /* [retval][out] */ int __RPC_FAR *numFiles) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_FileName( 
            /* [in] */ int index,
            /* [retval][out] */ BSTR __RPC_FAR *fileName) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE OpenStreamRead( 
            /* [in] */ BSTR filename,
            /* [retval][out] */ StreamReader __RPC_FAR *__RPC_FAR *stream) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ArchiveReaderVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ArchiveReader __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ArchiveReader __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ArchiveReader __RPC_FAR * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_NumFiles )( 
            ArchiveReader __RPC_FAR * This,
            /* [retval][out] */ int __RPC_FAR *numFiles);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_FileName )( 
            ArchiveReader __RPC_FAR * This,
            /* [in] */ int index,
            /* [retval][out] */ BSTR __RPC_FAR *fileName);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *OpenStreamRead )( 
            ArchiveReader __RPC_FAR * This,
            /* [in] */ BSTR filename,
            /* [retval][out] */ StreamReader __RPC_FAR *__RPC_FAR *stream);
        
        END_INTERFACE
    } ArchiveReaderVtbl;

    interface ArchiveReader
    {
        CONST_VTBL struct ArchiveReaderVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ArchiveReader_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ArchiveReader_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ArchiveReader_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ArchiveReader_get_NumFiles(This,numFiles)	\
    (This)->lpVtbl -> get_NumFiles(This,numFiles)

#define ArchiveReader_get_FileName(This,index,fileName)	\
    (This)->lpVtbl -> get_FileName(This,index,fileName)

#define ArchiveReader_OpenStreamRead(This,filename,stream)	\
    (This)->lpVtbl -> OpenStreamRead(This,filename,stream)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE ArchiveReader_get_NumFiles_Proxy( 
    ArchiveReader __RPC_FAR * This,
    /* [retval][out] */ int __RPC_FAR *numFiles);


void __RPC_STUB ArchiveReader_get_NumFiles_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE ArchiveReader_get_FileName_Proxy( 
    ArchiveReader __RPC_FAR * This,
    /* [in] */ int index,
    /* [retval][out] */ BSTR __RPC_FAR *fileName);


void __RPC_STUB ArchiveReader_get_FileName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ArchiveReader_OpenStreamRead_Proxy( 
    ArchiveReader __RPC_FAR * This,
    /* [in] */ BSTR filename,
    /* [retval][out] */ StreamReader __RPC_FAR *__RPC_FAR *stream);


void __RPC_STUB ArchiveReader_OpenStreamRead_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ArchiveReader_INTERFACE_DEFINED__ */


#ifndef __ArchiveWriter_INTERFACE_DEFINED__
#define __ArchiveWriter_INTERFACE_DEFINED__

/* interface ArchiveWriter */
/* [helpstring][nonextensible][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_ArchiveWriter;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("98A6E750-10C7-4133-9A0E-17FB62EC6ADE")
    ArchiveWriter : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE AddToArchive( 
            /* [in] */ BSTR fileName,
            /* [in] */ SeekableStreamReader __RPC_FAR *inStream,
            /* [in] */ int reserved) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE WriteArchive( 
            /* [in] */ StreamWriter __RPC_FAR *outStream) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ArchiveWriterVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ArchiveWriter __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ArchiveWriter __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ArchiveWriter __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AddToArchive )( 
            ArchiveWriter __RPC_FAR * This,
            /* [in] */ BSTR fileName,
            /* [in] */ SeekableStreamReader __RPC_FAR *inStream,
            /* [in] */ int reserved);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *WriteArchive )( 
            ArchiveWriter __RPC_FAR * This,
            /* [in] */ StreamWriter __RPC_FAR *outStream);
        
        END_INTERFACE
    } ArchiveWriterVtbl;

    interface ArchiveWriter
    {
        CONST_VTBL struct ArchiveWriterVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ArchiveWriter_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ArchiveWriter_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ArchiveWriter_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ArchiveWriter_AddToArchive(This,fileName,inStream,reserved)	\
    (This)->lpVtbl -> AddToArchive(This,fileName,inStream,reserved)

#define ArchiveWriter_WriteArchive(This,outStream)	\
    (This)->lpVtbl -> WriteArchive(This,outStream)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE ArchiveWriter_AddToArchive_Proxy( 
    ArchiveWriter __RPC_FAR * This,
    /* [in] */ BSTR fileName,
    /* [in] */ SeekableStreamReader __RPC_FAR *inStream,
    /* [in] */ int reserved);


void __RPC_STUB ArchiveWriter_AddToArchive_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ArchiveWriter_WriteArchive_Proxy( 
    ArchiveWriter __RPC_FAR * This,
    /* [in] */ StreamWriter __RPC_FAR *outStream);


void __RPC_STUB ArchiveWriter_WriteArchive_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ArchiveWriter_INTERFACE_DEFINED__ */


#ifndef __TileSet_INTERFACE_DEFINED__
#define __TileSet_INTERFACE_DEFINED__

/* interface TileSet */
/* [helpstring][nonextensible][oleautomation][uuid][object] */ 

/* [helpstring][v1_enum] */ 
enum TileSetSaveFormat
    {	Default	= 0,
	Bitmap	= 1
    };

EXTERN_C const IID IID_TileSet;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("C7F1E185-8079-4538-96CF-5950406AE1AA")
    TileSet : public IUnknown
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_NumTiles( 
            /* [retval][out] */ int __RPC_FAR *numTiles) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_TileSize( 
            /* [retval][out] */ int __RPC_FAR *tileSize) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_BitDepth( 
            /* [retval][out] */ int __RPC_FAR *bitDepth) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_NumPaletteEntries( 
            /* [retval][out] */ int __RPC_FAR *numPaletteEntries) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_PaletteEntry( 
            /* [in] */ int index,
            /* [retval][out] */ int __RPC_FAR *palEntry) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_PaletteEntry( 
            /* [in] */ int index,
            /* [in] */ int palEntry) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetNumTiles( 
            /* [in] */ int numTiles) = 0;
        
        virtual /* [helpstring][local] */ HRESULT STDMETHODCALLTYPE GetPixelData( 
            /* [in] */ int pBuffer,
            /* [in] */ int startOffset,
            /* [in] */ int numBytes) = 0;
        
        virtual /* [helpstring][local] */ HRESULT STDMETHODCALLTYPE SetPixelData( 
            /* [in] */ int pBuffer,
            /* [in] */ int startOffset,
            /* [in] */ int numBytes) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_MiniMapColors( 
            /* [in] */ int tileIndex,
            /* [retval][out] */ int __RPC_FAR *color) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE PasteTile( 
            /* [in] */ int destDC,
            /* [in] */ int pixelX,
            /* [in] */ int pixelY,
            /* [in] */ int tileNum) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SaveTileSet( 
            /* [in] */ StreamWriter __RPC_FAR *stream,
            /* [in] */ enum TileSetSaveFormat saveFormat) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct TileSetVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            TileSet __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            TileSet __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            TileSet __RPC_FAR * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_NumTiles )( 
            TileSet __RPC_FAR * This,
            /* [retval][out] */ int __RPC_FAR *numTiles);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_TileSize )( 
            TileSet __RPC_FAR * This,
            /* [retval][out] */ int __RPC_FAR *tileSize);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_BitDepth )( 
            TileSet __RPC_FAR * This,
            /* [retval][out] */ int __RPC_FAR *bitDepth);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_NumPaletteEntries )( 
            TileSet __RPC_FAR * This,
            /* [retval][out] */ int __RPC_FAR *numPaletteEntries);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_PaletteEntry )( 
            TileSet __RPC_FAR * This,
            /* [in] */ int index,
            /* [retval][out] */ int __RPC_FAR *palEntry);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_PaletteEntry )( 
            TileSet __RPC_FAR * This,
            /* [in] */ int index,
            /* [in] */ int palEntry);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetNumTiles )( 
            TileSet __RPC_FAR * This,
            /* [in] */ int numTiles);
        
        /* [helpstring][local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetPixelData )( 
            TileSet __RPC_FAR * This,
            /* [in] */ int pBuffer,
            /* [in] */ int startOffset,
            /* [in] */ int numBytes);
        
        /* [helpstring][local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetPixelData )( 
            TileSet __RPC_FAR * This,
            /* [in] */ int pBuffer,
            /* [in] */ int startOffset,
            /* [in] */ int numBytes);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_MiniMapColors )( 
            TileSet __RPC_FAR * This,
            /* [in] */ int tileIndex,
            /* [retval][out] */ int __RPC_FAR *color);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *PasteTile )( 
            TileSet __RPC_FAR * This,
            /* [in] */ int destDC,
            /* [in] */ int pixelX,
            /* [in] */ int pixelY,
            /* [in] */ int tileNum);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SaveTileSet )( 
            TileSet __RPC_FAR * This,
            /* [in] */ StreamWriter __RPC_FAR *stream,
            /* [in] */ enum TileSetSaveFormat saveFormat);
        
        END_INTERFACE
    } TileSetVtbl;

    interface TileSet
    {
        CONST_VTBL struct TileSetVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define TileSet_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define TileSet_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define TileSet_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define TileSet_get_NumTiles(This,numTiles)	\
    (This)->lpVtbl -> get_NumTiles(This,numTiles)

#define TileSet_get_TileSize(This,tileSize)	\
    (This)->lpVtbl -> get_TileSize(This,tileSize)

#define TileSet_get_BitDepth(This,bitDepth)	\
    (This)->lpVtbl -> get_BitDepth(This,bitDepth)

#define TileSet_get_NumPaletteEntries(This,numPaletteEntries)	\
    (This)->lpVtbl -> get_NumPaletteEntries(This,numPaletteEntries)

#define TileSet_get_PaletteEntry(This,index,palEntry)	\
    (This)->lpVtbl -> get_PaletteEntry(This,index,palEntry)

#define TileSet_put_PaletteEntry(This,index,palEntry)	\
    (This)->lpVtbl -> put_PaletteEntry(This,index,palEntry)

#define TileSet_SetNumTiles(This,numTiles)	\
    (This)->lpVtbl -> SetNumTiles(This,numTiles)

#define TileSet_GetPixelData(This,pBuffer,startOffset,numBytes)	\
    (This)->lpVtbl -> GetPixelData(This,pBuffer,startOffset,numBytes)

#define TileSet_SetPixelData(This,pBuffer,startOffset,numBytes)	\
    (This)->lpVtbl -> SetPixelData(This,pBuffer,startOffset,numBytes)

#define TileSet_get_MiniMapColors(This,tileIndex,color)	\
    (This)->lpVtbl -> get_MiniMapColors(This,tileIndex,color)

#define TileSet_PasteTile(This,destDC,pixelX,pixelY,tileNum)	\
    (This)->lpVtbl -> PasteTile(This,destDC,pixelX,pixelY,tileNum)

#define TileSet_SaveTileSet(This,stream,saveFormat)	\
    (This)->lpVtbl -> SaveTileSet(This,stream,saveFormat)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE TileSet_get_NumTiles_Proxy( 
    TileSet __RPC_FAR * This,
    /* [retval][out] */ int __RPC_FAR *numTiles);


void __RPC_STUB TileSet_get_NumTiles_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE TileSet_get_TileSize_Proxy( 
    TileSet __RPC_FAR * This,
    /* [retval][out] */ int __RPC_FAR *tileSize);


void __RPC_STUB TileSet_get_TileSize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE TileSet_get_BitDepth_Proxy( 
    TileSet __RPC_FAR * This,
    /* [retval][out] */ int __RPC_FAR *bitDepth);


void __RPC_STUB TileSet_get_BitDepth_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE TileSet_get_NumPaletteEntries_Proxy( 
    TileSet __RPC_FAR * This,
    /* [retval][out] */ int __RPC_FAR *numPaletteEntries);


void __RPC_STUB TileSet_get_NumPaletteEntries_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE TileSet_get_PaletteEntry_Proxy( 
    TileSet __RPC_FAR * This,
    /* [in] */ int index,
    /* [retval][out] */ int __RPC_FAR *palEntry);


void __RPC_STUB TileSet_get_PaletteEntry_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE TileSet_put_PaletteEntry_Proxy( 
    TileSet __RPC_FAR * This,
    /* [in] */ int index,
    /* [in] */ int palEntry);


void __RPC_STUB TileSet_put_PaletteEntry_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE TileSet_SetNumTiles_Proxy( 
    TileSet __RPC_FAR * This,
    /* [in] */ int numTiles);


void __RPC_STUB TileSet_SetNumTiles_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][local] */ HRESULT STDMETHODCALLTYPE TileSet_GetPixelData_Proxy( 
    TileSet __RPC_FAR * This,
    /* [in] */ int pBuffer,
    /* [in] */ int startOffset,
    /* [in] */ int numBytes);


void __RPC_STUB TileSet_GetPixelData_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][local] */ HRESULT STDMETHODCALLTYPE TileSet_SetPixelData_Proxy( 
    TileSet __RPC_FAR * This,
    /* [in] */ int pBuffer,
    /* [in] */ int startOffset,
    /* [in] */ int numBytes);


void __RPC_STUB TileSet_SetPixelData_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE TileSet_get_MiniMapColors_Proxy( 
    TileSet __RPC_FAR * This,
    /* [in] */ int tileIndex,
    /* [retval][out] */ int __RPC_FAR *color);


void __RPC_STUB TileSet_get_MiniMapColors_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE TileSet_PasteTile_Proxy( 
    TileSet __RPC_FAR * This,
    /* [in] */ int destDC,
    /* [in] */ int pixelX,
    /* [in] */ int pixelY,
    /* [in] */ int tileNum);


void __RPC_STUB TileSet_PasteTile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE TileSet_SaveTileSet_Proxy( 
    TileSet __RPC_FAR * This,
    /* [in] */ StreamWriter __RPC_FAR *stream,
    /* [in] */ enum TileSetSaveFormat saveFormat);


void __RPC_STUB TileSet_SaveTileSet_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __TileSet_INTERFACE_DEFINED__ */


#ifndef __TileSetSource_INTERFACE_DEFINED__
#define __TileSetSource_INTERFACE_DEFINED__

/* interface TileSetSource */
/* [helpstring][nonextensible][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_TileSetSource;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("153BC780-0FF2-44e4-8448-5B3F46050475")
    TileSetSource : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE LoadTileSet( 
            /* [in] */ BSTR tileSetName,
            /* [retval][out] */ TileSet __RPC_FAR *__RPC_FAR *tileSet) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE UnloadTileSet( 
            /* [in] */ BSTR tileSetName) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct TileSetSourceVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            TileSetSource __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            TileSetSource __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            TileSetSource __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *LoadTileSet )( 
            TileSetSource __RPC_FAR * This,
            /* [in] */ BSTR tileSetName,
            /* [retval][out] */ TileSet __RPC_FAR *__RPC_FAR *tileSet);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *UnloadTileSet )( 
            TileSetSource __RPC_FAR * This,
            /* [in] */ BSTR tileSetName);
        
        END_INTERFACE
    } TileSetSourceVtbl;

    interface TileSetSource
    {
        CONST_VTBL struct TileSetSourceVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define TileSetSource_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define TileSetSource_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define TileSetSource_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define TileSetSource_LoadTileSet(This,tileSetName,tileSet)	\
    (This)->lpVtbl -> LoadTileSet(This,tileSetName,tileSet)

#define TileSetSource_UnloadTileSet(This,tileSetName)	\
    (This)->lpVtbl -> UnloadTileSet(This,tileSetName)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE TileSetSource_LoadTileSet_Proxy( 
    TileSetSource __RPC_FAR * This,
    /* [in] */ BSTR tileSetName,
    /* [retval][out] */ TileSet __RPC_FAR *__RPC_FAR *tileSet);


void __RPC_STUB TileSetSource_LoadTileSet_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE TileSetSource_UnloadTileSet_Proxy( 
    TileSetSource __RPC_FAR * This,
    /* [in] */ BSTR tileSetName);


void __RPC_STUB TileSetSource_UnloadTileSet_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __TileSetSource_INTERFACE_DEFINED__ */


#ifndef __TileSetManager_INTERFACE_DEFINED__
#define __TileSetManager_INTERFACE_DEFINED__

/* interface TileSetManager */
/* [helpstring][nonextensible][oleautomation][uuid][object] */ 

/* [helpstring][v1_enum] */ 
enum TerrainTubeDirection
    {	DirLeftToRight	= 0,
	DirTopToBottom	= 1,
	DirLeftToBottom	= 2,
	DirRightToBottom	= 3,
	DirLeftToTop	= 4,
	DirRightToTop	= 5,
	DirLeftRightTop	= 6,
	DirLeftRightBottom	= 7,
	DirLeftRightTopBottom	= 8,
	DirLeftTopBottom	= 9,
	DirRightTopBottom	= 10,
	DirBottom	= 11,
	DirTop	= 12,
	DirRight	= 13,
	DirLeft	= 14,
	DirMiddleSectionOnly	= 15
    };

EXTERN_C const IID IID_TileSetManager;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("33A10A9E-A3B0-498f-A871-3ECC78B477FB")
    TileSetManager : public IUnknown
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_NumTileSets( 
            /* [retval][out] */ int __RPC_FAR *numTileSets) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_TileSetName( 
            /* [in] */ int index,
            /* [retval][out] */ BSTR __RPC_FAR *tileSetName) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_TileSet( 
            /* [in] */ int index,
            /* [retval][out] */ TileSet __RPC_FAR *__RPC_FAR *tileSet) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE AddTileSet( 
            /* [in] */ BSTR tileSetName,
            /* [retval][out] */ int __RPC_FAR *index) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE RemoveTileSet( 
            /* [in] */ BSTR tileSetName,
            /* [retval][out] */ int __RPC_FAR *index) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ReplaceTileSet( 
            /* [in] */ int index,
            /* [in] */ BSTR tileSetName) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE MapInTiles( 
            /* [in] */ int tileSetIndex,
            /* [in] */ int startTile,
            /* [in] */ int numTiles,
            /* [retval][out] */ int __RPC_FAR *mappingIndex) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetMappingIndex( 
            /* [in] */ int tileSetIndex,
            /* [in] */ int tileIndex,
            /* [in] */ int numTileReplacements,
            /* [in] */ int cycleDelay,
            /* [retval][out] */ int __RPC_FAR *mappingIndex) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_NumMappings( 
            /* [retval][out] */ int __RPC_FAR *numMappings) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_TileSetIndex( 
            /* [in] */ int mappingIndex,
            /* [retval][out] */ int __RPC_FAR *tileSetIndex) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_TileSetIndex( 
            /* [in] */ int mappingIndex,
            /* [in] */ int tileSetIndex) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_TileSetTileIndex( 
            /* [in] */ int mappingIndex,
            /* [retval][out] */ int __RPC_FAR *tileSetTileIndex) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_TileSetTileIndex( 
            /* [in] */ int mappingIndex,
            /* [in] */ int tileSetTileIndex) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_NumTileReplacements( 
            /* [in] */ int mappingIndex,
            /* [retval][out] */ int __RPC_FAR *numTileReplacements) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_NumTileReplacements( 
            /* [in] */ int mappingIndex,
            /* [in] */ int numTileReplacements) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_CycleDelay( 
            /* [in] */ int mappingIndex,
            /* [retval][out] */ int __RPC_FAR *cycleDelay) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_CycleDelay( 
            /* [in] */ int mappingIndex,
            /* [in] */ int cycleDelay) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_NumTerrains( 
            /* [retval][out] */ int __RPC_FAR *numTerrains) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetNumTerrains( 
            /* [in] */ int numTerrains) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_TerrainStartTile( 
            /* [in] */ int terrainIndex,
            /* [retval][out] */ int __RPC_FAR *startMapping) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_TerrainStartTile( 
            /* [in] */ int terrainIndex,
            /* [in] */ int startMapping) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_TerrainEndTile( 
            /* [in] */ int terrainIndex,
            /* [retval][out] */ int __RPC_FAR *endMapping) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_TerrainEndTile( 
            /* [in] */ int terrainIndex,
            /* [in] */ int endMapping) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_TerrainDozed( 
            /* [in] */ int terrainIndex,
            /* [retval][out] */ int __RPC_FAR *dataMapping) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_TerrainDozed( 
            /* [in] */ int terrainIndex,
            /* [in] */ int dataMapping) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_TerrainRubble( 
            /* [in] */ int terrainIndex,
            /* [retval][out] */ int __RPC_FAR *dataMapping) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_TerrainRubble( 
            /* [in] */ int terrainIndex,
            /* [in] */ int dataMapping) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_TerrainTubeUnk( 
            /* [in] */ int terrainIndex,
            /* [in] */ enum TerrainTubeDirection direction,
            /* [retval][out] */ int __RPC_FAR *dataMapping) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_TerrainTubeUnk( 
            /* [in] */ int terrainIndex,
            /* [in] */ enum TerrainTubeDirection direction,
            /* [in] */ int dataMapping) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_TerrainLavaWall( 
            /* [in] */ int terrainIndex,
            /* [in] */ enum TerrainTubeDirection direction,
            /* [retval][out] */ int __RPC_FAR *dataMapping) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_TerrainLavaWall( 
            /* [in] */ int terrainIndex,
            /* [in] */ enum TerrainTubeDirection direction,
            /* [in] */ int dataMapping) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_TerrainMicrobeWall( 
            /* [in] */ int terrainIndex,
            /* [in] */ enum TerrainTubeDirection direction,
            /* [retval][out] */ int __RPC_FAR *dataMapping) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_TerrainMicrobeWall( 
            /* [in] */ int terrainIndex,
            /* [in] */ enum TerrainTubeDirection direction,
            /* [in] */ int dataMapping) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_TerrainNormalWall( 
            /* [in] */ int terrainIndex,
            /* [in] */ enum TerrainTubeDirection direction,
            /* [retval][out] */ int __RPC_FAR *dataMapping) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_TerrainNormalWall( 
            /* [in] */ int terrainIndex,
            /* [in] */ enum TerrainTubeDirection direction,
            /* [in] */ int dataMapping) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_TerrainDamagedWall( 
            /* [in] */ int terrainIndex,
            /* [in] */ enum TerrainTubeDirection direction,
            /* [retval][out] */ int __RPC_FAR *dataMapping) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_TerrainDamagedWall( 
            /* [in] */ int terrainIndex,
            /* [in] */ enum TerrainTubeDirection direction,
            /* [in] */ int dataMapping) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_TerrainRuinedWall( 
            /* [in] */ int terrainIndex,
            /* [in] */ enum TerrainTubeDirection direction,
            /* [retval][out] */ int __RPC_FAR *dataMapping) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_TerrainRuinedWall( 
            /* [in] */ int terrainIndex,
            /* [in] */ enum TerrainTubeDirection direction,
            /* [in] */ int dataMapping) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_TerrainLava( 
            /* [in] */ int terrainIndex,
            /* [retval][out] */ int __RPC_FAR *dataMapping) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_TerrainLava( 
            /* [in] */ int terrainIndex,
            /* [in] */ int dataMapping) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_TerrainFlat1( 
            /* [in] */ int terrainIndex,
            /* [retval][out] */ int __RPC_FAR *dataMapping) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_TerrainFlat1( 
            /* [in] */ int terrainIndex,
            /* [in] */ int dataMapping) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_TerrainFlat2( 
            /* [in] */ int terrainIndex,
            /* [retval][out] */ int __RPC_FAR *dataMapping) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_TerrainFlat2( 
            /* [in] */ int terrainIndex,
            /* [in] */ int dataMapping) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_TerrainFlat3( 
            /* [in] */ int terrainIndex,
            /* [retval][out] */ int __RPC_FAR *dataMapping) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_TerrainFlat3( 
            /* [in] */ int terrainIndex,
            /* [in] */ int dataMapping) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_TerrainTube( 
            /* [in] */ int terrainIndex,
            /* [in] */ enum TerrainTubeDirection direction,
            /* [retval][out] */ int __RPC_FAR *dataMapping) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_TerrainTube( 
            /* [in] */ int terrainIndex,
            /* [in] */ enum TerrainTubeDirection direction,
            /* [in] */ int dataMapping) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_TerrainScorched( 
            /* [in] */ int terrainIndex,
            /* [retval][out] */ int __RPC_FAR *dataMapping) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_TerrainScorched( 
            /* [in] */ int terrainIndex,
            /* [in] */ int dataMapping) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_TerrainUnknown( 
            /* [in] */ int terrainIndex,
            /* [in] */ int unkIndex,
            /* [retval][out] */ int __RPC_FAR *dataMapping) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_TerrainUnknown( 
            /* [in] */ int terrainIndex,
            /* [in] */ int unkIndex,
            /* [in] */ int dataMapping) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct TileSetManagerVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            TileSetManager __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            TileSetManager __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            TileSetManager __RPC_FAR * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_NumTileSets )( 
            TileSetManager __RPC_FAR * This,
            /* [retval][out] */ int __RPC_FAR *numTileSets);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_TileSetName )( 
            TileSetManager __RPC_FAR * This,
            /* [in] */ int index,
            /* [retval][out] */ BSTR __RPC_FAR *tileSetName);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_TileSet )( 
            TileSetManager __RPC_FAR * This,
            /* [in] */ int index,
            /* [retval][out] */ TileSet __RPC_FAR *__RPC_FAR *tileSet);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AddTileSet )( 
            TileSetManager __RPC_FAR * This,
            /* [in] */ BSTR tileSetName,
            /* [retval][out] */ int __RPC_FAR *index);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *RemoveTileSet )( 
            TileSetManager __RPC_FAR * This,
            /* [in] */ BSTR tileSetName,
            /* [retval][out] */ int __RPC_FAR *index);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ReplaceTileSet )( 
            TileSetManager __RPC_FAR * This,
            /* [in] */ int index,
            /* [in] */ BSTR tileSetName);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *MapInTiles )( 
            TileSetManager __RPC_FAR * This,
            /* [in] */ int tileSetIndex,
            /* [in] */ int startTile,
            /* [in] */ int numTiles,
            /* [retval][out] */ int __RPC_FAR *mappingIndex);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetMappingIndex )( 
            TileSetManager __RPC_FAR * This,
            /* [in] */ int tileSetIndex,
            /* [in] */ int tileIndex,
            /* [in] */ int numTileReplacements,
            /* [in] */ int cycleDelay,
            /* [retval][out] */ int __RPC_FAR *mappingIndex);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_NumMappings )( 
            TileSetManager __RPC_FAR * This,
            /* [retval][out] */ int __RPC_FAR *numMappings);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_TileSetIndex )( 
            TileSetManager __RPC_FAR * This,
            /* [in] */ int mappingIndex,
            /* [retval][out] */ int __RPC_FAR *tileSetIndex);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_TileSetIndex )( 
            TileSetManager __RPC_FAR * This,
            /* [in] */ int mappingIndex,
            /* [in] */ int tileSetIndex);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_TileSetTileIndex )( 
            TileSetManager __RPC_FAR * This,
            /* [in] */ int mappingIndex,
            /* [retval][out] */ int __RPC_FAR *tileSetTileIndex);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_TileSetTileIndex )( 
            TileSetManager __RPC_FAR * This,
            /* [in] */ int mappingIndex,
            /* [in] */ int tileSetTileIndex);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_NumTileReplacements )( 
            TileSetManager __RPC_FAR * This,
            /* [in] */ int mappingIndex,
            /* [retval][out] */ int __RPC_FAR *numTileReplacements);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_NumTileReplacements )( 
            TileSetManager __RPC_FAR * This,
            /* [in] */ int mappingIndex,
            /* [in] */ int numTileReplacements);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_CycleDelay )( 
            TileSetManager __RPC_FAR * This,
            /* [in] */ int mappingIndex,
            /* [retval][out] */ int __RPC_FAR *cycleDelay);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_CycleDelay )( 
            TileSetManager __RPC_FAR * This,
            /* [in] */ int mappingIndex,
            /* [in] */ int cycleDelay);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_NumTerrains )( 
            TileSetManager __RPC_FAR * This,
            /* [retval][out] */ int __RPC_FAR *numTerrains);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetNumTerrains )( 
            TileSetManager __RPC_FAR * This,
            /* [in] */ int numTerrains);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_TerrainStartTile )( 
            TileSetManager __RPC_FAR * This,
            /* [in] */ int terrainIndex,
            /* [retval][out] */ int __RPC_FAR *startMapping);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_TerrainStartTile )( 
            TileSetManager __RPC_FAR * This,
            /* [in] */ int terrainIndex,
            /* [in] */ int startMapping);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_TerrainEndTile )( 
            TileSetManager __RPC_FAR * This,
            /* [in] */ int terrainIndex,
            /* [retval][out] */ int __RPC_FAR *endMapping);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_TerrainEndTile )( 
            TileSetManager __RPC_FAR * This,
            /* [in] */ int terrainIndex,
            /* [in] */ int endMapping);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_TerrainDozed )( 
            TileSetManager __RPC_FAR * This,
            /* [in] */ int terrainIndex,
            /* [retval][out] */ int __RPC_FAR *dataMapping);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_TerrainDozed )( 
            TileSetManager __RPC_FAR * This,
            /* [in] */ int terrainIndex,
            /* [in] */ int dataMapping);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_TerrainRubble )( 
            TileSetManager __RPC_FAR * This,
            /* [in] */ int terrainIndex,
            /* [retval][out] */ int __RPC_FAR *dataMapping);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_TerrainRubble )( 
            TileSetManager __RPC_FAR * This,
            /* [in] */ int terrainIndex,
            /* [in] */ int dataMapping);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_TerrainTubeUnk )( 
            TileSetManager __RPC_FAR * This,
            /* [in] */ int terrainIndex,
            /* [in] */ enum TerrainTubeDirection direction,
            /* [retval][out] */ int __RPC_FAR *dataMapping);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_TerrainTubeUnk )( 
            TileSetManager __RPC_FAR * This,
            /* [in] */ int terrainIndex,
            /* [in] */ enum TerrainTubeDirection direction,
            /* [in] */ int dataMapping);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_TerrainLavaWall )( 
            TileSetManager __RPC_FAR * This,
            /* [in] */ int terrainIndex,
            /* [in] */ enum TerrainTubeDirection direction,
            /* [retval][out] */ int __RPC_FAR *dataMapping);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_TerrainLavaWall )( 
            TileSetManager __RPC_FAR * This,
            /* [in] */ int terrainIndex,
            /* [in] */ enum TerrainTubeDirection direction,
            /* [in] */ int dataMapping);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_TerrainMicrobeWall )( 
            TileSetManager __RPC_FAR * This,
            /* [in] */ int terrainIndex,
            /* [in] */ enum TerrainTubeDirection direction,
            /* [retval][out] */ int __RPC_FAR *dataMapping);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_TerrainMicrobeWall )( 
            TileSetManager __RPC_FAR * This,
            /* [in] */ int terrainIndex,
            /* [in] */ enum TerrainTubeDirection direction,
            /* [in] */ int dataMapping);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_TerrainNormalWall )( 
            TileSetManager __RPC_FAR * This,
            /* [in] */ int terrainIndex,
            /* [in] */ enum TerrainTubeDirection direction,
            /* [retval][out] */ int __RPC_FAR *dataMapping);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_TerrainNormalWall )( 
            TileSetManager __RPC_FAR * This,
            /* [in] */ int terrainIndex,
            /* [in] */ enum TerrainTubeDirection direction,
            /* [in] */ int dataMapping);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_TerrainDamagedWall )( 
            TileSetManager __RPC_FAR * This,
            /* [in] */ int terrainIndex,
            /* [in] */ enum TerrainTubeDirection direction,
            /* [retval][out] */ int __RPC_FAR *dataMapping);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_TerrainDamagedWall )( 
            TileSetManager __RPC_FAR * This,
            /* [in] */ int terrainIndex,
            /* [in] */ enum TerrainTubeDirection direction,
            /* [in] */ int dataMapping);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_TerrainRuinedWall )( 
            TileSetManager __RPC_FAR * This,
            /* [in] */ int terrainIndex,
            /* [in] */ enum TerrainTubeDirection direction,
            /* [retval][out] */ int __RPC_FAR *dataMapping);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_TerrainRuinedWall )( 
            TileSetManager __RPC_FAR * This,
            /* [in] */ int terrainIndex,
            /* [in] */ enum TerrainTubeDirection direction,
            /* [in] */ int dataMapping);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_TerrainLava )( 
            TileSetManager __RPC_FAR * This,
            /* [in] */ int terrainIndex,
            /* [retval][out] */ int __RPC_FAR *dataMapping);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_TerrainLava )( 
            TileSetManager __RPC_FAR * This,
            /* [in] */ int terrainIndex,
            /* [in] */ int dataMapping);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_TerrainFlat1 )( 
            TileSetManager __RPC_FAR * This,
            /* [in] */ int terrainIndex,
            /* [retval][out] */ int __RPC_FAR *dataMapping);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_TerrainFlat1 )( 
            TileSetManager __RPC_FAR * This,
            /* [in] */ int terrainIndex,
            /* [in] */ int dataMapping);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_TerrainFlat2 )( 
            TileSetManager __RPC_FAR * This,
            /* [in] */ int terrainIndex,
            /* [retval][out] */ int __RPC_FAR *dataMapping);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_TerrainFlat2 )( 
            TileSetManager __RPC_FAR * This,
            /* [in] */ int terrainIndex,
            /* [in] */ int dataMapping);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_TerrainFlat3 )( 
            TileSetManager __RPC_FAR * This,
            /* [in] */ int terrainIndex,
            /* [retval][out] */ int __RPC_FAR *dataMapping);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_TerrainFlat3 )( 
            TileSetManager __RPC_FAR * This,
            /* [in] */ int terrainIndex,
            /* [in] */ int dataMapping);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_TerrainTube )( 
            TileSetManager __RPC_FAR * This,
            /* [in] */ int terrainIndex,
            /* [in] */ enum TerrainTubeDirection direction,
            /* [retval][out] */ int __RPC_FAR *dataMapping);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_TerrainTube )( 
            TileSetManager __RPC_FAR * This,
            /* [in] */ int terrainIndex,
            /* [in] */ enum TerrainTubeDirection direction,
            /* [in] */ int dataMapping);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_TerrainScorched )( 
            TileSetManager __RPC_FAR * This,
            /* [in] */ int terrainIndex,
            /* [retval][out] */ int __RPC_FAR *dataMapping);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_TerrainScorched )( 
            TileSetManager __RPC_FAR * This,
            /* [in] */ int terrainIndex,
            /* [in] */ int dataMapping);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_TerrainUnknown )( 
            TileSetManager __RPC_FAR * This,
            /* [in] */ int terrainIndex,
            /* [in] */ int unkIndex,
            /* [retval][out] */ int __RPC_FAR *dataMapping);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_TerrainUnknown )( 
            TileSetManager __RPC_FAR * This,
            /* [in] */ int terrainIndex,
            /* [in] */ int unkIndex,
            /* [in] */ int dataMapping);
        
        END_INTERFACE
    } TileSetManagerVtbl;

    interface TileSetManager
    {
        CONST_VTBL struct TileSetManagerVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define TileSetManager_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define TileSetManager_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define TileSetManager_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define TileSetManager_get_NumTileSets(This,numTileSets)	\
    (This)->lpVtbl -> get_NumTileSets(This,numTileSets)

#define TileSetManager_get_TileSetName(This,index,tileSetName)	\
    (This)->lpVtbl -> get_TileSetName(This,index,tileSetName)

#define TileSetManager_get_TileSet(This,index,tileSet)	\
    (This)->lpVtbl -> get_TileSet(This,index,tileSet)

#define TileSetManager_AddTileSet(This,tileSetName,index)	\
    (This)->lpVtbl -> AddTileSet(This,tileSetName,index)

#define TileSetManager_RemoveTileSet(This,tileSetName,index)	\
    (This)->lpVtbl -> RemoveTileSet(This,tileSetName,index)

#define TileSetManager_ReplaceTileSet(This,index,tileSetName)	\
    (This)->lpVtbl -> ReplaceTileSet(This,index,tileSetName)

#define TileSetManager_MapInTiles(This,tileSetIndex,startTile,numTiles,mappingIndex)	\
    (This)->lpVtbl -> MapInTiles(This,tileSetIndex,startTile,numTiles,mappingIndex)

#define TileSetManager_GetMappingIndex(This,tileSetIndex,tileIndex,numTileReplacements,cycleDelay,mappingIndex)	\
    (This)->lpVtbl -> GetMappingIndex(This,tileSetIndex,tileIndex,numTileReplacements,cycleDelay,mappingIndex)

#define TileSetManager_get_NumMappings(This,numMappings)	\
    (This)->lpVtbl -> get_NumMappings(This,numMappings)

#define TileSetManager_get_TileSetIndex(This,mappingIndex,tileSetIndex)	\
    (This)->lpVtbl -> get_TileSetIndex(This,mappingIndex,tileSetIndex)

#define TileSetManager_put_TileSetIndex(This,mappingIndex,tileSetIndex)	\
    (This)->lpVtbl -> put_TileSetIndex(This,mappingIndex,tileSetIndex)

#define TileSetManager_get_TileSetTileIndex(This,mappingIndex,tileSetTileIndex)	\
    (This)->lpVtbl -> get_TileSetTileIndex(This,mappingIndex,tileSetTileIndex)

#define TileSetManager_put_TileSetTileIndex(This,mappingIndex,tileSetTileIndex)	\
    (This)->lpVtbl -> put_TileSetTileIndex(This,mappingIndex,tileSetTileIndex)

#define TileSetManager_get_NumTileReplacements(This,mappingIndex,numTileReplacements)	\
    (This)->lpVtbl -> get_NumTileReplacements(This,mappingIndex,numTileReplacements)

#define TileSetManager_put_NumTileReplacements(This,mappingIndex,numTileReplacements)	\
    (This)->lpVtbl -> put_NumTileReplacements(This,mappingIndex,numTileReplacements)

#define TileSetManager_get_CycleDelay(This,mappingIndex,cycleDelay)	\
    (This)->lpVtbl -> get_CycleDelay(This,mappingIndex,cycleDelay)

#define TileSetManager_put_CycleDelay(This,mappingIndex,cycleDelay)	\
    (This)->lpVtbl -> put_CycleDelay(This,mappingIndex,cycleDelay)

#define TileSetManager_get_NumTerrains(This,numTerrains)	\
    (This)->lpVtbl -> get_NumTerrains(This,numTerrains)

#define TileSetManager_SetNumTerrains(This,numTerrains)	\
    (This)->lpVtbl -> SetNumTerrains(This,numTerrains)

#define TileSetManager_get_TerrainStartTile(This,terrainIndex,startMapping)	\
    (This)->lpVtbl -> get_TerrainStartTile(This,terrainIndex,startMapping)

#define TileSetManager_put_TerrainStartTile(This,terrainIndex,startMapping)	\
    (This)->lpVtbl -> put_TerrainStartTile(This,terrainIndex,startMapping)

#define TileSetManager_get_TerrainEndTile(This,terrainIndex,endMapping)	\
    (This)->lpVtbl -> get_TerrainEndTile(This,terrainIndex,endMapping)

#define TileSetManager_put_TerrainEndTile(This,terrainIndex,endMapping)	\
    (This)->lpVtbl -> put_TerrainEndTile(This,terrainIndex,endMapping)

#define TileSetManager_get_TerrainDozed(This,terrainIndex,dataMapping)	\
    (This)->lpVtbl -> get_TerrainDozed(This,terrainIndex,dataMapping)

#define TileSetManager_put_TerrainDozed(This,terrainIndex,dataMapping)	\
    (This)->lpVtbl -> put_TerrainDozed(This,terrainIndex,dataMapping)

#define TileSetManager_get_TerrainRubble(This,terrainIndex,dataMapping)	\
    (This)->lpVtbl -> get_TerrainRubble(This,terrainIndex,dataMapping)

#define TileSetManager_put_TerrainRubble(This,terrainIndex,dataMapping)	\
    (This)->lpVtbl -> put_TerrainRubble(This,terrainIndex,dataMapping)

#define TileSetManager_get_TerrainTubeUnk(This,terrainIndex,direction,dataMapping)	\
    (This)->lpVtbl -> get_TerrainTubeUnk(This,terrainIndex,direction,dataMapping)

#define TileSetManager_put_TerrainTubeUnk(This,terrainIndex,direction,dataMapping)	\
    (This)->lpVtbl -> put_TerrainTubeUnk(This,terrainIndex,direction,dataMapping)

#define TileSetManager_get_TerrainLavaWall(This,terrainIndex,direction,dataMapping)	\
    (This)->lpVtbl -> get_TerrainLavaWall(This,terrainIndex,direction,dataMapping)

#define TileSetManager_put_TerrainLavaWall(This,terrainIndex,direction,dataMapping)	\
    (This)->lpVtbl -> put_TerrainLavaWall(This,terrainIndex,direction,dataMapping)

#define TileSetManager_get_TerrainMicrobeWall(This,terrainIndex,direction,dataMapping)	\
    (This)->lpVtbl -> get_TerrainMicrobeWall(This,terrainIndex,direction,dataMapping)

#define TileSetManager_put_TerrainMicrobeWall(This,terrainIndex,direction,dataMapping)	\
    (This)->lpVtbl -> put_TerrainMicrobeWall(This,terrainIndex,direction,dataMapping)

#define TileSetManager_get_TerrainNormalWall(This,terrainIndex,direction,dataMapping)	\
    (This)->lpVtbl -> get_TerrainNormalWall(This,terrainIndex,direction,dataMapping)

#define TileSetManager_put_TerrainNormalWall(This,terrainIndex,direction,dataMapping)	\
    (This)->lpVtbl -> put_TerrainNormalWall(This,terrainIndex,direction,dataMapping)

#define TileSetManager_get_TerrainDamagedWall(This,terrainIndex,direction,dataMapping)	\
    (This)->lpVtbl -> get_TerrainDamagedWall(This,terrainIndex,direction,dataMapping)

#define TileSetManager_put_TerrainDamagedWall(This,terrainIndex,direction,dataMapping)	\
    (This)->lpVtbl -> put_TerrainDamagedWall(This,terrainIndex,direction,dataMapping)

#define TileSetManager_get_TerrainRuinedWall(This,terrainIndex,direction,dataMapping)	\
    (This)->lpVtbl -> get_TerrainRuinedWall(This,terrainIndex,direction,dataMapping)

#define TileSetManager_put_TerrainRuinedWall(This,terrainIndex,direction,dataMapping)	\
    (This)->lpVtbl -> put_TerrainRuinedWall(This,terrainIndex,direction,dataMapping)

#define TileSetManager_get_TerrainLava(This,terrainIndex,dataMapping)	\
    (This)->lpVtbl -> get_TerrainLava(This,terrainIndex,dataMapping)

#define TileSetManager_put_TerrainLava(This,terrainIndex,dataMapping)	\
    (This)->lpVtbl -> put_TerrainLava(This,terrainIndex,dataMapping)

#define TileSetManager_get_TerrainFlat1(This,terrainIndex,dataMapping)	\
    (This)->lpVtbl -> get_TerrainFlat1(This,terrainIndex,dataMapping)

#define TileSetManager_put_TerrainFlat1(This,terrainIndex,dataMapping)	\
    (This)->lpVtbl -> put_TerrainFlat1(This,terrainIndex,dataMapping)

#define TileSetManager_get_TerrainFlat2(This,terrainIndex,dataMapping)	\
    (This)->lpVtbl -> get_TerrainFlat2(This,terrainIndex,dataMapping)

#define TileSetManager_put_TerrainFlat2(This,terrainIndex,dataMapping)	\
    (This)->lpVtbl -> put_TerrainFlat2(This,terrainIndex,dataMapping)

#define TileSetManager_get_TerrainFlat3(This,terrainIndex,dataMapping)	\
    (This)->lpVtbl -> get_TerrainFlat3(This,terrainIndex,dataMapping)

#define TileSetManager_put_TerrainFlat3(This,terrainIndex,dataMapping)	\
    (This)->lpVtbl -> put_TerrainFlat3(This,terrainIndex,dataMapping)

#define TileSetManager_get_TerrainTube(This,terrainIndex,direction,dataMapping)	\
    (This)->lpVtbl -> get_TerrainTube(This,terrainIndex,direction,dataMapping)

#define TileSetManager_put_TerrainTube(This,terrainIndex,direction,dataMapping)	\
    (This)->lpVtbl -> put_TerrainTube(This,terrainIndex,direction,dataMapping)

#define TileSetManager_get_TerrainScorched(This,terrainIndex,dataMapping)	\
    (This)->lpVtbl -> get_TerrainScorched(This,terrainIndex,dataMapping)

#define TileSetManager_put_TerrainScorched(This,terrainIndex,dataMapping)	\
    (This)->lpVtbl -> put_TerrainScorched(This,terrainIndex,dataMapping)

#define TileSetManager_get_TerrainUnknown(This,terrainIndex,unkIndex,dataMapping)	\
    (This)->lpVtbl -> get_TerrainUnknown(This,terrainIndex,unkIndex,dataMapping)

#define TileSetManager_put_TerrainUnknown(This,terrainIndex,unkIndex,dataMapping)	\
    (This)->lpVtbl -> put_TerrainUnknown(This,terrainIndex,unkIndex,dataMapping)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE TileSetManager_get_NumTileSets_Proxy( 
    TileSetManager __RPC_FAR * This,
    /* [retval][out] */ int __RPC_FAR *numTileSets);


void __RPC_STUB TileSetManager_get_NumTileSets_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE TileSetManager_get_TileSetName_Proxy( 
    TileSetManager __RPC_FAR * This,
    /* [in] */ int index,
    /* [retval][out] */ BSTR __RPC_FAR *tileSetName);


void __RPC_STUB TileSetManager_get_TileSetName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE TileSetManager_get_TileSet_Proxy( 
    TileSetManager __RPC_FAR * This,
    /* [in] */ int index,
    /* [retval][out] */ TileSet __RPC_FAR *__RPC_FAR *tileSet);


void __RPC_STUB TileSetManager_get_TileSet_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE TileSetManager_AddTileSet_Proxy( 
    TileSetManager __RPC_FAR * This,
    /* [in] */ BSTR tileSetName,
    /* [retval][out] */ int __RPC_FAR *index);


void __RPC_STUB TileSetManager_AddTileSet_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE TileSetManager_RemoveTileSet_Proxy( 
    TileSetManager __RPC_FAR * This,
    /* [in] */ BSTR tileSetName,
    /* [retval][out] */ int __RPC_FAR *index);


void __RPC_STUB TileSetManager_RemoveTileSet_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE TileSetManager_ReplaceTileSet_Proxy( 
    TileSetManager __RPC_FAR * This,
    /* [in] */ int index,
    /* [in] */ BSTR tileSetName);


void __RPC_STUB TileSetManager_ReplaceTileSet_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE TileSetManager_MapInTiles_Proxy( 
    TileSetManager __RPC_FAR * This,
    /* [in] */ int tileSetIndex,
    /* [in] */ int startTile,
    /* [in] */ int numTiles,
    /* [retval][out] */ int __RPC_FAR *mappingIndex);


void __RPC_STUB TileSetManager_MapInTiles_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE TileSetManager_GetMappingIndex_Proxy( 
    TileSetManager __RPC_FAR * This,
    /* [in] */ int tileSetIndex,
    /* [in] */ int tileIndex,
    /* [in] */ int numTileReplacements,
    /* [in] */ int cycleDelay,
    /* [retval][out] */ int __RPC_FAR *mappingIndex);


void __RPC_STUB TileSetManager_GetMappingIndex_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE TileSetManager_get_NumMappings_Proxy( 
    TileSetManager __RPC_FAR * This,
    /* [retval][out] */ int __RPC_FAR *numMappings);


void __RPC_STUB TileSetManager_get_NumMappings_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE TileSetManager_get_TileSetIndex_Proxy( 
    TileSetManager __RPC_FAR * This,
    /* [in] */ int mappingIndex,
    /* [retval][out] */ int __RPC_FAR *tileSetIndex);


void __RPC_STUB TileSetManager_get_TileSetIndex_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE TileSetManager_put_TileSetIndex_Proxy( 
    TileSetManager __RPC_FAR * This,
    /* [in] */ int mappingIndex,
    /* [in] */ int tileSetIndex);


void __RPC_STUB TileSetManager_put_TileSetIndex_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE TileSetManager_get_TileSetTileIndex_Proxy( 
    TileSetManager __RPC_FAR * This,
    /* [in] */ int mappingIndex,
    /* [retval][out] */ int __RPC_FAR *tileSetTileIndex);


void __RPC_STUB TileSetManager_get_TileSetTileIndex_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE TileSetManager_put_TileSetTileIndex_Proxy( 
    TileSetManager __RPC_FAR * This,
    /* [in] */ int mappingIndex,
    /* [in] */ int tileSetTileIndex);


void __RPC_STUB TileSetManager_put_TileSetTileIndex_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE TileSetManager_get_NumTileReplacements_Proxy( 
    TileSetManager __RPC_FAR * This,
    /* [in] */ int mappingIndex,
    /* [retval][out] */ int __RPC_FAR *numTileReplacements);


void __RPC_STUB TileSetManager_get_NumTileReplacements_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE TileSetManager_put_NumTileReplacements_Proxy( 
    TileSetManager __RPC_FAR * This,
    /* [in] */ int mappingIndex,
    /* [in] */ int numTileReplacements);


void __RPC_STUB TileSetManager_put_NumTileReplacements_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE TileSetManager_get_CycleDelay_Proxy( 
    TileSetManager __RPC_FAR * This,
    /* [in] */ int mappingIndex,
    /* [retval][out] */ int __RPC_FAR *cycleDelay);


void __RPC_STUB TileSetManager_get_CycleDelay_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE TileSetManager_put_CycleDelay_Proxy( 
    TileSetManager __RPC_FAR * This,
    /* [in] */ int mappingIndex,
    /* [in] */ int cycleDelay);


void __RPC_STUB TileSetManager_put_CycleDelay_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE TileSetManager_get_NumTerrains_Proxy( 
    TileSetManager __RPC_FAR * This,
    /* [retval][out] */ int __RPC_FAR *numTerrains);


void __RPC_STUB TileSetManager_get_NumTerrains_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE TileSetManager_SetNumTerrains_Proxy( 
    TileSetManager __RPC_FAR * This,
    /* [in] */ int numTerrains);


void __RPC_STUB TileSetManager_SetNumTerrains_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE TileSetManager_get_TerrainStartTile_Proxy( 
    TileSetManager __RPC_FAR * This,
    /* [in] */ int terrainIndex,
    /* [retval][out] */ int __RPC_FAR *startMapping);


void __RPC_STUB TileSetManager_get_TerrainStartTile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE TileSetManager_put_TerrainStartTile_Proxy( 
    TileSetManager __RPC_FAR * This,
    /* [in] */ int terrainIndex,
    /* [in] */ int startMapping);


void __RPC_STUB TileSetManager_put_TerrainStartTile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE TileSetManager_get_TerrainEndTile_Proxy( 
    TileSetManager __RPC_FAR * This,
    /* [in] */ int terrainIndex,
    /* [retval][out] */ int __RPC_FAR *endMapping);


void __RPC_STUB TileSetManager_get_TerrainEndTile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE TileSetManager_put_TerrainEndTile_Proxy( 
    TileSetManager __RPC_FAR * This,
    /* [in] */ int terrainIndex,
    /* [in] */ int endMapping);


void __RPC_STUB TileSetManager_put_TerrainEndTile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE TileSetManager_get_TerrainDozed_Proxy( 
    TileSetManager __RPC_FAR * This,
    /* [in] */ int terrainIndex,
    /* [retval][out] */ int __RPC_FAR *dataMapping);


void __RPC_STUB TileSetManager_get_TerrainDozed_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE TileSetManager_put_TerrainDozed_Proxy( 
    TileSetManager __RPC_FAR * This,
    /* [in] */ int terrainIndex,
    /* [in] */ int dataMapping);


void __RPC_STUB TileSetManager_put_TerrainDozed_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE TileSetManager_get_TerrainRubble_Proxy( 
    TileSetManager __RPC_FAR * This,
    /* [in] */ int terrainIndex,
    /* [retval][out] */ int __RPC_FAR *dataMapping);


void __RPC_STUB TileSetManager_get_TerrainRubble_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE TileSetManager_put_TerrainRubble_Proxy( 
    TileSetManager __RPC_FAR * This,
    /* [in] */ int terrainIndex,
    /* [in] */ int dataMapping);


void __RPC_STUB TileSetManager_put_TerrainRubble_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE TileSetManager_get_TerrainTubeUnk_Proxy( 
    TileSetManager __RPC_FAR * This,
    /* [in] */ int terrainIndex,
    /* [in] */ enum TerrainTubeDirection direction,
    /* [retval][out] */ int __RPC_FAR *dataMapping);


void __RPC_STUB TileSetManager_get_TerrainTubeUnk_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE TileSetManager_put_TerrainTubeUnk_Proxy( 
    TileSetManager __RPC_FAR * This,
    /* [in] */ int terrainIndex,
    /* [in] */ enum TerrainTubeDirection direction,
    /* [in] */ int dataMapping);


void __RPC_STUB TileSetManager_put_TerrainTubeUnk_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE TileSetManager_get_TerrainLavaWall_Proxy( 
    TileSetManager __RPC_FAR * This,
    /* [in] */ int terrainIndex,
    /* [in] */ enum TerrainTubeDirection direction,
    /* [retval][out] */ int __RPC_FAR *dataMapping);


void __RPC_STUB TileSetManager_get_TerrainLavaWall_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE TileSetManager_put_TerrainLavaWall_Proxy( 
    TileSetManager __RPC_FAR * This,
    /* [in] */ int terrainIndex,
    /* [in] */ enum TerrainTubeDirection direction,
    /* [in] */ int dataMapping);


void __RPC_STUB TileSetManager_put_TerrainLavaWall_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE TileSetManager_get_TerrainMicrobeWall_Proxy( 
    TileSetManager __RPC_FAR * This,
    /* [in] */ int terrainIndex,
    /* [in] */ enum TerrainTubeDirection direction,
    /* [retval][out] */ int __RPC_FAR *dataMapping);


void __RPC_STUB TileSetManager_get_TerrainMicrobeWall_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE TileSetManager_put_TerrainMicrobeWall_Proxy( 
    TileSetManager __RPC_FAR * This,
    /* [in] */ int terrainIndex,
    /* [in] */ enum TerrainTubeDirection direction,
    /* [in] */ int dataMapping);


void __RPC_STUB TileSetManager_put_TerrainMicrobeWall_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE TileSetManager_get_TerrainNormalWall_Proxy( 
    TileSetManager __RPC_FAR * This,
    /* [in] */ int terrainIndex,
    /* [in] */ enum TerrainTubeDirection direction,
    /* [retval][out] */ int __RPC_FAR *dataMapping);


void __RPC_STUB TileSetManager_get_TerrainNormalWall_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE TileSetManager_put_TerrainNormalWall_Proxy( 
    TileSetManager __RPC_FAR * This,
    /* [in] */ int terrainIndex,
    /* [in] */ enum TerrainTubeDirection direction,
    /* [in] */ int dataMapping);


void __RPC_STUB TileSetManager_put_TerrainNormalWall_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE TileSetManager_get_TerrainDamagedWall_Proxy( 
    TileSetManager __RPC_FAR * This,
    /* [in] */ int terrainIndex,
    /* [in] */ enum TerrainTubeDirection direction,
    /* [retval][out] */ int __RPC_FAR *dataMapping);


void __RPC_STUB TileSetManager_get_TerrainDamagedWall_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE TileSetManager_put_TerrainDamagedWall_Proxy( 
    TileSetManager __RPC_FAR * This,
    /* [in] */ int terrainIndex,
    /* [in] */ enum TerrainTubeDirection direction,
    /* [in] */ int dataMapping);


void __RPC_STUB TileSetManager_put_TerrainDamagedWall_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE TileSetManager_get_TerrainRuinedWall_Proxy( 
    TileSetManager __RPC_FAR * This,
    /* [in] */ int terrainIndex,
    /* [in] */ enum TerrainTubeDirection direction,
    /* [retval][out] */ int __RPC_FAR *dataMapping);


void __RPC_STUB TileSetManager_get_TerrainRuinedWall_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE TileSetManager_put_TerrainRuinedWall_Proxy( 
    TileSetManager __RPC_FAR * This,
    /* [in] */ int terrainIndex,
    /* [in] */ enum TerrainTubeDirection direction,
    /* [in] */ int dataMapping);


void __RPC_STUB TileSetManager_put_TerrainRuinedWall_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE TileSetManager_get_TerrainLava_Proxy( 
    TileSetManager __RPC_FAR * This,
    /* [in] */ int terrainIndex,
    /* [retval][out] */ int __RPC_FAR *dataMapping);


void __RPC_STUB TileSetManager_get_TerrainLava_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE TileSetManager_put_TerrainLava_Proxy( 
    TileSetManager __RPC_FAR * This,
    /* [in] */ int terrainIndex,
    /* [in] */ int dataMapping);


void __RPC_STUB TileSetManager_put_TerrainLava_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE TileSetManager_get_TerrainFlat1_Proxy( 
    TileSetManager __RPC_FAR * This,
    /* [in] */ int terrainIndex,
    /* [retval][out] */ int __RPC_FAR *dataMapping);


void __RPC_STUB TileSetManager_get_TerrainFlat1_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE TileSetManager_put_TerrainFlat1_Proxy( 
    TileSetManager __RPC_FAR * This,
    /* [in] */ int terrainIndex,
    /* [in] */ int dataMapping);


void __RPC_STUB TileSetManager_put_TerrainFlat1_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE TileSetManager_get_TerrainFlat2_Proxy( 
    TileSetManager __RPC_FAR * This,
    /* [in] */ int terrainIndex,
    /* [retval][out] */ int __RPC_FAR *dataMapping);


void __RPC_STUB TileSetManager_get_TerrainFlat2_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE TileSetManager_put_TerrainFlat2_Proxy( 
    TileSetManager __RPC_FAR * This,
    /* [in] */ int terrainIndex,
    /* [in] */ int dataMapping);


void __RPC_STUB TileSetManager_put_TerrainFlat2_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE TileSetManager_get_TerrainFlat3_Proxy( 
    TileSetManager __RPC_FAR * This,
    /* [in] */ int terrainIndex,
    /* [retval][out] */ int __RPC_FAR *dataMapping);


void __RPC_STUB TileSetManager_get_TerrainFlat3_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE TileSetManager_put_TerrainFlat3_Proxy( 
    TileSetManager __RPC_FAR * This,
    /* [in] */ int terrainIndex,
    /* [in] */ int dataMapping);


void __RPC_STUB TileSetManager_put_TerrainFlat3_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE TileSetManager_get_TerrainTube_Proxy( 
    TileSetManager __RPC_FAR * This,
    /* [in] */ int terrainIndex,
    /* [in] */ enum TerrainTubeDirection direction,
    /* [retval][out] */ int __RPC_FAR *dataMapping);


void __RPC_STUB TileSetManager_get_TerrainTube_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE TileSetManager_put_TerrainTube_Proxy( 
    TileSetManager __RPC_FAR * This,
    /* [in] */ int terrainIndex,
    /* [in] */ enum TerrainTubeDirection direction,
    /* [in] */ int dataMapping);


void __RPC_STUB TileSetManager_put_TerrainTube_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE TileSetManager_get_TerrainScorched_Proxy( 
    TileSetManager __RPC_FAR * This,
    /* [in] */ int terrainIndex,
    /* [retval][out] */ int __RPC_FAR *dataMapping);


void __RPC_STUB TileSetManager_get_TerrainScorched_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE TileSetManager_put_TerrainScorched_Proxy( 
    TileSetManager __RPC_FAR * This,
    /* [in] */ int terrainIndex,
    /* [in] */ int dataMapping);


void __RPC_STUB TileSetManager_put_TerrainScorched_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE TileSetManager_get_TerrainUnknown_Proxy( 
    TileSetManager __RPC_FAR * This,
    /* [in] */ int terrainIndex,
    /* [in] */ int unkIndex,
    /* [retval][out] */ int __RPC_FAR *dataMapping);


void __RPC_STUB TileSetManager_get_TerrainUnknown_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE TileSetManager_put_TerrainUnknown_Proxy( 
    TileSetManager __RPC_FAR * This,
    /* [in] */ int terrainIndex,
    /* [in] */ int unkIndex,
    /* [in] */ int dataMapping);


void __RPC_STUB TileSetManager_put_TerrainUnknown_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __TileSetManager_INTERFACE_DEFINED__ */


#ifndef __TileGroup_INTERFACE_DEFINED__
#define __TileGroup_INTERFACE_DEFINED__

/* interface TileGroup */
/* [helpstring][nonextensible][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_TileGroup;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("8E43C614-715F-41df-B376-CB0B55F29090")
    TileGroup : public IUnknown
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_TileWidth( 
            /* [retval][out] */ int __RPC_FAR *tileWidth) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_TileHeight( 
            /* [retval][out] */ int __RPC_FAR *tileHeight) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_TileSetManager( 
            /* [retval][out] */ TileSetManager __RPC_FAR *__RPC_FAR *tileSetManager) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_MappingIndex( 
            /* [in] */ int tileX,
            /* [in] */ int tileY,
            /* [retval][out] */ int __RPC_FAR *tileMappingIndex) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_MappingIndex( 
            /* [in] */ int tileX,
            /* [in] */ int tileY,
            /* [in] */ int tileMappingIndex) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Draw( 
            /* [in] */ int destDC,
            /* [in] */ int sourcePixelX,
            /* [in] */ int sourcePixelY,
            /* [in] */ int pixelWidth,
            /* [in] */ int pixelHeight) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct TileGroupVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            TileGroup __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            TileGroup __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            TileGroup __RPC_FAR * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_TileWidth )( 
            TileGroup __RPC_FAR * This,
            /* [retval][out] */ int __RPC_FAR *tileWidth);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_TileHeight )( 
            TileGroup __RPC_FAR * This,
            /* [retval][out] */ int __RPC_FAR *tileHeight);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_TileSetManager )( 
            TileGroup __RPC_FAR * This,
            /* [retval][out] */ TileSetManager __RPC_FAR *__RPC_FAR *tileSetManager);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_MappingIndex )( 
            TileGroup __RPC_FAR * This,
            /* [in] */ int tileX,
            /* [in] */ int tileY,
            /* [retval][out] */ int __RPC_FAR *tileMappingIndex);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_MappingIndex )( 
            TileGroup __RPC_FAR * This,
            /* [in] */ int tileX,
            /* [in] */ int tileY,
            /* [in] */ int tileMappingIndex);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Draw )( 
            TileGroup __RPC_FAR * This,
            /* [in] */ int destDC,
            /* [in] */ int sourcePixelX,
            /* [in] */ int sourcePixelY,
            /* [in] */ int pixelWidth,
            /* [in] */ int pixelHeight);
        
        END_INTERFACE
    } TileGroupVtbl;

    interface TileGroup
    {
        CONST_VTBL struct TileGroupVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define TileGroup_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define TileGroup_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define TileGroup_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define TileGroup_get_TileWidth(This,tileWidth)	\
    (This)->lpVtbl -> get_TileWidth(This,tileWidth)

#define TileGroup_get_TileHeight(This,tileHeight)	\
    (This)->lpVtbl -> get_TileHeight(This,tileHeight)

#define TileGroup_get_TileSetManager(This,tileSetManager)	\
    (This)->lpVtbl -> get_TileSetManager(This,tileSetManager)

#define TileGroup_get_MappingIndex(This,tileX,tileY,tileMappingIndex)	\
    (This)->lpVtbl -> get_MappingIndex(This,tileX,tileY,tileMappingIndex)

#define TileGroup_put_MappingIndex(This,tileX,tileY,tileMappingIndex)	\
    (This)->lpVtbl -> put_MappingIndex(This,tileX,tileY,tileMappingIndex)

#define TileGroup_Draw(This,destDC,sourcePixelX,sourcePixelY,pixelWidth,pixelHeight)	\
    (This)->lpVtbl -> Draw(This,destDC,sourcePixelX,sourcePixelY,pixelWidth,pixelHeight)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE TileGroup_get_TileWidth_Proxy( 
    TileGroup __RPC_FAR * This,
    /* [retval][out] */ int __RPC_FAR *tileWidth);


void __RPC_STUB TileGroup_get_TileWidth_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE TileGroup_get_TileHeight_Proxy( 
    TileGroup __RPC_FAR * This,
    /* [retval][out] */ int __RPC_FAR *tileHeight);


void __RPC_STUB TileGroup_get_TileHeight_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE TileGroup_get_TileSetManager_Proxy( 
    TileGroup __RPC_FAR * This,
    /* [retval][out] */ TileSetManager __RPC_FAR *__RPC_FAR *tileSetManager);


void __RPC_STUB TileGroup_get_TileSetManager_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE TileGroup_get_MappingIndex_Proxy( 
    TileGroup __RPC_FAR * This,
    /* [in] */ int tileX,
    /* [in] */ int tileY,
    /* [retval][out] */ int __RPC_FAR *tileMappingIndex);


void __RPC_STUB TileGroup_get_MappingIndex_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE TileGroup_put_MappingIndex_Proxy( 
    TileGroup __RPC_FAR * This,
    /* [in] */ int tileX,
    /* [in] */ int tileY,
    /* [in] */ int tileMappingIndex);


void __RPC_STUB TileGroup_put_MappingIndex_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE TileGroup_Draw_Proxy( 
    TileGroup __RPC_FAR * This,
    /* [in] */ int destDC,
    /* [in] */ int sourcePixelX,
    /* [in] */ int sourcePixelY,
    /* [in] */ int pixelWidth,
    /* [in] */ int pixelHeight);


void __RPC_STUB TileGroup_Draw_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __TileGroup_INTERFACE_DEFINED__ */


#ifndef __MapFile_INTERFACE_DEFINED__
#define __MapFile_INTERFACE_DEFINED__

/* interface MapFile */
/* [helpstring][nonextensible][oleautomation][uuid][object] */ 

/* [helpstring][v1_enum] */ 
enum MapLoadSaveFormat
    {	MapOnly	= 0,
	TileGroups	= 1,
	Units	= 2,
	SavedGameHeader	= 4
    };

EXTERN_C const IID IID_MapFile;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("E1C7751A-AA0C-40b7-95C4-1693C86784FC")
    MapFile : public TileGroup
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_AroundTheWorld( 
            /* [retval][out] */ int __RPC_FAR *bAroundTheWorld) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_TileData( 
            /* [in] */ int tileX,
            /* [in] */ int tileY,
            /* [retval][out] */ int __RPC_FAR *tile) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_TileData( 
            /* [in] */ int tileX,
            /* [in] */ int tileY,
            /* [in] */ int newTile) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_CellType( 
            /* [in] */ int tileX,
            /* [in] */ int tileY,
            /* [retval][out] */ int __RPC_FAR *cellType) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_CellType( 
            /* [in] */ int tileX,
            /* [in] */ int tileY,
            /* [in] */ int newCellType) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_UnitIndex( 
            /* [in] */ int tileX,
            /* [in] */ int tileY,
            /* [retval][out] */ int __RPC_FAR *unitIndex) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_UnitIndex( 
            /* [in] */ int tileX,
            /* [in] */ int tileY,
            /* [in] */ int newUnitIndex) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Lava( 
            /* [in] */ int tileX,
            /* [in] */ int tileY,
            /* [retval][out] */ int __RPC_FAR *lava) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Lava( 
            /* [in] */ int tileX,
            /* [in] */ int tileY,
            /* [in] */ int lava) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_LavaPossible( 
            /* [in] */ int tileX,
            /* [in] */ int tileY,
            /* [retval][out] */ int __RPC_FAR *lavaPossible) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_LavaPossible( 
            /* [in] */ int tileX,
            /* [in] */ int tileY,
            /* [in] */ int lavaPossible) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Expand( 
            /* [in] */ int tileX,
            /* [in] */ int tileY,
            /* [retval][out] */ int __RPC_FAR *expand) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Expand( 
            /* [in] */ int tileX,
            /* [in] */ int tileY,
            /* [in] */ int expand) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Microbe( 
            /* [in] */ int tileX,
            /* [in] */ int tileY,
            /* [retval][out] */ int __RPC_FAR *microbe) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Microbe( 
            /* [in] */ int tileX,
            /* [in] */ int tileY,
            /* [in] */ int microbe) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_WallOrBuilding( 
            /* [in] */ int tileX,
            /* [in] */ int tileY,
            /* [retval][out] */ int __RPC_FAR *wallOrBuilding) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_WallOrBuilding( 
            /* [in] */ int tileX,
            /* [in] */ int tileY,
            /* [in] */ int wallOrBuilding) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Copy( 
            /* [in] */ int tileX1,
            /* [in] */ int tileY1,
            /* [in] */ int tileX2,
            /* [in] */ int tileY2,
            /* [retval][out] */ TileGroup __RPC_FAR *__RPC_FAR *tileGroup) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Paste( 
            /* [in] */ int tileX,
            /* [in] */ int tileY,
            /* [in] */ TileGroup __RPC_FAR *tileGroup) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_NumTileGroups( 
            /* [retval][out] */ int __RPC_FAR *numTileGroups) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_TileGroup( 
            /* [in] */ int tileGroupIndex,
            /* [retval][out] */ TileGroup __RPC_FAR *__RPC_FAR *tileGroup) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_TileGroupName( 
            /* [in] */ int tileGroupIndex,
            /* [retval][out] */ BSTR __RPC_FAR *tileGroupName) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_TileGroupName( 
            /* [in] */ int tileGroupIndex,
            /* [in] */ BSTR tileGroupName) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE AddTileGroup( 
            /* [in] */ TileGroup __RPC_FAR *newTileGroup) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE RemoveTileGroup( 
            /* [in] */ int tileGroupIndex) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SaveMap( 
            /* [in] */ StreamWriter __RPC_FAR *stream,
            /* [in] */ enum MapLoadSaveFormat saveFlags,
            /* [retval][out] */ int __RPC_FAR *status) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct MapFileVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            MapFile __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            MapFile __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            MapFile __RPC_FAR * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_TileWidth )( 
            MapFile __RPC_FAR * This,
            /* [retval][out] */ int __RPC_FAR *tileWidth);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_TileHeight )( 
            MapFile __RPC_FAR * This,
            /* [retval][out] */ int __RPC_FAR *tileHeight);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_TileSetManager )( 
            MapFile __RPC_FAR * This,
            /* [retval][out] */ TileSetManager __RPC_FAR *__RPC_FAR *tileSetManager);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_MappingIndex )( 
            MapFile __RPC_FAR * This,
            /* [in] */ int tileX,
            /* [in] */ int tileY,
            /* [retval][out] */ int __RPC_FAR *tileMappingIndex);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_MappingIndex )( 
            MapFile __RPC_FAR * This,
            /* [in] */ int tileX,
            /* [in] */ int tileY,
            /* [in] */ int tileMappingIndex);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Draw )( 
            MapFile __RPC_FAR * This,
            /* [in] */ int destDC,
            /* [in] */ int sourcePixelX,
            /* [in] */ int sourcePixelY,
            /* [in] */ int pixelWidth,
            /* [in] */ int pixelHeight);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_AroundTheWorld )( 
            MapFile __RPC_FAR * This,
            /* [retval][out] */ int __RPC_FAR *bAroundTheWorld);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_TileData )( 
            MapFile __RPC_FAR * This,
            /* [in] */ int tileX,
            /* [in] */ int tileY,
            /* [retval][out] */ int __RPC_FAR *tile);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_TileData )( 
            MapFile __RPC_FAR * This,
            /* [in] */ int tileX,
            /* [in] */ int tileY,
            /* [in] */ int newTile);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_CellType )( 
            MapFile __RPC_FAR * This,
            /* [in] */ int tileX,
            /* [in] */ int tileY,
            /* [retval][out] */ int __RPC_FAR *cellType);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_CellType )( 
            MapFile __RPC_FAR * This,
            /* [in] */ int tileX,
            /* [in] */ int tileY,
            /* [in] */ int newCellType);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_UnitIndex )( 
            MapFile __RPC_FAR * This,
            /* [in] */ int tileX,
            /* [in] */ int tileY,
            /* [retval][out] */ int __RPC_FAR *unitIndex);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_UnitIndex )( 
            MapFile __RPC_FAR * This,
            /* [in] */ int tileX,
            /* [in] */ int tileY,
            /* [in] */ int newUnitIndex);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Lava )( 
            MapFile __RPC_FAR * This,
            /* [in] */ int tileX,
            /* [in] */ int tileY,
            /* [retval][out] */ int __RPC_FAR *lava);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Lava )( 
            MapFile __RPC_FAR * This,
            /* [in] */ int tileX,
            /* [in] */ int tileY,
            /* [in] */ int lava);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_LavaPossible )( 
            MapFile __RPC_FAR * This,
            /* [in] */ int tileX,
            /* [in] */ int tileY,
            /* [retval][out] */ int __RPC_FAR *lavaPossible);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_LavaPossible )( 
            MapFile __RPC_FAR * This,
            /* [in] */ int tileX,
            /* [in] */ int tileY,
            /* [in] */ int lavaPossible);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Expand )( 
            MapFile __RPC_FAR * This,
            /* [in] */ int tileX,
            /* [in] */ int tileY,
            /* [retval][out] */ int __RPC_FAR *expand);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Expand )( 
            MapFile __RPC_FAR * This,
            /* [in] */ int tileX,
            /* [in] */ int tileY,
            /* [in] */ int expand);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Microbe )( 
            MapFile __RPC_FAR * This,
            /* [in] */ int tileX,
            /* [in] */ int tileY,
            /* [retval][out] */ int __RPC_FAR *microbe);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Microbe )( 
            MapFile __RPC_FAR * This,
            /* [in] */ int tileX,
            /* [in] */ int tileY,
            /* [in] */ int microbe);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_WallOrBuilding )( 
            MapFile __RPC_FAR * This,
            /* [in] */ int tileX,
            /* [in] */ int tileY,
            /* [retval][out] */ int __RPC_FAR *wallOrBuilding);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_WallOrBuilding )( 
            MapFile __RPC_FAR * This,
            /* [in] */ int tileX,
            /* [in] */ int tileY,
            /* [in] */ int wallOrBuilding);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Copy )( 
            MapFile __RPC_FAR * This,
            /* [in] */ int tileX1,
            /* [in] */ int tileY1,
            /* [in] */ int tileX2,
            /* [in] */ int tileY2,
            /* [retval][out] */ TileGroup __RPC_FAR *__RPC_FAR *tileGroup);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Paste )( 
            MapFile __RPC_FAR * This,
            /* [in] */ int tileX,
            /* [in] */ int tileY,
            /* [in] */ TileGroup __RPC_FAR *tileGroup);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_NumTileGroups )( 
            MapFile __RPC_FAR * This,
            /* [retval][out] */ int __RPC_FAR *numTileGroups);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_TileGroup )( 
            MapFile __RPC_FAR * This,
            /* [in] */ int tileGroupIndex,
            /* [retval][out] */ TileGroup __RPC_FAR *__RPC_FAR *tileGroup);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_TileGroupName )( 
            MapFile __RPC_FAR * This,
            /* [in] */ int tileGroupIndex,
            /* [retval][out] */ BSTR __RPC_FAR *tileGroupName);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_TileGroupName )( 
            MapFile __RPC_FAR * This,
            /* [in] */ int tileGroupIndex,
            /* [in] */ BSTR tileGroupName);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AddTileGroup )( 
            MapFile __RPC_FAR * This,
            /* [in] */ TileGroup __RPC_FAR *newTileGroup);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *RemoveTileGroup )( 
            MapFile __RPC_FAR * This,
            /* [in] */ int tileGroupIndex);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SaveMap )( 
            MapFile __RPC_FAR * This,
            /* [in] */ StreamWriter __RPC_FAR *stream,
            /* [in] */ enum MapLoadSaveFormat saveFlags,
            /* [retval][out] */ int __RPC_FAR *status);
        
        END_INTERFACE
    } MapFileVtbl;

    interface MapFile
    {
        CONST_VTBL struct MapFileVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define MapFile_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define MapFile_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define MapFile_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define MapFile_get_TileWidth(This,tileWidth)	\
    (This)->lpVtbl -> get_TileWidth(This,tileWidth)

#define MapFile_get_TileHeight(This,tileHeight)	\
    (This)->lpVtbl -> get_TileHeight(This,tileHeight)

#define MapFile_get_TileSetManager(This,tileSetManager)	\
    (This)->lpVtbl -> get_TileSetManager(This,tileSetManager)

#define MapFile_get_MappingIndex(This,tileX,tileY,tileMappingIndex)	\
    (This)->lpVtbl -> get_MappingIndex(This,tileX,tileY,tileMappingIndex)

#define MapFile_put_MappingIndex(This,tileX,tileY,tileMappingIndex)	\
    (This)->lpVtbl -> put_MappingIndex(This,tileX,tileY,tileMappingIndex)

#define MapFile_Draw(This,destDC,sourcePixelX,sourcePixelY,pixelWidth,pixelHeight)	\
    (This)->lpVtbl -> Draw(This,destDC,sourcePixelX,sourcePixelY,pixelWidth,pixelHeight)


#define MapFile_get_AroundTheWorld(This,bAroundTheWorld)	\
    (This)->lpVtbl -> get_AroundTheWorld(This,bAroundTheWorld)

#define MapFile_get_TileData(This,tileX,tileY,tile)	\
    (This)->lpVtbl -> get_TileData(This,tileX,tileY,tile)

#define MapFile_put_TileData(This,tileX,tileY,newTile)	\
    (This)->lpVtbl -> put_TileData(This,tileX,tileY,newTile)

#define MapFile_get_CellType(This,tileX,tileY,cellType)	\
    (This)->lpVtbl -> get_CellType(This,tileX,tileY,cellType)

#define MapFile_put_CellType(This,tileX,tileY,newCellType)	\
    (This)->lpVtbl -> put_CellType(This,tileX,tileY,newCellType)

#define MapFile_get_UnitIndex(This,tileX,tileY,unitIndex)	\
    (This)->lpVtbl -> get_UnitIndex(This,tileX,tileY,unitIndex)

#define MapFile_put_UnitIndex(This,tileX,tileY,newUnitIndex)	\
    (This)->lpVtbl -> put_UnitIndex(This,tileX,tileY,newUnitIndex)

#define MapFile_get_Lava(This,tileX,tileY,lava)	\
    (This)->lpVtbl -> get_Lava(This,tileX,tileY,lava)

#define MapFile_put_Lava(This,tileX,tileY,lava)	\
    (This)->lpVtbl -> put_Lava(This,tileX,tileY,lava)

#define MapFile_get_LavaPossible(This,tileX,tileY,lavaPossible)	\
    (This)->lpVtbl -> get_LavaPossible(This,tileX,tileY,lavaPossible)

#define MapFile_put_LavaPossible(This,tileX,tileY,lavaPossible)	\
    (This)->lpVtbl -> put_LavaPossible(This,tileX,tileY,lavaPossible)

#define MapFile_get_Expand(This,tileX,tileY,expand)	\
    (This)->lpVtbl -> get_Expand(This,tileX,tileY,expand)

#define MapFile_put_Expand(This,tileX,tileY,expand)	\
    (This)->lpVtbl -> put_Expand(This,tileX,tileY,expand)

#define MapFile_get_Microbe(This,tileX,tileY,microbe)	\
    (This)->lpVtbl -> get_Microbe(This,tileX,tileY,microbe)

#define MapFile_put_Microbe(This,tileX,tileY,microbe)	\
    (This)->lpVtbl -> put_Microbe(This,tileX,tileY,microbe)

#define MapFile_get_WallOrBuilding(This,tileX,tileY,wallOrBuilding)	\
    (This)->lpVtbl -> get_WallOrBuilding(This,tileX,tileY,wallOrBuilding)

#define MapFile_put_WallOrBuilding(This,tileX,tileY,wallOrBuilding)	\
    (This)->lpVtbl -> put_WallOrBuilding(This,tileX,tileY,wallOrBuilding)

#define MapFile_Copy(This,tileX1,tileY1,tileX2,tileY2,tileGroup)	\
    (This)->lpVtbl -> Copy(This,tileX1,tileY1,tileX2,tileY2,tileGroup)

#define MapFile_Paste(This,tileX,tileY,tileGroup)	\
    (This)->lpVtbl -> Paste(This,tileX,tileY,tileGroup)

#define MapFile_get_NumTileGroups(This,numTileGroups)	\
    (This)->lpVtbl -> get_NumTileGroups(This,numTileGroups)

#define MapFile_get_TileGroup(This,tileGroupIndex,tileGroup)	\
    (This)->lpVtbl -> get_TileGroup(This,tileGroupIndex,tileGroup)

#define MapFile_get_TileGroupName(This,tileGroupIndex,tileGroupName)	\
    (This)->lpVtbl -> get_TileGroupName(This,tileGroupIndex,tileGroupName)

#define MapFile_put_TileGroupName(This,tileGroupIndex,tileGroupName)	\
    (This)->lpVtbl -> put_TileGroupName(This,tileGroupIndex,tileGroupName)

#define MapFile_AddTileGroup(This,newTileGroup)	\
    (This)->lpVtbl -> AddTileGroup(This,newTileGroup)

#define MapFile_RemoveTileGroup(This,tileGroupIndex)	\
    (This)->lpVtbl -> RemoveTileGroup(This,tileGroupIndex)

#define MapFile_SaveMap(This,stream,saveFlags,status)	\
    (This)->lpVtbl -> SaveMap(This,stream,saveFlags,status)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE MapFile_get_AroundTheWorld_Proxy( 
    MapFile __RPC_FAR * This,
    /* [retval][out] */ int __RPC_FAR *bAroundTheWorld);


void __RPC_STUB MapFile_get_AroundTheWorld_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE MapFile_get_TileData_Proxy( 
    MapFile __RPC_FAR * This,
    /* [in] */ int tileX,
    /* [in] */ int tileY,
    /* [retval][out] */ int __RPC_FAR *tile);


void __RPC_STUB MapFile_get_TileData_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE MapFile_put_TileData_Proxy( 
    MapFile __RPC_FAR * This,
    /* [in] */ int tileX,
    /* [in] */ int tileY,
    /* [in] */ int newTile);


void __RPC_STUB MapFile_put_TileData_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE MapFile_get_CellType_Proxy( 
    MapFile __RPC_FAR * This,
    /* [in] */ int tileX,
    /* [in] */ int tileY,
    /* [retval][out] */ int __RPC_FAR *cellType);


void __RPC_STUB MapFile_get_CellType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE MapFile_put_CellType_Proxy( 
    MapFile __RPC_FAR * This,
    /* [in] */ int tileX,
    /* [in] */ int tileY,
    /* [in] */ int newCellType);


void __RPC_STUB MapFile_put_CellType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE MapFile_get_UnitIndex_Proxy( 
    MapFile __RPC_FAR * This,
    /* [in] */ int tileX,
    /* [in] */ int tileY,
    /* [retval][out] */ int __RPC_FAR *unitIndex);


void __RPC_STUB MapFile_get_UnitIndex_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE MapFile_put_UnitIndex_Proxy( 
    MapFile __RPC_FAR * This,
    /* [in] */ int tileX,
    /* [in] */ int tileY,
    /* [in] */ int newUnitIndex);


void __RPC_STUB MapFile_put_UnitIndex_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE MapFile_get_Lava_Proxy( 
    MapFile __RPC_FAR * This,
    /* [in] */ int tileX,
    /* [in] */ int tileY,
    /* [retval][out] */ int __RPC_FAR *lava);


void __RPC_STUB MapFile_get_Lava_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE MapFile_put_Lava_Proxy( 
    MapFile __RPC_FAR * This,
    /* [in] */ int tileX,
    /* [in] */ int tileY,
    /* [in] */ int lava);


void __RPC_STUB MapFile_put_Lava_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE MapFile_get_LavaPossible_Proxy( 
    MapFile __RPC_FAR * This,
    /* [in] */ int tileX,
    /* [in] */ int tileY,
    /* [retval][out] */ int __RPC_FAR *lavaPossible);


void __RPC_STUB MapFile_get_LavaPossible_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE MapFile_put_LavaPossible_Proxy( 
    MapFile __RPC_FAR * This,
    /* [in] */ int tileX,
    /* [in] */ int tileY,
    /* [in] */ int lavaPossible);


void __RPC_STUB MapFile_put_LavaPossible_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE MapFile_get_Expand_Proxy( 
    MapFile __RPC_FAR * This,
    /* [in] */ int tileX,
    /* [in] */ int tileY,
    /* [retval][out] */ int __RPC_FAR *expand);


void __RPC_STUB MapFile_get_Expand_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE MapFile_put_Expand_Proxy( 
    MapFile __RPC_FAR * This,
    /* [in] */ int tileX,
    /* [in] */ int tileY,
    /* [in] */ int expand);


void __RPC_STUB MapFile_put_Expand_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE MapFile_get_Microbe_Proxy( 
    MapFile __RPC_FAR * This,
    /* [in] */ int tileX,
    /* [in] */ int tileY,
    /* [retval][out] */ int __RPC_FAR *microbe);


void __RPC_STUB MapFile_get_Microbe_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE MapFile_put_Microbe_Proxy( 
    MapFile __RPC_FAR * This,
    /* [in] */ int tileX,
    /* [in] */ int tileY,
    /* [in] */ int microbe);


void __RPC_STUB MapFile_put_Microbe_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE MapFile_get_WallOrBuilding_Proxy( 
    MapFile __RPC_FAR * This,
    /* [in] */ int tileX,
    /* [in] */ int tileY,
    /* [retval][out] */ int __RPC_FAR *wallOrBuilding);


void __RPC_STUB MapFile_get_WallOrBuilding_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE MapFile_put_WallOrBuilding_Proxy( 
    MapFile __RPC_FAR * This,
    /* [in] */ int tileX,
    /* [in] */ int tileY,
    /* [in] */ int wallOrBuilding);


void __RPC_STUB MapFile_put_WallOrBuilding_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE MapFile_Copy_Proxy( 
    MapFile __RPC_FAR * This,
    /* [in] */ int tileX1,
    /* [in] */ int tileY1,
    /* [in] */ int tileX2,
    /* [in] */ int tileY2,
    /* [retval][out] */ TileGroup __RPC_FAR *__RPC_FAR *tileGroup);


void __RPC_STUB MapFile_Copy_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE MapFile_Paste_Proxy( 
    MapFile __RPC_FAR * This,
    /* [in] */ int tileX,
    /* [in] */ int tileY,
    /* [in] */ TileGroup __RPC_FAR *tileGroup);


void __RPC_STUB MapFile_Paste_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE MapFile_get_NumTileGroups_Proxy( 
    MapFile __RPC_FAR * This,
    /* [retval][out] */ int __RPC_FAR *numTileGroups);


void __RPC_STUB MapFile_get_NumTileGroups_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE MapFile_get_TileGroup_Proxy( 
    MapFile __RPC_FAR * This,
    /* [in] */ int tileGroupIndex,
    /* [retval][out] */ TileGroup __RPC_FAR *__RPC_FAR *tileGroup);


void __RPC_STUB MapFile_get_TileGroup_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE MapFile_get_TileGroupName_Proxy( 
    MapFile __RPC_FAR * This,
    /* [in] */ int tileGroupIndex,
    /* [retval][out] */ BSTR __RPC_FAR *tileGroupName);


void __RPC_STUB MapFile_get_TileGroupName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE MapFile_put_TileGroupName_Proxy( 
    MapFile __RPC_FAR * This,
    /* [in] */ int tileGroupIndex,
    /* [in] */ BSTR tileGroupName);


void __RPC_STUB MapFile_put_TileGroupName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE MapFile_AddTileGroup_Proxy( 
    MapFile __RPC_FAR * This,
    /* [in] */ TileGroup __RPC_FAR *newTileGroup);


void __RPC_STUB MapFile_AddTileGroup_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE MapFile_RemoveTileGroup_Proxy( 
    MapFile __RPC_FAR * This,
    /* [in] */ int tileGroupIndex);


void __RPC_STUB MapFile_RemoveTileGroup_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE MapFile_SaveMap_Proxy( 
    MapFile __RPC_FAR * This,
    /* [in] */ StreamWriter __RPC_FAR *stream,
    /* [in] */ enum MapLoadSaveFormat saveFlags,
    /* [retval][out] */ int __RPC_FAR *status);


void __RPC_STUB MapFile_SaveMap_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __MapFile_INTERFACE_DEFINED__ */


#ifndef __IResourceManager_INTERFACE_DEFINED__
#define __IResourceManager_INTERFACE_DEFINED__

/* interface IResourceManager */
/* [helpstring][nonextensible][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IResourceManager;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("2A73E1A3-5FAA-4ac8-AC58-D28C77E780F0")
    IResourceManager : public IUnknown
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_RootPath( 
            /* [retval][out] */ BSTR __RPC_FAR *path) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_RootPath( 
            /* [in] */ BSTR path) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE OpenStreamRead( 
            /* [in] */ BSTR fileName,
            /* [retval][out] */ StreamReader __RPC_FAR *__RPC_FAR *stream) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE OpenStreamWrite( 
            /* [in] */ BSTR fileName,
            /* [retval][out] */ StreamWriter __RPC_FAR *__RPC_FAR *stream) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE LoadMapFile( 
            /* [in] */ BSTR fileName,
            /* [in] */ enum MapLoadSaveFormat loadFlags,
            /* [retval][out] */ MapFile __RPC_FAR *__RPC_FAR *mapFile) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE LoadMap( 
            /* [in] */ StreamReader __RPC_FAR *inStream,
            /* [in] */ enum MapLoadSaveFormat loadFlags,
            /* [retval][out] */ MapFile __RPC_FAR *__RPC_FAR *mapFile) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE CreateNewMap( 
            /* [in] */ int width,
            /* [in] */ int height,
            /* [retval][out] */ MapFile __RPC_FAR *__RPC_FAR *newMap) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE LoadTileSetFile( 
            /* [in] */ BSTR fileName,
            /* [retval][out] */ TileSet __RPC_FAR *__RPC_FAR *tileSet) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE LoadTileSet( 
            /* [in] */ StreamReader __RPC_FAR *inStream,
            /* [retval][out] */ TileSet __RPC_FAR *__RPC_FAR *tileSet) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE CreateTileSet( 
            /* [in] */ int numTiles,
            /* [in] */ int bitDepth,
            /* [in] */ int width,
            /* [retval][out] */ TileSet __RPC_FAR *__RPC_FAR *newTileSet) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE LoadVolFile( 
            /* [in] */ BSTR fileName,
            /* [in] */ int bAttachToStream,
            /* [retval][out] */ ArchiveReader __RPC_FAR *__RPC_FAR *volReader) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE LoadVol( 
            /* [in] */ SeekableStreamReader __RPC_FAR *inStream,
            /* [in] */ int bAttachToStream,
            /* [retval][out] */ ArchiveReader __RPC_FAR *__RPC_FAR *volReader) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE CreateVolFile( 
            /* [retval][out] */ ArchiveWriter __RPC_FAR *__RPC_FAR *volWriter) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE LoadClmFile( 
            /* [in] */ BSTR fileName,
            /* [in] */ int bAttachToStream,
            /* [retval][out] */ ArchiveReader __RPC_FAR *__RPC_FAR *clmReader) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE LoadClm( 
            /* [in] */ SeekableStreamReader __RPC_FAR *inStream,
            /* [in] */ int bAttachToStream,
            /* [retval][out] */ ArchiveReader __RPC_FAR *__RPC_FAR *clmReader) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE CreateClmFile( 
            /* [retval][out] */ ArchiveWriter __RPC_FAR *__RPC_FAR *clmWriter) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE AddArchiveToSearch( 
            /* [in] */ ArchiveReader __RPC_FAR *archiveReader) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ClearSearchPath( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IResourceManagerVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IResourceManager __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IResourceManager __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IResourceManager __RPC_FAR * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_RootPath )( 
            IResourceManager __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *path);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_RootPath )( 
            IResourceManager __RPC_FAR * This,
            /* [in] */ BSTR path);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *OpenStreamRead )( 
            IResourceManager __RPC_FAR * This,
            /* [in] */ BSTR fileName,
            /* [retval][out] */ StreamReader __RPC_FAR *__RPC_FAR *stream);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *OpenStreamWrite )( 
            IResourceManager __RPC_FAR * This,
            /* [in] */ BSTR fileName,
            /* [retval][out] */ StreamWriter __RPC_FAR *__RPC_FAR *stream);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *LoadMapFile )( 
            IResourceManager __RPC_FAR * This,
            /* [in] */ BSTR fileName,
            /* [in] */ enum MapLoadSaveFormat loadFlags,
            /* [retval][out] */ MapFile __RPC_FAR *__RPC_FAR *mapFile);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *LoadMap )( 
            IResourceManager __RPC_FAR * This,
            /* [in] */ StreamReader __RPC_FAR *inStream,
            /* [in] */ enum MapLoadSaveFormat loadFlags,
            /* [retval][out] */ MapFile __RPC_FAR *__RPC_FAR *mapFile);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CreateNewMap )( 
            IResourceManager __RPC_FAR * This,
            /* [in] */ int width,
            /* [in] */ int height,
            /* [retval][out] */ MapFile __RPC_FAR *__RPC_FAR *newMap);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *LoadTileSetFile )( 
            IResourceManager __RPC_FAR * This,
            /* [in] */ BSTR fileName,
            /* [retval][out] */ TileSet __RPC_FAR *__RPC_FAR *tileSet);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *LoadTileSet )( 
            IResourceManager __RPC_FAR * This,
            /* [in] */ StreamReader __RPC_FAR *inStream,
            /* [retval][out] */ TileSet __RPC_FAR *__RPC_FAR *tileSet);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CreateTileSet )( 
            IResourceManager __RPC_FAR * This,
            /* [in] */ int numTiles,
            /* [in] */ int bitDepth,
            /* [in] */ int width,
            /* [retval][out] */ TileSet __RPC_FAR *__RPC_FAR *newTileSet);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *LoadVolFile )( 
            IResourceManager __RPC_FAR * This,
            /* [in] */ BSTR fileName,
            /* [in] */ int bAttachToStream,
            /* [retval][out] */ ArchiveReader __RPC_FAR *__RPC_FAR *volReader);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *LoadVol )( 
            IResourceManager __RPC_FAR * This,
            /* [in] */ SeekableStreamReader __RPC_FAR *inStream,
            /* [in] */ int bAttachToStream,
            /* [retval][out] */ ArchiveReader __RPC_FAR *__RPC_FAR *volReader);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CreateVolFile )( 
            IResourceManager __RPC_FAR * This,
            /* [retval][out] */ ArchiveWriter __RPC_FAR *__RPC_FAR *volWriter);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *LoadClmFile )( 
            IResourceManager __RPC_FAR * This,
            /* [in] */ BSTR fileName,
            /* [in] */ int bAttachToStream,
            /* [retval][out] */ ArchiveReader __RPC_FAR *__RPC_FAR *clmReader);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *LoadClm )( 
            IResourceManager __RPC_FAR * This,
            /* [in] */ SeekableStreamReader __RPC_FAR *inStream,
            /* [in] */ int bAttachToStream,
            /* [retval][out] */ ArchiveReader __RPC_FAR *__RPC_FAR *clmReader);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CreateClmFile )( 
            IResourceManager __RPC_FAR * This,
            /* [retval][out] */ ArchiveWriter __RPC_FAR *__RPC_FAR *clmWriter);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AddArchiveToSearch )( 
            IResourceManager __RPC_FAR * This,
            /* [in] */ ArchiveReader __RPC_FAR *archiveReader);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ClearSearchPath )( 
            IResourceManager __RPC_FAR * This);
        
        END_INTERFACE
    } IResourceManagerVtbl;

    interface IResourceManager
    {
        CONST_VTBL struct IResourceManagerVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IResourceManager_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IResourceManager_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IResourceManager_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IResourceManager_get_RootPath(This,path)	\
    (This)->lpVtbl -> get_RootPath(This,path)

#define IResourceManager_put_RootPath(This,path)	\
    (This)->lpVtbl -> put_RootPath(This,path)

#define IResourceManager_OpenStreamRead(This,fileName,stream)	\
    (This)->lpVtbl -> OpenStreamRead(This,fileName,stream)

#define IResourceManager_OpenStreamWrite(This,fileName,stream)	\
    (This)->lpVtbl -> OpenStreamWrite(This,fileName,stream)

#define IResourceManager_LoadMapFile(This,fileName,loadFlags,mapFile)	\
    (This)->lpVtbl -> LoadMapFile(This,fileName,loadFlags,mapFile)

#define IResourceManager_LoadMap(This,inStream,loadFlags,mapFile)	\
    (This)->lpVtbl -> LoadMap(This,inStream,loadFlags,mapFile)

#define IResourceManager_CreateNewMap(This,width,height,newMap)	\
    (This)->lpVtbl -> CreateNewMap(This,width,height,newMap)

#define IResourceManager_LoadTileSetFile(This,fileName,tileSet)	\
    (This)->lpVtbl -> LoadTileSetFile(This,fileName,tileSet)

#define IResourceManager_LoadTileSet(This,inStream,tileSet)	\
    (This)->lpVtbl -> LoadTileSet(This,inStream,tileSet)

#define IResourceManager_CreateTileSet(This,numTiles,bitDepth,width,newTileSet)	\
    (This)->lpVtbl -> CreateTileSet(This,numTiles,bitDepth,width,newTileSet)

#define IResourceManager_LoadVolFile(This,fileName,bAttachToStream,volReader)	\
    (This)->lpVtbl -> LoadVolFile(This,fileName,bAttachToStream,volReader)

#define IResourceManager_LoadVol(This,inStream,bAttachToStream,volReader)	\
    (This)->lpVtbl -> LoadVol(This,inStream,bAttachToStream,volReader)

#define IResourceManager_CreateVolFile(This,volWriter)	\
    (This)->lpVtbl -> CreateVolFile(This,volWriter)

#define IResourceManager_LoadClmFile(This,fileName,bAttachToStream,clmReader)	\
    (This)->lpVtbl -> LoadClmFile(This,fileName,bAttachToStream,clmReader)

#define IResourceManager_LoadClm(This,inStream,bAttachToStream,clmReader)	\
    (This)->lpVtbl -> LoadClm(This,inStream,bAttachToStream,clmReader)

#define IResourceManager_CreateClmFile(This,clmWriter)	\
    (This)->lpVtbl -> CreateClmFile(This,clmWriter)

#define IResourceManager_AddArchiveToSearch(This,archiveReader)	\
    (This)->lpVtbl -> AddArchiveToSearch(This,archiveReader)

#define IResourceManager_ClearSearchPath(This)	\
    (This)->lpVtbl -> ClearSearchPath(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IResourceManager_get_RootPath_Proxy( 
    IResourceManager __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *path);


void __RPC_STUB IResourceManager_get_RootPath_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IResourceManager_put_RootPath_Proxy( 
    IResourceManager __RPC_FAR * This,
    /* [in] */ BSTR path);


void __RPC_STUB IResourceManager_put_RootPath_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IResourceManager_OpenStreamRead_Proxy( 
    IResourceManager __RPC_FAR * This,
    /* [in] */ BSTR fileName,
    /* [retval][out] */ StreamReader __RPC_FAR *__RPC_FAR *stream);


void __RPC_STUB IResourceManager_OpenStreamRead_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IResourceManager_OpenStreamWrite_Proxy( 
    IResourceManager __RPC_FAR * This,
    /* [in] */ BSTR fileName,
    /* [retval][out] */ StreamWriter __RPC_FAR *__RPC_FAR *stream);


void __RPC_STUB IResourceManager_OpenStreamWrite_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IResourceManager_LoadMapFile_Proxy( 
    IResourceManager __RPC_FAR * This,
    /* [in] */ BSTR fileName,
    /* [in] */ enum MapLoadSaveFormat loadFlags,
    /* [retval][out] */ MapFile __RPC_FAR *__RPC_FAR *mapFile);


void __RPC_STUB IResourceManager_LoadMapFile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IResourceManager_LoadMap_Proxy( 
    IResourceManager __RPC_FAR * This,
    /* [in] */ StreamReader __RPC_FAR *inStream,
    /* [in] */ enum MapLoadSaveFormat loadFlags,
    /* [retval][out] */ MapFile __RPC_FAR *__RPC_FAR *mapFile);


void __RPC_STUB IResourceManager_LoadMap_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IResourceManager_CreateNewMap_Proxy( 
    IResourceManager __RPC_FAR * This,
    /* [in] */ int width,
    /* [in] */ int height,
    /* [retval][out] */ MapFile __RPC_FAR *__RPC_FAR *newMap);


void __RPC_STUB IResourceManager_CreateNewMap_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IResourceManager_LoadTileSetFile_Proxy( 
    IResourceManager __RPC_FAR * This,
    /* [in] */ BSTR fileName,
    /* [retval][out] */ TileSet __RPC_FAR *__RPC_FAR *tileSet);


void __RPC_STUB IResourceManager_LoadTileSetFile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IResourceManager_LoadTileSet_Proxy( 
    IResourceManager __RPC_FAR * This,
    /* [in] */ StreamReader __RPC_FAR *inStream,
    /* [retval][out] */ TileSet __RPC_FAR *__RPC_FAR *tileSet);


void __RPC_STUB IResourceManager_LoadTileSet_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IResourceManager_CreateTileSet_Proxy( 
    IResourceManager __RPC_FAR * This,
    /* [in] */ int numTiles,
    /* [in] */ int bitDepth,
    /* [in] */ int width,
    /* [retval][out] */ TileSet __RPC_FAR *__RPC_FAR *newTileSet);


void __RPC_STUB IResourceManager_CreateTileSet_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IResourceManager_LoadVolFile_Proxy( 
    IResourceManager __RPC_FAR * This,
    /* [in] */ BSTR fileName,
    /* [in] */ int bAttachToStream,
    /* [retval][out] */ ArchiveReader __RPC_FAR *__RPC_FAR *volReader);


void __RPC_STUB IResourceManager_LoadVolFile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IResourceManager_LoadVol_Proxy( 
    IResourceManager __RPC_FAR * This,
    /* [in] */ SeekableStreamReader __RPC_FAR *inStream,
    /* [in] */ int bAttachToStream,
    /* [retval][out] */ ArchiveReader __RPC_FAR *__RPC_FAR *volReader);


void __RPC_STUB IResourceManager_LoadVol_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IResourceManager_CreateVolFile_Proxy( 
    IResourceManager __RPC_FAR * This,
    /* [retval][out] */ ArchiveWriter __RPC_FAR *__RPC_FAR *volWriter);


void __RPC_STUB IResourceManager_CreateVolFile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IResourceManager_LoadClmFile_Proxy( 
    IResourceManager __RPC_FAR * This,
    /* [in] */ BSTR fileName,
    /* [in] */ int bAttachToStream,
    /* [retval][out] */ ArchiveReader __RPC_FAR *__RPC_FAR *clmReader);


void __RPC_STUB IResourceManager_LoadClmFile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IResourceManager_LoadClm_Proxy( 
    IResourceManager __RPC_FAR * This,
    /* [in] */ SeekableStreamReader __RPC_FAR *inStream,
    /* [in] */ int bAttachToStream,
    /* [retval][out] */ ArchiveReader __RPC_FAR *__RPC_FAR *clmReader);


void __RPC_STUB IResourceManager_LoadClm_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IResourceManager_CreateClmFile_Proxy( 
    IResourceManager __RPC_FAR * This,
    /* [retval][out] */ ArchiveWriter __RPC_FAR *__RPC_FAR *clmWriter);


void __RPC_STUB IResourceManager_CreateClmFile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IResourceManager_AddArchiveToSearch_Proxy( 
    IResourceManager __RPC_FAR * This,
    /* [in] */ ArchiveReader __RPC_FAR *archiveReader);


void __RPC_STUB IResourceManager_AddArchiveToSearch_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IResourceManager_ClearSearchPath_Proxy( 
    IResourceManager __RPC_FAR * This);


void __RPC_STUB IResourceManager_ClearSearchPath_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IResourceManager_INTERFACE_DEFINED__ */



#ifndef __OP2Editor_LIBRARY_DEFINED__
#define __OP2Editor_LIBRARY_DEFINED__

/* library OP2Editor */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_OP2Editor;

EXTERN_C const CLSID CLSID_ResourceManager;

#ifdef __cplusplus

class DECLSPEC_UUID("C8DE4CDE-4554-4fe9-8688-A90D91EBCA0B")
ResourceManager;
#endif
#endif /* __OP2Editor_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  BSTR_UserSize(     unsigned long __RPC_FAR *, unsigned long            , BSTR __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  BSTR_UserMarshal(  unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, BSTR __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  BSTR_UserUnmarshal(unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, BSTR __RPC_FAR * ); 
void                      __RPC_USER  BSTR_UserFree(     unsigned long __RPC_FAR *, BSTR __RPC_FAR * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
