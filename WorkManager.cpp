#include "WorkManager.h"

WorkManager::WorkManager()
{
	//文件不存在
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	
	if (!ifs.is_open())
	{
		/*cout << "文件不存在" << endl;*/
		//初始化属性
		this->m_Number = 0;

		this->m_EmpArray = NULL;

		this->m_FileIsEmpty = true;
		ifs.close();
		return;
	}
	//文件存在 数据为空
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		//文件为空
		/*cout << "文件为空" << endl;*/
		this->m_Number = 0;

		this->m_EmpArray = NULL;

		this->m_FileIsEmpty = true;
		ifs.close();
		return;
	}
	//文件存在有数据
	int num = this->get_EmpNumber();
	/*cout << "职工人数：" << num << endl;*/
	this->m_Number = num;
	
	this->m_EmpArray = new Worker * [this->m_Number];
	//将文件中的数据存到数组中
	this->init_Emp();
	/*for (int i=0;i<this->m_Number;i++)
	{
		cout << "职工编号：" << this->m_EmpArray[i]->m_Id
			<< "姓名：" << this->m_EmpArray[i]->m_Name
			<< "职位：" << this->m_EmpArray[i]->m_DeptId << endl;
	}*/

}
WorkManager::~WorkManager()
{
	if (this->m_EmpArray != NULL)
	{
		delete[] this->m_EmpArray;
		this->m_EmpArray = NULL;
	}
}
void WorkManager::Showmenu()
{
	cout << "职工管理系统" << endl;
	cout << "0.退出" << endl;
	cout << "1.增加职工信息" << endl;
	cout << "2.显示职工信息" << endl;
	cout << "3.删除离职职工" << endl;
	cout << "4.修改职工信息" << endl;
	cout << "5.查找职工信息" << endl;
	cout << "6.按照编号排序" << endl;
	cout << "7.清空文档" << endl;
	cout << "**************" << endl;
	cout << endl;
}

void WorkManager::ExitSystem()
{
	cout << "欢迎下次使用!" << endl;
	system("pause");
	exit(0);
}

void WorkManager::Add_Emp()
{
	cout << "职工数量：" << endl;
	int addNum = 0;
	cin >> addNum;

	if (addNum > 0)
	{
		//添加
		
			
		int newSize = this->m_Number + addNum;
		//开辟新空间
		Worker**newspace=new Worker* [newSize];
		if (this->m_EmpArray != NULL)
		{
			for (int i = 0; i < this->m_Number; i++)
			{
				newspace[i] = this->m_EmpArray[i];

			}
		}
		//批量添加新数据
		for (int i = 0; i < addNum; i++)
		{
			int id;
			string name;
			int dSelect;

			cout << "请输入第" << i + 1 << "个新员工编号" << endl;
			cin >> id;
			cout << "请输入第" << i + 1 << "个新员工姓名" << endl;
			cin >> name;

			cout << "请选择该职工岗位：" << endl;
			cout << "1,普通职工" << endl;
			cout << "2,经理" << endl;
			cout << "3，boss" << endl;
			cin >> dSelect;

			Worker* worker = NULL;
			switch (dSelect)
			{
			case 1:
				worker = new Employee(id, name, 1);
				break;
			case 2:
				worker = new Manager(id, name, 2);
				break;
			case 3:
				worker = new Boss(id, name, 3);
				break;
			default:
				break;

			
			}
			//将创建职工职责，保存到数组中
			newspace[this->m_Number + i] = worker;

		}
		delete[] this->m_EmpArray;

		this->m_EmpArray = newspace;

		this->m_Number = newSize;

		this->m_FileIsEmpty = false;
		//成功添加后保存到文件
		this->Save();

		//提示添加成功
		cout << "成功添加"<<addNum <<"名" << endl;
	}
	else
	{
		cout << "输入数据有误" << endl;
	}

	//按任意键清屏
	system("pause");
	system("cls");
}

void WorkManager::Save()
{
	ofstream ofs;
	ofs.open(FILENAME, ios::out);

	//将每人的数据写入
	for (int i = 0; i < this->m_Number; i++)
	{
		ofs << this->m_EmpArray[i]->m_Id << " "
			<< this->m_EmpArray[i]->m_Name << " "
			<< this->m_EmpArray[i]->m_DeptId << endl;

	}
	ofs.close();
}

int WorkManager::get_EmpNumber()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	int id;
	int num = 0;
	string name;
	int did;
	while (ifs >> id && ifs >> name && ifs >> did)
	{
		num++;
	}
	return num;

}

void WorkManager::init_Emp()
{
	ifstream ifs;
	ifs.open(FILENAME,ios::in);

	int id;
	int did;
	string name;
	int index=0;

	while (ifs>>id&&ifs>>name&&ifs>>did)

	{
		Worker* worker = NULL;
		if (did == 1)
		{
			worker = new Employee(id, name, did);

		}
		else if (did == 2)
		{
			worker = new Manager(id, name, did);
			
		}
		else 
		{
			worker = new Boss(id, name, did);

		}
		this->m_EmpArray[index] = worker;
		index++;
	}
	ifs.close();
}

