/*
 * Copyright (c) 2004 Apple Computer, Inc. All rights reserved.
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

$Log: mDNSLibraryResources.r,v $
Revision 1.25  2005/01/28 00:04:16  cheshire
mDNSResponder-98

Revision 1.24  2005/01/22 01:15:14  ksekar
Update version string to 1.0a97

Revision 1.23  2005/01/13 19:50:17  ksekar
Update version string to 1.0a94

Revision 1.22  2005/01/10 16:33:26  ksekar
Update version string to 1.0a93

Revision 1.21  2004/12/23 23:50:59  ksekar
Update version string to 1.0a92

Revision 1.20  2004/12/20 23:26:47  cheshire
mDNSResponder-90

Revision 1.19  2004/12/16 20:52:38  cheshire
mDNSResponder-89

Revision 1.18  2004/12/15 20:25:49  cheshire
mDNSResponder-88

Revision 1.17  2004/12/13 21:54:30  cheshire
mDNSResponder-87

Revision 1.16  2004/12/06 19:09:47  cheshire
mDNSResponder-86

Revision 1.15  2004/11/29 23:36:15  cheshire
mDNSResponder-85

Revision 1.14  2004/11/23 03:46:31  cheshire
mDNSResponder-84

Revision 1.13  2004/10/26 20:30:30  cheshire
mDNSResponder-82

Revision 1.12  2004/10/14 23:38:04  cheshire
mDNSResponder-80

Revision 1.11  2004/10/07 21:49:15  cheshire
mDNSResponder-79

Revision 1.10  2004/09/25 02:52:09  cheshire
mDNSResponder-78

Revision 1.9  2004/09/22 22:52:07  cheshire
mDNSResponder-77

Revision 1.8  2004/09/21 00:20:52  cheshire
mDNSResponder-76

Revision 1.7  2004/09/15 19:45:06  cheshire
mDNSResponder-75

Revision 1.6  2004/09/09 23:32:35  cheshire
mDNSResponder-74

Revision 1.5  2004/08/10 21:51:45  cheshire
mDNSResponder-69

Revision 1.4  2004/06/10 20:28:16  cheshire
Update version string to 1.0a66

Revision 1.3  2004/06/05 00:37:12  cheshire
Update version string to 1.0a65

Revision 1.2  2004/05/27 06:24:21  cheshire
Update version string to 1.0a64

Revision 1.1  2004/03/12 21:30:26  cheshire
Build a System-Context Shared Library from mDNSCore, for the benefit of developers
like Muse Research who want to be able to use mDNS/DNS-SD from GPL-licensed code.

 */

#ifndef __TYPES.R__
#include "Types.r"
#endif

/* Format is :
 * Two-char BCD major version (0-99)
 * One-char BCD minor version, One-char BCD bugfix version (0-9, 0-9)
 * development/alpha/beta/final
 * One-byte non-final build number (0-255)
 * Version numbers can therefore range from 0.0.0 to 99.9.9,
 * with a following build stage and build number (e.g. 2.0.1 beta 219)
 */

resource 'vers' (1, purgeable)
	{
   0x01, 0x00, alpha, 98, verUS,
   "1.0a98",
   "Multicast DNS & DNS Service Discovery 1.0a98"
	};

resource 'vers' (2, purgeable)
	{
   0x01, 0x00, alpha, 98, verUS,
   "1.0a98",
   "developer.apple.com/darwin/projects/rendezvous/"
	};

/* We need to load OT, so make sure the system heap has enough space for it */
type 'sysz' { longint; };
resource 'sysz' (0, purgeable) { 2500000 };

resource 'BNDL' (128, purgeable, protected) {
	'mDNS',
	0,
	{	/* array TypeArray: 2 elements */
		/* [1] */
		'FREF',
		{	/* array IDArray: 1 elements */
			/* [1] */
			0, 128
		},
		/* [2] */
		'ICN#',
		{	/* array IDArray: 1 elements */
			/* [1] */
			0, 128
		}
	}
};

resource 'FREF' (128, purgeable, protected) {
	'INIT',
	0,
	""
};

