#include<iostream>
#include<windows.h>
#include <Tlhelp32.h>
using namespace std;
DWORD Pid;
int open();
int EnableDebugPrivilege(const LPTSTR name);
bool Inject();
int main()
{
	open();
	Sleep(10000);
	Inject();
	system("pause");
	return 0;
}
/////////////////////////////////////////////////////////////////////////////////////////
bool Inject()
{
	EnableDebugPrivilege(SE_DEBUG_NAME);
    HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, Pid);
	if(hProcess==NULL)
	{
		cout<<"目标进程句柄获取失败"<<endl;
	}
	else{cout<<"目标进程句柄获取成功"<<endl;}
	//1 在目标进程中申请一个空间
    LPVOID pRemoteAddress = VirtualAllocEx(hProcess,NULL,1024,MEM_COMMIT,PAGE_READWRITE);
	if(pRemoteAddress==NULL)
	{
		cout<<"目标进程中内存空间申请失败"<<endl;
	}
	else{cout<<"目标进程中内存空间申请成功"<<endl;}
	//调用WriteProcessMemory,给进程写入DLL的路径
	char path[MAX_PATH];
	GetCurrentDirectoryA(MAX_PATH, path);
	strcpy(path,strcat(path,"\\cdll.dll"));
	//cout<<path<<endl;
    BOOL bRet = WriteProcessMemory(hProcess,pRemoteAddress,path,strlen(path)+1,NULL);
    if(!bRet)
    {
       cout<<"内存写入失败"<<endl;
	   return false;
    }
	else{cout<<"内存写入成功"<<endl;}
	Sleep(50);
	HANDLE hThreadHandle = CreateRemoteThread(hProcess,NULL,0,(LPTHREAD_START_ROUTINE)LoadLibrary,pRemoteAddress,0,NULL);
	if(hThreadHandle==NULL)
	{
		cout<<"进程创建失败"<<endl;
		return false;
	}
	else{cout<<"进程创建成功"<<endl;}
	WaitForSingleObject(hThreadHandle, -1);//等候dll载入完成。
	cout<<"远程线程注入完毕"<<endl;
    //4 释放申请的虚拟内存空间
    VirtualFreeEx(hProcess, pRemoteAddress, 1024, MEM_DECOMMIT);
}
////////////////////////////////////////////////////////////////////////////////////////////////////
int open()
{
	PROCESS_INFORMATION pi;
	STARTUPINFOA si = {sizeof(si)};
	//CONTEXT ct = { 0 };
	//char *name = "C:\\汉化补丁\\DeBug\\paint.exe";
	char Path[MAX_PATH];
	GetCurrentDirectoryA(MAX_PATH, Path);
	strcpy(Path,strcat(Path,"\\CG_TA_01.exe"));//程序的名称
	//创建进程
	if (CreateProcessA(Path, NULL, NULL, NULL, NULL,NULL,NULL,NULL, &si, &pi) == FALSE)
	{
		//cout<<Path<<endl;
		MessageBoxA(0,"未能正确打开进程!",0,MB_ICONERROR | MB_OK);
		return 0;
	}
	char *ProgramName="CG_TA_01.exe";
	PROCESSENTRY32 pe32; 
	// 在使用这个结构之前，先设置它的大小  
	pe32.dwSize = sizeof(pe32);   
			
	// 给系统内的所有进程拍一个快照  
	HANDLE hProcessSnap = ::CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);  
	if(hProcessSnap == INVALID_HANDLE_VALUE)  
	{  
			cout<<" CreateToolhelp32Snapshot调用失败！"<<endl;   
	}  
			
	// 遍历进程快照，轮流显示每个进程的信息  
	BOOL bMore = ::Process32First(hProcessSnap, &pe32);  
	while(bMore)  
	{  
			if(lstrcmpi(pe32.szExeFile,ProgramName)==0)
			{  
				Pid=pe32.th32ProcessID;
				/*char Pid_char[100]={0};
	            itoa(Pid,Pid_char,10);
	            MessageBox(0,Pid_char, "Pid", 0);*/
			}
			bMore = ::Process32Next(hProcessSnap, &pe32);
	}  
			
	// 不要忘记清除掉snapshot对象  
	::CloseHandle(hProcessSnap); 
	////////////////////////////////////////////////////////
	Sleep(50);
}

//提升进程权限   
int EnableDebugPrivilege(const LPTSTR name)  
{  
    HANDLE token;  
    TOKEN_PRIVILEGES tp;  
    //打开进程令牌环   
    if(!OpenProcessToken(GetCurrentProcess(),  
        TOKEN_ADJUST_PRIVILEGES|TOKEN_QUERY,&token))  
    {  
        cout<<"open process token error!\n";  
        return 0;  
    }  
    //获得进程本地唯一ID   
    LUID luid;  
    if(!LookupPrivilegeValue(NULL,name,&luid))  
    {  
        cout<<"lookup privilege value error!\n";  
        return 0;  
    }  
    tp.PrivilegeCount=1;  
    tp.Privileges[0].Attributes=SE_PRIVILEGE_ENABLED;  
    tp.Privileges[0].Luid=luid;  
    //调整进程权限   
    if(!AdjustTokenPrivileges(token,0,&tp,sizeof(TOKEN_PRIVILEGES),NULL,NULL))  
    {  
        cout<<"adjust token privilege error!\n";  
        return 0;  
    }  
    return 1;  
}
