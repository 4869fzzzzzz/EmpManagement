#pragma once
#include <iostream>
#include "Worker.h"
using namespace std;
#include <string>

class Manager :public Worker
{
public:
	Manager(int id, string name, int did);

	virtual void showInfo();

	virtual string getDeptName();

};