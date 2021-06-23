#pragma once
#include<iostream>
using namespace std;
#include"worker.h"
#include"employee.h"
#include"manager.h"
#include"boss.h"
#include<fstream>
#define FILENAME "empFile.txt"
class WorkerManager
{
public:
	//构造函数
	WorkerManager();
	//展示菜单
	void Show_Menu();
	//退出系统
	void  ExitSystem();
	//记录员工人数
	int m_EmpNum;
	//员工指针
	Worker** m_EmpNumArray;
	//添加员工
	void Add_Emp();
	//保存文件
	void save();
	//判断文件是否为空
	bool m_FileIsEmpty;
	//统计文件中人数
	int get_EmpNum();
	//初始化职工人数
	void   init_Emp();
	//显示职工
	void Show_Emp();
	//删除职工
	void Del_Emp();
	//判断职工是否存在，如果存在返回职工所在数组，不存在返回-1
	int IsExist(int id);
	//修改职工
	void Mod_Emp();
	//查找职工
	void Find_Emp();
	//职工排序
	void  sort_Emp();
	//清空文件吗
	void Clean_File();

	~WorkerManager();

};