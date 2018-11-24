/* 头文件　*/ 
#include <iostream> 
#include <windows.h>
#include <conio.h>
#include"SetWindowHook.h"
/* 类型定义　*/
// 指向函数的指针类型
//typedef DWORD (*MY_EXPORT_PROC)();
typedef void(*hool)();
// main
int main() 
{ 
	hool dll_;
	HINSTANCE hinstLib;
	// 获得Dll模块句柄
	hinstLib = LoadLibrary(TEXT("SetWindowHook.dll")); 
	if(hinstLib==NULL)
	{FreeLibrary(hinstLib);}
	dll_=(hool)GetProcAddress(hinstLib,"InstallHook");
	dll_();
    if(dll_==NULL)
  {FreeLibrary(hinstLib);}
	Sleep(10000);
	dll_=(hool)GetProcAddress(hinstLib,"UnstallHook");
	dll_();
    if(dll_==NULL)
  {FreeLibrary(hinstLib);}
/*
	HINSTANCE hinstLib; 
	MY_EXPORT_PROC lpProcAdd,lpProcAdd1; 
	BOOL fFreeResult, fRunTimeLinkSuccess = FALSE; 
 
	// 获得Dll模块句柄
	hinstLib = LoadLibrary(TEXT("SetWindowHook.dll")); 
 
	// 是否加载成功
	if (hinstLib != NULL) 
	{ 
		// 获得指定导出函数的地址
		lpProcAdd = (MY_EXPORT_PROC) GetProcAddress(hinstLib, "InstallHook"); 
	printf("成功\n");
		// 判断是否成功
		if (NULL != lpProcAdd) 
		{
			printf("成功\n");
			fRunTimeLinkSuccess = TRUE;
			//如果加载成功，则运行函数installhook
			(lpProcAdd) (); 
			printf("here\n");
		} 
		printf("sleeping\n");
		Sleep(10000);
		
		//释放DLL之前先UnstallHook		
		lpProcAdd1 = (MY_EXPORT_PROC) GetProcAddress(hinstLib, "UnstallHook");
		// 判断是否成功
		if (NULL != lpProcAdd1) 
		{
			printf("成功\n");
			fRunTimeLinkSuccess = TRUE;
			//如果加载成功，则运行函数Unstallhook
			(lpProcAdd1) (); 
		}
 
		// 释放DLL
		fFreeResult = FreeLibrary(hinstLib); 
	} 
 
	// 出错
	if (! fRunTimeLinkSuccess) 
		printf("error; %u\n",GetLastError()); */
	getch();
	return 0;
}
