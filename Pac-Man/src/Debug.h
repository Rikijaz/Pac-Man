// Debug.h : Defines the headers for debugging memory leaks

#ifndef DEBUG_H
#define DEBUG_H

#define _CRTDBG_MAP_ALLOC

#include<iostream>

#include <crtdbg.h>

#ifdef _DEBUG

#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)

#define new DEBUG_NEW

#endif 

#endif // !DEBUG_H

