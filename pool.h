constexpr auto origin = 1e8;
namespace pool {
	double award[7] = { 0,0,0,3000,200,10,5 };//���Ƚ���ע����� 
	double a, b, c, d, e, f;
	int i;
	int nums[7] = { 0 };//���Ƚ��е�ע���������� 
	int number = 0;//��ע�� 
	int sales;
	double bonus;//���ڽ���
	double low_bonus,high_bonus;
	double fund_1;//�����ʽ� 
	double fund_2;//���ڽ����ʽ� 
	double fund_saved = 0;//δ�г��Ľ���
	double fund_surplus = 0;//����500��Ĳ���
	void round();
	void start() {
		fund_1 = origin;
	}
}