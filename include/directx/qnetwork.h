/*** Autogenerated by WIDL 0.9.44 from qnetwork.idl - Do not edit ***/
#include <rpc.h>
#include <rpcndr.h>

#ifndef __WIDL_QNETWORK_H
#define __WIDL_QNETWORK_H
#ifdef __cplusplus
extern "C" {
#endif
#include <unknwn.h>
#include <strmif.h>
#include <wtypes.h>
#ifndef __IAMMediaContent_FWD_DEFINED__
#define __IAMMediaContent_FWD_DEFINED__
typedef interface IAMMediaContent IAMMediaContent;
#endif

/*****************************************************************************
 * IAMMediaContent interface
 */
#ifndef __IAMMediaContent_INTERFACE_DEFINED__
#define __IAMMediaContent_INTERFACE_DEFINED__

DEFINE_GUID(IID_IAMMediaContent, 0xfa2aa8f4, 0x8b62, 0x11d0, 0xa5,0x20, 0x00,0x00,0x00,0x00,0x00,0x00);
#if defined(__cplusplus) && !defined(CINTERFACE)
interface IAMMediaContent : public IDispatch
{
    virtual HRESULT STDMETHODCALLTYPE get_AuthorName(
        BSTR *pbstrAuthorName) = 0;

    virtual HRESULT STDMETHODCALLTYPE get_Title(
        BSTR *pbstrTitle) = 0;

    virtual HRESULT STDMETHODCALLTYPE get_Rating(
        BSTR *pbstrRating) = 0;

    virtual HRESULT STDMETHODCALLTYPE get_Description(
        BSTR *pbstrDescription) = 0;

    virtual HRESULT STDMETHODCALLTYPE get_Copyright(
        BSTR *pbstrCopyright) = 0;

    virtual HRESULT STDMETHODCALLTYPE get_BaseURL(
        BSTR *pbstrBaseURL) = 0;

    virtual HRESULT STDMETHODCALLTYPE get_LogoURL(
        BSTR *pbstrLogoURL) = 0;

    virtual HRESULT STDMETHODCALLTYPE get_LogoIconURL(
        BSTR *pbstrLogoURL) = 0;

    virtual HRESULT STDMETHODCALLTYPE get_WatermarkURL(
        BSTR *pbstrWatermarkURL) = 0;

    virtual HRESULT STDMETHODCALLTYPE get_MoreInfoURL(
        BSTR *pbstrMoreInfoURL) = 0;

    virtual HRESULT STDMETHODCALLTYPE get_MoreInfoBannerImage(
        BSTR *pbstrMoreInfoBannerImage) = 0;

    virtual HRESULT STDMETHODCALLTYPE get_MoreInfoBannerURL(
        BSTR *pbstrMoreInfoBannerURL) = 0;

    virtual HRESULT STDMETHODCALLTYPE get_MoreInfoText(
        BSTR *pbstrMoreInfoText) = 0;

};
#else
typedef struct IAMMediaContentVtbl {
    BEGIN_INTERFACE

    /*** IUnknown methods ***/
    HRESULT (STDMETHODCALLTYPE *QueryInterface)(
        IAMMediaContent* This,
        REFIID riid,
        void **ppvObject);

    ULONG (STDMETHODCALLTYPE *AddRef)(
        IAMMediaContent* This);

    ULONG (STDMETHODCALLTYPE *Release)(
        IAMMediaContent* This);

    /*** IDispatch methods ***/
    HRESULT (STDMETHODCALLTYPE *GetTypeInfoCount)(
        IAMMediaContent* This,
        UINT *pctinfo);

    HRESULT (STDMETHODCALLTYPE *GetTypeInfo)(
        IAMMediaContent* This,
        UINT iTInfo,
        LCID lcid,
        ITypeInfo **ppTInfo);

    HRESULT (STDMETHODCALLTYPE *GetIDsOfNames)(
        IAMMediaContent* This,
        REFIID riid,
        LPOLESTR *rgszNames,
        UINT cNames,
        LCID lcid,
        DISPID *rgDispId);

    HRESULT (STDMETHODCALLTYPE *Invoke)(
        IAMMediaContent* This,
        DISPID dispIdMember,
        REFIID riid,
        LCID lcid,
        WORD wFlags,
        DISPPARAMS *pDispParams,
        VARIANT *pVarResult,
        EXCEPINFO *pExcepInfo,
        UINT *puArgErr);

    /*** IAMMediaContent methods ***/
    HRESULT (STDMETHODCALLTYPE *get_AuthorName)(
        IAMMediaContent* This,
        BSTR *pbstrAuthorName);

    HRESULT (STDMETHODCALLTYPE *get_Title)(
        IAMMediaContent* This,
        BSTR *pbstrTitle);

    HRESULT (STDMETHODCALLTYPE *get_Rating)(
        IAMMediaContent* This,
        BSTR *pbstrRating);

    HRESULT (STDMETHODCALLTYPE *get_Description)(
        IAMMediaContent* This,
        BSTR *pbstrDescription);

    HRESULT (STDMETHODCALLTYPE *get_Copyright)(
        IAMMediaContent* This,
        BSTR *pbstrCopyright);

    HRESULT (STDMETHODCALLTYPE *get_BaseURL)(
        IAMMediaContent* This,
        BSTR *pbstrBaseURL);

    HRESULT (STDMETHODCALLTYPE *get_LogoURL)(
        IAMMediaContent* This,
        BSTR *pbstrLogoURL);

    HRESULT (STDMETHODCALLTYPE *get_LogoIconURL)(
        IAMMediaContent* This,
        BSTR *pbstrLogoURL);

    HRESULT (STDMETHODCALLTYPE *get_WatermarkURL)(
        IAMMediaContent* This,
        BSTR *pbstrWatermarkURL);

    HRESULT (STDMETHODCALLTYPE *get_MoreInfoURL)(
        IAMMediaContent* This,
        BSTR *pbstrMoreInfoURL);

    HRESULT (STDMETHODCALLTYPE *get_MoreInfoBannerImage)(
        IAMMediaContent* This,
        BSTR *pbstrMoreInfoBannerImage);

    HRESULT (STDMETHODCALLTYPE *get_MoreInfoBannerURL)(
        IAMMediaContent* This,
        BSTR *pbstrMoreInfoBannerURL);

    HRESULT (STDMETHODCALLTYPE *get_MoreInfoText)(
        IAMMediaContent* This,
        BSTR *pbstrMoreInfoText);

    END_INTERFACE
} IAMMediaContentVtbl;
interface IAMMediaContent {
    CONST_VTBL IAMMediaContentVtbl* lpVtbl;
};

#ifdef COBJMACROS
/*** IUnknown methods ***/
#define IAMMediaContent_QueryInterface(p,a,b) (p)->lpVtbl->QueryInterface(p,a,b)
#define IAMMediaContent_AddRef(p) (p)->lpVtbl->AddRef(p)
#define IAMMediaContent_Release(p) (p)->lpVtbl->Release(p)
/*** IDispatch methods ***/
#define IAMMediaContent_GetTypeInfoCount(p,a) (p)->lpVtbl->GetTypeInfoCount(p,a)
#define IAMMediaContent_GetTypeInfo(p,a,b,c) (p)->lpVtbl->GetTypeInfo(p,a,b,c)
#define IAMMediaContent_GetIDsOfNames(p,a,b,c,d,e) (p)->lpVtbl->GetIDsOfNames(p,a,b,c,d,e)
#define IAMMediaContent_Invoke(p,a,b,c,d,e,f,g,h) (p)->lpVtbl->Invoke(p,a,b,c,d,e,f,g,h)
/*** IAMMediaContent methods ***/
#define IAMMediaContent_get_AuthorName(p,a) (p)->lpVtbl->get_AuthorName(p,a)
#define IAMMediaContent_get_Title(p,a) (p)->lpVtbl->get_Title(p,a)
#define IAMMediaContent_get_Rating(p,a) (p)->lpVtbl->get_Rating(p,a)
#define IAMMediaContent_get_Description(p,a) (p)->lpVtbl->get_Description(p,a)
#define IAMMediaContent_get_Copyright(p,a) (p)->lpVtbl->get_Copyright(p,a)
#define IAMMediaContent_get_BaseURL(p,a) (p)->lpVtbl->get_BaseURL(p,a)
#define IAMMediaContent_get_LogoURL(p,a) (p)->lpVtbl->get_LogoURL(p,a)
#define IAMMediaContent_get_LogoIconURL(p,a) (p)->lpVtbl->get_LogoIconURL(p,a)
#define IAMMediaContent_get_WatermarkURL(p,a) (p)->lpVtbl->get_WatermarkURL(p,a)
#define IAMMediaContent_get_MoreInfoURL(p,a) (p)->lpVtbl->get_MoreInfoURL(p,a)
#define IAMMediaContent_get_MoreInfoBannerImage(p,a) (p)->lpVtbl->get_MoreInfoBannerImage(p,a)
#define IAMMediaContent_get_MoreInfoBannerURL(p,a) (p)->lpVtbl->get_MoreInfoBannerURL(p,a)
#define IAMMediaContent_get_MoreInfoText(p,a) (p)->lpVtbl->get_MoreInfoText(p,a)
#endif

#endif

HRESULT CALLBACK IAMMediaContent_get_AuthorName_Proxy(
    IAMMediaContent* This,
    BSTR *pbstrAuthorName);
void __RPC_STUB IAMMediaContent_get_AuthorName_Stub(
    IRpcStubBuffer* This,
    IRpcChannelBuffer* pRpcChannelBuffer,
    PRPC_MESSAGE pRpcMessage,
    DWORD* pdwStubPhase);
HRESULT CALLBACK IAMMediaContent_get_Title_Proxy(
    IAMMediaContent* This,
    BSTR *pbstrTitle);
void __RPC_STUB IAMMediaContent_get_Title_Stub(
    IRpcStubBuffer* This,
    IRpcChannelBuffer* pRpcChannelBuffer,
    PRPC_MESSAGE pRpcMessage,
    DWORD* pdwStubPhase);
HRESULT CALLBACK IAMMediaContent_get_Rating_Proxy(
    IAMMediaContent* This,
    BSTR *pbstrRating);
void __RPC_STUB IAMMediaContent_get_Rating_Stub(
    IRpcStubBuffer* This,
    IRpcChannelBuffer* pRpcChannelBuffer,
    PRPC_MESSAGE pRpcMessage,
    DWORD* pdwStubPhase);
HRESULT CALLBACK IAMMediaContent_get_Description_Proxy(
    IAMMediaContent* This,
    BSTR *pbstrDescription);
void __RPC_STUB IAMMediaContent_get_Description_Stub(
    IRpcStubBuffer* This,
    IRpcChannelBuffer* pRpcChannelBuffer,
    PRPC_MESSAGE pRpcMessage,
    DWORD* pdwStubPhase);
HRESULT CALLBACK IAMMediaContent_get_Copyright_Proxy(
    IAMMediaContent* This,
    BSTR *pbstrCopyright);
void __RPC_STUB IAMMediaContent_get_Copyright_Stub(
    IRpcStubBuffer* This,
    IRpcChannelBuffer* pRpcChannelBuffer,
    PRPC_MESSAGE pRpcMessage,
    DWORD* pdwStubPhase);
HRESULT CALLBACK IAMMediaContent_get_BaseURL_Proxy(
    IAMMediaContent* This,
    BSTR *pbstrBaseURL);
void __RPC_STUB IAMMediaContent_get_BaseURL_Stub(
    IRpcStubBuffer* This,
    IRpcChannelBuffer* pRpcChannelBuffer,
    PRPC_MESSAGE pRpcMessage,
    DWORD* pdwStubPhase);
HRESULT CALLBACK IAMMediaContent_get_LogoURL_Proxy(
    IAMMediaContent* This,
    BSTR *pbstrLogoURL);
void __RPC_STUB IAMMediaContent_get_LogoURL_Stub(
    IRpcStubBuffer* This,
    IRpcChannelBuffer* pRpcChannelBuffer,
    PRPC_MESSAGE pRpcMessage,
    DWORD* pdwStubPhase);
HRESULT CALLBACK IAMMediaContent_get_LogoIconURL_Proxy(
    IAMMediaContent* This,
    BSTR *pbstrLogoURL);
void __RPC_STUB IAMMediaContent_get_LogoIconURL_Stub(
    IRpcStubBuffer* This,
    IRpcChannelBuffer* pRpcChannelBuffer,
    PRPC_MESSAGE pRpcMessage,
    DWORD* pdwStubPhase);
HRESULT CALLBACK IAMMediaContent_get_WatermarkURL_Proxy(
    IAMMediaContent* This,
    BSTR *pbstrWatermarkURL);
void __RPC_STUB IAMMediaContent_get_WatermarkURL_Stub(
    IRpcStubBuffer* This,
    IRpcChannelBuffer* pRpcChannelBuffer,
    PRPC_MESSAGE pRpcMessage,
    DWORD* pdwStubPhase);
HRESULT CALLBACK IAMMediaContent_get_MoreInfoURL_Proxy(
    IAMMediaContent* This,
    BSTR *pbstrMoreInfoURL);
void __RPC_STUB IAMMediaContent_get_MoreInfoURL_Stub(
    IRpcStubBuffer* This,
    IRpcChannelBuffer* pRpcChannelBuffer,
    PRPC_MESSAGE pRpcMessage,
    DWORD* pdwStubPhase);
HRESULT CALLBACK IAMMediaContent_get_MoreInfoBannerImage_Proxy(
    IAMMediaContent* This,
    BSTR *pbstrMoreInfoBannerImage);
void __RPC_STUB IAMMediaContent_get_MoreInfoBannerImage_Stub(
    IRpcStubBuffer* This,
    IRpcChannelBuffer* pRpcChannelBuffer,
    PRPC_MESSAGE pRpcMessage,
    DWORD* pdwStubPhase);
HRESULT CALLBACK IAMMediaContent_get_MoreInfoBannerURL_Proxy(
    IAMMediaContent* This,
    BSTR *pbstrMoreInfoBannerURL);
void __RPC_STUB IAMMediaContent_get_MoreInfoBannerURL_Stub(
    IRpcStubBuffer* This,
    IRpcChannelBuffer* pRpcChannelBuffer,
    PRPC_MESSAGE pRpcMessage,
    DWORD* pdwStubPhase);
HRESULT CALLBACK IAMMediaContent_get_MoreInfoText_Proxy(
    IAMMediaContent* This,
    BSTR *pbstrMoreInfoText);
void __RPC_STUB IAMMediaContent_get_MoreInfoText_Stub(
    IRpcStubBuffer* This,
    IRpcChannelBuffer* pRpcChannelBuffer,
    PRPC_MESSAGE pRpcMessage,
    DWORD* pdwStubPhase);

#endif  /* __IAMMediaContent_INTERFACE_DEFINED__ */

#ifndef __IAMNetworkStatus_FWD_DEFINED__
#define __IAMNetworkStatus_FWD_DEFINED__
typedef interface IAMNetworkStatus IAMNetworkStatus;
#endif

/*****************************************************************************
 * IAMNetworkStatus interface
 */
#ifndef __IAMNetworkStatus_INTERFACE_DEFINED__
#define __IAMNetworkStatus_INTERFACE_DEFINED__

DEFINE_GUID(IID_IAMNetworkStatus, 0xfa2aa8f3, 0x8b62, 0x11d0, 0xa5,0x20, 0x00,0x00,0x00,0x00,0x00,0x00);
#if defined(__cplusplus) && !defined(CINTERFACE)
interface IAMNetworkStatus : public IDispatch
{
    virtual HRESULT STDMETHODCALLTYPE get_ReceivedPackets(
        long *pReceivedPackets) = 0;

    virtual HRESULT STDMETHODCALLTYPE get_RecoveredPackets(
        long *pRecoveredPackets) = 0;

    virtual HRESULT STDMETHODCALLTYPE get_LostPackets(
        long *pLostPackets) = 0;

    virtual HRESULT STDMETHODCALLTYPE get_ReceptionQuality(
        long *pReceptionQuality) = 0;

    virtual HRESULT STDMETHODCALLTYPE get_BufferingCount(
        long *pBufferingCount) = 0;

    virtual HRESULT STDMETHODCALLTYPE get_IsBroadcast(
        VARIANT_BOOL *pIsBroadcast) = 0;

    virtual HRESULT STDMETHODCALLTYPE get_BufferingProgress(
        long *pBufferingProgress) = 0;

};
#else
typedef struct IAMNetworkStatusVtbl {
    BEGIN_INTERFACE

    /*** IUnknown methods ***/
    HRESULT (STDMETHODCALLTYPE *QueryInterface)(
        IAMNetworkStatus* This,
        REFIID riid,
        void **ppvObject);

    ULONG (STDMETHODCALLTYPE *AddRef)(
        IAMNetworkStatus* This);

    ULONG (STDMETHODCALLTYPE *Release)(
        IAMNetworkStatus* This);

    /*** IDispatch methods ***/
    HRESULT (STDMETHODCALLTYPE *GetTypeInfoCount)(
        IAMNetworkStatus* This,
        UINT *pctinfo);

    HRESULT (STDMETHODCALLTYPE *GetTypeInfo)(
        IAMNetworkStatus* This,
        UINT iTInfo,
        LCID lcid,
        ITypeInfo **ppTInfo);

    HRESULT (STDMETHODCALLTYPE *GetIDsOfNames)(
        IAMNetworkStatus* This,
        REFIID riid,
        LPOLESTR *rgszNames,
        UINT cNames,
        LCID lcid,
        DISPID *rgDispId);

    HRESULT (STDMETHODCALLTYPE *Invoke)(
        IAMNetworkStatus* This,
        DISPID dispIdMember,
        REFIID riid,
        LCID lcid,
        WORD wFlags,
        DISPPARAMS *pDispParams,
        VARIANT *pVarResult,
        EXCEPINFO *pExcepInfo,
        UINT *puArgErr);

    /*** IAMNetworkStatus methods ***/
    HRESULT (STDMETHODCALLTYPE *get_ReceivedPackets)(
        IAMNetworkStatus* This,
        long *pReceivedPackets);

    HRESULT (STDMETHODCALLTYPE *get_RecoveredPackets)(
        IAMNetworkStatus* This,
        long *pRecoveredPackets);

    HRESULT (STDMETHODCALLTYPE *get_LostPackets)(
        IAMNetworkStatus* This,
        long *pLostPackets);

    HRESULT (STDMETHODCALLTYPE *get_ReceptionQuality)(
        IAMNetworkStatus* This,
        long *pReceptionQuality);

    HRESULT (STDMETHODCALLTYPE *get_BufferingCount)(
        IAMNetworkStatus* This,
        long *pBufferingCount);

    HRESULT (STDMETHODCALLTYPE *get_IsBroadcast)(
        IAMNetworkStatus* This,
        VARIANT_BOOL *pIsBroadcast);

    HRESULT (STDMETHODCALLTYPE *get_BufferingProgress)(
        IAMNetworkStatus* This,
        long *pBufferingProgress);

    END_INTERFACE
} IAMNetworkStatusVtbl;
interface IAMNetworkStatus {
    CONST_VTBL IAMNetworkStatusVtbl* lpVtbl;
};

#ifdef COBJMACROS
/*** IUnknown methods ***/
#define IAMNetworkStatus_QueryInterface(p,a,b) (p)->lpVtbl->QueryInterface(p,a,b)
#define IAMNetworkStatus_AddRef(p) (p)->lpVtbl->AddRef(p)
#define IAMNetworkStatus_Release(p) (p)->lpVtbl->Release(p)
/*** IDispatch methods ***/
#define IAMNetworkStatus_GetTypeInfoCount(p,a) (p)->lpVtbl->GetTypeInfoCount(p,a)
#define IAMNetworkStatus_GetTypeInfo(p,a,b,c) (p)->lpVtbl->GetTypeInfo(p,a,b,c)
#define IAMNetworkStatus_GetIDsOfNames(p,a,b,c,d,e) (p)->lpVtbl->GetIDsOfNames(p,a,b,c,d,e)
#define IAMNetworkStatus_Invoke(p,a,b,c,d,e,f,g,h) (p)->lpVtbl->Invoke(p,a,b,c,d,e,f,g,h)
/*** IAMNetworkStatus methods ***/
#define IAMNetworkStatus_get_ReceivedPackets(p,a) (p)->lpVtbl->get_ReceivedPackets(p,a)
#define IAMNetworkStatus_get_RecoveredPackets(p,a) (p)->lpVtbl->get_RecoveredPackets(p,a)
#define IAMNetworkStatus_get_LostPackets(p,a) (p)->lpVtbl->get_LostPackets(p,a)
#define IAMNetworkStatus_get_ReceptionQuality(p,a) (p)->lpVtbl->get_ReceptionQuality(p,a)
#define IAMNetworkStatus_get_BufferingCount(p,a) (p)->lpVtbl->get_BufferingCount(p,a)
#define IAMNetworkStatus_get_IsBroadcast(p,a) (p)->lpVtbl->get_IsBroadcast(p,a)
#define IAMNetworkStatus_get_BufferingProgress(p,a) (p)->lpVtbl->get_BufferingProgress(p,a)
#endif

#endif

HRESULT CALLBACK IAMNetworkStatus_get_ReceivedPackets_Proxy(
    IAMNetworkStatus* This,
    long *pReceivedPackets);
void __RPC_STUB IAMNetworkStatus_get_ReceivedPackets_Stub(
    IRpcStubBuffer* This,
    IRpcChannelBuffer* pRpcChannelBuffer,
    PRPC_MESSAGE pRpcMessage,
    DWORD* pdwStubPhase);
HRESULT CALLBACK IAMNetworkStatus_get_RecoveredPackets_Proxy(
    IAMNetworkStatus* This,
    long *pRecoveredPackets);
void __RPC_STUB IAMNetworkStatus_get_RecoveredPackets_Stub(
    IRpcStubBuffer* This,
    IRpcChannelBuffer* pRpcChannelBuffer,
    PRPC_MESSAGE pRpcMessage,
    DWORD* pdwStubPhase);
HRESULT CALLBACK IAMNetworkStatus_get_LostPackets_Proxy(
    IAMNetworkStatus* This,
    long *pLostPackets);
void __RPC_STUB IAMNetworkStatus_get_LostPackets_Stub(
    IRpcStubBuffer* This,
    IRpcChannelBuffer* pRpcChannelBuffer,
    PRPC_MESSAGE pRpcMessage,
    DWORD* pdwStubPhase);
HRESULT CALLBACK IAMNetworkStatus_get_ReceptionQuality_Proxy(
    IAMNetworkStatus* This,
    long *pReceptionQuality);
void __RPC_STUB IAMNetworkStatus_get_ReceptionQuality_Stub(
    IRpcStubBuffer* This,
    IRpcChannelBuffer* pRpcChannelBuffer,
    PRPC_MESSAGE pRpcMessage,
    DWORD* pdwStubPhase);
HRESULT CALLBACK IAMNetworkStatus_get_BufferingCount_Proxy(
    IAMNetworkStatus* This,
    long *pBufferingCount);
void __RPC_STUB IAMNetworkStatus_get_BufferingCount_Stub(
    IRpcStubBuffer* This,
    IRpcChannelBuffer* pRpcChannelBuffer,
    PRPC_MESSAGE pRpcMessage,
    DWORD* pdwStubPhase);
HRESULT CALLBACK IAMNetworkStatus_get_IsBroadcast_Proxy(
    IAMNetworkStatus* This,
    VARIANT_BOOL *pIsBroadcast);
void __RPC_STUB IAMNetworkStatus_get_IsBroadcast_Stub(
    IRpcStubBuffer* This,
    IRpcChannelBuffer* pRpcChannelBuffer,
    PRPC_MESSAGE pRpcMessage,
    DWORD* pdwStubPhase);
HRESULT CALLBACK IAMNetworkStatus_get_BufferingProgress_Proxy(
    IAMNetworkStatus* This,
    long *pBufferingProgress);
void __RPC_STUB IAMNetworkStatus_get_BufferingProgress_Stub(
    IRpcStubBuffer* This,
    IRpcChannelBuffer* pRpcChannelBuffer,
    PRPC_MESSAGE pRpcMessage,
    DWORD* pdwStubPhase);

#endif  /* __IAMNetworkStatus_INTERFACE_DEFINED__ */

/* Begin additional prototypes for all interfaces */

ULONG           __RPC_USER BSTR_UserSize     (ULONG *, ULONG, BSTR *);
unsigned char * __RPC_USER BSTR_UserMarshal  (ULONG *, unsigned char *, BSTR *);
unsigned char * __RPC_USER BSTR_UserUnmarshal(ULONG *, unsigned char *, BSTR *);
void            __RPC_USER BSTR_UserFree     (ULONG *, BSTR *);

/* End additional prototypes */

#ifdef __cplusplus
}
#endif
#endif /* __WIDL_QNETWORK_H */