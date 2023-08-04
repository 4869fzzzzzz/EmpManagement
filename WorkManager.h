#pragma once
#include <iostream>
using namespace std;
#include <string>
#include <fstream>
#include "Worker.h"
#include "boss.h"
#include "employee.h"
#include "manager.h"
#define FILENAME "empFile.txt"
class WorkManager
{
public:
	WorkManager();

	void Showmenu();

	//退出
	void ExitSystem();

	~WorkManager();

	//记录职工人数
	int m_Number;

	//职工数组指针
	Worker** m_EmpArray;

	//添加职工
	void Add_Emp();

	//保存文件
	void Save();

	//判断文件是否为空
	bool m_FileIsEmpty;

	//统计人数
	int get_EmpNumber();

	//初始化员工
	void init_Emp();

	//显示职工
	void Show_Emp();

	//删除职工
	void Del_Emp();

	//判断职工是否存在
	int IsExit(int id);

	//修改职工
	void Mod_Emp();

	//查找职工
	void Find_Emp();

	//排序
	void Sort_Emp();

	//清空文件
	void Clean_File();


};

//职工抽象类

