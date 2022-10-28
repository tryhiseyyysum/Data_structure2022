#include<iostream>
#include<cmath>
#include<cstdlib>
#include<ctime>
#include"queue.h"
using namespace std;

struct plane
{
	int id;
	int time;
	int t;		//飞机在机场的停留时间(剩余时间)
};

enum action { arrive, depart };
class Airport
{
public:
	Airport();
	void Start();
	bool isIdle();		//判断跑道是否空闲
private:
	Queue<plane> landing;	//降落队列
	Queue<plane> takeoff;	//起飞队列
	double exparrive;
	double expdepart;
	int landmax;
	int takeoffmax;
	int currenttime;                            //当前时间
	int endtime;                                //模拟时间单元数
	int idletime;                               //跑道空闲时间单元数
	int landwait;                               //已降落飞机等待时间 
	int takeoffwait;                            //已起飞飞机等待时间
	int nland;                                  //降落飞机数
	int nplanes;                                //处理飞机数
	int nrefuse;                                //拒绝服务的飞机数
	int ntakeoff;                               //起飞飞机数
	int nforcelanding;                          //紧急降落飞机数
	int landtime;							   //降落飞机总停留时间

	int PoissionRandom(double& expvalue);       //泊松分布生成随机数
	plane* Newplane(plane& p, action kind);     //建立新飞机数据
	void Refuse(plane& p, action king);
	void land1(plane& p);
	void fly1(plane& p);
	void land2(plane& p);
	void fly2(plane& p);
	void land3(plane& p);
	void idle();
	void conclude();
};


Airport::Airport()
{
	bool ok = false;
	cout << "输入机场运行时间单元数：";
	cin >> endtime;
	idletime = landwait = nplanes = nrefuse = ntakeoff = takeoffwait = 0;
	srand((unsigned)time(NULL));

	
	do {
		cout << "输入一个时间单元内期望降落飞机数：";
		cin >> exparrive;
		cout << "输入一个时间单元内期望起飞飞机数：";
		cin >> expdepart;
		if (exparrive < 0 || expdepart < 0)
		{   
			cout << "输入不合法，不能为负数！\n"; 
			ok=false;
		}
		else if (exparrive > 3 || expdepart > 3)
		{	cout << "机场将饱和！\n";
			ok=false;
		}
		else ok = true;
		
	} while (ok == false);
}

void Airport::Start()
{
	int pri;                       //伪随机整数
	plane p;
	landtime=p.t;

	for (currenttime = 1; currenttime <= endtime; currenttime++)
	{
		int flag1 = 0, flag2 = 0;
		cout<<endl;
		cout << "时间单元" << currenttime << "：\n";
		//pri = PoissionRandom(exparrive);
		pri = rand() % (3);
		for (int i = 1; i <= pri; i++)              //要降落的飞机入队
		{
			p = *Newplane(p,arrive);
			if (landing.isfull()) Refuse(p, arrive);
			else landing.Add(p);
		}
		//pri = PoissionRandom(expdepart);
		pri = rand() % (3);
		for (int i = 1; i <= pri; i++)               //要起飞的飞机入队
		{
			p = *Newplane(p, depart);
			if (takeoff.isfull()) Refuse(p, depart);
			else takeoff.Add(p);
		}

		cout << "本单元接受请求结束，接下来进行机场调度\n";
		//优先考虑考虑是否有需要紧急迫降
		//如果剩余时间为1，则紧急降落
		if(p.t==1 && isIdle())					//紧急降落
		{
			p = *landing.Delete(p);
			land3(p);
			nforcelanding++;
		}
		else if(p.t==1)
		{
			p = *landing.Delete(p);
			cout << "需要征用跑道1进行紧急降落\n";
			land1(p);
			nforcelanding++;
			flag1 = 1;
		}
		else if (p.t==1)
		{
			p = *landing.Delete(p);
			cout << "需要征用跑道2进行紧急降落\n";
			land2(p);
			nforcelanding++;
			flag2 = 1;
		}

		//考虑跑道1
		if (landing.QueueCount() != 0 && flag1 == 0)
		{
			p = *landing.Delete(p);
			land1(p);
		}
		else if (takeoff.QueueCount() != 0 && flag1 == 0)
		{
			p = *takeoff.Delete(p);
			fly1(p);
		}
		else if (flag1 == 0)
		{
			idle();
		}

		//考虑跑道2
		if (landing.QueueCount() != 0 && flag2 == 0)
		{
			p = *landing.Delete(p);
			land2(p);
		}
		else if (takeoff.QueueCount() != 0 && flag2 == 0)
		{
			p = *takeoff.Delete(p);
			fly2(p);
		}
		else if (flag2 == 0)
		{
			idle();
		}

		cout<<"降落的平均剩余时间"<<(double)landtime/nland<<endl;
		cout<<"紧急降落的飞机数"<<nforcelanding<<endl;
		nforcelanding=0;

	}
	//for 循环结束
	conclude();
}

