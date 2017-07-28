#include<iostream>
//#include<string>
//#include<algorithm>
//#include<cmath>
#include<vector>
#include<queue>
#include <map>
#include <algorithm>
//#include<stack>
//#include<iomanip>
using namespace std;

#define MAX 535  //最大站点数量
int gFlag[MAX];
typedef unsigned int STATIONID;
typedef unsigned int LINENO;

//保存所有的站点，以及每个站点的可达站点
map<STATIONID, vector<STATIONID> > gAllStations;

//保存每一个站点对应的地铁线编号
map<STATIONID, vector<LINENO> > gStationToLines;

/*******************************************************************************************************************
函数说明： 增加某条地铁线路
函数原型： void AddLine(unsigned int LineNo, unsigned int StationNum ,unsigned  int *pStationArray)；
输入参数：
LineNo        地铁线路号；
StationNum    该条地铁线中的站点数目，由调用者保证不小于2；
pStationArray 该条地铁线的所有站点信息，pStationArray指向的存储空间在函数外会被释放，请自行申请存储空间；
输出参数： 无
返回值  ： 无
********************************************************************************************************************/
void AddLine(unsigned int LineNo, unsigned int StationNum, unsigned  int *pStationArray)
{
	if (NULL == pStationArray || 0 == StationNum) return;

	//下面的循环不够完善，没有检测节点是否已经存在就直接添加到vector中了
	for (int index = 0; index < StationNum - 1; ++index) {
		gAllStations[pStationArray[index]].push_back(pStationArray[index + 1]);
		gAllStations[pStationArray[index + 1]].push_back(pStationArray[index]);

		gStationToLines[pStationArray[index]].push_back(LineNo);
	}
	gStationToLines[pStationArray[StationNum - 1]].push_back(LineNo);

	//环形
	if (pStationArray[0] == pStationArray[StationNum - 1]) {
		gAllStations[pStationArray[StationNum - 1]].push_back(pStationArray[0]);
		gAllStations[pStationArray[0]].push_back(pStationArray[StationNum - 1]);
	}
}

/*********************************************************************************************************************
函数说明：计算从起点站到终点站的最短路线长度   
函数原型：int CalcMinPathLen(unsigned int SrcStation, unsigned int DesStation)；
输入参数：
SrcStation  起点站；
DesStation 终点站；
输出参数：无
返回值  ：
起点站到终点站的最短路线长度
-1：任何出错情况（包括路线不存在、站点不存在、起点和终点重叠等等）
**********************************************************************************************************************/
int CalcMinPathLen(unsigned int SrcStation, unsigned int DesStation)
{
	//可以使用广度优先搜索进行探测出最短路线长度
	queue<STATIONID> waitingQueue;
	if (gAllStations.end() == gAllStations.find(SrcStation)
		|| gAllStations.end() == gAllStations.find(DesStation)
		|| SrcStation == DesStation)
		return -1;

	vector<STATIONID> & adjacencyList = gAllStations[SrcStation];
	for (int index = 0; index < adjacencyList.size(); ++index)
	{
		if (adjacencyList[index] == DesStation) return 1;
		waitingQueue.push(adjacencyList[index]);
	}

	memset(gFlag, 0, sizeof(gFlag));
	gFlag[SrcStation] = 1;

	int minLine = 0;
	while (!waitingQueue.empty())
	{
		++minLine;
		int count = waitingQueue.size();
		for (int i = 0; i < count; ++i) //循环次数 ，也就是控制一层节点的个数
		{
			STATIONID curSrcStation = waitingQueue.front();
			gFlag[curSrcStation] = 1;
			vector<STATIONID> & adjacencyList = gAllStations[curSrcStation];
			for (int index = 0; index < adjacencyList.size(); ++index)
			{
				if (adjacencyList[index] == DesStation) 
					return ++minLine;
				if (0 == gFlag[adjacencyList[index]]) 
					waitingQueue.push(adjacencyList[index]);
			}
			waitingQueue.pop();
		}
	}
	return -1;
}




