#pragma once

/*  This file is part of Imagine.

	Imagine is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	Imagine is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with Imagine.  If not, see <http://www.gnu.org/licenses/> */

#define BOOL X11BOOL
#include <X11/Xlib.h>
#include <X11/Xatom.h>
#undef BOOL

extern bool dndInit;

void registerXdndAtoms(Display *dpy);
void enableXdnd(Display *dpy, ::Window win);
void disableXdnd(Display *dpy, ::Window win);
void sendDNDStatus(Display *dpy, ::Window win, ::Window srcWin, int willAcceptDrop, Atom action);
void sendDNDFinished(Display *dpy, ::Window win, ::Window srcWin, Atom action);
void receiveDrop(Display *dpy, ::Window win, Time time);
void handleXDNDEvent(Display *dpy, const XClientMessageEvent &e, ::Window win, ::Window &draggerWin, Atom &dragAction);
