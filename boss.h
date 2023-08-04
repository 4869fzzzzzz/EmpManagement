#pragma once
#include <iostream>
#include "Worker.h"
using namespace std;
#include <string>

class Boss :public Worker
{
public:
	Boss(int id, string name, int did);

	virtual void showInfo();

	virtual string getDeptName();

};
