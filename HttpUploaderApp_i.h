

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 7.00.0555 */
/* at Thu Nov 28 16:57:39 2019
 */
/* Compiler settings for HttpUploaderApp.idl:
    Oicf, W1, Zp8, env=Win32 (32b run), target_arch=X86 7.00.0555 
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */

#pragma warning( disable: 4049 )  /* more than 64k source lines */


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
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

#ifndef __HttpUploaderApp_i_h__
#define __HttpUploaderApp_i_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IHttpPartition_FWD_DEFINED__
#define __IHttpPartition_FWD_DEFINED__
typedef interface IHttpPartition IHttpPartition;
#endif 	/* __IHttpPartition_FWD_DEFINED__ */


#ifndef __IHttpDroper_FWD_DEFINED__
#define __IHttpDroper_FWD_DEFINED__
typedef interface IHttpDroper IHttpDroper;
#endif 	/* __IHttpDroper_FWD_DEFINED__ */


#ifndef ___IHttpPartitionEvents_FWD_DEFINED__
#define ___IHttpPartitionEvents_FWD_DEFINED__
typedef interface _IHttpPartitionEvents _IHttpPartitionEvents;
#endif 	/* ___IHttpPartitionEvents_FWD_DEFINED__ */


#ifndef __HttpPartition_FWD_DEFINED__
#define __HttpPartition_FWD_DEFINED__

#ifdef __cplusplus
typedef class HttpPartition HttpPartition;
#else
typedef struct HttpPartition HttpPartition;
#endif /* __cplusplus */

#endif 	/* __HttpPartition_FWD_DEFINED__ */


#ifndef __HttpDroper_FWD_DEFINED__
#define __HttpDroper_FWD_DEFINED__

#ifdef __cplusplus
typedef class HttpDroper HttpDroper;
#else
typedef struct HttpDroper HttpDroper;
#endif /* __cplusplus */

#endif 	/* __HttpDroper_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"
#include "dispex.h"

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __IHttpPartition_INTERFACE_DEFINED__
#define __IHttpPartition_INTERFACE_DEFINED__

/* interface IHttpPartition */
/* [unique][helpstring][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IHttpPartition;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("C1496BE0-9157-4CD2-B9E2-C967A6FFE77C")
    IHttpPartition : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE postMessage( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE FireRecvMessage( 
            /* [in] */ BSTR json) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Version( 
            /* [retval][out] */ BSTR *val) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_recvMessage( 
            /* [in] */ IDispatchEx *newVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IHttpPartitionVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IHttpPartition * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IHttpPartition * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IHttpPartition * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IHttpPartition * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IHttpPartition * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IHttpPartition * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IHttpPartition * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *postMessage )( 
            IHttpPartition * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *FireRecvMessage )( 
            IHttpPartition * This,
            /* [in] */ BSTR json);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Version )( 
            IHttpPartition * This,
            /* [retval][out] */ BSTR *val);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_recvMessage )( 
            IHttpPartition * This,
            /* [in] */ IDispatchEx *newVal);
        
        END_INTERFACE
    } IHttpPartitionVtbl;

    interface IHttpPartition
    {
        CONST_VTBL struct IHttpPartitionVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IHttpPartition_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IHttpPartition_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IHttpPartition_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IHttpPartition_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IHttpPartition_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IHttpPartition_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IHttpPartition_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IHttpPartition_postMessage(This,newVal)	\
    ( (This)->lpVtbl -> postMessage(This,newVal) ) 

#define IHttpPartition_FireRecvMessage(This,json)	\
    ( (This)->lpVtbl -> FireRecvMessage(This,json) ) 

#define IHttpPartition_get_Version(This,val)	\
    ( (This)->lpVtbl -> get_Version(This,val) ) 

#define IHttpPartition_put_recvMessage(This,newVal)	\
    ( (This)->lpVtbl -> put_recvMessage(This,newVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IHttpPartition_INTERFACE_DEFINED__ */


#ifndef __IHttpDroper_INTERFACE_DEFINED__
#define __IHttpDroper_INTERFACE_DEFINED__

/* interface IHttpDroper */
/* [unique][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IHttpDroper;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("A1AB4568-CEC2-4EFA-B063-FFE23EC7ECBB")
    IHttpDroper : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_recvMessage( 
            /* [in] */ IDispatchEx *newVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IHttpDroperVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IHttpDroper * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IHttpDroper * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IHttpDroper * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IHttpDroper * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IHttpDroper * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IHttpDroper * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IHttpDroper * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_recvMessage )( 
            IHttpDroper * This,
            /* [in] */ IDispatchEx *newVal);
        
        END_INTERFACE
    } IHttpDroperVtbl;

    interface IHttpDroper
    {
        CONST_VTBL struct IHttpDroperVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IHttpDroper_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IHttpDroper_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IHttpDroper_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IHttpDroper_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IHttpDroper_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IHttpDroper_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IHttpDroper_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IHttpDroper_put_recvMessage(This,newVal)	\
    ( (This)->lpVtbl -> put_recvMessage(This,newVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IHttpDroper_INTERFACE_DEFINED__ */



#ifndef __HttpUploaderAppLib_LIBRARY_DEFINED__
#define __HttpUploaderAppLib_LIBRARY_DEFINED__

/* library HttpUploaderAppLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_HttpUploaderAppLib;

#ifndef ___IHttpPartitionEvents_DISPINTERFACE_DEFINED__
#define ___IHttpPartitionEvents_DISPINTERFACE_DEFINED__

/* dispinterface _IHttpPartitionEvents */
/* [helpstring][uuid] */ 


EXTERN_C const IID DIID__IHttpPartitionEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("E749CDE5-ADE5-4E74-AF8C-9107369A3389")
    _IHttpPartitionEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _IHttpPartitionEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _IHttpPartitionEvents * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _IHttpPartitionEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _IHttpPartitionEvents * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _IHttpPartitionEvents * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _IHttpPartitionEvents * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _IHttpPartitionEvents * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _IHttpPartitionEvents * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } _IHttpPartitionEventsVtbl;

    interface _IHttpPartitionEvents
    {
        CONST_VTBL struct _IHttpPartitionEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _IHttpPartitionEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define _IHttpPartitionEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define _IHttpPartitionEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define _IHttpPartitionEvents_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define _IHttpPartitionEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define _IHttpPartitionEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define _IHttpPartitionEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___IHttpPartitionEvents_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_HttpPartition;

#ifdef __cplusplus

class DECLSPEC_UUID("885164DE-E5DA-49A6-BE7C-CBC9A7AB5FE3")
HttpPartition;
#endif

EXTERN_C const CLSID CLSID_HttpDroper;

#ifdef __cplusplus

class DECLSPEC_UUID("5E985DAB-5CDD-4DAB-A7E2-327540AEEDEF")
HttpDroper;
#endif
#endif /* __HttpUploaderAppLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  BSTR_UserSize(     unsigned long *, unsigned long            , BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserMarshal(  unsigned long *, unsigned char *, BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserUnmarshal(unsigned long *, unsigned char *, BSTR * ); 
void                      __RPC_USER  BSTR_UserFree(     unsigned long *, BSTR * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


