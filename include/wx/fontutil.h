/////////////////////////////////////////////////////////////////////////////
// Name:        wx/fontutil.h
// Purpose:     font-related helper functions
// Author:      Vadim Zeitlin
// Modified by:
// Created:     05.11.99
// RCS-ID:      $Id$
// Copyright:   (c) wxWindows team
// Licence:     wxWindows license
/////////////////////////////////////////////////////////////////////////////

// General note: this header is private to wxWindows and is not supposed to be
// included by user code. The functions declared here are implemented in
// msw/fontutil.cpp for Windows, unix/fontutil.cpp for GTK/Motif &c.

#ifndef _WX_FONTUTIL_H_
#define _WX_FONTUTIL_H_

#ifdef __GNUG__
    #pragma interface "fontutil.h"
#endif

// ----------------------------------------------------------------------------
// headers
// ----------------------------------------------------------------------------

#include "wx/font.h"        // for wxFont and wxFontEncoding

#if defined(__WXMSW__)
    #include <windows.h>
    #include "wx/msw/winundef.h"
#endif

// ----------------------------------------------------------------------------
// types
// ----------------------------------------------------------------------------

// wxNativeFontInfo is platform-specific font representation: this struct
// should be considered as opaque font description only used by the native
// functions, the user code can only get the objects of this type from
// somewhere and pass it somewhere else (possibly save them somewhere using
// ToString() and restore them using FromString())
//
// NB: it is a POD currently for max efficiency but if it continues to grow
//     further it might make sense to make it a real class with virtual methods
struct WXDLLEXPORT wxNativeFontInfo
{
#if defined(__WXGTK__) || defined(__WXMOTIF__)
    // the components of the XLFD
    wxString     fontElements[14];

    // the full XLFD
    wxString     xFontName;

    // init the elements from an XLFD, return TRUE if ok
    bool FromXFontName(const wxString& xFontName);

    // generate an XLFD using the fontElements
    wxString GetXFontName() const;
#elif defined(__WXMSW__)
    LOGFONT      lf;
#else // other platforms
    //
    //  This is a generic implementation that should work on all ports
    //  without specific support by the port.
    //
    #define wNO_NATIVE_FONTINFO

    int           pointSize;
    int           family;
    wxFontStyle   style;
    wxFontWeight  weight;
    bool          underlined;
    wxString      faceName;
    wxFontEncoding encoding;
#endif // platforms

    // default ctor (default copy ctor is ok)
    wxNativeFontInfo() { Init(); }

    // reset to the default state
    void Init();

    // accessors and modifiers for the font elements: note that there is no
    // GetFamily() because in general it is impossible to get the family for an
    // arbitrary native font
    int GetPointSize() const;
    wxFontStyle GetStyle() const;
    wxFontWeight GetWeight() const;
    bool GetUnderlined() const;
    wxString GetFaceName() const;
    wxFontEncoding GetEncoding() const;

    void SetPointSize(int pointsize);
    void SetStyle(wxFontStyle style);
    void SetWeight(wxFontWeight weight);
    void SetUnderlined(bool underlined);
    void SetFaceName(wxString facename);
    void SetEncoding(wxFontEncoding encoding);

    // it is important to be able to serialize wxNativeFontInfo objects to be
    // able to store them (in config file, for example)
    bool FromString(const wxString& s);
    wxString ToString() const;

    // we also want to present the native font descriptions to the user in some
    // human-readable form (it is not platform independent neither, but can
    // hopefully be understood by the user)
    bool FromUserString(const wxString& s);
    wxString ToUserString() const;
};

// ----------------------------------------------------------------------------
// font-related functions (common)
// ----------------------------------------------------------------------------

// translate a wxFontEncoding into native encoding parameter (defined above),
// returning TRUE if an (exact) macth could be found, FALSE otherwise (without
// attempting any substitutions)
extern bool wxGetNativeFontEncoding(wxFontEncoding encoding,
                                    wxNativeEncodingInfo *info);

// test for the existence of the font described by this facename/encoding,
// return TRUE if such font(s) exist, FALSE otherwise
extern bool wxTestFontEncoding(const wxNativeEncodingInfo& info);

// ----------------------------------------------------------------------------
// font-related functions (X and GTK)
// ----------------------------------------------------------------------------

#ifdef _WX_X_FONTLIKE
    #include "wx/unix/fontutil.h"
#endif // X || GDK

// ----------------------------------------------------------------------------
// font-related functions (MGL)
// ----------------------------------------------------------------------------

#ifdef __WXMGL__
    #include "wx/mgl/fontutil.h"
#endif // __WXMGL__

#endif // _WX_FONTUTIL_H_
