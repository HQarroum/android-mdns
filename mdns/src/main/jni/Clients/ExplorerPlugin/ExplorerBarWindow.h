/*
 * Copyright (c) 2003-2004 Apple Computer, Inc. All rights reserved.
 *
 * @APPLE_LICENSE_HEADER_START@
 * 
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the Apple Public Source License
 * Version 2.0 (the 'License'). You may not use this file except in
 * compliance with the License. Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this
 * file.
 * 
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 * 
 * @APPLE_LICENSE_HEADER_END@

    Change History (most recent first):
    
$Log: ExplorerBarWindow.h,v $
Revision 1.6  2005/01/27 22:27:03  shersche
Add m_about member for "About Rendezvous" tree item

Revision 1.5  2004/07/26 05:47:31  shersche
use TXTRecord APIs, fix bug in locating service to be removed

Revision 1.4  2004/07/20 06:49:18  shersche
clean up socket handling code

Revision 1.3  2004/07/13 21:24:21  rpantos
Fix for <rdar://problem/3701120>.

Revision 1.2  2004/06/27 14:59:59  shersche
reference count service info to handle multi-homed hosts

Revision 1.1  2004/06/18 04:34:59  rpantos
Move to Clients from mDNSWindows

Revision 1.3  2004/04/15 01:00:05  bradley
Removed support for automatically querying for A/AAAA records when resolving names. Platforms
without .local name resolving support will need to manually query for A/AAAA records as needed.

Revision 1.2  2004/04/08 09:43:43  bradley
Changed callback calling conventions to __stdcall so they can be used with C# delegates.

Revision 1.1  2004/01/30 03:01:56  bradley
Explorer Plugin to browse for DNS-SD advertised Web and FTP servers from within Internet Explorer.

*/

#ifndef	__EXPLORER_BAR_WINDOW__
#define	__EXPLORER_BAR_WINDOW__

#pragma once

#include	"afxtempl.h"

#include	"dns_sd.h"
#include	<list>

//===========================================================================================================================
//	Structures
//===========================================================================================================================

// Forward Declarations

struct	ServiceHandlerEntry;
class	ExplorerBarWindow;

// ServiceInfo

struct	ServiceInfo
{
	CString						displayName;
	char *						name;
	char *						type;
	char *						domain;
	uint32_t					ifi;
	HTREEITEM					item;
	ServiceHandlerEntry *		handler;
	DWORD						refs;
	
	ServiceInfo( void )
	{
		item	= NULL;
		type 	= NULL;
		domain	= NULL;
		handler	= NULL;
	}
	
	~ServiceInfo( void )
	{
		if( name )
		{
			free( name );
		}
		if( type )
		{
			free( type );
		}
		if( domain )
		{
			free( domain );
		}
	}
};

typedef CArray < ServiceInfo *, ServiceInfo * >		ServiceInfoArray;

// TextRecord

struct	TextRecord
{
	uint8_t *		mData;
	uint16_t		mSize;
	
	TextRecord( void )
	{
		mData = NULL;
		mSize = 0;
	}
	
	~TextRecord( void )
	{
		if( mData )
		{
			free( mData );
		}
	}
	
	void	GetData( void *outData, uint16_t *outSize )
	{
		if( outData )
		{
			*( (void **) outData ) = mData;
		}
		if( outSize )
		{
			*outSize = mSize;
		}
	}
	
	OSStatus	SetData( const void *inData, uint16_t inSize )
	{
		OSStatus		err;
		uint8_t *		newData;
		
		newData = (uint8_t *) malloc( inSize );
		require_action( newData, exit, err = kNoMemoryErr );
		memcpy( newData, inData, inSize );
		
		if( mData )
		{
			free( mData );
		}
		mData = newData;
		mSize = inSize;
		err  = kNoErr;
		
	exit:
		return( err );
	}
};

// ResolveInfo

struct	ResolveInfo
{
	CString						host;
	uint16_t					port;
	uint32_t					ifi;
	TextRecord					txt;
	ServiceHandlerEntry *		handler;
};

// ServiceHandlerEntry

struct	ServiceHandlerEntry
{
	const char *			type;
	const char *			urlScheme;
	DNSServiceRef			ref;
	ServiceInfoArray		array;
	HTREEITEM				treeItem;
	bool					treeFirst;
	ExplorerBarWindow *		obj;
	bool					needsLogin;
	
	ServiceHandlerEntry( void )
	{
		type		= NULL;
		urlScheme	= NULL;
		ref 		= NULL;
		treeItem	= NULL;
		treeFirst	= true;
		obj			= NULL;
		needsLogin	= false;
	}
	
	~ServiceHandlerEntry( void )
	{
		int		i;
		int		n;
		
		n = (int) array.GetSize();
		for( i = 0; i < n; ++i )
		{
			delete array[ i ];
		}
	}
};

typedef CArray < ServiceHandlerEntry *, ServiceHandlerEntry * >		ServiceHandlerArray;

//===========================================================================================================================
//	ExplorerBarWindow
//===========================================================================================================================

class	ExplorerBar;	// Forward Declaration

class	ExplorerBarWindow : public CWnd
{
	protected:

		ExplorerBar *			mOwner;
		CTreeCtrl				mTree;
		
		ServiceHandlerArray		mServiceHandlers;
		DNSServiceRef			mResolveServiceRef;
		
	public:
		
		ExplorerBarWindow( void );
		virtual	~ExplorerBarWindow( void );

	protected:
		
		// General
		
		afx_msg int		OnCreate( LPCREATESTRUCT inCreateStruct );
		afx_msg void	OnDestroy( void );
		afx_msg void	OnSize( UINT inType, int inX, int inY );
		afx_msg void	OnDoubleClick( NMHDR *inNMHDR, LRESULT *outResult );
		afx_msg LONG	OnServiceEvent( WPARAM inWParam, LPARAM inLParam );
		
		// Browsing
		
		static void DNSSD_API
			BrowseCallBack(
				DNSServiceRef 			inRef,
				DNSServiceFlags 		inFlags,
				uint32_t 				inInterfaceIndex,
				DNSServiceErrorType 	inErrorCode,
				const char *			inName,	
				const char *			inType,	
				const char *			inDomain,	
				void *					inContext );
		LONG OnServiceAdd( ServiceInfo * service );
		LONG OnServiceRemove( ServiceInfo * service );
		
		// Resolving
		
		OSStatus	StartResolve( ServiceInfo *inService );
		void		StopResolve( void );


		void		Stop( DNSServiceRef ref );


		static void DNSSD_API
			ResolveCallBack(
				DNSServiceRef			inRef,
				DNSServiceFlags			inFlags,
				uint32_t				inInterfaceIndex,
				DNSServiceErrorType		inErrorCode,
				const char *			inFullName,	
				const char *			inHostName, 
				uint16_t 				inPort,
				uint16_t 				inTXTSize,
				const char *			inTXT,
				void *					inContext );
		LONG OnResolve( ResolveInfo * resolve );		
				
		// Accessors
	
	public:
	
		ExplorerBar *	GetOwner( void ) const				{ return( mOwner ); }
		void			SetOwner( ExplorerBar *inOwner )	{ mOwner = inOwner; }
		
		DECLARE_MESSAGE_MAP()
	private:

		typedef std::list< DNSServiceRef >  ServiceRefList;
		
		HTREEITEM		m_about;
		ServiceRefList	m_serviceRefs;
		CImageList		m_imageList;
};

#endif	// __EXPLORER_BAR_WINDOW__
