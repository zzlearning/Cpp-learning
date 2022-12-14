#include"student.h"
#include"orderFile.h"


//默认构造
Student::Student()
{

}
//有参构造，参数：学号，姓名，密码
Student::Student(int id, string name, string pwd)
{
	this->m_Id = id;
	this->m_Name = name;
	this->m_Pwd = pwd;
	this->initComRoom();
}
//菜单界面
void Student::operMenu()
{
	cout << "*******************欢迎学生" << this->m_Name << "登录！***********************" << endl;
	cout << "\t\t-----------------------------------------------\n";
	cout << "\t\t|                                              |\n";
	cout << "\t\t|                1.申请预约                    |\n";
	cout << "\t\t|                                              |\n";
	cout << "\t\t|                2.查看自身预约                |\n";
	cout << "\t\t|                                              |\n";
	cout << "\t\t|                3.查看所有预约                |\n";
	cout << "\t\t|                                              |\n";
	cout << "\t\t|                4.取消预约                    |\n";
	cout << "\t\t|                                              |\n";
	cout << "\t\t|                0.注销登录                    |\n";
	cout << "\t\t-----------------------------------------------\n";
	cout << "输入您的选择： ";
 }
void Student::initComRoom()
{
	ifstream ifs;
	ifs.open(COMPUTER_FILE, ios::in);
	if (!ifs.is_open())
	{
		cout << "文件读取失败" << endl;
		return;
	}
	ComputerRoom c;
	while (ifs >> c.m_ComId && ifs >> c.m_MaxNum)
	{
		vCom.push_back(c);
	}
	ifs.close();
}


