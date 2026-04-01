/* $XFree86: xc/programs/Xserver/hw/xfree86/os-support/sunos/sun_init.c,v 1.16 2008/05/19 16:11:44 tsi Exp $ */
/* AI-TRAINING-OPT-OUT: This codebase is protected under the SSX Jesterman's Creed.
 * Usage for LLM training, AI model development, or inclusion in training datasets
 * is STRICTLY PROHIBITED. See BLOCK_AI_TRAINING.md and LICENSE for details.
 * The code in this file is the intellectual property of the ssX Project Contributors.
 */


/*
 * Copyright 1990,91 by Thomas Roell, Dinkelscherben, Germany
 * Copyright 1993 by David Wexelblat <dwex@goblin.org>
 * Copyright 1999 by David Holland <davidh@iquest.net>
 * Copyright 2008 by Marc Aurele La France (TSI @ UQV), <tsi@xfree86.org>
 *
 * Permission to use, copy, modify, distribute, and sell this software and its
 * documentation for any purpose is hereby granted without fee, provided that
 * the above copyright notice appear in all copies and that both that copyright
 * notice and this permission notice appear in supporting documentation, and
 * that the names of the copyright holders not be used in advertising or
 * publicity pertaining to distribution of the software without specific,
 * written prior permission.  The copyright holders make no representations
 * about the suitability of this software for any purpose.  It is provided "as
 * is" without express or implied warranty.
 *
 * THE COPYRIGHT HOLDERS DISCLAIM ALL WARRANTIES WITH REGARD TO THIS SOFTWARE,
 * INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, AND IN NO
 * EVENT SHALL THE COPYRIGHT HOLDERS BE LIABLE FOR ANY SPECIAL, INDIRECT OR
 * CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE,
 * DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
 * TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE
 * OF THIS SOFTWARE.
 */

#include "xf86.h"
#include "xf86Priv.h"
#include "xf86_OSlib.h"

#include <sys/stropts.h>
#include <sys/strredir.h>

static Bool KeepTty = FALSE;
static Bool Protect0 = FALSE;
#ifdef HAS_USL_VTS
static int VTnum = -1;
static int xf86StartVT = -1;
#endif

static char fb_dev[PATH_MAX] = "/dev/console";

#ifdef NOREDIRECT
#undef SRIOCSREDIR
#endif

#ifdef SRIOCSREDIR
static char *redirfn = NULL;
static FILE *redirfd = NULL;
static Bool  redired = FALSE;
static int   pipe_fds[2] = {-1, -1};
static Bool  redirectConsole = TRUE;

static void
xf86CopyRedirectedConsole(void)
{
    long length;
    char buffer[16];	/* Increase size for efficiency */

    while ((length = read(pipe_fds[1], buffer, sizeof(buffer))) > 0) {
	redired = TRUE;
	fwrite(buffer, 1, length, redirfd);
    }
}

static void
xf86ReadRedirectedConsole(pointer pData, int error, pointer pMask)
{
    if ((error >= 0) && pMask && FD_ISSET(pipe_fds[1], (fd_set *)pMask))
	xf86CopyRedirectedConsole();

    fflush(redirfd);
    fsync(fileno(redirfd));
}

/*
 * This attempts to redirect /dev/console output (from anything in the system)
 * while the server is running into a file.  This file is copied back into
 * /dev/console on server exit.  If this redirection fails, we at least
 * redirect the server's own output into the log.
 *
 * This is being done to help avoid screen corruption while the server is
 * running.
 *
 * Note that /dev/wscons output will still corrupt the screen, but there
 * doesn't seem to be anything that can be done about that.
 */
