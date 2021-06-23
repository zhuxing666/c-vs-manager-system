#pragma once
//普通员工
#include<iostream>
#include"worker.h"
using namespace std;
class Employee :public Worker
{
public:
	Employee(int id,string name,int dId);
	//显示个人信息
	virtual void showInfo() ;
	// 	   获取岗位
	virtual  string getDeptName();
};