void printComRoom01(ComputerRoom& com)
{
	cout << com.m_ComId << "号机房容量为" << com.m_MaxNum << "人" << endl;
}
//申请预约
 void Student::applyOrder()
 {
	 cout << "机房开放时间为周一到周五，请输入申请预约时间" << endl;
	 cout << "1.周一" << endl;
	 cout << "2.周二" << endl;
	 cout << "3.周三" << endl;
	 cout << "4.周四" << endl;
	 cout << "5.周五" << endl;

	 int date = 0;
	 int interval = 0;
	 int room = 0;
	
	 while (true)
	 {
		 cin >> date;
		 if (date >= 1 && date << 5)
		 {
			 break;
		 }
		 cout << "输入有误，请重新输入" << endl;
	 }

	 cout << "请输入预约时间段" << endl;
	 cout << "1.上午" << endl;
	 cout << "2.下午" << endl;

	 while (true)
	 {
		 cin >> interval;
		 if (interval >= 1 && interval <= 2)
			 break;
		 cout << "输入有误，请重新输入" << endl;
	 }

	 cout << "请选择机房" << endl;
	 for_each(vCom.begin(), vCom.end(), printComRoom01);
	 while (true)
	 {
		 cin >> room;
		 if (room >= 1 && room <= 3)
			 break;
		 cout << "输入有误，请重新输入" << endl;
	 }
	 cout << "预约成功,等待老师审批" << endl;

	 ofstream ofs;
	 ofs.open(ORDER_FILE, ios::app);
	 ofs << "date:" << date << " ";
	 ofs << "interval:"<<interval <<" ";
	 ofs << "stuId:"<<this->m_Id <<" ";
	 ofs << "stuName:"<<this->m_Name <<" ";
	 ofs << "roomId:"<<room <<" ";
	 ofs << "status:" << 1 << endl;

	 ofs.close();
	 system("pause");
	 system("cls");
}
//查看自身预约
void Student::showMyOrder()
{
	OrderFile of;
	if (of.m_Size == 0)
	{
		cout << "无预约记录" << endl;
		system("pause");
		system("cls");
		return;
	}
	for (int i = 0; i < of.m_Size; i++)
	{
		//string转为int
		//string利用.c_str()转const char *
		//利用atoi（const char*）转int
		if (this->m_Id == atoi(of.m_orderData[i]["stuId"].c_str()))
		{
			cout << "预约时间：周" << of.m_orderData[i]["date"];
			cout << "    时间段：" << (of.m_orderData[i]["interval"] == "1" ? "上午": "下午");
			cout << "    机房号：" << of.m_orderData[i]["roomId"];
			string status = "    状态：";
			//1审核中  2已预约 -1预约失败 0取消预约
			if (of.m_orderData[i]["status"] == "1")
			{
				status += "审核中";
			}
			else if (of.m_orderData[i]["status"] == "2")
			{
				status += "预约成功";
			}
			else if (of.m_orderData[i]["status"] == "-1")
			{
				status += "预约失败";
			}
			else 
			{
				status += "预约已取消";
			}
			cout << status << endl;
		}
	}
	system("pause");
	system("cls");

}
//查看所有预约
void Student::showAllOrder()
{
	OrderFile of;
	if (of.m_Size == 0)
	{
		cout << "无预约记录" << endl;
		system("pause");
		system("cls");
		return;
	}
	for (int i = 0; i < of.m_Size; i++)
	{
		cout << i + 1 << " 、";
		cout << "预约时间：周" << of.m_orderData[i]["date"];
		cout << "    时间段：" << (of.m_orderData[i]["interval"] == "1" ? "上午" : "下午");
		cout << "    机房号：" << of.m_orderData[i]["roomId"];
		cout << "    预约人姓名：" << of.m_orderData[i]["stuName"];
		cout << "    预约人学号：" << of.m_orderData[i]["stuId"];
		string status = "    状态：";
		//1审核中  2已预约 -1预约失败 0取消预约
		if (of.m_orderData[i]["status"] == "1")
		{
			status += "审核中";
		}
		else if (of.m_orderData[i]["status"] == "2")
		{
			status += "预约成功";
		}
		else if (of.m_orderData[i]["status"] == "-1")
		{
			status += "预约失败";
		}
		else
		{
			status += "预约已取消";
		}
		cout << status << endl;
	}	
	system("pause");
	system("cls");

}
//取消预约
void Student::cancelOrder()
{
	OrderFile of;
	if (of.m_Size == 0)
	{
		cout << "无预约记录" << endl;
		system("pause");
		system("cls");
		return;
	}
	
	int index = 1;
	vector<int> v;
	for (int i = 0; i < of.m_Size; i++)
	{	//判断是自身学号
		if (this->m_Id == atoi(of.m_orderData[i]["stuId"].c_str()))
		{	//筛选状态
			if (of.m_orderData[i]["status"] == "1" || of.m_orderData[i]["status"] == "2")
			{
				v.push_back(i);
				cout << index++ << "、";
				cout << "预约时间：周" << of.m_orderData[i]["date"];
				cout << "    时间段：" << (of.m_orderData[i]["interval"] == "1" ? "上午" : "下午");
				cout << "    机房号：" << of.m_orderData[i]["roomId"];
				string status = "    状态：";
				//1审核中  2已预约 
				if (of.m_orderData[i]["status"] == "1")
				{
					status += "审核中";
				}
				else if (of.m_orderData[i]["status"] == "2")
				{
					status += "预约成功";
				}
				cout << status << endl;
			}
		}
	}
	if (index == 1)
	{
		cout << "没有可以取消的记录" << endl;
		system("pause");
		system("cls");
		return;
	}
	else
	{
		cout << "审核中或预约成功的记录可以取消，请输入要取消的记录,0返回" << endl;
	}
	int select = 0;
	while (true)
	{
		cin >> select;
		if (select >= 0 && select <= v.size())
		{
			if (select == 0)
			{
				system("cls");
				return;
			}
			else
			{
				of.m_orderData[v[select - 1]]["status"] = "0";
				of.updateOrder();
				cout << "取消成功" << endl;
				system("pause");
				system("cls");
				return;
			}
		}
		cout << "输入有误，请重新输入" << endl;
	}
}