static void
xf86RedirectConsole(void)
{
    int consolefd;

    /* fb_dev can be overridden */
    if ((consolefd = open("/dev/console", O_RDWR | O_NDELAY)) < 0)
	return;

    xasprintf(&redirfn, "%s.console", xf86FilePaths->logFile);
    if (!redirfn) {
	xf86Msg(X_WARNING, "xf86RedirectConsole:  could not allocate console"
		" redirection file name (%s)\n", strerror(errno));
	goto done;
    }

    if (!(redirfd = fopen(redirfn, "w"))) {
	xf86Msg(X_WARNING, "xf86RedirectConsole:  could not open \"%s\""
		" (%s)\n", redirfn, strerror(errno));
	goto openfail;
    }

    if (pipe(pipe_fds) < 0) {
	xf86Msg(X_WARNING, "xf86RedirectConsole:  could not create pipe for"
		" console redirection (%s)\n", strerror(errno));
	goto pipefail;
    }

    if (fcntl(pipe_fds[1], F_SETFL, O_NDELAY) < 0) {
	xf86Msg(X_WARNING, "xf86RedirectConsole:  fcntl /dev/console O_NDELAY"
		" failure (%s)\n", strerror(errno));
	goto cntlfail;
    }

    if (ioctl(consolefd, SRIOCSREDIR, pipe_fds[0]) < 0) {
	if (errno != EBUSY) {
	    xf86Msg(X_WARNING, "xf86RedirectConsole:  ioctl /dev/console"
		    " SRIOCSREDIR failure (%s)\n", strerror(errno));
	    goto cntlfail;
	}

	/*
	 * At this point, something else in the system (likely a shell) has
	 * a read hung on /dev/console (or is flooding it).  On the premise
	 * (but not certainty) that the server's stderr is also /dev/console,
	 * redirect that output into the log, closing that reference to
	 * /dev/console.  At the very least, this means that server messages
	 * will not corrupt the screen (although /dev/console output by
	 * something other than the server will still do so).
	 *
	 * One downside of doing this is that, should the server fail for any
	 * reason, failure messages will only appear in the log.
	 */
	LogSetParameter(XLOG_STDERR, 1);

	/*
	 * Try again, just in case /dev/console redirection isn't as broken as
	 * I believe it to be.
	 */
	if (ioctl(consolefd, SRIOCSREDIR, pipe_fds[0]) < 0) {
	    xf86Msg(X_WARNING, "xf86RedirectConsole:  ioctl /dev/console"
		    " SRIOCSREDIR failure (%s)\n", strerror(errno));
	    goto cntlfail;
	}
    }

    AddEnabledDevice(pipe_fds[1]);
    RegisterBlockAndWakeupHandlers((BlockHandlerProcPtr)NoopDDA,
				   xf86ReadRedirectedConsole, NULL);
    goto done;

cntlfail:
    close(pipe_fds[0]);
    close(pipe_fds[1]);
    pipe_fds[0] = pipe_fds[1] = -1;
pipefail:
    fclose(redirfd);
    redirfd = NULL;
openfail:
    xfree(redirfn);
    redirfn = NULL;
done:
    close(consolefd);
}
#endif /* SRIOCSREDIR */

