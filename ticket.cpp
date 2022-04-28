#include<cstdio>
#include<iostream>
#include<cstdlib>
#include"ticket.h"
#include"pool.h"
#include<ctime>
#include<Windows.h>
#pragma warning(disable:4996)
using namespace std;
int Red_Ball[35],Blue_Ball;
void info_output();																	//起始信息输出
void menu();																		//主菜单函数
void set_prize();																	//单注票开奖
void set_compound();																//复式票开奖
int now;																			//本次购买了多少注彩票
int now_prize;																		//本注彩票中了多少钱
int sums;																			// 总中奖金额
int single_get;																		//总共购买了多少单式票
int compound_get;																	//购买的复式票等效于多少单式票
int com_get;																		//购买的复式票，未等效
void get_single();																	//购买一张单式票的函数
void get_compound();																//购买一张复式票的函数
void set_nums();																	//设置单式票的中奖信息
void end();																			//程序的结束与统计数据的输出
inline int fact(int n) {
	return n == 0 ? 1 : n == 1 ? 1 : n * fact(--n);
}
																					//阶乘函数，用于组合的计算
inline int combination(int a, int b) {
	return fact(a) / (fact(b) * fact(a - b));
}
																					//组合数的计算
int equal_number(int* a, int* b) {
	int n = 0;
	int i, j;
	for (i = 1; i <= 6; i++)
		for (j = 1; j <= 6; j++)
			if (a[i] == Red_Ball[j]) n++;
	return n;
}
int equal_number(int* a, int lena) {
	int n = 0;
	int i, j;
	for (i = 1; i <= lena; i++)
		for (j = 1; j <= 6; j++)
			if (a[i] == Red_Ball[j]) n++;
	return n;
}
void set_ticket() {
	cout << "正在生成中奖彩票，请稍候" << endl;
	int i = 1;
	int st[100] = {0};
	bool ex[35] = {0};
	while (i <= 6) {
		auto t = Get_new_rand('R');
		if (!ex[t]) {
			st[i] = t;
			ex[t] = true;
			i++;
		}
		else continue;
	}
	for (i = 1; i <= 6; i++) Red_Ball[i] = st[i];
	cout << "本次中奖号码为:" << endl;
	cout << "红球:";
	for (i = 1; i <= 6; i++) cout << Red_Ball[i] << ' ';
	Blue_Ball = Get_new_rand('B');
	cout << endl<<"蓝球:" << Blue_Ball << endl;
}
																					//生成并输出中奖彩票
inline void judge(double& p) {
	p = p >= 5e6 ? 5e6 : p;
}
																					//辅助函数，用于奖池计算
int Get_new_rand(char ch) {
	srand(time(NULL));
	auto n = ch == 'r' || ch == 'R' ? rand() % 33 + 1 : ch == 'B' || ch == 'b' ? rand() % 16 + 1 : -1;
	return n;
}
																					//生成随机数的函数
int highest(Ticket_compound t) {
	int red_c = equal_number(t.getred(), t.get_red_nums());
	auto blue = t.getblue();
	int i, bans = 0;
	auto size = t.get_blue_nums();
	for (i = 1; i <= size; i++) {
		if (Blue_Ball == blue[i]) {
			bans = 1;
			break;
		}
	}
	if (bans) {
		switch (red_c) {
		case 6:return 1; break;
		case 5:return 3; break;
		case 4:return 3; break;
		case 3:return 5; break;
		case 2:return 6; break;
		case 1:return 6; break;
		case 0:return 6; break;
		}
	}
	else {
		switch (red_c) {
		case 6:return 2; break;
		case 5:return 4; break;
		case 4:return 5; break;
		case 3:return 0; break;
		case 2:return 0; break;
		case 1:return 0; break;
		case 0:return 0; break;
		}
	}
	return -1;
}
																					//确定复式票的最高奖级
int* turn(Ticket_compound t) {
	bool flag = false;//用来标记蓝球是否中奖
	auto arr = t.getblue();
	auto len = t.get_blue_nums();
	auto rc = equal_number(t.getred(), Red_Ball);
	for (int i = 1; i <= len; i++) 
		if (arr[i] == Blue_Ball) {
			flag = true;
			break;
		}
	auto aha = highest(t);
	int s[10];
	s[aha] = 1;
	if (aha == 1) {
		s[2] = 1;
		s[3] = 6;
		s[4] = combination(6, 4) + combination(6, 5);
		s[5] = combination(6, 3) + combination(6, 4);
		s[6] = combination(6, 2) + combination(6, 1) + 1;
	}
	else if (aha == 2) {
		s[1] = s[3] = s[6] = 0;
		s[4] = combination(6, 5);
		s[5] = combination(6, 4);
	}
	else if (aha == 3) {
		s[1] = s[2] = 0;
		s[4] = 1 + combination(5, 4);
		s[5] = combination(5, 4) + combination(5, 3);
		s[6] = combination(5, 2) + combination(5, 1) + 1;
	}
	else if (aha == 4) {
		s[1] = s[2] = s[3] = 0;
		if (flag) {
			s[5] = 1 + combination(4, 3);
			s[6] = combination(4, 2) + combination(4, 1) + 1;
		}
		else {
			s[5] = combination(5, 4);
			s[6] = 0;
		}
	}
	else if (aha == 5) {
		s[1] = s[2] = s[3] = s[4] = 0;
		if (flag) s[6] = combination(3, 2) + combination(3, 1) + 1;
		else s[6] = 0;
	}
	else if (aha == 6) {
		s[1] = s[2] = s[3] = s[4] = s[5] = 0;
		s[6] = rc == 2 ? 4 : rc == 1 ? 2 : 1;
	}
	else  s[1] = s[2] = s[3] = s[4] = s[5] = s[6] = 0;
	return s;
}
																					//确定此注复式票的价值，注意返回值是数组