int Airport::PoissionRandom(double& expvalue)
{
	int n = 0;		//循环次数
	double limit;	
	double x;	//随机数
	limit = exp(-expvalue);
	//x = (rand() % 1000000) / (double)1000000 + limit;
	x = rand() / (double)INT_MAX;
	while (x > limit)
	{
		n++;
		x *= rand() / (double)INT_MAX;
	}
	return n;
}

plane* Airport::Newplane(plane& p, action kind)
{
	nplanes++;
	p.id = nplanes;
	p.time = currenttime;
	p.t=rand()%4+1;		//随机生成飞机剩余时间,1-4

	landtime=p.t;
	switch (kind)
	{
	case arrive:
		cout << "飞机" << nplanes << "准备降落" << endl;
		break;
	case depart:
		cout << "飞机" << nplanes << "准备起飞" << endl;
		break;
	}
	return &p;
}
void Airport::Refuse(plane& p, action kind)
{
	switch (kind)
	{
	case arrive:
		cout <<"本机场降落队列已满，请飞机" << p.id << "前往其他机场降落" << endl;
		break;
	case depart:
		cout << "本机场起飞队列已满，请飞机" << p.id << "等待起飞指令" << endl;
		break;
	}
	nrefuse++;
}
void Airport::land1(plane& p)
{
	int wait = currenttime - p.time;
	cout << "飞机" << p.id << "在跑道1降落，该机等候降落时间为：" << wait << endl;
	nland++;
	landwait += wait;
}
void Airport::fly1(plane& p)
{
	int wait = currenttime - p.time;
	cout << "飞机" << p.id << "在跑道1起飞，该机等候起飞时间为：" << wait << endl;
	ntakeoff++;
	takeoffwait += wait;
}
void Airport::land2(plane& p)
{
	int wait = currenttime - p.time;
	cout << "飞机" << p.id << "在跑道2降落，该机等候降落时间为：" << wait << endl;
	nland++;
	landwait += wait;
}
void Airport::fly2(plane& p)
{
	int wait = currenttime - p.time;
	cout << "飞机" << p.id << "在跑道2起飞，该机等候起飞时间为：" << wait << endl;
	ntakeoff++;
	takeoffwait += wait;
}
void Airport::land3(plane& p)
{
	int wait = currenttime - p.time;
	cout << "飞机" << p.id << "在紧急跑道3紧急降落，该机等候降落时间为：" << wait << endl;
	nland++;
	landwait += wait;
}
void Airport::idle()
{
	cout << "跑道空闲" << endl;
	idletime++;
}

void Airport::conclude()
{
	cout<<endl;
	cout << "总模拟时间单元数：" << endtime << endl;
	cout << "总共处理的飞机数：" << nplanes << endl;
	cout << "降落飞机总数：" << nland << endl;
	cout << "起飞飞机总数：" << ntakeoff << endl;
	//cout << "紧急降落飞机总数：" << nforcelanding << endl;
	cout << "被拒绝服务的飞机总数：" << nrefuse << endl;
	cout << "剩余的准备起飞飞机数：" << takeoff.size() << endl;
	cout << "剩余的准备降落飞机数：" << landing.size() << endl;


	if (ntakeoff > 0)
		cout << "起飞平均等待时间：" << (double)takeoffwait / ntakeoff << endl;
	if (nland > 0)
		cout << "降落平均等待时间：" << (double)landwait / nland << endl;

	
	
}

bool Airport::isIdle()
{
	if (landing.size() == 0 && takeoff.size() == 0)
		return true;
	else
		return false;
}

int main()
{
	Airport s;
	s.Start();
	return 0;
}