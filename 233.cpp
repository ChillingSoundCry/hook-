/* ͷ�ļ���*/ 
#include <iostream> 
#include <windows.h>
#include <conio.h>
#include"SetWindowHook.h"
/* ���Ͷ��塡*/
// ָ������ָ������
//typedef DWORD (*MY_EXPORT_PROC)();
typedef void(*hool)();
// main
int main() 
{ 
	hool dll_;
	HINSTANCE hinstLib;
	// ���Dllģ����
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
 
	// ���Dllģ����
	hinstLib = LoadLibrary(TEXT("SetWindowHook.dll")); 
 
	// �Ƿ���سɹ�
	if (hinstLib != NULL) 
	{ 
		// ���ָ�����������ĵ�ַ
		lpProcAdd = (MY_EXPORT_PROC) GetProcAddress(hinstLib, "InstallHook"); 
	printf("�ɹ�\n");
		// �ж��Ƿ�ɹ�
		if (NULL != lpProcAdd) 
		{
			printf("�ɹ�\n");
			fRunTimeLinkSuccess = TRUE;
			//������سɹ��������к���installhook
			(lpProcAdd) (); 
			printf("here\n");
		} 
		printf("sleeping\n");
		Sleep(10000);
		
		//�ͷ�DLL֮ǰ��UnstallHook		
		lpProcAdd1 = (MY_EXPORT_PROC) GetProcAddress(hinstLib, "UnstallHook");
		// �ж��Ƿ�ɹ�
		if (NULL != lpProcAdd1) 
		{
			printf("�ɹ�\n");
			fRunTimeLinkSuccess = TRUE;
			//������سɹ��������к���Unstallhook
			(lpProcAdd1) (); 
		}
 
		// �ͷ�DLL
		fFreeResult = FreeLibrary(hinstLib); 
	} 
 
	// ����
	if (! fRunTimeLinkSuccess) 
		printf("error; %u\n",GetLastError()); */
	getch();
	return 0;
}
