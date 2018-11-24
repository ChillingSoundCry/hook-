// SetWindowHook.cpp : Defines the entry point for the DLL application.
//
#include "stdafx.h"
#include "SetWindowHook.h"
#include <Windows.h>
#include <iostream> 
using namespace std;
static HHOOK hkb=NULL;
static HINSTANCE hins;
LRESULT RetVal;
 
 
// 使用__declspec(dllexport)声明导出函数
__declspec(dllexport) LRESULT CALLBACK HookProc(int nCode,WPARAM wParam,LPARAM lParam);
__declspec(dllexport)  BOOL InstallHook();
__declspec(dllexport) BOOL UnstallHook();
/*************************************
* DllMain
**************************************/
BOOL WINAPI DllMain(
	HINSTANCE hinstDLL,  // DLL模块的句柄
	DWORD fdwReason,     // 调用的情况
	LPVOID lpReserved )  // reserved
{
	// 在不同的情况下都会调用DllMain函数，分别处理
	switch( fdwReason ) 
	{ 
		// 加载Dll
	case DLL_PROCESS_ATTACH:
		{
			hins = hinstDLL;
			printf("The dll loaded!\n");
			break;
		}
		// 新建线程
	case DLL_THREAD_ATTACH:
		break;
		// 线程退出
	case DLL_THREAD_DETACH:
		break;
		// 释放Dll
	case DLL_PROCESS_DETACH:
		hins = NULL;
		printf("The dll released!\n");
		break;
	}
	return TRUE;
}

 
LRESULT CALLBACK HookProc(int nCode,WPARAM wParam,LPARAM lParam)
{	
	switch(wParam)
	{
	case WM_EXITMENULOOP:
		cout<<"已经进入了菜单循环模式"<<endl;
		break;
	case WM_RBUTTONUP:
		cout<<"按下鼠标右键"<<endl;
		MessageBox(0,"按下鼠标右键",0,0);
	}
	return 1;
}
 
 
/********************************************************
*install a hook procedure to monitor the system for all 
*threads in the same desktop as the calling thread
*******************************************************/
BOOL InstallHook()
{
	HWND h = ::FindWindow(NULL, "乱斗"); // 寻找并打开进程 
	DWORD processid; 
	GetWindowThreadProcessId(h, &processid);
	HANDLE hprocess = 0; 
	hprocess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, processid); 
	if (hprocess == 0) { // 对应处理 
		printf("打开进程成功!\n"); 
		hkb=SetWindowsHookEx(WH_GETMESSAGE,(HOOKPROC)HookProc,hins,processid);
	    if(hkb != NULL)
		{
		printf("Setwindowshook done!\n");
		}
	return true; 
	} 
	else { 
		printf("打开进程失败!\n");
		return false;
	}
	
}
 
 
 
BOOL UnstallHook()
{   	
	BOOL unhooked = UnhookWindowsHookEx(hkb);
	return unhooked;
}

// This is the constructor of a class that has been exported.
// see SetWindowHook.h for the class definition
extern "C" _declspec(dllexport) CSetWindowHook::CSetWindowHook()
{ 
	return; 
}