int main() {
	pool::start();
	info_output();
	menu();
	set_prize();
	set_compound();
	end();
	return 0;
}
void info_output() {
	system("title 模拟彩票购买程序");
	cout << "欢迎来到模拟彩票购买程序"<<endl;
	cout << "按任意键以进入程序" << endl;
	system("pause");
	system("cls");
}
void menu() {
	printf("目前奖池:%.0f元\n", pool::fund_1);
buy:	
	cout << "1 - 购买单式票" << endl;
	cout << "2 - 购买复式票" << endl;
	char ch;
	while (1) {
		cin >> ch;
		if (ch == '1') {
			cout << "您想购买多少张单式票" << endl;
			int n,i;
			cin >> n;
			for(i = 1;i <= n;i++) get_single();
			cout << "购买成功!" << endl;
ifgo:
			cout << "是否需要再次购买 (Y/N)" << endl;
			char c1;
			cin >> c1;
			if (c1 == 'Y' || c1 == 'y') goto buy;
			else if(c1 == 'N' || c1 == 'n')break;
			else {
				cout << "输入错误，请重新输入"<<endl;
				goto ifgo;
			}
		}
		else if (ch == '2') {
			cout << "您想购买多少张复式票" << endl;
			int n, i;
			cin >> n;
			for (i = 1; i <= n; i++) get_compound();
			cout << "购买成功!" << endl;
ifgo2:
			cout << "是否需要再次购买(Y/N)" << endl;
			char c1;
			cin >> c1;
			if (c1 == 'y' || c1 == 'Y') goto buy;
			else if (c1 == 'n' || c1 == 'N') break;
			else {
				cout << "输入错误，请重新输入" << endl;
				goto ifgo2;
			}
			get_compound();
			break;
		}
		else {
			cout << "输入错误，请重新输入";
			continue;
		}
	}

}
void set_prize() {																	//单式票开奖
	set_ticket();
	freopen("ticket.dat", "r", stdin);
	int i;
	Ticket_single now_t;
	for (i = 1; i <= now; i++) {
		cin >> now_t;
		auto p = now_t.prize();														//p：该次彩票中奖的奖级
		pool::nums[p]++;
		now_t.bonus = pool::award[p];
		sums += now_t.bonus;
	}
}
void get_single() {																	//购买一张单式票
	now++;
	single_get++;
	cout << "请选择购买类型:1-机选 2-自选 3-返回到上一级 其他-退出程序" << endl;
	getchar();
	char ch = getchar();
	while (1) {
		if (ch == '1') {
			auto t = Ticket_single();
			t.summon();
			cout << "您购买的号码为:" << endl;
			cout << t;
			freopen("ticket.dat", "a", stdout);
			cout << t;
			freopen("CON", "w", stdout);
			break;
		}
		else if (ch == '2') {
		buy_tic:
			cout << "请输入您希望购买的红球,按回车结束输入"<<endl;
			int arr[10] = {0}, bl;
			int i;
			for (i = 1; i <= 6; i++) cin >> arr[i];
			cout << "请输入您希望购买的蓝球，按回车结束输入"<<endl;
			cin >> bl;
			auto t = Ticket_single(arr, bl);
			if (!t.legal()) {
				cout << "您输入的彩票不符合规范，请重新输入!"<<endl;
				goto buy_tic;
			}
			freopen("ticket.dat", "a", stdout);
			cout << t;
			freopen("CON", "w", stdout);
			break;
		}
		else if(ch == '3') return;
		else exit(0);
	}
}
void get_compound() {																//购买一张复式票
	int size;
	com_get++;
	cout << "请选择购买类型:1-机选 2-自选 3-返回到上一级 其他-退出程序" << endl;
	char ch;
	while (1) {
		cin >> ch;
		int r,b;
		auto t = Ticket_compound();
		switch (ch) {
		case '1':
			cout << "请输入您希望购买的红球数量:";
			cin >> r;
			cout << "请输入您希望购买的蓝球数量:";
			cin >> b;
			size = combination(r, 6) * b;
			now += size;
			compound_get += size;
			t.summon(r,b);
			freopen("compound.dat","a", stdout);
			cout << t;
			freopen("CON", "w", stdout);
			return;
		case '2':
			cout << "请输入您希望购买的红球数量:";
			cin >> r;
			cout << "请输入您希望购买的蓝球数量:";
			cin >> b;
			size = combination(r, 6) * b;
			now += size;
			compound_get += size;
			int i;
			int temp1[35],temp2[35];
			cout << "请依次输入红球" << endl;
			for (i = 1; i <= r; i++)
				cin >> temp1[i];
			cout << "请依次输入蓝球" << endl;
			for (i = 1; i <= b; i++)
				cin >> temp2[i];
			t = Ticket_compound(r, b, temp1, temp2);
			if (!t.legal()) cout << "您的输入有误，请重新输入:" << endl;
			freopen("compound.dat", "a", stdout);
			cout << t;
			freopen("CON", "w", stdout);
			return;
		case '3':
			return;
			break;
		default:
			exit(0);
			break;
		}
	}
}
void set_nums() {
	int i;
	freopen("ticket.dat", "r", stdin);
	Ticket_single t;
	for (i = 1; i <= single_get; i++) {
		cin >> t;
		auto p = t.prize( );
		pool::nums[p]++;                                                                                                                         
	}
	freopen("CON", "r", stdin);
}
void set_nums_com() {
	int i;
	freopen("compound.dat", "r", stdin);
	Ticket_compound t;
	for (i = 1; i <= compound_get; i++) {
		cin >> t;
		auto p = highest(t);//确定此复式票所获得的最高奖级
		auto st = turn(t);
		for (i = 1; i <= 6; i++) pool::nums[st[i]]++;
	}
	freopen("CON", "r", stdin);
}
void end() {
	char ch;
	cout << "您本次一共购买了" << single_get << "张单式票"<<endl;
	cout << "您本次一共购买了" << com_get << "张复式票" << endl;
	cout << "总投资" << now * 2 << "元" << endl;
	cout << "总回报" << sums << "元" <<endl;
	double t1, t2, t3;
	t1 = (double)now * 2;
	t2 = (double)sums;

	printf("回报率%.2lf%%\n", t2/t1 * 100.0);
	cout << "按任意键退出程序\n" << endl;
	cin >> ch;
	cout << "感谢使用，程序将于五秒后自动关闭" << endl;
	Sleep(5000);
	exit(0);
}
void set_compound() {
	freopen("compound.dat", "r", stdin);
	auto now_t = Ticket_compound();
	int i;
	for (i = 1; i <= com_get; i++) {
		cin >> now_t;
		auto p = highest(now_t);
		auto arr = turn(now_t);
		auto all_bonus = 0;
		for (int j = 1; j <= 6; j++) all_bonus += pool::award[j]*arr[j];
	}
	freopen("CON", "r", stdin);
}
int Ticket_single::prize() {
	auto n = equal_number(r, Red_Ball);
	if (b == Blue_Ball) {
		switch (n) {
			 case 6:level = 1; return 1; break;
			 case 5:level = 3; return 3; break;
			 case 4:level = 3; return 3; break;
			 case 3:level = 5; return 5; break;
			 case 2:level = 6; return 6; break;
			 case 1:level = 6; return 6; break;
			 case 0:level = 6; return 6; break;
		}
	}
	else {
		switch (n) {
			 case 6:level = 2; return 2; break;
			 case 5:level = 4; return 4; break;
			 case 4:level = 5; return 5; break;
			 case 3:level = 0; return 0; break;
			 case 2:level = 0; return 0; break;
			 case 1:level = 0; return 0; break;
			 case 0:level = 0; return 0; break;
			 }
		 }
	return -1;
 }
void pool::round() {
	for (i = 1; i <= 6; i++) number += nums[i];//计算中奖的彩票注数
	sales = 2 * number;
	bonus = 0.49 * sales;
	for (i = 3; i <= 6; i++) low_bonus += nums[i] * award[i];
	high_bonus = bonus - low_bonus;
	a = (0.3 * high_bonus) / nums[2];
	b = (0.7 * high_bonus + fund_1) / nums[1];
	c = (0.5 * high_bonus + fund_1) / nums[1];
	d = (0.2 * high_bonus + fund_1) / nums[1];
	if (nums[2]) {
		award[2] = a;
		judge(award[2]);
		fund_surplus += (a - award[2]);
	}
	else  fund_saved += a;
	if (nums[1]) {
		if (fund_1 < 1e8) {
			award[1] = b;
			judge(award[1]);
			fund_surplus += (b - award[1]);
		}
		else {
			e = c;
			f = d;
			judge(e);
			judge(f);
			award[1] = e + f;
			fund_surplus += c - e + d - f;
		}
	}
	else  fund_saved += b;
	fund_2 = fund_saved + fund_surplus;
	fund_1 = fund_2;
}