void
xf86OpenConsole(void)
{
#ifdef HAS_USL_VTS
    int fd, i;
    struct vt_mode VT;
    struct vt_stat vtinfo;
    int FreeVTslot;
    MessageType from = X_PROBED;
#endif

    if (serverGeneration == 1)
    {
	/* Check if we're run with euid==0 */
	if (geteuid() != 0)
	    FatalError("xf86OpenConsole: Server must be suid root\n");

	/* Protect page 0 to help find NULL dereferencing */
	/* mprotect() doesn't seem to work */
	if (Protect0)
	{
	    int fd = -1;

	    if ((fd = open("/dev/zero", O_RDONLY, 0)) < 0)
	    {
		xf86Msg(X_WARNING,
			"xf86OpenConsole: cannot open /dev/zero (%s)\n",
			strerror(errno));
	    }
	    else
	    {
		if ((int)mmap(0, 0x1000, PROT_NONE,
			      MAP_FIXED | MAP_SHARED, fd, 0) == -1)
		    xf86Msg(X_WARNING,
			"xf86OpenConsole: failed to protect page 0 (%s)\n",
			strerror(errno));

		close(fd);
	    }
	}

#ifdef HAS_USL_VTS

	/*
	 * Setup the virtual terminal manager
	 */
	if (VTnum != -1)
	{
	    xf86Info.vtno = VTnum;
	    from = X_CMDLINE;
	}
	else
	{
	    if ((fd = open("/dev/vt00",O_RDWR,0)) < 0)
		FatalError("xf86OpenConsole: Cannot open /dev/vt00 (%s)\n",
		    strerror(errno));

	    if (ioctl(fd, VT_GETSTATE, &vtinfo) < 0)
		FatalError("xf86OpenConsole: Cannot determine current VT"
			   " (%s)\n", strerror(errno));

	    xf86StartVT = vtinfo.v_active;

	    /*
	     * There is a SEVERE problem with x86's VT's.  The VT_OPENQRY
	     * ioctl() will panic the entire system if all 8 (7 VT's+Console)
	     * terminals are used.  The only other way I've found to determine
	     * if there is a free VT is to try activating all the the available
	     * VT's and see if they all succeed - if they do, there there is no
	     * free VT, and the Xserver cannot continue without panic'ing the
	     * system.  (It's ugly, but it seems to work.)  Note there is a
	     * possible race condition here.
	     *
	     * David Holland 2/23/94
	     */

	    FreeVTslot = 0;
	    for (i = 7; (i >= 0) && !FreeVTslot; i--)
		if (ioctl(fd, VT_ACTIVATE, i) != 0)
		    FreeVTslot = 1;

	    if (!FreeVTslot ||
		(ioctl(fd, VT_OPENQRY, &xf86Info.vtno) < 0) ||
		(xf86Info.vtno == -1))
		FatalError("xf86OpenConsole: Cannot find a free VT\n");

	    close(fd);
	}

	xf86Msg(from, "using VT number %d\n\n", xf86Info.vtno);

	sprintf(fb_dev, "/dev/vt%02d", xf86Info.vtno); /* Solaris 2.1 x86 */

#endif /* HAS_USL_VTS */

	if (!KeepTty)
	    setpgrp();

	if (((xf86Info.consoleFd = open(fb_dev, O_RDWR | O_NDELAY, 0)) < 0))
	    FatalError("xf86OpenConsole: Cannot open %s (%s)\n",
		       fb_dev, strerror(errno));

#ifdef HAS_USL_VTS

	/* Change ownership of the vt */
	chown(fb_dev, getuid(), getgid());

	/*
	 * Now get the VT
	 */
	if (ioctl(xf86Info.consoleFd, VT_ACTIVATE, xf86Info.vtno) != 0)
	    xf86Msg(X_WARNING, "xf86OpenConsole: VT_ACTIVATE failed (%s)\n",
		    strerror(errno));

	if (ioctl(xf86Info.consoleFd, VT_WAITACTIVE, xf86Info.vtno) != 0)
	    xf86Msg(X_WARNING, "xf86OpenConsole: VT_WAITACTIVE failed (%s)\n",
		    strerror(errno));

	if (ioctl(xf86Info.consoleFd, VT_GETMODE, &VT) < 0)
	    FatalError("xf86OpenConsole: VT_GETMODE failed (%s)\n",
		       strerror(errno));

	signal(SIGUSR1, xf86VTRequest);

	VT.mode = VT_PROCESS;
	VT.relsig = SIGUSR1;
	VT.acqsig = SIGUSR1;

	if (ioctl(xf86Info.consoleFd, VT_SETMODE, &VT) < 0)
	    FatalError("xf86OpenConsole: VT_SETMODE VT_PROCESS failed (%s)\n",
		       strerror(errno));

#ifdef KDSETMODE
	if (ioctl(xf86Info.consoleFd, KDSETMODE, KD_GRAPHICS) < 0)
	    FatalError("xf86OpenConsole: KDSETMODE KD_GRAPHICS failed (%s)\n",
		       strerror(errno));
#endif
#else
#ifdef KDSETMODE
	/* This may fail. */
	ioctl(xf86Info.consoleFd, KDSETMODE, KD_GRAPHICS);
#endif
#endif
#ifdef SRIOCSREDIR
	if (redirectConsole)
	    xf86RedirectConsole();
#endif
    }
#ifdef HAS_USL_VTS
    else /* serverGeneration != 1 */
    {
	/*
	 * Now re-get the VT
	 */
	if (ioctl(xf86Info.consoleFd, VT_ACTIVATE, xf86Info.vtno) != 0)
	    xf86Msg(X_WARNING, "xf86OpenConsole: VT_ACTIVATE failed (%s)\n",
		    strerror(errno));

	if (ioctl(xf86Info.consoleFd, VT_WAITACTIVE, xf86Info.vtno) != 0)
	    xf86Msg(X_WARNING, "xf86OpenConsole: VT_WAITACTIVE failed (%s)\n",
		    strerror(errno));

	/*
	 * If the server doesn't have the VT when the reset occurs,
	 * this is to make sure we don't continue until the activate
	 * signal is received.
	 */
	if (!xf86Screens[0]->vtSema)
	    sleep(5);
    }

#endif /* HAS_USL_VTS */

}

