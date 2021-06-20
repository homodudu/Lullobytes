/* =========================================================================================

   This is an auto-generated file: Any edits you make may be overwritten!

*/

#pragma once

namespace BinaryData
{
    extern const char*   frame_png;
    const int            frame_pngSize = 14300;

    extern const char*   handle_png;
    const int            handle_pngSize = 11901;

    extern const char*   info_png;
    const int            info_pngSize = 145793;

    extern const char*   info_button_off_png;
    const int            info_button_off_pngSize = 16403;

    extern const char*   info_button_on_png;
    const int            info_button_on_pngSize = 20609;

    extern const char*   knob_png;
    const int            knob_pngSize = 8323;

    extern const char*   link_button_off_png;
    const int            link_button_off_pngSize = 26862;

    extern const char*   link_button_on_png;
    const int            link_button_on_pngSize = 37218;

    extern const char*   marker_png;
    const int            marker_pngSize = 7907;

    extern const char*   t_off_png;
    const int            t_off_pngSize = 6238;

    extern const char*   t_on_png;
    const int            t_on_pngSize = 18764;

    extern const char*   v_off_png;
    const int            v_off_pngSize = 7170;

    extern const char*   v_on_png;
    const int            v_on_pngSize = 19902;

    // Number of elements in the namedResourceList and originalFileNames arrays.
    const int namedResourceListSize = 13;

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
