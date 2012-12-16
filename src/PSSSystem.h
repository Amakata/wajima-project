#pragma once

// Windows ヘッダー ファイル :
#include <windows.h>
// C ランタイム ヘッダー ファイル
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <iostream>
#include <fstream>
#include <sstream>

#include "resource.h"
#include "cppunit/TestCase.h"
#include "cppunit/ui/text/TestRunner.h"
#include "cppunit/CompilerOutputter.h"
#include "std/win32debug_console_stream.h"
#include "std/win32console_stream.h"
#include "std/Logger.h"
#include "std/Timer.h"
#include "application/ApplicationInitializer.h"
#include "application/ApplicationBase.h"
#include "input/KeyInput.h"
#include "input/MouseInput.h"
#include "graphics/Graphics7.h"
#include "graphics/Image.h"
#include "graphics/GraphicsConverter.h"

extern "C" {
#include "lua/lua.h"
#include "lua/lualib.h"
#include "lua/lauxlib.h"

#include "tolua/tolua++.h"
}
extern int tolua_zefiro_open (lua_State* tolua_S);
