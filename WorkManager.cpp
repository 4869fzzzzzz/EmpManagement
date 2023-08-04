#include "WorkManager.h"

WorkManager::WorkManager()
{
	//�ļ�������
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	
	if (!ifs.is_open())
	{
		/*cout << "�ļ�������" << endl;*/
		//��ʼ������
		this->m_Number = 0;

		this->m_EmpArray = NULL;

		this->m_FileIsEmpty = true;
		ifs.close();
		return;
	}
	//�ļ����� ����Ϊ��
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		//�ļ�Ϊ��
		/*cout << "�ļ�Ϊ��" << endl;*/
		this->m_Number = 0;

		this->m_EmpArray = NULL;

		this->m_FileIsEmpty = true;
		ifs.close();
		return;
	}
	//�ļ�����������
	int num = this->get_EmpNumber();
	/*cout << "ְ��������" << num << endl;*/
	this->m_Number = num;
	
	this->m_EmpArray = new Worker * [this->m_Number];
	//���ļ��е����ݴ浽������
	this->init_Emp();
	/*for (int i=0;i<this->m_Number;i++)
	{
		cout << "ְ����ţ�" << this->m_EmpArray[i]->m_Id
			<< "������" << this->m_EmpArray[i]->m_Name
			<< "ְλ��" << this->m_EmpArray[i]->m_DeptId << endl;
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
	cout << "ְ������ϵͳ" << endl;
	cout << "0.�˳�" << endl;
	cout << "1.����ְ����Ϣ" << endl;
	cout << "2.��ʾְ����Ϣ" << endl;
	cout << "3.ɾ����ְְ��" << endl;
	cout << "4.�޸�ְ����Ϣ" << endl;
	cout << "5.����ְ����Ϣ" << endl;
	cout << "6.���ձ������" << endl;
	cout << "7.����ĵ�" << endl;
	cout << "**************" << endl;
	cout << endl;
}

void WorkManager::ExitSystem()
{
	cout << "��ӭ�´�ʹ��!" << endl;
	system("pause");
	exit(0);
}

void WorkManager::Add_Emp()
{
	cout << "ְ��������" << endl;
	int addNum = 0;
	cin >> addNum;

	if (addNum > 0)
	{
		//���
		
			
		int newSize = this->m_Number + addNum;
		//�����¿ռ�
		Worker**newspace=new Worker* [newSize];
		if (this->m_EmpArray != NULL)
		{
			for (int i = 0; i < this->m_Number; i++)
			{
				newspace[i] = this->m_EmpArray[i];

			}
		}
		//�������������
		for (int i = 0; i < addNum; i++)
		{
			int id;
			string name;
			int dSelect;

			cout << "�������" << i + 1 << "����Ա�����" << endl;
			cin >> id;
			cout << "�������" << i + 1 << "����Ա������" << endl;
			cin >> name;

			cout << "��ѡ���ְ����λ��" << endl;
			cout << "1,��ְͨ��" << endl;
			cout << "2,����" << endl;
			cout << "3��boss" << endl;
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
			//������ְ��ְ�𣬱��浽������
			newspace[this->m_Number + i] = worker;

		}
		delete[] this->m_EmpArray;

		this->m_EmpArray = newspace;

		this->m_Number = newSize;

		this->m_FileIsEmpty = false;
		//�ɹ���Ӻ󱣴浽�ļ�
		this->Save();

		//��ʾ��ӳɹ�
		cout << "�ɹ����"<<addNum <<"��" << endl;
	}
	else
	{
		cout << "������������" << endl;
	}

	//�����������
	system("pause");
	system("cls");
}

void WorkManager::Save()
{
	ofstream ofs;
	ofs.open(FILENAME, ios::out);

	//��ÿ�˵�����д��
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
		cout << "�ļ������ڻ��߼�¼Ϊ��" << endl;

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
//ɾ��ְ��
void WorkManager::Del_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ������ڻ��߼�¼Ϊ��" << endl;
	}
	else
	{
		//��ְ�����ɾ��
		cout << "������Ҫɾ����ְ�����" << endl;
		int id = 0;
		cin >> id;

		int index = this->IsExit(id);

		if (index != -1)
		{
			for (int i = index; i < this->m_Number - 1; i++)
			{
				//����ǰ��
				this->m_EmpArray[i] = this->m_EmpArray[i + 1];

			}
			this->m_Number--;
			this->Save();

			cout << "ɾ���ɹ�" << endl;
		}
		else
		{
			cout <<"ɾ��ʧ�ܣ�δ�ҵ���Ա��" << endl;
	
		}
	}
	system("pause");
	system("cls");
}

//�ж�ְ���Ƿ����
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
		cout << "�ļ������ڻ��߼�¼Ϊ��" << endl;

	
	}
	else
	{
		cout << "�������޸�Ա����id" << endl;
		int id;
		cin >> id;

		int ret = this->IsExit(id);
		if (ret != -1)
		{
			delete this->m_EmpArray[ret];

			int newId = 0;
			string newName="";
			int dSelect=0;

			cout << "�鵽"<<id<<"��ְ�����������µ�ְ���ţ�" << endl;
			cin >> newId;

			cout << "�������µ�������" << endl;
			cin >> newName;

			cout << "�������¸�λ" << endl;
			cout << "1,��ͨԱ��" << endl;
			cout << "2������" << endl;
			cout << "3��boss" << endl;

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
			//��������
			this->m_EmpArray[ret] = worker;

			cout << "�޸ĳɹ�" << endl;

			this->Save();
		}
		else
		{
			cout << "�޸�ʧ�ܣ����޴���" << endl;
		
		}
	}
	system("pause");
	system("cls");
}

void WorkManager::Find_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ�������" << endl;
	}
	else
	{
		cout << "��������ҷ�ʽ" << endl;
		cout << "1����id" << endl;
		cout << "2��������" << endl;
		int select = 0;
		cin >> select;
		if (select == 1)
		{
			int id;
			cout << "��������ұ��" << endl;
			cin >> id;

			int ret = IsExit(id);
			if (ret != -1)
			{
				cout << "���ҳɹ�����ְ����Ϣ���£�" << endl;
				this->m_EmpArray[ret]->showInfo();

			
			}
			else
			{
				cout << "����ʧ�ܣ����޴���" << endl;
			
			}
		
		}
		else if (select == 2)
		{
			string name;
			cout << "��������ҵ�����" << endl;
			cin >> name;

			//�жϲ����Ƿ�鵽�ı�ʶ
			bool flag=false;
			for (int i = 0; i < m_Number; i++)
			{
				if (this->m_EmpArray[i]->m_Name == name)
				{
					cout << "���ҳɹ���ְ�����Ϊ��"
						<<this->m_EmpArray[i]->m_Id
						<<"ְ����Ϣ���£�" << endl;
					this->m_EmpArray[i]->showInfo(); \
						flag = true;
				}
			}
			if (flag == false)
			{
				cout << "����ʧ��" << endl;
			}
		}
		else
		{
			cout << "ѡ�����" << endl;
		}
	}
	system("pause");
	system("cls");
}

void WorkManager::Sort_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ�������" << endl;
		system("pause");
		system("cls");
	}
	else
	{
		cout << "��ѡ������ʽ" << endl;
		cout << "1����ְ���Ž�������" << endl;
		cout << "2,��ְ���Ž�������" << endl;

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

		cout << "����ɹ������Ϊ" << endl;
		this->Save();
		this->Show_Emp();
	}
}

void WorkManager::Clean_File()
{
	cout << "ȷ����գ�" << endl;
	cout << "1��ȷ��" << endl;
	cout << "2������" << endl;

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
		cout << "��ճɹ�" << endl;

	}
	system("pause");
	system("cls");
}