void WorkManager::Show_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或者记录为空" << endl;

	}
	else
	{
		for (int i = 0; i < m_Number; i++)
		{
			this->m_EmpArray[i]->showInfo();
		
		}
		
	}
	system("pause");
	system("cls");
}
//删除职工
void WorkManager::Del_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或者记录为空" << endl;
	}
	else
	{
		//按职工编号删除
		cout << "输入想要删除的职工编号" << endl;
		int id = 0;
		cin >> id;

		int index = this->IsExit(id);

		if (index != -1)
		{
			for (int i = index; i < this->m_Number - 1; i++)
			{
				//数据前移
				this->m_EmpArray[i] = this->m_EmpArray[i + 1];

			}
			this->m_Number--;
			this->Save();

			cout << "删除成功" << endl;
		}
		else
		{
			cout <<"删除失败，未找到该员工" << endl;
	
		}
	}
	system("pause");
	system("cls");
}

//判断职工是否存在
int WorkManager::IsExit(int id)
{
	int index = -1;
	for (int i = 0; i < this->m_Number; i++)
	{
		if (this->m_EmpArray[i]->m_Id == id)
		{
			index = i;
			break;
		}
	
	}
	return index;
}

void WorkManager::Mod_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或者记录为空" << endl;

	
	}
	else
	{
		cout << "请输入修改员工的id" << endl;
		int id;
		cin >> id;

		int ret = this->IsExit(id);
		if (ret != -1)
		{
			delete this->m_EmpArray[ret];

			int newId = 0;
			string newName="";
			int dSelect=0;

			cout << "查到"<<id<<"号职工，请输入新的职工号：" << endl;
			cin >> newId;

			cout << "请输入新的姓名：" << endl;
			cin >> newName;

			cout << "请输入新岗位" << endl;
			cout << "1,普通员工" << endl;
			cout << "2，经理" << endl;
			cout << "3，boss" << endl;

			cin >> dSelect;

			Worker* worker = NULL;
			switch (dSelect)
			{
			case 1:
				worker = new Employee(newId, newName, dSelect);
				break;
			case 2:
				worker = new Manager(newId, newName, dSelect);
				break;
			case 3:
				worker = new Boss(newId, newName, dSelect);
				break;
			default:
				break;
			}
			//更新数据
			this->m_EmpArray[ret] = worker;

			cout << "修改成功" << endl;

			this->Save();
		}
		else
		{
			cout << "修改失败，查无此人" << endl;
		
		}
	}
	system("pause");
	system("cls");
}

void WorkManager::Find_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在" << endl;
	}
	else
	{
		cout << "请输入查找方式" << endl;
		cout << "1，按id" << endl;
		cout << "2，按姓名" << endl;
		int select = 0;
		cin >> select;
		if (select == 1)
		{
			int id;
			cout << "请输入查找编号" << endl;
			cin >> id;

			int ret = IsExit(id);
			if (ret != -1)
			{
				cout << "查找成功！该职工信息如下：" << endl;
				this->m_EmpArray[ret]->showInfo();

			
			}
			else
			{
				cout << "查找失败，查无此人" << endl;
			
			}
		
		}
		else if (select == 2)
		{
			string name;
			cout << "请输入查找的姓名" << endl;
			cin >> name;

			//判断查找是否查到的标识
			bool flag=false;
			for (int i = 0; i < m_Number; i++)
			{
				if (this->m_EmpArray[i]->m_Name == name)
				{
					cout << "查找成功，职工编号为："
						<<this->m_EmpArray[i]->m_Id
						<<"职工信息如下：" << endl;
					this->m_EmpArray[i]->showInfo(); \
						flag = true;
				}
			}
			if (flag == false)
			{
				cout << "查找失败" << endl;
			}
		}
		else
		{
			cout << "选项错误" << endl;
		}
	}
	system("pause");
	system("cls");
}

void WorkManager::Sort_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在" << endl;
		system("pause");
		system("cls");
	}
	else
	{
		cout << "请选择排序方式" << endl;
		cout << "1，按职工号进行升序" << endl;
		cout << "2,按职工号降序排序" << endl;

		int select = 0;
		cin >> select;
		for (int i = 0; i < m_Number; i++)
		{
			int minOrMax = i;
			for (int j = i + 1; j < this->m_Number; j++)
			{
				if (select == 1)
				{
					if (this->m_EmpArray[minOrMax]->m_Id > this->m_EmpArray[j]->m_Id)
					{
						minOrMax = j;
					}
				}
				else
				{
					if (this->m_EmpArray[minOrMax]->m_Id <this->m_EmpArray[j]->m_Id)
					{
						minOrMax = j;
					}
				}
			}
			if (i != minOrMax)
			{
				Worker* temp = this->m_EmpArray[i];
				this->m_EmpArray[i] = this->m_EmpArray[minOrMax];
				this->m_EmpArray[minOrMax] = temp;
			}
		}

		cout << "排序成功，结果为" << endl;
		this->Save();
		this->Show_Emp();
	}
}

void WorkManager::Clean_File()
{
	cout << "确定清空？" << endl;
	cout << "1，确定" << endl;
	cout << "2，返回" << endl;

	int select = 0;
	cin >> select;

	if (select == 1)
	{
		ofstream ofs(FILENAME, ios::trunc);
		ofs.close();

		if (this->m_EmpArray != NULL)
		{
			for (int i = 0; i < this->m_Number; i++)
			{
				delete this->m_EmpArray[i];
				this->m_EmpArray[i] = NULL;
			}

			delete[] this->m_EmpArray;
			this->m_EmpArray = NULL;
			this->m_Number = 0;
			this->m_FileIsEmpty = true;
		}
		cout << "清空成功" << endl;

	}
	system("pause");
	system("cls");
}
