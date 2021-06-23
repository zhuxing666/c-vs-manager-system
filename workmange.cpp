#include"��ͷ.h"
WorkerManager::WorkerManager()
{
	//1.�ļ�������
	ifstream ifs;
	ifs.open(FILENAME, ios::in);//���ļ�
	if(!ifs.is_open())
	{
		//cout << "�ļ�������" << endl;
		//��ʼ������
		//��ʼ����¼����
		this->m_EmpNum = 0;
		//��ʼ������ָ��
		this->m_EmpNumArray = NULL;
		//��ʼ���ļ��Ƿ�Ϊ��
		this->m_FileIsEmpty = true;
		ifs.close();
		return;
		}
	//2.�ļ����ڣ�����Ϊ��
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		//�ļ�Ϊ��
		cout << "�ļ�������" << endl;
		//��ʼ������
		//��ʼ����¼����
		this->m_EmpNum = 0;
		//��ʼ������ָ��
		this->m_EmpNumArray = NULL;
		//��ʼ���ļ��Ƿ�Ϊ��
		this->m_FileIsEmpty = true;
		ifs.close();
		return;

	}
	//3.�ļ����ڣ����Ҽ�¼����
	int num = this->get_EmpNum();
	cout << "ְ������Ϊ�� " << num << endl;
	this->m_EmpNum = num;

	//��ʼ������
	//���ٿռ�
	this->m_EmpNumArray = new Worker * [this->m_EmpNum];

	this->init_Emp();

}


void WorkerManager::Show_Menu()
{
	cout << "****************************" << endl;
	cout << "****��ӭʹ��ְ������ϵͳ!****" << endl;
	cout << "*****0.�˳��������****" << endl;
	cout << "*****1.����ְ����Ϣ****" << endl;
	cout << "*****2.��ʾְ����Ϣ****" << endl;
	cout << "*****3.ɾ����ְְ��****" << endl;
	cout << "*****4.�޸�ְ����Ϣ****" << endl;
	cout << "*****5.����ְ����Ϣ****" << endl;
	cout << "*****6.���ձ������****" << endl;
	cout << "*****7.��������ĵ�****" << endl;
	cout << "****************************" << endl;
	cout << endl;

}


void WorkerManager::ExitSystem()
{
	cout << "��ӭ�´�ʹ��" << endl;
	system("pause");
	exit(0);//�˳�����
}


void WorkerManager::Add_Emp()
{
	cout << "������ְ�������� " << endl;
	int addNum = 0;
	cin >> addNum;
	if (addNum > 0)
	{
		//��Ӽ���ռ��С
		int newSize = this->m_EmpNum + addNum;
		//�����¿ռ�
		Worker** newSpace = new Worker * [newSize];
		//��ԭ���ռ����ݣ��������¿ռ�
		if (this->m_EmpNumArray != NULL)
		{
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				newSpace[i] = this->m_EmpNumArray[i];
			}
		}
		//�������������
		for (int i = 0; i < addNum; i++)
		{
			int id;//ְ�����
			string name;//ְ������
			int dSelect;//����ѡ��

			cout << "������ڣ�" << i + 1 << "����Ա����ţ� " << endl;
			cin >> id;
			cout << "������ڣ�" << i + 1 << "����Ա�������� " << endl;
			cin >> name;

			cout << "����ѡ���λ�� " << endl;
			cout << "1.��ͨԱ��" << endl;
			cout << "2.����" << endl;
			cout << "3.�ϰ�" << endl;
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
			newSpace[this->m_EmpNum + i] = worker;
		}
		//�ͷ�ԭ�пռ�
		delete[]this->m_EmpNumArray;
		//�����¿ռ�
		this->m_EmpNumArray = newSpace;
		//������ְ������
		this->m_EmpNum = newSize;
		//����ְ����Ϊ�ձ�־
		this->m_FileIsEmpty = false;
		//��ʾ��ӳɹ�
		cout << "�ɹ����" << addNum << "����ְ����" << endl;
		//�������ݵ��ļ���
		this->save();
	}
	else 
	{
		cout << "�������" << endl;
	}
	system("pause");
	system("cls");

}

void WorkerManager::save()
{
	ofstream ofs;
	ofs.open(FILENAME, ios::out);
	//��ÿ��������д���ļ���
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
	ifs.open(FILENAME, ios::in);//���ļ� ���ļ�
	int id;
	string name;
	int did;
	int num = 0;
	while (ifs >> id && ifs >> name && ifs >> did)
	{
		//ͳ����������
		num++;
	}
	return num;
}

//��ʼ��ְ������
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
		if (did == 1)//��ְͨ��
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
//��ʾְ��
void  WorkerManager::Show_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ�������" << endl;
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

//ɾ��ְ��
void WorkerManager::Del_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ�������" << endl;
	}
	else
	{
		//����ְ�����ɾ��
		cout << "��������Ҫɾ��ְ����ţ�" << endl;
		int id = 0;
		cin >> id;
		int index=this->IsExist(id);
		if (index != -1)
		{
			//����ǰ��
			for (int i = index; i < this->m_EmpNum - 1; i++)
			{
				this->m_EmpNumArray[i] = this->m_EmpNumArray[i + 1];
			}
			//��¼����
			this->m_EmpNum--;
			//���µ��ļ���
			this->save();
			cout << "ɾ���ɹ���" << endl;

		}
		else
		{
			cout << "û�������" << endl;
		}
	}
	system("pause");
	system("cls");
}

