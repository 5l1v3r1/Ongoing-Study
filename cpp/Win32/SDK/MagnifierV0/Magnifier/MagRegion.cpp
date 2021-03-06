#include "stdafx.h"
#include "MagRegion.h"
#include "Common/Canvas.h"
#include "Common/Utility.h"


namespace Mag
{

void DynamicRegion::Draw(HDC hdc, const RECT &rcDest, const RECT &rcMag)
{
    assert(hdc != NULL);

    // GetWindowDC(GetDesktopWindow());
    // GetDC(NULL);
    HDC hdcScreen = CreateDC(_T("DISPLAY"), NULL, NULL, NULL);
    assert(hdcScreen != NULL);

    StretchBlt(hdc, rcDest.left, rcDest.top, Utility::RCWidth(rcDest), Utility::RCHeight(rcDest), 
        hdcScreen, rcMag.left, rcMag.top, Utility::RCWidth(rcMag), Utility::RCHeight(rcMag), 
        SRCCOPY);

    DeleteDC(hdcScreen);
}

SnapshotRegion::SnapshotRegion()
{
    HDC hdcScreen = CreateDC(_T("DISPLAY"), NULL, NULL, NULL);
    assert(hdcScreen != NULL);

    // GetDeviceCaps(hdcScreen, HORZRES); GetDeviceCaps(hdcScreen, VERTRES));
    // MonitorFromWindow(hwnd, MONITOR_DEFAULTTONEAREST); GetMonitorInfo;
    int cxScreen = GetSystemMetrics(SM_CXSCREEN);
    int cyScreen = GetSystemMetrics(SM_CYSCREEN);

    m_ScreenCache.reset(new Utility::Canvas(hdcScreen, cxScreen, cyScreen));
    assert(m_ScreenCache != nullptr);

    BitBlt(m_ScreenCache->GetHDC(), 0, 0, cxScreen, cyScreen, 
        hdcScreen, 0, 0, SRCCOPY);

    DeleteDC(hdcScreen);
}

void SnapshotRegion::Draw(HDC hdc, const RECT &rcDest, const RECT &rcMag)
{
    assert(hdc != NULL);
    assert(m_ScreenCache != nullptr);

    StretchBlt(hdc, rcDest.left, rcDest.top, Utility::RCWidth(rcDest), Utility::RCHeight(rcDest), 
        m_ScreenCache->GetHDC(), rcMag.left, rcMag.top, Utility::RCWidth(rcMag), Utility::RCHeight(rcMag), 
        SRCCOPY);
}

} // namespace Mag
