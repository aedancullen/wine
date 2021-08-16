/*
 * Copyright 2005 Mike McCormack
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301, USA
 */

#ifndef __MSXML_DISPEX__
#define __MSXML_DISPEX__

#include "dispex.h"

#include "wine/heap.h"
#include "wine/list.h"

typedef enum
{
    MSXML_DEFAULT = 0,
    MSXML2        = 20,
    MSXML26       = 26,
    MSXML3        = 30,
    MSXML4        = 40,
    MSXML6        = 60
} MSXML_VERSION;

typedef enum tid_t
{
    NULL_tid,
    IXMLDOMAttribute_tid,
    IXMLDOMCDATASection_tid,
    IXMLDOMComment_tid,
    IXMLDOMDocument_tid,
    IXMLDOMDocument2_tid,
    IXMLDOMDocument3_tid,
    IXMLDOMDocumentFragment_tid,
    IXMLDOMDocumentType_tid,
    IXMLDOMElement_tid,
    IXMLDOMEntityReference_tid,
    IXMLDOMImplementation_tid,
    IXMLDOMNamedNodeMap_tid,
    IXMLDOMNode_tid,
    IXMLDOMNodeList_tid,
    IXMLDOMParseError2_tid,
    IXMLDOMProcessingInstruction_tid,
    IXMLDOMSchemaCollection_tid,
    IXMLDOMSchemaCollection2_tid,
    IXMLDOMSelection_tid,
    IXMLDOMText_tid,
    IXMLElement_tid,
    IXMLDocument_tid,
    IXMLHTTPRequest_tid,
    IXSLProcessor_tid,
    IXSLTemplate_tid,
    IVBSAXAttributes_tid,
    IVBSAXContentHandler_tid,
    IVBSAXDeclHandler_tid,
    IVBSAXDTDHandler_tid,
    IVBSAXEntityResolver_tid,
    IVBSAXErrorHandler_tid,
    IVBSAXLexicalHandler_tid,
    IVBSAXLocator_tid,
    IVBSAXXMLFilter_tid,
    IVBSAXXMLReader_tid,
    IMXAttributes_tid,
    IMXReaderControl_tid,
    IMXWriter_tid,
    IVBMXNamespaceManager_tid,
    IServerXMLHTTPRequest_tid,
    LAST_tid
} tid_t;

extern HRESULT get_typeinfo(tid_t tid, ITypeInfo **typeinfo) DECLSPEC_HIDDEN;
extern void release_typelib(void) DECLSPEC_HIDDEN;

typedef struct dispex_data_t dispex_data_t;

typedef struct
{
    HRESULT (*get_dispid)(IUnknown*,BSTR,DWORD,DISPID*);
    HRESULT (*invoke)(IUnknown*,DISPID,LCID,WORD,DISPPARAMS*,VARIANT*,EXCEPINFO*);
} dispex_static_data_vtbl_t;

typedef struct
{
    const dispex_static_data_vtbl_t *vtbl;
    const tid_t disp_tid;
    dispex_data_t *data;
    const tid_t* const iface_tids;
} dispex_static_data_t;

typedef struct
{
    IDispatchEx IDispatchEx_iface;

    IUnknown *outer;

    dispex_static_data_t *data;
} DispatchEx;

void init_dispex(DispatchEx*,IUnknown*,dispex_static_data_t*) DECLSPEC_HIDDEN;
void release_dispex(DispatchEx*) DECLSPEC_HIDDEN;
BOOL dispex_query_interface(DispatchEx*,REFIID,void**) DECLSPEC_HIDDEN;
const IID *get_riid_from_tid(enum tid_t tid) DECLSPEC_HIDDEN;

#endif /* __MSXML_DISPEX__ */
