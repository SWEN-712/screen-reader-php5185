/*
This file is a part of the NVDA project.
URL: http://www.nvda-project.org/
Copyright 2006-2010 NVDA contributers.
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License version 2.1, as published by
the Free Software Foundation.
This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
This license can be found at:
http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html
*/

#include <string>
#include <sstream>
#include <rpc.h>
#include "nvdaController.h"
#include <common/winIPCUtils.h>

using namespace std;

void* __RPC_USER midl_user_allocate(size_t size) {
	return malloc(size);
}

void __RPC_USER midl_user_free(void* p) {
	free(p);
}

BOOL WINAPI DllMain(HINSTANCE hModule,DWORD reason,LPVOID lpReserved) {
	if(reason==DLL_PROCESS_ATTACH) {
		wchar_t desktopSpecificNamespace[64];
		generateDesktopSpecificNamespace(desktopSpecificNamespace,ARRAYSIZE(desktopSpecificNamespace));
		wstringstream s;
		s<<L"ncalrpc:[NvdaCtlr."<<desktopSpecificNamespace<<L"]";
		RpcBindingFromStringBinding((RPC_WSTR)(s.str().c_str()),&nvdaControllerBindingHandle);
	} else if(reason==DLL_PROCESS_DETACH) {
		RpcBindingFree(&nvdaControllerBindingHandle);
	}
	return TRUE;
}
