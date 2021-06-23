#include"标头.h"
WorkerManager::WorkerManager()
{
	//1.文件不存在
	ifstream ifs;
	ifs.open(FILENAME, ios::in);//读文件
	if(!ifs.is_open())
	{
		//cout << "文件不存在" << endl;
		//初始化属性
		//初始化记录人数
		this->m_EmpNum = 0;
		//初始化数组指针
		this->m_EmpNumArray = NULL;
		//初始化文件是否为空
		this->m_FileIsEmpty = true;
		ifs.close();
		return;
		}
	//2.文件存在，数据为空
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		//文件为空
		cout << "文件不存在" << endl;
		//初始化属性
		//初始化记录人数
		this->m_EmpNum = 0;
		//初始化数组指针
		this->m_EmpNumArray = NULL;
		//初始化文件是否为空
		this->m_FileIsEmpty = true;
		ifs.close();
		return;

	}
	//3.文件存在，并且记录数据
	int num = this->get_EmpNum();
	cout << "职工人数为： " << num << endl;
	this->m_EmpNum = num;

	//初始化属性
	//开辟空间
	this->m_EmpNumArray = new Worker * [this->m_EmpNum];

	this->init_Emp();

}


void WorkerManager::Show_Menu()
{
	cout << "****************************" << endl;
	cout << "****欢迎使用职工管理系统!****" << endl;
	cout << "*****0.退出管理程序****" << endl;
	cout << "*****1.增加职工信息****" << endl;
	cout << "*****2.显示职工信息****" << endl;
	cout << "*****3.删除离职职工****" << endl;
	cout << "*****4.修改职工信息****" << endl;
	cout << "*****5.查找职工信息****" << endl;
	cout << "*****6.按照编号排序****" << endl;
	cout << "*****7.清空所有文档****" << endl;
	cout << "****************************" << endl;
	cout << endl;

}


void WorkerManager::ExitSystem()
{
	cout << "欢迎下次使用" << endl;
	system("pause");
	exit(0);//退出程序
}


void WorkerManager::Add_Emp()
{
	cout << "请输入职工数量： " << endl;
	int addNum = 0;
	cin >> addNum;
	if (addNum > 0)
	{
		//添加计算空间大小
		int newSize = this->m_EmpNum + addNum;
		//开辟新空间
		Worker** newSpace = new Worker * [newSize];
		//将原来空间数据，拷贝到新空间
		if (this->m_EmpNumArray != NULL)
		{
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				newSpace[i] = this->m_EmpNumArray[i];
			}
		}
		//批量添加新数据
		for (int i = 0; i < addNum; i++)
		{
			int id;//职工编号
			string name;//职工姓名
			int dSelect;//部门选择

			cout << "请输入第：" << i + 1 << "个新员工编号： " << endl;
			cin >> id;
			cout << "请输入第：" << i + 1 << "个新员工姓名： " << endl;
			cin >> name;

			cout << "输入选择岗位： " << endl;
			cout << "1.普通员工" << endl;
			cout << "2.经理" << endl;
			cout << "3.老板" << endl;
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
			newSpace[this->m_EmpNum + i] = worker;
		}
		//释放原有空间
		delete[]this->m_EmpNumArray;
		//更改新空间
		this->m_EmpNumArray = newSpace;
		//更改新职工人数
		this->m_EmpNum = newSize;
		//更新职工不为空标志
		this->m_FileIsEmpty = false;
		//提示添加成功
		cout << "成功添加" << addNum << "名新职工！" << endl;
		//保存数据到文件中
		this->save();
	}
	else 
	{
		cout << "输出有误" << endl;
	}
	system("pause");
	system("cls");

}

void WorkerManager::save()
{
	ofstream ofs;
	ofs.open(FILENAME, ios::out);
	//将每个人数据写入文件中
	for (int i = 0; i < this->m_EmpNum; i++)
	{
		ofs << this->m_EmpNumArray[i]->m_Id << "   "
			<< this->m_EmpNumArray[i]->m_Name << "  "
			<< this->m_EmpNumArray[i]->m_DeptId << endl;
	}
	ofs.close();
}

int WorkerManager::get_EmpNum()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);//打开文件 读文件
	int id;
	string name;
	int did;
	int num = 0;
	while (ifs >> id && ifs >> name && ifs >> did)
	{
		//统计人数变量
		num++;
	}
	return num;
}

//初始化职工人数
void   WorkerManager::init_Emp()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);
	int id;
	string name;
	int did;
	int index = 0;
	while (ifs >> id && ifs >> name && ifs >> did)
	{
		Worker* worker = NULL;
		if (did == 1)//普通职工
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
		this->m_EmpNumArray[index] = worker;
		index++;
	 }
	ifs.close();
}
//显示职工
void  WorkerManager::Show_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在" << endl;
	}
	else
	{
		for (int i = 0; i < m_EmpNum; i++)
		{
			this->m_EmpNumArray[i]->showInfo();
		}
	}
	system("pause");
	system("cls");
}

//删除职工
void WorkerManager::Del_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在" << endl;
	}
	else
	{
		//按照职工编号删除
		cout << "请输入想要删除职工编号：" << endl;
		int id = 0;
		cin >> id;
		int index=this->IsExist(id);
		if (index != -1)
		{
			//数据前移
			for (int i = index; i < this->m_EmpNum - 1; i++)
			{
				this->m_EmpNumArray[i] = this->m_EmpNumArray[i + 1];
			}
			//记录人数
			this->m_EmpNum--;
			//更新到文件中
			this->save();
			cout << "删除成功！" << endl;

		}
		else
		{
			cout << "没有这个人" << endl;
		}
	}
	system("pause");
	system("cls");
}

