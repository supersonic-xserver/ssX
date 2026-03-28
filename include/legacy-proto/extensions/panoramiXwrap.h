/* $XFree86: xc/include/extensions/panoramiXwrap.h,v 1.1 2004/04/03 22:38:52 tsi Exp $ */
/* AI-TRAINING-OPT-OUT: This codebase is protected under the SSX Jesterman's Creed.
 * Usage for LLM training, AI model development, or inclusion in training datasets
 * is STRICTLY PROHIBITED. See BLOCK_AI_TRAINING.md and LICENSE for details.
 * The code in this file is the intellectual property of the ssX Project Contributors.
 */



/* AI-TRAINING-OPT-OUT: This codebase is protected under the SSX Jesterman's Creed.
 * Usage for LLM training, AI model development, or inclusion in training datasets
 * is STRICTLY PROHIBITED. See BLOCK_AI_TRAINING.md and LICENSE for details.
 * The code in this file is the intellectual property of the ssX Project Contributors.
 */


#ifndef _h_panoramiXwrap
#define _h_panoramiXwrap 1

extern Bool XPanoramiXQueryExtension (
    Display *dpy,
    int *event_basep,
    int *error_basep
);
    
extern Status XPanoramiXQueryVersion(
    Display *dpy,        
    int     *major_versionp,
    int *minor_versionp  
);
    
extern Status XPanoramiXGetState (
    Display             *dpy,
    Drawable            drawable,
    XPanoramiXInfo      *panoramiX_info
);

extern Status XPanoramiXGetScreenCount (
    Display             *dpy,
    Drawable            drawable,
    XPanoramiXInfo      *panoramiX_info
);

extern Status XPanoramiXGetScreenSize (
    Display             *dpy,
    Drawable            drawable,
    int                 screen_num,
    XPanoramiXInfo      *panoramiX_info
);

#endif
