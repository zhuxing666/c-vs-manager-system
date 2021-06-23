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
	//���캯��
	WorkerManager();
	//չʾ�˵�
	void Show_Menu();
	//�˳�ϵͳ
	void  ExitSystem();
	//��¼Ա������
	int m_EmpNum;
	//Ա��ָ��
	Worker** m_EmpNumArray;
	//���Ա��
	void Add_Emp();
	//�����ļ�
	void save();
	//�ж��ļ��Ƿ�Ϊ��
	bool m_FileIsEmpty;
	//ͳ���ļ�������
	int get_EmpNum();
	//��ʼ��ְ������
	void   init_Emp();
	//��ʾְ��
	void Show_Emp();
	//ɾ��ְ��
	void Del_Emp();
	//�ж�ְ���Ƿ���ڣ�������ڷ���ְ���������飬�����ڷ���-1
	int IsExist(int id);
	//�޸�ְ��
	void Mod_Emp();
	//����ְ��
	void Find_Emp();
	//ְ������
	void  sort_Emp();
	//����ļ���
	void Clean_File();

	~WorkerManager();

};