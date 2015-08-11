/*
 * Copyright (c) 1997-2004 Apple Computer, Inc. All rights reserved.
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
    
$Log: FourthPage.cpp,v $
Revision 1.5  2005/01/06 08:17:08  shersche
Display the selected protocol ("Raw", "LPR", "IPP") rather than the port name

Revision 1.4  2004/07/13 20:15:04  shersche
<rdar://problem/3726363> Load large font name from resource
Bug #: 3726363

Revision 1.3  2004/07/12 06:59:03  shersche
<rdar://problem/3723695> Use resource strings for Yes/No
Bug #: 3723695

Revision 1.2  2004/06/26 23:27:12  shersche
support for installing multiple printers of the same name

Revision 1.1  2004/06/18 04:36:57  rpantos
First checked in


*/

#include "stdafx.h"
#include "PrinterSetupWizardApp.h"
#include "PrinterSetupWizardSheet.h"
#include "FourthPage.h"


// CFourthPage dialog

IMPLEMENT_DYNAMIC(CFourthPage, CPropertyPage)
CFourthPage::CFourthPage()
	: CPropertyPage(CFourthPage::IDD),
		m_initialized(false)
{
	CString fontName;

	m_psp.dwFlags &= ~(PSP_HASHELP);
	m_psp.dwFlags |= PSP_DEFAULT|PSP_HIDEHEADER;

	fontName.LoadString(IDS_LARGE_FONT);

	// create the large font
	m_largeFont.CreateFont(-16, 0, 0, 0, 
		FW_BOLD, FALSE, FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, 
		CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, fontName);
}

CFourthPage::~CFourthPage()
{
}

void CFourthPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_GOODBYE, m_goodbye);
	DDX_Control(pDX, IDC_PRINTER_NAME, m_printerNameCtrl);
	DDX_Control(pDX, IDC_PRINTER_MANUFACTURER, m_printerManufacturerCtrl);
	DDX_Control(pDX, IDC_PRINTER_MODEL, m_printerModelCtrl);
	DDX_Control(pDX, IDC_PRINTER_PROTOCOL, m_printerProtocolCtrl);
	DDX_Control(pDX, IDC_PRINTER_DEFAULT, m_printerDefault);
}


BEGIN_MESSAGE_MAP(CFourthPage, CPropertyPage)
END_MESSAGE_MAP()


// CFourthPage message handlers
OSStatus 
CFourthPage::OnInitPage()
{
	return kNoErr;
}


BOOL
CFourthPage::OnSetActive()
{
	CPrinterSetupWizardSheet	*	psheet;
	CString							goodbyeText;
	Printer						*	printer;
	CString							defaultText;

	psheet = reinterpret_cast<CPrinterSetupWizardSheet*>(GetParent());
	require_quiet( psheet, exit );
   
	printer = psheet->GetSelectedPrinter();
	require_quiet( psheet, exit );
	
	psheet->SetWizardButtons(PSWIZB_BACK|PSWIZB_FINISH);

	if (m_initialized == false)
	{
		m_initialized = true;
		OnInitPage();
	}

	m_goodbye.SetFont(&m_largeFont);

	goodbyeText.LoadString(IDS_GOODBYE);
	m_goodbye.SetWindowText(goodbyeText);

	m_printerNameCtrl.SetWindowText( printer->actualName );
	m_printerManufacturerCtrl.SetWindowText ( printer->manufacturer );
	m_printerModelCtrl.SetWindowText ( printer->model );

	Service * service = printer->services.front();
	require_quiet( service, exit );
	m_printerProtocolCtrl.SetWindowText ( service->protocol );

	if (printer->deflt)
	{
		defaultText.LoadString(IDS_YES);
	}
	else
	{
		defaultText.LoadString(IDS_NO);
	}

	m_printerDefault.SetWindowText ( defaultText );

exit:

	return CPropertyPage::OnSetActive();
}