//�ж�ְ���Ƿ���ڣ�������ڷ���ְ���������飬�����ڷ���-1
int WorkerManager::IsExist(int id)
{
	int index = -1;
	for (int i = 0; i < this->m_EmpNum; i++)
	{
		if (this->m_EmpNumArray[i]->m_Id == id)
		{

			//�ҵ�Ա��
			index = i;
			break;
		}

	}
	return index;
}
//�޸�ְ��
void WorkerManager::Mod_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ���������" << endl;
	}
	else
	{
		cout << "�������޸�ְ����ţ� " << endl;
		int id;
		cin >> id;
		int ret = this->IsExist(id);
		if (ret != -1)
		{
			//���ҵ�ְ�����
			delete this->m_EmpNumArray[ret];
			int newId = 0;
			string newName = "";
			int dSelect = 0;
			cout << "�鵽�� " << id << "��Ա������������ְ���ţ�" << endl;
			cin >> newId;

			cout << "�������������� " << endl;
			cin >> newName;

			cout << "�������λ�� " << endl;
			cout << "1.��ְͨ��" << endl;
			cout << "2.����" << endl;
			cout << "3.�ϰ�" << endl;

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
			cout << "�޸ĳɹ���" << endl;
			//���浽�ļ���
			this->save();
		}
		else
		{
			cout << "�޸�ʧ�ܣ����޴��ˣ�" << endl;
		}

	}
	system("pause");
	system("cls");
}

//����ְ��
void WorkerManager::Find_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ�������" << endl;
	}
	else
	{
		cout << "��������ҷ�ʽ" << endl;
		cout << "1.����ְ����Ų���" << endl;
		cout << "2.����ְ����������" << endl;
		int select = 0;
		cin >> select;
		if (select == 1)
		{

			int id;//���ձ�Ų�
			cout << "���������ְ����ţ� " << endl;
			cin >> id;
			int ret = IsExist(id);
			if (ret != -1)
			{
				cout << "���ҵ�ְ������Ϣ���£� " << endl;
				this->m_EmpNumArray[ret]->showInfo();
			}
			else
			{
				cout << "����ʧ��" << endl;
			}
		}
		else if (select == 2)
		{
			//������������
			string name;
			cout << "������ҵ�������" << endl;
			cin >> name;

			// �ж��Ƿ����

			bool flag = false;//Ĭ��δ�ҵ�ְ��

			for (int i = 0; i < m_EmpNum; i++)
			{
				if (m_EmpNumArray[i]->m_Name == name)
				{
					cout << "���ҳɹ���ְ�����Ϊ�� "
						<< this->m_EmpNumArray[i]->m_Id
						<< "��ְ����Ϣ���£� " << endl;
					flag = true;
					this->m_EmpNumArray[i]->showInfo();//������Ϣ
				}
			}
			if (flag == false)
			{
				cout << "����ʧ�ܣ��޴���" << endl;
			}
		}
		else
		{
			cout << "����������" << endl;

		}
	}
	system ("pause");
	system("cls");
}

//ְ������
void WorkerManager::sort_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ�Ϊ�գ�" << endl;
		system("pause");
		system("cls");
	}
	else
	{
		cout << "��ѡ������ʽ�� " << endl;
		cout << "1.��ְ����������" << endl;
		cout << "2.��ְ���Ž��н���" << endl;

		int select = 0;
		cin >> select;
		for (int i = 0; i < m_EmpNum; i++)
		{
			int minOrMax = i;//������Сֵ�������ֵ�±�
			for (int j = i + 1; j < this->m_EmpNum; j++)
			{
				if (select == 1)//����
				{

					if (this->m_EmpNumArray[minOrMax]->m_Id > m_EmpNumArray[j]->m_Id)
					{
						minOrMax = j;
					}
				}
				else  ///����
				{

					if (this->m_EmpNumArray[minOrMax]->m_Id < m_EmpNumArray[j]->m_Id)
					{

						minOrMax = j;
					}

				}

			}
			//�ж�һ��ʼ�϶�����Сֵ�ǲ�����Сֵ������ΰ�֮������Ҫ����
			if (i != minOrMax)
			{
				Worker* temp = this->m_EmpNumArray[i];
				this->m_EmpNumArray[i] = this->m_EmpNumArray[minOrMax];
				this->m_EmpNumArray[minOrMax] = temp;
			}

		}
		cout << "����ɹ��������Ľ��Ϊ��" << endl;
			this->save();//�����������ļ�
			this->Show_Emp();//չʾ����ְ��

	}

}
//����ļ�
void  WorkerManager::Clean_File()
{
	cout << "ȷ����գ�" << endl;
	cout << "1.ȷ��" << endl;
	cout << "2.����" << endl;
	int select = 0;
	cin >> select;
	if (select == 1)
	{

		//����ļ�
		ofstream ofs(FILENAME, ios::trunc);//ɾ���ļ������´���
		ofs.close();

		if (this->m_EmpNumArray != NULL)
		{
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				delete this->m_EmpNumArray[i];
				this->m_EmpNumArray[i] = NULL;
			}
			//ɾ����������ָ��
			delete[]this->m_EmpNumArray;
			this->m_EmpNumArray = NULL;
			this->m_EmpNum = 0;
			this->m_FileIsEmpty = true;
		}
		cout << "��ճɹ���" << endl;
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