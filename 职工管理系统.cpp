#include<iostream>
using namespace std;
#include"��ͷ.h"

#include"worker.h"
#include"employee.h"
#include"manager.h"
#include"boss.h"
int main()
{
	//Worker* worker = NULL;
	//worker = new Employee(1, "����",1);
	//worker->showInfo();
	//delete worker;

	//worker = new Manager(2, "У��", 2);
	//worker->showInfo();
	//delete worker;




	WorkerManager wm;
	int choice = 0;
	while (true)
	{
		wm.Show_Menu();
		cout << "���������ѡ�� " << endl;
		cin >> choice;
		switch (choice)
		{
		case 0://�˳�ϵͳ
			wm.ExitSystem();
			break;
		case 1://����ְ��
			wm.Add_Emp();
			break;
		case 2://��ʾְ��
			wm.Show_Emp();
			break;
		case 3://ɾ��ְ��
			wm.Del_Emp();
			break;
		case 4://�޸�ְ��
			wm.Mod_Emp();
			break;
		case 5://����ְ��
			wm.Find_Emp();
			break;
		case 6://����ְ��
			wm.sort_Emp();
			break;
		case 7://����ĵ�
			wm.Clean_File();
			break;
		default:
			system("cls");
			break;
		}
	}
	
	
	system("pause");
	return 0;

}