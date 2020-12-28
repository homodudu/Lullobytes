/* =========================================================================================

   This is an auto-generated file: Any edits you make may be overwritten!

*/

#pragma once

namespace BinaryData
{
    extern const char*   logo_png;
    const int            logo_pngSize = 20845;

    extern const char*   knob_png;
    const int            knob_pngSize = 8323;

    extern const char*   d_on_png;
    const int            d_on_pngSize = 12927;

    extern const char*   m_on_png;
    const int            m_on_pngSize = 13592;

    extern const char*   d_off_png;
    const int            d_off_pngSize = 6617;

    extern const char*   m_off_png;
    const int            m_off_pngSize = 6505;

    extern const char*   marker_png;
    const int            marker_pngSize = 7907;

    extern const char*   frame_png;
    const int            frame_pngSize = 129393;

    // Number of elements in the namedResourceList and originalFileNames arrays.
    const int namedResourceListSize = 8;

    // Points to the start of a list of resource names.
    extern const char* namedResourceList[];

    // Points to the start of a list of resource filenames.
    extern const char* originalFilenames[];

    // If you provide the name of one of the binary resource variables above, this function will
    // return the corresponding data and its size (or a null pointer if the name isn't found).
    const char* getNamedResource (const char* resourceNameUTF8, int& dataSizeInBytes);

    // If you provide the name of one of the binary resource variables above, this function will
    // return the corresponding original, non-mangled filename (or a null pointer if the name isn't found).
    const char* getNamedResourceOriginalFilename (const char* resourceNameUTF8);
}