resource 'icl8' (128, purgeable, protected) {
	$"FDFF FFFF FFFF FFFF FFFF FFFF FFFF FFFF"
	$"FFFF FFFF FFFF FFFF FFFF FFFF FD00 0000"
	$"FF00 0000 0000 0000 0000 0000 0000 0000"
	$"0000 0000 0000 0000 0000 00F6 FF00 0000"
	$"FF00 F6F6 F6F6 F6F6 F6F6 F6F6 F6F6 F6F6"
	$"F6F6 F6F6 F6F6 F6F6 F6F6 F6F9 FF00 0000"
	$"FF00 F6F6 F6F6 F6F6 F6F6 F6F6 F6F6 F6F6"
	$"F6F6 F6F6 F6F6 F6F6 F6F6 F6F9 FD00 0000"
	$"FF00 F6F6 F6F6 F6F6 F6F6 F6F6 F6F6 F6F6"
	$"F6F6 F6F6 F6F6 F6F6 F6F6 F6F9 FE00 0000"
	$"FF00 F6F6 F6F6 F6F6 F62B 07F6 F6F6 F6F6"
	$"F6F6 F6F6 F6F6 F6F6 F6F6 F6F9 FE00 0000"
	$"FF00 F6F6 F6F6 F6F6 3A16 402B F7F6 F6F6"
	$"F6F6 F656 F9F9 F956 2BF6 F6F9 FE00 0000"
	$"FF00 F6F6 F6F6 2B08 4116 4008 F8FA 2BF6"
	$"F6F7 FAFA FA81 FAFA FAF7 F6F9 FE00 0000"
	$"FF00 F9F6 F62B F92B 163A 172B F881 FAF6"
	$"2BF8 F6F6 2BF7 8181 FA81 F6F9 FE00 FD00"
	$"FF00 FFF9 F6F9 F9F8 2B2C 2BF6 F6F6 F8FA"
	$"2BF6 F6F6 F6F6 F781 F956 F8F9 FEFD FFFD"
	$"FFFF 00FE F5FA FA81 F7F6 F6F6 F6F6 F656"
	$"56F6 F6F6 F6F6 F62B 2B2B F6F9 FEFF 00FF"
	$"0000 00FF F5FA FAFA F6F6 F6F6 F6F6 2BF6"
	$"F7F8 F6F6 F6F6 F607 3A16 39F9 FF00 F9FF"
	$"0000 00FF 00FA 81FA F6F6 F6F6 F62B 2BF6"
	$"F6F8 F6F6 F6F6 F633 1C3B 1CF6 F6F6 F9FF"
	$"0000 00FE 0056 81FA F6F6 F6F6 F6F8 F6F6"
	$"F6F6 F8F6 F6F6 F62C 163A 3AF6 F6F6 F9FF"
	$"0000 00FE 00F6 8181 2BF6 F6F6 F72B F6F6"
	$"F6F6 F62B F6F6 2B2B 2C32 F6F6 F6F6 F9FF"
	$"0000 00FE 00F6 2BFA 81F6 F6F6 F9F6 F6F6"
	$"F6F6 F62B F6F7 FA81 F8F6 F6F6 F6F6 F9FF"
	$"0000 00FE 00F6 F6F6 F7F9 F72B F9F6 F6F6"
	$"F62B F756 F9FA F9F7 F6F6 F6F6 F6F6 F9FF"
	$"0000 00FE 00F6 F6F6 F6F6 F6F9 F82B 2BF7"
	$"F7F7 F72B F8F6 F6F6 F6F6 F6F6 F6F6 F9FF"
	$"0000 00FE 00F6 F6F6 F6F6 F681 2BF6 F6F6"
	$"F6F6 F6F6 F7F6 F6F6 F6F6 F6F6 F6F6 F9FF"
	$"0000 00FE 00F6 F6F6 F6F6 2B81 F7F6 F6F6"
	$"F6F6 F6F6 562B F6F6 F6F6 F6F6 F9F6 F9FF"
	$"0000 00FE 00F6 F6F6 F6F6 F7FB F7F6 F6F6"
	$"F6F6 F6F6 FAF7 F6F6 F6F6 F6F9 FEF9 F9FF"
	$"FFFF 00FE 00F6 F6F6 F6F6 F7F7 2BF6 F6F6"
	$"F6F6 F6F8 81F7 F6F6 F6F6 F6F9 FEFF F9FF"
	$"FF00 FF00 00F6 F6F6 F6F6 F60E 3A16 32F6"
	$"F6F6 56FA 812B F6F6 F6F6 F6F9 FEFD FFFD"
	$"FF00 0000 F6F6 F6F6 F6F6 F640 1640 16F6"
	$"F9F9 FA81 F9F6 F6F6 F6F6 F6F9 FE00 FD00"
	$"FF00 F6F6 F6F6 F6F6 F6F6 F633 173A 332B"
	$"FAFA 8181 2BF6 F6F6 F6F6 F6F9 FE00 0000"
	$"FF00 F6F6 F6F6 F6F6 F6F6 F6F6 3232 F6F9"
	$"8181 FA2B F6F6 F6F6 F6F6 F6F9 FE00 0000"
	$"FF00 F6F6 F6F6 F6F6 F6F6 F6F6 F6F6 2BF8"
	$"F82B F6F6 F6F6 F6F6 F6F6 F6F9 FE00 0000"
	$"FF00 F6F6 F6F6 F6F6 F6F6 F6F6 F6F6 F6F6"
	$"F6F6 F6F6 F6F6 F6F6 F6F6 F6F9 FE00 0000"
	$"FF00 F6F6 F6F6 F6F6 F6F6 F6F6 F6F6 F6F6"
	$"F6F6 F6F6 F6F6 F6F6 F6F6 F6F9 FD00 0000"
	$"FF00 F6F6 F6F6 F6F6 F6F6 F6F6 F6F6 F6F6"
	$"F6F6 F6F6 F6F6 F6F6 F6F6 F6F9 FF00 0000"
	$"FFF6 F9F9 F9F9 F9F9 F9F9 F9F9 F9F9 F9F9"
	$"F9F9 F9F9 F9F9 F9F9 F9F9 F9F9 FF00 0000"
	$"FDFF FFFF FFFF FFFF FFFF FFFF FFFF FFFF"
	$"FFFF FFFF FFFF FFFF FFFF FFFF FD"
};

