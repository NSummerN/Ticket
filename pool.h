constexpr auto origin = 1e8;
namespace pool {
	double award[7] = { 0,0,0,3000,200,10,5 };//各等奖单注奖金额 
	double a, b, c, d, e, f;
	int i;
	int nums[7] = { 0 };//各等奖中的注数（待处理） 
	int number = 0;//总注数 
	int sales;
	double bonus;//当期奖金
	double low_bonus,high_bonus;
	double fund_1;//奖池资金 
	double fund_2;//下期奖池资金 
	double fund_saved = 0;//未中出的奖金
	double fund_surplus = 0;//多于500万的部分
	void round();
	void start() {
		fund_1 = origin;
	}
}