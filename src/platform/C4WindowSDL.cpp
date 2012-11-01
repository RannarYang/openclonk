/*
 * OpenClonk, http://www.openclonk.org
 *
 * Copyright (c) 2006  Julian Raschke
 * Copyright (c) 2010  Peter Wortmann
 * Copyright (c) 2010  Benjamin Herr
 * Copyright (c) 2010  Armin Burgmeier
 * Copyright (c) 2011  Günther Brammer
 * Copyright (c) 2005-2009, RedWolf Design GmbH, http://www.clonk.de
 *
 * Portions might be copyrighted by other authors who have contributed
 * to OpenClonk.
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 * See isc_license.txt for full license and disclaimer.
 *
 * "Clonk" is a registered trademark of Matthes Bender.
 * See clonk_trademark_license.txt for full license.
 */

/* A wrapper class to OS dependent event and window interfaces, SDL version */

#include <C4Include.h>
#include <C4Window.h>

#include <C4Application.h>
#include <C4DrawGL.h>
#include <StdFile.h>
#include <StdBuf.h>

#include "C4Version.h"
#include <C4Rect.h>
#include <C4Config.h>

/* C4Window */

C4Window::C4Window ():
		Active(false), pSurface(0)
{
}

C4Window::~C4Window ()
{
	Clear();
}

C4Window * C4Window::Init(WindowKind windowKind, C4AbstractApp * pApp, const char * Title, const C4Rect * size)
{
	if (windowKind != W_Fullscreen)
		return NULL;
	Active = true;
	// SDL doesn't support multiple monitors.
	if (!SDL_SetVideoMode(Application.GetConfigWidth()  == -1 ? 0 : Application.GetConfigWidth(),
	                      Application.GetConfigHeight() == -1 ? 0 : Application.GetConfigHeight(),
	                      Config.Graphics.BitDepth, SDL_OPENGL | (Config.Graphics.Windowed ? 0 : SDL_FULLSCREEN)))
	{
		Log(SDL_GetError());
		return 0;
	}
	SDL_ShowCursor(SDL_DISABLE);
	SetTitle(Title);
	return this;
}

bool C4Window::ReInit(C4AbstractApp* pApp)
{
	// TODO: How do we enable multisampling with SDL?
	// Maybe re-call SDL_SetVideoMode?
	return false;
}

void C4Window::Clear() {}

void C4Window::EnumerateMultiSamples(std::vector<int>& samples) const
{
	// TODO: Enumerate multi samples
}

bool C4Window::StorePosition(const char *, const char *, bool) { return true; }

bool C4Window::RestorePosition(const char *, const char *, bool) { return true; }

// Window size is automatically managed by C4AbstractApp's display mode management.
// Just remember the size for others to query.

bool C4Window::GetSize(C4Rect * pRect)
{
	pRect->x = pRect->y = 0;
	const SDL_VideoInfo * info = SDL_GetVideoInfo();
	pRect->Wdt = info->current_w, pRect->Hgt = info->current_h;
	return true;
}

void C4Window::SetSize(unsigned int X, unsigned int Y)
{
}

void C4Window::SetTitle(const char * Title)
{
	SDL_WM_SetCaption(Title, 0);
}

void C4Window::RequestUpdate()
{
	// just invoke directly
	PerformUpdate();
}

// For Max OS X, the implementation resides in StdMacApp.mm
#ifndef __APPLE__

void C4Window::FlashWindow()
{
}

#endif
