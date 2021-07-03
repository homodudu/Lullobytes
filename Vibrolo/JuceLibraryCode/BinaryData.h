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
    const int            t_on_pngSize = 16882;

    extern const char*   v_off_png;
    const int            v_off_pngSize = 7170;

    extern const char*   v_on_png;
    const int            v_on_pngSize = 17877;

    extern const char*   AAFilter_lo;
    const int            AAFilter_loSize = 268;

    extern const char*   BPMDetect_lo;
    const int            BPMDetect_loSize = 270;

    extern const char*   cpu_detect_x86_lo;
    const int            cpu_detect_x86_loSize = 280;

    extern const char*   FIFOSampleBuffer_lo;
    const int            FIFOSampleBuffer_loSize = 284;

    extern const char*   FIRFilter_lo;
    const int            FIRFilter_loSize = 270;

    extern const char*   InterpolateCubic_lo;
    const int            InterpolateCubic_loSize = 284;

    extern const char*   InterpolateLinear_lo;
    const int            InterpolateLinear_loSize = 286;

    extern const char*   InterpolateShannon_lo;
    const int            InterpolateShannon_loSize = 288;

    extern const char*   libSoundTouch_la;
    const int            libSoundTouch_laSize = 933;

    extern const char*   libSoundTouchMMX_la;
    const int            libSoundTouchMMX_laSize = 878;

    extern const char*   libSoundTouchMMX_lammx_optimized_lo;
    const int            libSoundTouchMMX_lammx_optimized_loSize = 318;

    extern const char*   libSoundTouchSSE_la;
    const int            libSoundTouchSSE_laSize = 878;

    extern const char*   libSoundTouchSSE_lasse_optimized_lo;
    const int            libSoundTouchSSE_lasse_optimized_loSize = 318;

    extern const char*   Makefile;
    const int            MakefileSize = 27353;

    extern const char*   Makefile_am;
    const int            Makefile_amSize = 2876;

    extern const char*   Makefile_in;
    const int            Makefile_inSize = 28153;

    extern const char*   PeakFinder_lo;
    const int            PeakFinder_loSize = 272;

    extern const char*   RateTransposer_lo;
    const int            RateTransposer_loSize = 280;

    extern const char*   SoundTouch_lo;
    const int            SoundTouch_loSize = 272;

    extern const char*   SoundTouch_sln;
    const int            SoundTouch_slnSize = 1422;

    extern const char*   SoundTouch_vcxproj;
    const int            SoundTouch_vcxprojSize = 20341;

    extern const char*   TDStretch_lo;
    const int            TDStretch_loSize = 270;

    // Number of elements in the namedResourceList and originalFileNames arrays.
    const int namedResourceListSize = 35;

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