/**********************************************************************************************************
函数说明：输出从起点站到终点站的最短路线
函数原型：int SearchMinPathes(unsigned int SrcStation,
unsigned int DesStation,
unsigned int* pPathNum,
unsigned int* pPathLen,
unsigned int **ppPathes);
输入参数：
SrcStation 起点站；
DesStation 终点站；
Output Param
pPathNum 最短路线条数;
pPathLen  最短路线长度;
ppPathes 存储最短路线的内存地址，内存空间在本函数内申请，调用者释放，内存空间的存储格式请见PPT要求；
返回值  ：
0 ：成功
-1：任何出错情况（包括路线不存在、站点不存在、起点和终点重叠等等）

************************************************************************************************************/

//dfs search paths
void DFS(unsigned int SrcStation, unsigned int DesStation, 
	map<STATIONID, pair<int, vector<STATIONID> > > & mapPrecursor,
	vector<vector<STATIONID> > & paths)
{
	if (DesStation == SrcStation) {
		vector<STATIONID> vec;
		vec.push_back(SrcStation);
		paths.push_back(vec);
		return;
	}
	
	vector<vector<STATIONID> > tmpPaths;
	vector<STATIONID> & vecPrecursor = mapPrecursor[DesStation].second;
	for (vector<STATIONID>::iterator itrPre = vecPrecursor.begin(); 
		vecPrecursor.end() != itrPre; ++itrPre)
	{	
		DFS(SrcStation, *itrPre, mapPrecursor, tmpPaths);
	}

	for (int index = 0; index < tmpPaths.size(); ++index) {
		tmpPaths[index].push_back(DesStation);
		paths.push_back(tmpPaths[index]);
	}
}

//保存站点的前驱站点以及源节点到此节点的路径长度，前驱节点可能存在多个
map<STATIONID, pair<int, vector<STATIONID> > > mapPrecursor;

const int nINFINITY = 0x7FFFFFFF;

