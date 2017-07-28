#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

typedef unsigned int CELLID;

//保存所有的蜂窝小区
map<CELLID, vector<CELLID> > gAllCells;

//初始化蜂窝网络拓扑
int InitializeCellular(unsigned int unMaxCellNum)
{
	vector<unsigned int> startNum, overNum;
	startNum.push_back(1);
	overNum.push_back(1);

	int layer = (int)sqrt(double((unMaxCellNum - 1) / 3)) + 1;
	for (int i = 1; i < layer; ++i)
	{
		startNum.push_back(overNum[i - 1] + 1);
		overNum.push_back(overNum[i - 1] + i * 6);
	}

	int interval = -1;
	for (unsigned int num = 2, layer = 1, inner = 1; num <= unMaxCellNum; ++num)
	{
		if (num == startNum[layer]) {
			interval = layer - 1;
			inner = startNum[layer - 1];

			gAllCells[num].push_back(inner);
			gAllCells[inner].push_back(num);

			if (layer > 1) {
				gAllCells[num].push_back(overNum[layer - 1]);
				gAllCells[overNum[layer - 1]].push_back(num);
			}
			--interval;
		}
		else if (num > startNum[layer] && num < overNum[layer]) {
			gAllCells[num].push_back(num - 1);
			gAllCells[num - 1].push_back(num);

			gAllCells[num].push_back(inner);
			gAllCells[inner].push_back(num);
			if (interval > 0) {
				++inner;
				gAllCells[num].push_back(inner);
				gAllCells[inner].push_back(num);
				--interval;
			}
			else {
				interval = layer - 1;
			}
		}
		else if (num == overNum[layer]) {
			gAllCells[num].push_back(num - 1);
			gAllCells[num - 1].push_back(num);

			gAllCells[num].push_back(inner);
			gAllCells[inner].push_back(num);

			gAllCells[num].push_back(startNum[layer]);
			gAllCells[startNum[layer]].push_back(num);

			++layer;
		}
	}


	return 0;
}






int main()
{
	InitializeCellular(61);
	return 0;
}