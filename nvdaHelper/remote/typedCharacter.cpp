/*
This file is a part of the NVDA project.
URL: http://www.nvda-project.org/
Copyright 2006-2010 NVDA contributers.
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 2.0, as published by
    the Free Software Foundation.
    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
This license can be found at:
http://www.gnu.org/licenses/old-licenses/gpl-2.0.html
*/

#define WIN32_LEAN_AND_MEAN 
#include <windows.h>
#include <wchar.h>
#include "nvdaHelperRemote.h"
#include "nvdaControllerInternal.h"
#include "typedCharacter.h"

HWND typedCharacter_window=NULL;

LRESULT CALLBACK typedCharacter_getMessageHook(int code, WPARAM wParam, LPARAM lParam) {
	static WPARAM lastCharacter=0;
	MSG* pmsg=(MSG*)lParam;
	if(pmsg->message==WM_KEYDOWN) {
		typedCharacter_window=pmsg->hwnd;
		lastCharacter=0;
	} else if((typedCharacter_window!=0)&&(pmsg->message==WM_CHAR)&&(pmsg->hwnd==typedCharacter_window)&&(pmsg->wParam!=lastCharacter)) { 
		nvdaControllerInternal_typedCharacterNotify(GetCurrentThreadId(),static_cast<wchar_t>(pmsg->wParam));
		lastCharacter=pmsg->wParam;
	}
	return 0;
}

void typedCharacter_inProcess_initialize() {
	registerWindowsHook(WH_GETMESSAGE,typedCharacter_getMessageHook);
}

void typedCharacter_inProcess_terminate() {
	unregisterWindowsHook(WH_GETMESSAGE,typedCharacter_getMessageHook);
}
