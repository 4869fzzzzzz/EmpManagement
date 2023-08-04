#include <iostream>
using namespace std;

#include "WorkManager.h"
#include "Worker.h"
#include "employee.h"
#include "manager.h"
#include "boss.h"
int main()
{
	//测试代码
	/*Worker* worker = NULL;
	worker = new Employee(1, "张三", 1);
	worker->showInfo();
	delete worker;

	worker = new Manager(2, "李四", 2);
	worker->showInfo();
	delete worker;

	worker = new Boss(2, "王五", 2);
	worker->showInfo();
	delete worker;*/
	
	//实例化管理者对象
	WorkManager wm;

	int choice = 0;

	while (true)
	{
		wm.Showmenu();

		cout << "请输入选择：" << endl;
		cin >> choice;

		switch (choice)
		{
		case 0:		//退出
			wm.ExitSystem();
			break;
		case 1:		//增加
			wm.Add_Emp();
			break;
		case 2:		//显示
			wm.Show_Emp();
			break;
		case 3:		//删除
			wm.Del_Emp();
			break;
		case 4:		//修改
			wm.Mod_Emp();
			break;
		case 5:		//查找
			wm.Find_Emp();
			break;
		case 6:		//排序
			wm.Sort_Emp();
			break;
		case 7:		//清空
			wm.Clean_File();
			break;
		default:
			system("cls");
			break;
		}
	}
	

	return 0;
}