//广度优先搜索算法
int SearchMinPathes(unsigned int SrcStation,
	unsigned int DesStation,
	unsigned int* pPathNum,
	unsigned int* pPathLen,
	unsigned int **ppPathes)
{
	if (gAllStations.end() == gAllStations.find(SrcStation)
		|| gAllStations.end() == gAllStations.find(DesStation)
		|| SrcStation == DesStation
		|| NULL == pPathNum
		|| NULL == pPathLen
		|| NULL == ppPathes)
		return -1;

	//int nTotalStationCount = gAllStations.size();
	map<STATIONID, vector<STATIONID> >::iterator itrStation = gAllStations.begin();
	for ( ; gAllStations.end() != itrStation; ++itrStation)
	{
		pair<int, vector<STATIONID> > pairMetricPre;
		if (itrStation->first == SrcStation) {
			pairMetricPre = make_pair(0, vector<STATIONID>());
		}	
		else if (itrStation->second.end() != 
			std::find(itrStation->second.begin(), itrStation->second.end(), SrcStation)) {
			pairMetricPre = make_pair(1, vector<STATIONID>());
			pairMetricPre.second.push_back(SrcStation);
		}
		else
			pairMetricPre = make_pair(nINFINITY, vector<STATIONID>());

		mapPrecursor.insert(make_pair(itrStation->first, pairMetricPre));
	}

	map<STATIONID, int> stationInQueue;
	queue<STATIONID> waitingQueue;
	stationInQueue[SrcStation] = 1;
	vector<STATIONID> & adjacencyList = gAllStations[SrcStation];
	for (int index = 0; index < adjacencyList.size(); ++index)
	{
		if (adjacencyList[index] == DesStation) return 1;
		waitingQueue.push(adjacencyList[index]);
		stationInQueue[adjacencyList[index]] = 1;
	}

	memset(gFlag, 0, sizeof(gFlag));
	gFlag[SrcStation] = 1;

	while (!waitingQueue.empty())
	{
		STATIONID curStation = waitingQueue.front();
		vector<STATIONID> & adjacencyList = gAllStations[curStation];
		for (int index = 0; index < adjacencyList.size(); ++index)
		{
			if (1 == gFlag[adjacencyList[index]]) continue;
			if (mapPrecursor[curStation].first + 1 < mapPrecursor[adjacencyList[index]].first) {
				mapPrecursor[adjacencyList[index]].first = mapPrecursor[curStation].first + 1;
				mapPrecursor[adjacencyList[index]].second.clear();
				mapPrecursor[adjacencyList[index]].second.push_back(curStation);
			}
			else if (mapPrecursor[curStation].first + 1 == mapPrecursor[adjacencyList[index]].first) {
				mapPrecursor[adjacencyList[index]].second.push_back(curStation);
			}

			if (stationInQueue[adjacencyList[index]] != 1) {
				waitingQueue.push(adjacencyList[index]);
				stationInQueue[adjacencyList[index]] = 1;
			}
		}

		gFlag[curStation] = 1;
		waitingQueue.pop();

		if (curStation == DesStation) break;
	}

	if (gFlag[DesStation] != 1) return -1;

	vector<vector<STATIONID> > shortestPaths;
	DFS(SrcStation, DesStation, mapPrecursor, shortestPaths);
	*pPathNum = shortestPaths.size();
	if (0 == *pPathNum) 
		return -1;
	*pPathLen = shortestPaths[0].size() - 1;
	for (int i = 0; i < shortestPaths.size(); ++i)
	{
		ppPathes[i] = (unsigned int*)malloc(sizeof(unsigned int) * (*pPathLen + 1));
		for (int j = 0; j < shortestPaths[i].size(); ++j)
		{
			ppPathes[i][j] = shortestPaths[i][j];
		}
	}
	
	return 0;
}


/*************************************************************************************************
函数说明：输出从起点站到终点站的最优路线
函数原型：int SearchBestPathes(unsigned int SrcStation,
unsigned int DesStation,
unsigned int *pPathNum,
unsigned int* pPathLen,
unsigned int** ppPathes);
输入参数：
SrcStation 起点站；
DesStation 终点站；
Output Param
pPathNum 最优路线条数;
pPathLen  最短路线长度;
ppPathes 存储最短路线的内存地址，内存格式见下图,内存空间在本函数内申请，调用者释放；
返回值 ：
0：成功
-1：任何出错情况（包括路线不存在、站点不存在、起点和终点重叠等等）
**************************************************************************************************/
bool PairCompare(pair<int, int> & first, pair<int, int> & second) { return (first.first < second.first); }

