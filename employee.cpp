#pragma once
#include <iostream>
#include "employee.h"
using namespace std;
#include <string>

Employee::Employee(int id, string name, int did)
{
	this->m_Id = id;
	this->m_Name = name;
	this->m_DeptId = did;
}
void Employee::showInfo()
{
	cout << "ְ�����:" << this->m_Id
		<< "\tְ������:" << this->m_Name
		<< "\t��λ:" << this->getDeptName()
		<< "\t��λְ����ɾ�����������" << endl;

	
}

string Employee::getDeptName()
{
	return string("Ա��");
}