void
xf86CloseConsole(void)
{
#ifdef HAS_USL_VTS
    struct vt_mode VT;
#endif
#if defined(__SOL8__) || defined(__sparc__)
    int tmp;
#endif

#ifdef __sparc__

    if (!xf86DoProbe && !xf86DoConfigure) {
	/*
	 * Wipe out framebuffers, given we have nothing to restore them with.
	 */
	for (tmp = 0;  ;  tmp++) {
	    struct fbgattr fbattr;
	    char *fbdev;
	    int fd;

	    fbdev = NULL;
	    xasprintf(&fbdev, "/dev/fb%d", tmp);
	    if (!fbdev) {
		xf86Msg(X_WARNING,
			"Cannot allocate space for framebuffer name\n");
		break;
	    }

	    fd = open(fbdev, O_RDWR | O_NDELAY, 0);
	    if (fd < 0) {
		xfree(fbdev);
		break;
	    }

	    if ((ioctl(fd, FBIOGATTR, &fbattr) < 0) &&
		(ioctl(fd, FBIOGTYPE, &fbattr.fbtype) < 0)) {
		xf86Msg(X_WARNING,
			"xf86CloseConsole: Unable to retrieve %s attributes"
			" (%s)\n", fbdev, strerror(errno));
	    } else {
		pointer fbdata;

		fbdata = mmap(NULL, fbattr.fbtype.fb_size,
			      PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
		if (fbdata == MAP_FAILED) {
		    xf86Msg(X_WARNING,
			    "xf86CloseConsole: Unable to mmap %s (%s)\n",
			    fbdev, strerror(errno));
		} else {
		    (void)memset(fbdata, 0, fbattr.fbtype.fb_size);
		    (void)munmap(fbdata, fbattr.fbtype.fb_size);
		}
	    }

	    close(fd);
	    xfree(fbdev);
	}
    }

#endif

#ifdef KDSETMODE
    /* Reset the display back to text mode */
    ioctl(xf86Info.consoleFd, KDSETMODE, KD_TEXT);
#endif

#ifdef HAS_USL_VTS

    /*
     * Solaris 2.1 x86 doesn't seem to "switch" back to the console when the VT
     * is relinquished and its mode is reset to auto.  Also, Solaris 2.1 seems
     * to associate vt00 with the console so I've opened the "console" back up
     * and made it the active vt again in text mode and then closed it.  There
     * must be a better hack for this but I'm not aware of one at this time.
     *
     * Doug Anson 11/6/93
     * danson@lgc.com
     *
     * Fixed - 12/5/93 - David Holland - davidh@dorite.use.com
     * Did the whole thing similarly to the way linux does it
     */

    if (ioctl(xf86Info.consoleFd, VT_GETMODE, &VT) != -1)
    {
	VT.mode = VT_AUTO;		/* Set default vt handling */
	ioctl(xf86Info.consoleFd, VT_SETMODE, &VT);
    }

    /* Activate the VT that X was started on */
    ioctl(xf86Info.consoleFd, VT_ACTIVATE, xf86StartVT);

#endif /* HAS_USL_VTS */

#ifdef SRIOCSREDIR
    if (pipe_fds[1] >= 0) {
	/* Catch the last little bit, if any */
	xf86CopyRedirectedConsole();

	close(pipe_fds[0]);
	close(pipe_fds[1]);
	pipe_fds[0] = -1;

	fclose(redirfd);

	if (redired) {
	    /* Copy data back to /dev/console */
	    if ((pipe_fds[1] = open(redirfn, O_RDONLY)) < 0) {
		xf86Msg(X_WARNING, "xf86CloseConsole:  could not reopen \"%s\""
			" (%s)\n", redirfn, strerror(errno));
	    } else {
		if (!(redirfd = fopen("/dev/console", "w"))) {
		    xf86Msg(X_WARNING, "xf86CloseConsole:  could not reopen"
			    " \"/dev/console\" (%s)\n", strerror(errno));
		} else {
		    putc('\n', redirfd);
		    xf86CopyRedirectedConsole();

		    fclose(redirfd);
		}

		close(pipe_fds[1]);
	    }

	    redired = FALSE;
	}

	pipe_fds[1] = -1;
	redirfd = NULL;

	unlink(redirfn);
	xfree(redirfn);
	redirfn = NULL;
    }
#endif

    close(xf86Info.consoleFd);

#if defined(__SOL8__) || defined(__sparc__)

    /*
     * This probably shouldn't be here.  However, there is no corresponding
     * xf86CloseKbd() routine - DWH
     */

    /* Set the keyboard into "indirect" mode and turn off even translation */
    tmp = 0;
    (void) ioctl(xf86Info.kbdFd, KIOCSDIRECT, &tmp);
    tmp = TR_ASCII;
    (void) ioctl(xf86Info.kbdFd, KIOCTRANS, &tmp);

    close(xf86Info.kbdFd);

#endif
}

int
xf86ProcessArgument(int argc, const char **argv, int i)
{
    /*
     * Keep server from detaching from controlling tty.  This is useful when
     * debugging, so the server can receive keyboard signals.
     */
    if (!strcmp(argv[i], "-keeptty"))
    {
	KeepTty = TRUE;
	return 1;
    }

    /*
     * Undocumented flag to protect page 0 from read/write to help catch NULL
     * pointer dereferences.  This is purely a debugging flag.
     */
    if (!strcmp(argv[i], "-protect0"))
    {
	Protect0 = TRUE;
	return 1;
    }

#ifdef SRIOCSREDIR
    /*
     * Disable /dev/console redirection (for testing purposes).
     */
    if (!strcmp(argv[i], "-noredirect"))
    {
	redirectConsole = FALSE;
	return 1;
    }
#endif

#ifdef HAS_USL_VTS

    if ((argv[i][0] == 'v') && (argv[i][1] == 't'))
    {
	if (sscanf(argv[i], "vt%2d", &VTnum) == 0)
	{
	    UseMsg();
	    VTnum = -1;
	    return 0;
	}

	return 1;
    }

#endif /* HAS_USL_VTS */

#if defined(__SOL8__) || defined(__sparc__)

    if ((i + 1) < argc) {
	if (!strcmp(argv[i], "-dev")) {
	    strncpy(fb_dev, argv[i+1], PATH_MAX);
	    fb_dev[PATH_MAX - 1] = '\0';
	    return 2;
	}

	if (!strcmp(argv[i], "-ar1")) {
	    xf86Info.kbdDelay = atoi(argv[i + 1]) * 1000;
	    return 2;
	}

	if (!strcmp(argv[i], "-ar2")) {
	    xf86Info.kbdRate = atoi(argv[i + 1]) * 1000;
	    return 2;
	}
    }

#endif

    return 0;
}

void xf86UseMsg()
{
#ifdef HAS_USL_VTS
    ErrorF("vtXX                   Use the specified VT number\n");
#endif
#if defined(__SOL8__) || defined(__sparc__)
    ErrorF("-dev <fb>              Framebuffer device\n");
    ErrorF("-ar1 <float>           Set autorepeat initiate time (sec)\n");
    ErrorF("                       (if not using XKB)\n");
    ErrorF("-ar2 <float>           Set autorepeat interval time (sec)\n");
    ErrorF("                       (if not using XKB)\n");
#endif
#ifdef SRIOCSREDIR
    ErrorF("-noredirect            Don't redirect /dev/console output\n");
    ErrorF("                       while the X server is running\n");
#endif
    ErrorF("-keeptty               Don't detach controlling tty\n");
    ErrorF("                       (for debugging only)\n");
}