int SearchBestPathes(unsigned int SrcStation,
	unsigned int DesStation,
	unsigned int *pPathNum,
	unsigned int* pPathLen,
	unsigned int** ppPathes)
{
	unsigned int shortestPathNum, *ppShortestPathes[70] = { NULL };
	SearchMinPathes(SrcStation, DesStation, &shortestPathNum, pPathLen, ppShortestPathes);
	vector<int> vecTransferTime;
	for (int i = 0; i < shortestPathNum; ++i) {
		vecTransferTime.push_back(0);
	}

	vector<LINENO> takeLines;
	for (int i = 0; i < shortestPathNum; ++i) {
		takeLines.clear();
		for (int k = 0; k < gStationToLines[SrcStation].size(); ++k) {
			takeLines.push_back(gStationToLines[SrcStation][k]);
		}

		for (int j = 0; j < *pPathLen; ++j) {
			vector<LINENO> & vecCurLines = gStationToLines[ppShortestPathes[i][j]];
			vector<LINENO>::iterator itrLine = takeLines.begin();
			for (; takeLines.end() != itrLine; ) {
				if (vecCurLines.end() != std::find(vecCurLines.begin(), vecCurLines.end(), *itrLine)) {
					++itrLine;
				}
				else {
					itrLine = takeLines.erase(itrLine);
				}
			}

			//如果本站还在原来乘坐的线路上，但是下一站已经不在了，则说明在本站就需要换乘了
			bool isNextFound = false;
			vector<LINENO> & vecNextLines = gStationToLines[ppShortestPathes[i][j + 1]];
			for (itrLine = takeLines.begin(); takeLines.end() != itrLine; ++itrLine) {
				if (vecNextLines.end() != std::find(vecNextLines.begin(), vecNextLines.end(), *itrLine)) {
					isNextFound = true;
				}
			}
			if (!isNextFound) {
				++vecTransferTime[i];

				vector<LINENO> tmpTakeLines = vecCurLines;
				for (itrLine = takeLines.begin(); takeLines.end() != itrLine;) {
					if (tmpTakeLines.end() != std::find(tmpTakeLines.begin(), tmpTakeLines.end(), *itrLine)) {
						itrLine = takeLines.erase(itrLine);
					}
					else {
						++itrLine;
					}
				}
				takeLines = tmpTakeLines;
			}
		}
	}

	int index = 0;
	//pair<times, index>
	vector<pair<int, int> > timesIndex;
	for (vector<int>::iterator itrTime = vecTransferTime.begin();
		vecTransferTime.end() != itrTime; ++itrTime, ++index) {
		timesIndex.push_back(make_pair(*itrTime, index));
	}

	std::sort(timesIndex.begin(), timesIndex.end(), PairCompare);
	int minTransfer = timesIndex[0].first;
	*pPathNum = 1;
	ppPathes[0] = ppShortestPathes[timesIndex[0].second];

	for (int i = 1; i < timesIndex.size(); ++i) {
		if (timesIndex[i].first == minTransfer) {
			ppPathes[i] = ppShortestPathes[timesIndex[i].second];
		} 
		else {
			free(ppShortestPathes[timesIndex[i].second]);
		}
	}

	return 0;
}

/*************************************************************************************************
函数说明：清空所有的线路信息
函数原型：void Clear();
输入参数：无
输出参数：无
返回值  ：无
**************************************************************************************************/
void Clear()
{

	/* 在这里实现功能 */
	
	return;

}

int main()
{
	unsigned int Line1[] = { 1, 2, 3, 4, 5 };
	unsigned int Line2[] = { 1, 10, 9, 7, 6 };
	unsigned int Line3[] = { 5, 7, 8 };
	unsigned int Line4[] = { 11, 5 };
	int Ret, i;
	unsigned int pPathNum, pPathLen, *ppPathes[70] = { NULL };
	AddLine(1, 5, &Line1[0]);
	AddLine(2, 5, &Line2[0]);
	AddLine(3, 3, &Line3[0]);
	AddLine(4, 2, &Line4[0]);

	/*cout << CalcMinPathLen(1, 11) << endl;
	SearchMinPathes(1, 11, &pPathNum, &pPathLen, ppPathes);
	cout << pPathLen << " " << pPathNum << endl;
	for (Ret = 0; Ret<pPathNum; Ret++)
	{
	for (i = 0; i <= pPathLen; i++)
	cout << ppPathes[Ret][i] << " ";
	cout << endl;
	}
	Clear();*/

	SearchBestPathes(1, 11, &pPathNum, &pPathLen, ppPathes);
	cout << pPathLen << " " << pPathNum << endl;
	for (Ret = 0; Ret < pPathNum; Ret++)
	{
		for (i = 0; i <= pPathLen; i++)
			cout << ppPathes[Ret][i] << " ";
		cout << endl;
	}
	/*if (SearchMinPathes(1, 11, &pPathNum, &pPathLen, ppPathes) == -1)cout << "NO" << endl;
	cout << CalcMinPathLen(1, 11) << endl;*/
	return 0;
}