//判断职工是否存在，如果存在返回职工所在数组，不存在返回-1
int WorkerManager::IsExist(int id)
{
	int index = -1;
	for (int i = 0; i < this->m_EmpNum; i++)
	{
		if (this->m_EmpNumArray[i]->m_Id == id)
		{

			//找到员工
			index = i;
			break;
		}

	}
	return index;
}
//修改职工
void WorkerManager::Mod_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件不不能再" << endl;
	}
	else
	{
		cout << "请输入修改职工编号： " << endl;
		int id;
		cin >> id;
		int ret = this->IsExist(id);
		if (ret != -1)
		{
			//查找到职工编号
			delete this->m_EmpNumArray[ret];
			int newId = 0;
			string newName = "";
			int dSelect = 0;
			cout << "查到： " << id << "号员工，请输入新职工号：" << endl;
			cin >> newId;

			cout << "请输入新姓名： " << endl;
			cin >> newName;

			cout << "请输入岗位： " << endl;
			cout << "1.普通职工" << endl;
			cout << "2.经理" << endl;
			cout << "3.老板" << endl;

			cin >> dSelect;

			Worker* worker = NULL;
			switch (dSelect)
			{
			case1:
				worker = new Employee(newId, newName, dSelect);
				break;
			case2:
				worker = new Manager(newId, newName, dSelect);
				break;
			case3:
				worker = new Boss(newId, newName, dSelect);
				break;

			default:
				break;
			}
			this->m_EmpNumArray[ret] = worker;
			cout << "修改成功！" << endl;
			//保存到文件中
			this->save();
		}
		else
		{
			cout << "修改失败，查无此人！" << endl;
		}

	}
	system("pause");
	system("cls");
}

//查找职工
void WorkerManager::Find_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在" << endl;
	}
	else
	{
		cout << "请输入查找方式" << endl;
		cout << "1.按照职工编号查找" << endl;
		cout << "2.按照职工姓名查找" << endl;
		int select = 0;
		cin >> select;
		if (select == 1)
		{

			int id;//按照编号查
			cout << "请输入查找职工编号： " << endl;
			cin >> id;
			int ret = IsExist(id);
			if (ret != -1)
			{
				cout << "查找到职工！信息如下： " << endl;
				this->m_EmpNumArray[ret]->showInfo();
			}
			else
			{
				cout << "查找失败" << endl;
			}
		}
		else if (select == 2)
		{
			//按照姓名查找
			string name;
			cout << "输入查找的姓名：" << endl;
			cin >> name;

			// 判断是否加入

			bool flag = false;//默认未找到职工

			for (int i = 0; i < m_EmpNum; i++)
			{
				if (m_EmpNumArray[i]->m_Name == name)
				{
					cout << "查找成功，职工编号为： "
						<< this->m_EmpNumArray[i]->m_Id
						<< "好职工信息如下： " << endl;
					flag = true;
					this->m_EmpNumArray[i]->showInfo();//调用信息
				}
			}
			if (flag == false)
			{
				cout << "查找失败，无此人" << endl;
			}
		}
		else
		{
			cout << "输入项有误！" << endl;

		}
	}
	system ("pause");
	system("cls");
}

//职工排序
void WorkerManager::sort_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件为空！" << endl;
		system("pause");
		system("cls");
	}
	else
	{
		cout << "请选择排序方式： " << endl;
		cout << "1.按职工进行升序" << endl;
		cout << "2.按职工号进行降序" << endl;

		int select = 0;
		cin >> select;
		for (int i = 0; i < m_EmpNum; i++)
		{
			int minOrMax = i;//声明最小值或者最大值下标
			for (int j = i + 1; j < this->m_EmpNum; j++)
			{
				if (select == 1)//升序
				{

					if (this->m_EmpNumArray[minOrMax]->m_Id > m_EmpNumArray[j]->m_Id)
					{
						minOrMax = j;
					}
				}
				else  ///降序
				{

					if (this->m_EmpNumArray[minOrMax]->m_Id < m_EmpNumArray[j]->m_Id)
					{

						minOrMax = j;
					}

				}

			}
			//判断一开始认定的最小值是不是最小值或者组滴啊之，不是要交换
			if (i != minOrMax)
			{
				Worker* temp = this->m_EmpNumArray[i];
				this->m_EmpNumArray[i] = this->m_EmpNumArray[minOrMax];
				this->m_EmpNumArray[minOrMax] = temp;
			}

		}
		cout << "排序成功！排序后的结果为：" << endl;
			this->save();//排序结果保存文件
			this->Show_Emp();//展示所有职工

	}

}
//清空文件
void  WorkerManager::Clean_File()
{
	cout << "确定清空？" << endl;
	cout << "1.确定" << endl;
	cout << "2.返回" << endl;
	int select = 0;
	cin >> select;
	if (select == 1)
	{

		//清空文件
		ofstream ofs(FILENAME, ios::trunc);//删除文件后重新创建
		ofs.close();

		if (this->m_EmpNumArray != NULL)
		{
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				delete this->m_EmpNumArray[i];
				this->m_EmpNumArray[i] = NULL;
			}
			//删除堆区数组指针
			delete[]this->m_EmpNumArray;
			this->m_EmpNumArray = NULL;
			this->m_EmpNum = 0;
			this->m_FileIsEmpty = true;
		}
		cout << "清空成功！" << endl;
	}
	system("pause");
	system("cls");

}



WorkerManager::~WorkerManager()
{
	if (this->m_EmpNumArray != NULL)
	{

		delete[]this->m_EmpNumArray;
		this->m_EmpNumArray = NULL;
	}

}