/*
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

 */
    
/* loclibrary.c                                                          
 * ----------------------------------------------------------------------
 * Source for localization library                                       
 * Originally created by jsantamaria: 3 may 2004                         
 * ----------------------------------------------------------------------
 */
 
#include <windows.h>
#include <stdio.h>
#include "isocode.h"
#include "loclibrary.h"
#include "Shlwapi.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <wchar.h>

#ifdef __cplusplus
extern "c" {
#endif

#ifdef _MSC_VER
#define swprintf _snwprintf
#define snprintf _snprintf
#endif



#define DEFAULT_LANG_CODE "en"

// gets the user language
static LANGID _getUserLanguage( void ) {
	
	return GetUserDefaultUILanguage();

}


// gets the ISO mapping
static int _getISOCode(LANGID wLangID, char *isoLangCode, int codeLen) {
	int i;
	unsigned short langCode;

	for (i = 0; i < NUM_ISOCODES; i++) {
		int startIndex = i * MODULO_ISOCODES;
		
		langCode = (ISOCODES[startIndex] << 8);
		langCode += ( (unsigned short) (ISOCODES[startIndex + 1]) );

		if (langCode == wLangID) {
			char *langStr = (char *)&(ISOCODES[startIndex+2]);
			strncpy(isoLangCode, langStr, codeLen);
			return 0;
		}
	}
	return 1;
}

static char isoLangCode[LANG_CODE_LEN + 1] = "";
static LANGID wLangID = (LANGID) -1;

static void _setLanguageIfNeeded(void) {
	
	// get the language code if we don't have it cached
	if (!strncmp(isoLangCode,"",LANG_CODE_LEN + 1)) {
		
		// if we haven't cached the language id, do the lookup
		if (wLangID == (LANGID) -1) {
			wLangID = _getUserLanguage();
		}
		
		// if no ISOCode, set it to DEFAULT_LANG_CODE
		if (_getISOCode(wLangID, isoLangCode, LANG_CODE_LEN + 1)) {
			strncpy(isoLangCode, DEFAULT_LANG_CODE, LANG_CODE_LEN+1);
		}
	}

}

//// PathForResource

// Gets the PathForResource for handle 0 for the current process


static char appPathNameA[MAX_PATH] = "";

int PathForResourceA ( HMODULE module, const char *name, char *locFile, int locFileLen) {
	if (!strcmp(appPathNameA,"")) {
		GetModuleFileNameA(module, appPathNameA, MAX_PATH);
	}

	return PathForResourceWithPathA (appPathNameA, name, locFile, locFileLen);

}

static wchar_t appPathNameW[MAX_PATH] = L"";

int PathForResourceW ( HMODULE module, const wchar_t *name, wchar_t *locFile, int locFileLen) {
	if (!wcscmp(appPathNameW,L"")) {
		GetModuleFileNameW( module, appPathNameW, MAX_PATH);
	}

OutputDebugString( appPathNameW );

	return PathForResourceWithPathW (appPathNameW, name, locFile, locFileLen);
}


//// PathForResourceWithPath

#define TMP_BUF_SIZE MAX_PATH

int PathForResourceWithPathA (const char *path, const char *nm, 
									char *locFile, int locFileLen) {
	char tmpBuffer[TMP_BUF_SIZE];

	// build the path to the executable in the generic 
	// resources folder, check there first
	snprintf(tmpBuffer, MAX_PATH, "%s.Resources\\%s", path, nm);

	if (!PathFileExistsA(tmpBuffer)) {

		// didn't hit generic resource folder, so need to get language codes
		_setLanguageIfNeeded();

		// test to see if localized directory exists, 
		// if so, we don't fall back if we don't find the file.
		snprintf(tmpBuffer, TMP_BUF_SIZE, 
				 "%s.Resources\\%s.lproj", path, isoLangCode);

		if (PathFileExistsA(tmpBuffer)) {
			snprintf(tmpBuffer, TMP_BUF_SIZE, "%s\\%s", tmpBuffer, nm);

			if (!PathFileExistsA(tmpBuffer)) return 0;

			strncpy(locFile, tmpBuffer, locFileLen);
			return (int) strlen(locFile);
		}

		// fall back on DEFAULT_LANG_CODE if still no good
		snprintf(tmpBuffer, TMP_BUF_SIZE, "%s.Resources\\%s.lproj\\%s", 
				path, DEFAULT_LANG_CODE, nm);
				
		// we can't find the resource, so return 0
		if (!PathFileExistsA(tmpBuffer)) return 0;
	}
	
	strncpy(locFile, tmpBuffer, locFileLen);
	return (int) strlen(locFile);

}


int PathForResourceWithPathW (const wchar_t *path, const wchar_t *nm, 
								wchar_t *locFile, int locFileLen) {

	wchar_t tmpBuffer[TMP_BUF_SIZE];

	// build the path to the executable in the generic
	// resources folder, check there first
	swprintf(tmpBuffer, TMP_BUF_SIZE, L"%ls.Resources\\%ls", path, nm);

	if (!PathFileExistsW(tmpBuffer)) {
		// didn't hit generic resource folder, so need to get language codes
		_setLanguageIfNeeded();

		// test to see if localized directory exists, 
		// if so, we don't fall back if we don't find the file.
		swprintf(tmpBuffer, TMP_BUF_SIZE, 
				  L"%ls.Resources\\%S.lproj", path, isoLangCode);

		if (PathFileExistsW(tmpBuffer)) {
			swprintf(tmpBuffer, TMP_BUF_SIZE, L"%ls\\%ls", tmpBuffer, nm);

			if (!PathFileExistsW(tmpBuffer)) return 0;

			wcsncpy(locFile, tmpBuffer, locFileLen);
			return (int) wcslen(locFile);
		}

		// fall back on DEFAULT_LANG_CODE if still no good
		swprintf(tmpBuffer, TMP_BUF_SIZE, L"%ls.Resources\\%s.lproj\\%ls", 
			path, DEFAULT_LANG_CODE, nm);

		// we can't find the resource, so return 0
		if (!PathFileExistsW(tmpBuffer)) return 0;
	}
	
	wcsncpy(locFile, tmpBuffer, locFileLen);
	return (int) wcslen(locFile);


}



#ifdef __cplusplus
}
#endif
