// n个骰子的点数
// 把n个骰子仍地上，所有骰子朝上一面的点数之和为s
// 输入n，打印出s的所有可能的值出现的概率

int g_maxValue = 6;

void PrintProbability(int number) {
	// 分配哈希数组，用于存储每个可能出现的s的值的概率
	if (number < 1) 
		return;
	int maxSum = number * g_maxValue;
	int *pProbability = new int[maxSum - number + 1];
	for (int i = number; i <= maxSum; i++)
		pProbability[i - number] = 0;
	// 调用主要计算函数，模拟投骰子的过程，统计出现的频数
	probability(number, pProbability);
	// 计算概率
	int total = power(static_cast<double>(g_maxValue), number);
	for (int i = number; i <= maxSum; i++) {
		double ratio = static_cast<double>(pProbability[i - number]) / number;
		std::cout << i << "出现的概率为 " << ratio << std::endl;
	}
	delete [] pProbability;
}

void probability(int number, int *pProbability) {
	// 具体模拟的统计过程
	if (number <= 0)
		return;

}

// hash table 视为一种字典结构
// 线性探测 二次探测 开链 负载系数（元素个数/表格的大小）
// 惰性删除