/*
 * OpenClonk, http://www.openclonk.org
 *
 * Copyright (c) 2007  Matthes Bender
 * Copyright (c) 2001-2009, RedWolf Design GmbH, http://www.clonk.de
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

/* Core component of a folder */

#include <C4Include.h>
#include <C4Folder.h>

#ifndef BIG_C4INCLUDE
#include <C4Random.h>
#include <C4Group.h>
#include <C4Components.h>
#include <C4Game.h>
#ifdef C4ENGINE
#endif
#endif

#if defined(C4FRONTEND) || defined (C4GROUP)
#include "C4CompilerWrapper.h"
#endif

//================= C4FolderHead ====================

void C4FolderHead::Default()
  {
	Index = 0;
	Sort[0] = 0;
  }

void C4FolderHead::CompileFunc(StdCompiler *pComp)
  {
  pComp->Value(mkNamingAdapt(Index,                     "Index",                0));
  pComp->Value(mkNamingAdapt(mkStringAdaptMA(Sort),     "Sort",                 ""));
  }

//=================== C4Folder ======================

C4Folder::C4Folder()
  {
  Default();
  }

void C4Folder::Default()
  {
	Head.Default();
  }

BOOL C4Folder::Load(C4Group &hGroup)
  {
	char *pSource;
	// Load
	if (!hGroup.LoadEntry(C4CFN_FolderCore, &pSource, NULL, 1)) return FALSE;
	// Compile
	if (!Compile(pSource)) { delete [] pSource; return FALSE; }
	delete [] pSource;
	// Success
	return TRUE;
  }

/*BOOL C4Folder::Save(C4Group &hGroup)
	{
	char *Buffer; int32_t BufferSize;
	if (!Decompile(&Buffer,&BufferSize))
		return FALSE;
	if (!hGroup.Add(C4Folder, Buffer, BufferSize, FALSE, TRUE))
		{ StdBuf Buf; Buf.Take(Buffer, BufferSize); return FALSE; }
	return TRUE;
	}*/

void C4Folder::CompileFunc(StdCompiler *pComp)
  {
  pComp->Value(mkNamingAdapt(Head, "Head"));
  }

BOOL C4Folder::Compile(const char *szSource)
	{
	Default();
  return CompileFromBuf_LogWarn<StdCompilerINIRead>(*this, StdStrBuf(szSource), C4CFN_FolderCore);
	}

