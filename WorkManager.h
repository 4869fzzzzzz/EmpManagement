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

	//�˳�
	void ExitSystem();

	~WorkManager();

	//��¼ְ������
	int m_Number;

	//ְ������ָ��
	Worker** m_EmpArray;

	//���ְ��
	void Add_Emp();

	//�����ļ�
	void Save();

	//�ж��ļ��Ƿ�Ϊ��
	bool m_FileIsEmpty;

	//ͳ������
	int get_EmpNumber();

	//��ʼ��Ա��
	void init_Emp();

	//��ʾְ��
	void Show_Emp();

	//ɾ��ְ��
	void Del_Emp();

	//�ж�ְ���Ƿ����
	int IsExit(int id);

	//�޸�ְ��
	void Mod_Emp();

	//����ְ��
	void Find_Emp();

	//����
	void Sort_Emp();

	//����ļ�
	void Clean_File();


};

//ְ��������

