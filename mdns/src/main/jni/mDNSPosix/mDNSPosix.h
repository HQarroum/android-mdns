/* -*- Mode: C; tab-width: 4 -*-
 *
 * Copyright (c) 2002-2004 Apple Computer, Inc. All rights reserved.
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

$Log: mDNSPosix.h,v $
Revision 1.16  2004/11/30 22:37:01  cheshire
Update copyright dates and add "Mode: C; tab-width: 4" headers

Revision 1.15  2004/02/06 01:19:51  cheshire
Conditionally exclude IPv6 code unless HAVE_IPV6 is set

Revision 1.14  2004/01/28 21:12:15  cheshire
Reconcile mDNSIPv6Support & HAVE_IPV6 into a single flag (HAVE_IPV6)

Revision 1.13  2004/01/24 05:12:03  cheshire
<rdar://problem/3534352>: Need separate socket for issuing unicast queries

Revision 1.12  2004/01/23 21:37:08  cheshire
For consistency, rename multicastSocket to multicastSocket4, and multicastSocketv6 to multicastSocket6

Revision 1.11  2003/12/11 03:03:51  rpantos
Clean up mDNSPosix so that it builds on OS X again.

Revision 1.10  2003/12/08 20:47:02  rpantos
Add support for mDNSResponder on Linux.

Revision 1.9  2003/10/30 19:25:19  cheshire
Fix warning on certain compilers

Revision 1.8  2003/08/12 19:56:26  cheshire
Update to APSL 2.0

Revision 1.7  2003/07/02 21:19:59  cheshire
<rdar://problem/3313413> Update copyright notices, etc., in source code comments

Revision 1.6  2003/03/13 03:46:21  cheshire
Fixes to make the code build on Linux

Revision 1.5  2003/03/08 00:35:56  cheshire
Switched to using new "mDNS_Execute" model (see "mDNSCore/Implementer Notes.txt")

Revision 1.4  2002/12/23 22:13:31  jgraessl

Reviewed by: Stuart Cheshire
Initial IPv6 support for mDNSResponder.

Revision 1.3  2002/09/21 20:44:53  zarzycki
Added APSL info

Revision 1.2  2002/09/19 04:20:44  cheshire
Remove high-ascii characters that confuse some systems

Revision 1.1  2002/09/17 06:24:34  cheshire
First checkin

*/

#ifndef __mDNSPlatformPosix_h
#define __mDNSPlatformPosix_h

#ifdef TARGET_OS_ANDROID
#include <sys/socket.h>
#include <sys/select.h>
#endif

#include <signal.h>
#include <sys/time.h>

#ifdef  __cplusplus
    extern "C" {
#endif

// PosixNetworkInterface is a record extension of the core NetworkInterfaceInfo
// type that supports extra fields needed by the Posix platform.
//
// IMPORTANT: coreIntf must be the first field in the structure because
// we cast between pointers to the two different types regularly.

typedef struct PosixNetworkInterface PosixNetworkInterface;

struct PosixNetworkInterface
	{
	NetworkInterfaceInfo    coreIntf;
	const char *            intfName;
	PosixNetworkInterface * aliasIntf;
	int                     index;
	int                     multicastSocket4;
#if HAVE_IPV6
	int                     multicastSocket6;
#endif
	};

// This is a global because debugf_() needs to be able to check its value
extern int gMDNSPlatformPosixVerboseLevel;

struct mDNS_PlatformSupport_struct
	{
	int unicastSocket4;
#if HAVE_IPV6
	int unicastSocket6;
#endif
	};

extern mStatus mDNSPlatformPosixRefreshInterfaceList(mDNS *const m);
    // See comment in implementation.

// Call mDNSPosixGetFDSet before calling select(), to update the parameters
// as may be necessary to meet the needs of the mDNSCore code.
// The timeout pointer MUST NOT be NULL.
// Set timeout->tv_sec to 0x3FFFFFFF if you want to have effectively no timeout
// After calling mDNSPosixGetFDSet(), call select(nfds, &readfds, NULL, NULL, &timeout); as usual
// After select() returns, call mDNSPosixProcessFDSet() to let mDNSCore do its work
extern void mDNSPosixGetFDSet(mDNS *m, int *nfds, fd_set *readfds, struct timeval *timeout);
extern void mDNSPosixProcessFDSet(mDNS *const m, fd_set *readfds);

typedef	void (*mDNSPosixEventCallback)( void *context);

extern mStatus mDNSPosixAddFDToEventLoop( int fd, mDNSPosixEventCallback callback, void *context);
extern mStatus mDNSPosixRemoveFDFromEventLoop( int fd);
extern mStatus mDNSPosixListenForSignalInEventLoop( int signum);
extern mStatus mDNSPosixIgnoreSignalInEventLoop( int signum);
extern mStatus mDNSPosixRunEventLoopOnce( mDNS *m, const struct timeval *pTimeout, sigset_t *pSignalsReceived, mDNSBool *pDataDispatched);

#ifdef  __cplusplus
    }
#endif

#endif
