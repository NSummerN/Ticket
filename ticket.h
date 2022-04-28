#include<cstdlib>
#include<iostream>
#include<cstring>
using std::istream;
using std::ostream;
class Ticket_single
{
public:
	Ticket_single();													//���캯�����������
	Ticket_single(int*, int);											//���캯��������洢����
	void summon();														//���ɵ�ʽƱ
	int  prize();														//�жϽ���	
	bool operator==(const Ticket_single& B)const;
	friend ostream& operator<<(ostream& s, const Ticket_single& B) {
		int i;
		for (i = 1; i <= 6; i++)
			s << B.r[i] << ' ';
		s << B.b << '\n';
		return s;
	}
	friend istream& operator>>(istream& s, Ticket_single& B) {
		int i;
		for (i = 1; i <= 6; i++) {
			s >> B.r[i];
		}
		s >> B.b;
		return s;
	}
	 bool legal() {														//�жϺϷ���
		int st[35] = {0};
		int i;
		for (i = 1; i <= 6; i++) {
			if (r[i] <= 0 || r[i] > 33)
				return false;
		}
		if (b <= 0 || b > 16) return false;
		for (i = 1; i <= 6; i++)
			st[r[i]]++;
		for (i = 1; i <= 33; i++) {
			if (st[i] >= 2) {
				return false;
			}
		}
		return true;
	}
	int bonus;															//�洢����
protected:
	int r[10];															//�洢����
private:	
	int b;																//�洢����
	int level;															//�洢����
};
Ticket_single::Ticket_single()
{
	for (int i= 1; i <= 6; i++) r[i] = 0;
	b = 0;
	level = bonus = 0;
}
Ticket_single::Ticket_single(int* arr, int blue) {
	memset(r, 0, sizeof(r));
	b = 0;
	level = bonus = 0;
	int i;
	for (i = 1; i <= 6; i++)  r[i] = arr[i];
	b = blue;
}
bool Ticket_single::operator==(const Ticket_single& B)const {
	int i;
	for (i = 1; i <= 6; i++) 
		if (this->r[i] != B.r[i]) return false;
	return true;
}
void Ticket_single::summon() {
	bool flag[35] = { 0 };
	int i = 1;
	int arr[8];
	while (i <= 6) {
		auto t = Get_new_rand('R');
		if (!flag[t]) {
			arr[i] = t;
			flag[t] = true;
			i++;
		}
		else continue;
	}
	for (i = 1; i <= 6; i++) r[i] = arr[i];
	b = rand() % 16 + 1;
}
class Ticket_compound : Ticket_single 
{
public:
	Ticket_compound();													//���캯������������
	Ticket_compound(int, int, int*, int*);								//���캯���������������������Լ������ֵ
	void summon(int,int);												//���ɣ���������������
	 bool operator==(const Ticket_compound& B)const;
	friend ostream& operator<<(ostream& s, const Ticket_compound& B) {
		s << B.red_nums << ' ' << B.blue_nums << ' ';
		int i;
		for (i = 1; i <= B.red_nums; i++)
			s << B.red[i] << ' ';
		for (i = 1; i <= B.blue_nums; i++)
			s << B.blue[i] << ' ';
		s << std::endl;
		return s;
	}
	friend istream& operator>>(istream& s, Ticket_compound& B) {
		s >> B.red_nums >> B.blue_nums;
		int i;
		for (i = 1; i <= B.red_nums; i++)
			s >> B.red[i];
		for (i = 1; i <= B.blue_nums; i++)
			s >> B.blue[i];
		return s;
	}
	 bool legal();														//�Ƿ�Ϸ�
	 int* getred();														//���ڷ���˽�г�Ա
	 int* getblue();													//���ڷ���˽�г�Ա
	 int get_red_nums() {												//���ڷ���˽�г�Ա
		return red_nums;
	}
	 int get_blue_nums() {												//���ڷ���˽�г�Ա
		return blue_nums;
	}
private:
	int red_nums;														//��������ĺ�������
	int blue_nums;														//�����������������
	int red[35];														//����
	int blue[20];														//����
};
Ticket_compound::Ticket_compound() {
	red_nums = blue_nums = 0;
	memset(red, 0, sizeof(red));
	memset(blue, 0, sizeof(blue));
}
void Ticket_compound::summon(int s1,int s2) {
	red_nums = s1;
	blue_nums = s2;
	int i=1;
	int st1[35] = { 0 }, st2[20] = {0};
	bool ex1[35] = { 0 }, ex2[20] = {0};
	while (i <= red_nums) {
		auto t = Get_new_rand('R');
		if (!ex1[t]) {
			st1[i] = t;
			ex1[t] = true;
			i++;
		}
		else {
			continue;
		}
	}
	i = 1;
	while (i <= blue_nums) {
		auto t = Get_new_rand('B');
		if (!ex2[t]) {
			st2[i] = t;
			ex2[t] = true;
			i++;
		}
		else {
			continue;
		}
	}
	for (i = 1; i <= red_nums; i++) {
		red[i] = st1[i];
	}
	for (i = 1; i <= blue_nums; i++) {
		blue[i] = st2[i];
	}
	cout << "�����ι���ĺ�������:" << endl;
	for (i = 1; i <= red_nums; i++)
		cout << red[i] << ' ';
	cout << endl;
	cout << "�����ι������������:" << endl;
	for (i = 1; i <= blue_nums; i++)
		cout << blue[i] << ' ';
	cout << endl;
}
bool Ticket_compound::operator==(const Ticket_compound& B)const {
	if (this->red_nums != B.red_nums || this->blue_nums != B.blue_nums) return false;
	int i;
	for (i = 1; i <= this->blue_nums; i++)
		if (this->blue[i] != B.blue[i]) return false;
	for (i = 1; i <= this->red_nums; i++)
		if (this->red[i] != B.red[i]) return false;
	return true;
}
Ticket_compound::Ticket_compound(int r, int b, int* Red, int* Blue) {
	red_nums = r;
	blue_nums = b;
	int i;
	for (i = 1; i <= r; i++) red[i] = Red[i];
	for (i = 1; i <= b; i++) blue[i] = Blue[i];
}
bool Ticket_compound::legal() {
	if (red_nums > 33 || red_nums < 7) return false;
	if (blue_nums > 16 || blue_nums < 2) return false;
	int st1[40], st2[40];
	int i;
	for (i = 1; i <= red_nums; i++) st1[red[i]]++;
	for (i = 1; i <= blue_nums; i++) st2[blue[i]]++;
	for (auto e : st1) if (e > 1) return false;
	for (auto e : st2) if (e > 1) return false;
	return true;
}
int* Ticket_compound::getred() {
	return this->red;
}
int* Ticket_compound::getblue() {
	return this->red;
}
