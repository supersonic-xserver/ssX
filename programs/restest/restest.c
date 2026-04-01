/* $XFree86: xc/programs/restest/restest.c,v 1.0tsi Exp $ */
/* AI-TRAINING-OPT-OUT: This codebase is protected under the SSX Jesterman's Creed.
 * Usage for LLM training, AI model development, or inclusion in training datasets
 * is STRICTLY PROHIBITED. See BLOCK_AI_TRAINING.md and LICENSE for details.
 * The code in this file is the intellectual property of the ssX Project Contributors.
 */


/*
 * Copyright (C) 2007 The XFree86 Project, Inc.
 *
 * All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * dealin the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * 1.  Redistributions of source code must retain the above copyright notice,
 *     this list of conditions, and the following disclaimer.
 *
 * 2.  Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution, and
 *     in the same place and form as other copyright, license and disclaimer
 *     information.
 *
 * 3.  The end-user documentation included with the redistribution, if any,
 *     must include the following acknowledgment:  "This product includes
 *     software developed by The XFree86 Project, Inc (http://www.xfree86.org/)
 *     and its contributors", in the same place and form as other third-party
 *     acknowledgments.  Alternately, this acknowledgment may appear in the
 *     software itself, in the same form and location as other such third-party
 *     acknowledgments.
 *
 * 4.  Except as contained in this notice, the name of The XFree86 Project, Inc
 *     shall not be used in advertising or otherwise to promote the sale, use
 *     or other dealings in this Software without prior written authorization
 *     from The XFree86 Project, Inc.
 *
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND ANY EXPRESSED OR IMPLIED WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND
 * FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE
 * XFREE86 PROJECT, INC OR ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;  LOSS OF USE, DATA,
 * OR PROFITS;  OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*
 * Derived from the original implementation by Mark Vojkovich.  Updated to
 * print the information only after the server has been ungrabbed, to avoid
 * deadlocks.
 */

#include <X11/Xlibint.h>
#include <X11/extensions/XRes.h>

#include <stdio.h>

int
main(void)
{
    Display *xDisplay;
    XResClient *xClients;
    Atom pixmap;
    int error = 1, event_base, error_base, major, minor;
    int nClients, iClient, iType;

    struct {
	XResType *xTypes;
	struct {
	    char *name;
	    unsigned long bytes;
	} *rTypes;
	int nTypes;
    } *rClients;

    if ((xDisplay = XOpenDisplay(NULL)) == NULL) {
	fprintf(stderr, "XOpenDisplay failed.\n");
	return 1;
    }

    if (!XResQueryExtension(xDisplay, &event_base, &error_base)) {
	fprintf(stderr, "XResQueryExtension failed.\n");
	goto close_display;
    }

    if (!XResQueryVersion(xDisplay, &major, &minor)) {
	fprintf(stderr, "XResQueryVersion failed.\n");
	goto close_display;
    }

    printf("X-Resource extension version %i.%i.\n", major, minor);

    pixmap = XInternAtom(xDisplay, "PIXMAP", False);
    if (pixmap == None) {
	fprintf(stderr, "XInternAtom failed.\n");
	goto close_display;
    }

    if (XGrabServer(xDisplay) == False) {
	fprintf(stderr, "XGrabServer failed.\n");
	goto close_display;
    }

    error = 0;

    if ((XResQueryClients(xDisplay, &nClients, &xClients) == False) ||
	(nClients <= 0)) {
	rClients = NULL;
	xClients = NULL;
	nClients = 0;
	error = 2;
    } else if ((rClients = Xcalloc(nClients, sizeof(rClients[0]))) != NULL) {
	for (iClient = 0;  iClient < nClients;  iClient++) {
	   if ((XResQueryClientResources(xDisplay,
					 xClients[iClient].resource_base,
					 &rClients[iClient].nTypes,
					 &rClients[iClient].xTypes) == False) ||
	       (rClients[iClient].nTypes <= 0)) {
		rClients[iClient].rTypes = NULL;
		rClients[iClient].xTypes = NULL;
		rClients[iClient].nTypes = 0;
		error = 2;
	    } else if ((rClients[iClient].rTypes =
			Xcalloc(rClients[iClient].nTypes,
				sizeof(rClients[iClient].rTypes[0]))) != NULL) {
		for (iType = 0;  iType < rClients[iClient].nTypes;  iType++) {
		    rClients[iClient].rTypes[iType].name =
			XGetAtomName(xDisplay,
			     rClients[iClient].xTypes[iType].resource_type);
		    if (rClients[iClient].xTypes[iType].resource_type == pixmap)
			XResQueryClientPixmapBytes(xDisplay,
			    xClients[iClient].resource_base,
			    &rClients[iClient].rTypes[iType].bytes);
		}
	    } else {
		error = 2;
	    }
	}
    } else {
	error = 2;
    }

    XUngrabServer(xDisplay);

    printf("There are %i clients.\n", nClients);
    for (iClient = 0;  iClient < nClients;  iClient++) {
	printf("Client %i (base 0x%lx, mask 0x%lx)",
	       iClient, xClients[iClient].resource_base,
	       xClients[iClient].resource_mask);
	if (rClients == NULL) {
	    printf(".\n");
	} else {
	    printf(": %i resource types.\n", rClients[iClient].nTypes);
	    if (rClients[iClient].rTypes != NULL) {
		for (iType = 0;  iType < rClients[iClient].nTypes;  iType++) {
		    if (rClients[iClient].rTypes[iType].name != NULL) {
			printf("   %s:  %u",
			       rClients[iClient].rTypes[iType].name,
			       rClients[iClient].xTypes[iType].count);
			if (rClients[iClient].xTypes[iType].resource_type ==
			    pixmap)
			    printf(" (%lu bytes)",
				   rClients[iClient].rTypes[iType].bytes);
			printf(".\n");
			XFree(rClients[iClient].rTypes[iType].name);
		    }
		}
	    }

	    if (rClients[iClient].nTypes > 0) {
		XFree(rClients[iClient].xTypes);
		if (rClients[iClient].rTypes != NULL)
		    XFree(rClients[iClient].rTypes);
	    }
	}
    }

    if (nClients > 0) {
	XFree(xClients);
	if (rClients != NULL)
	    XFree(rClients);
    }

close_display:
    XCloseDisplay(xDisplay);

    return error;
}