data 'mDNS' (0, "Owner resource") {
	$"0644 6172 7769 6E"                                  /* .Darwin */
};

resource 'ICN#' (128) {
	{	/* array: 2 elements */
		/* [1] */
		$"FFFF FFF8 8000 0008 8000 0008 8000 0008"
		$"8000 0008 80E0 0408 81FC 3F88 83FE 7FC8"
		$"87FF EFEA A7E3 83EF D781 81ED 1F02 C1E9"
		$"1706 61F1 1704 21E1 178C 33C1 13C8 1781"
		$"10F8 FF01 101F F801 1018 0801 1038 0C01"
		$"1038 0C09 D03C 1C0D A01E 7C0F 801F F80A"
		$"801F F808 800F F008 8003 C008 8000 0008"
		$"8000 0008 8000 0008 8000 0008 FFFF FFF8",
		/* [2] */
		$"FFFF FFF8 FFFF FFF8 FFFF FFF8 FFFF FFF8"
		$"FFFF FFF8 FFFF FFF8 FFFF FFF8 FFFF FFF8"
		$"FFFF FFFA FFFF FFFF DFFF FFFF 1FFF FFFF"
		$"1FFF FFFF 1FFF FFFF 1FFF FFFF 1FFF FFFF"
		$"1FFF FFFF 1FFF FFFF 1FFF FFFF 1FFF FFFF"
		$"1FFF FFFF DFFF FFFF FFFF FFFF FFFF FFFA"
		$"FFFF FFF8 FFFF FFF8 FFFF FFF8 FFFF FFF8"
		$"FFFF FFF8 FFFF FFF8 FFFF FFF8 FFFF FFF8"
	}
};

resource 'ics#' (128, purgeable) {
	{	/* array: 2 elements */
		/* [1] */
		$"FFFE 8002 8002 8C02 DE73 D19B 5299 5451"
		$"4C61 47C1 C443 C483 8702 8302 8002 FFFE",
		/* [2] */
		$"FFFE FFFE FFFE FFFE FFFF FFFF 7FFF 7FFF"
		$"7FFF 7FFF FFFF FFFF FFFE FFFE FFFE FFFE"
	}
};

resource 'ics8' (128) {
	$"FFFF FFFF FFFF FFFF FFFF FFFF FFFF FF00"
	$"FFF6 F6F6 F6F6 F6F6 F6F6 F6F6 F6F6 FD00"
	$"FFF6 F6F6 32F6 F6F6 F6F6 F7F7 F6F6 FF00"
	$"FFF6 F632 2233 81F6 2B56 81AC FBF6 FF00"
	$"FFFE FAF9 2CF6 2BFA 2BF6 F6F8 FAF8 FEFF"
	$"FFFD FCFA F6F6 F62B F8F6 F6F6 3333 FEFF"
	$"00FE 81F9 F6F6 2BF6 F62B F6F6 4040 F6FF"
	$"00FF 2BFB 2BF6 F7F6 F62B F6F9 32F6 F6FF"
	$"00FE F6F6 F7F8 F7F6 2BF8 56F8 F6F6 F6FF"
	$"00FE F6F6 F6FA F6F6 F6F6 F7F6 F6F6 F6FF"
	$"FFFE F6F6 F6FA 2BF6 F6F6 FAF6 F6F6 FEFF"
	$"FFFE F6F6 F632 3AF6 2BF9 81F6 F6F6 FEFF"
	$"FFF6 F6F6 F632 4632 FCAC F7F6 F6F6 FE00"
	$"FFF6 F6F6 F6F6 F6F8 562B F6F6 F6F6 FE00"
	$"FFF6 F6F6 F6F6 F6F6 F6F6 F6F6 F6F6 FE00"
	$"FFFF FFFF FFFF FFFF FFFF FFFF FFFF FF"
};

