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

#define MAX 535  //���վ������
int gFlag[MAX];
typedef unsigned int STATIONID;
typedef unsigned int LINENO;

//�������е�վ�㣬�Լ�ÿ��վ��Ŀɴ�վ��
map<STATIONID, vector<STATIONID> > gAllStations;

//����ÿһ��վ���Ӧ�ĵ����߱��
map<STATIONID, vector<LINENO> > gStationToLines;

/*******************************************************************************************************************
����˵���� ����ĳ��������·
����ԭ�ͣ� void AddLine(unsigned int LineNo, unsigned int StationNum ,unsigned  int *pStationArray)��
���������
LineNo        ������·�ţ�
StationNum    �����������е�վ����Ŀ���ɵ����߱�֤��С��2��
pStationArray ���������ߵ�����վ����Ϣ��pStationArrayָ��Ĵ洢�ռ��ں�����ᱻ�ͷţ�����������洢�ռ䣻
��������� ��
����ֵ  �� ��
********************************************************************************************************************/
void AddLine(unsigned int LineNo, unsigned int StationNum, unsigned  int *pStationArray)
{
	if (NULL == pStationArray || 0 == StationNum) return;

	//�����ѭ���������ƣ�û�м��ڵ��Ƿ��Ѿ����ھ�ֱ����ӵ�vector����
	for (int index = 0; index < StationNum - 1; ++index) {
		gAllStations[pStationArray[index]].push_back(pStationArray[index + 1]);
		gAllStations[pStationArray[index + 1]].push_back(pStationArray[index]);

		gStationToLines[pStationArray[index]].push_back(LineNo);
	}
	gStationToLines[pStationArray[StationNum - 1]].push_back(LineNo);

	//����
	if (pStationArray[0] == pStationArray[StationNum - 1]) {
		gAllStations[pStationArray[StationNum - 1]].push_back(pStationArray[0]);
		gAllStations[pStationArray[0]].push_back(pStationArray[StationNum - 1]);
	}
}

/*********************************************************************************************************************
����˵������������վ���յ�վ�����·�߳���   
����ԭ�ͣ�int CalcMinPathLen(unsigned int SrcStation, unsigned int DesStation)��
���������
SrcStation  ���վ��
DesStation �յ�վ��
�����������
����ֵ  ��
���վ���յ�վ�����·�߳���
-1���κγ������������·�߲����ڡ�վ�㲻���ڡ������յ��ص��ȵȣ�
**********************************************************************************************************************/
int CalcMinPathLen(unsigned int SrcStation, unsigned int DesStation)
{
	//����ʹ�ù��������������̽������·�߳���
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
		for (int i = 0; i < count; ++i) //ѭ������ ��Ҳ���ǿ���һ��ڵ�ĸ���
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
����˵������������վ���յ�վ�����·��
����ԭ�ͣ�int SearchMinPathes(unsigned int SrcStation,
unsigned int DesStation,
unsigned int* pPathNum,
unsigned int* pPathLen,
unsigned int **ppPathes);
���������
SrcStation ���վ��
DesStation �յ�վ��
Output Param
pPathNum ���·������;
pPathLen  ���·�߳���;
ppPathes �洢���·�ߵ��ڴ��ַ���ڴ�ռ��ڱ����������룬�������ͷţ��ڴ�ռ�Ĵ洢��ʽ���PPTҪ��
����ֵ  ��
0 ���ɹ�
-1���κγ������������·�߲����ڡ�վ�㲻���ڡ������յ��ص��ȵȣ�

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

//����վ���ǰ��վ���Լ�Դ�ڵ㵽�˽ڵ��·�����ȣ�ǰ���ڵ���ܴ��ڶ��
map<STATIONID, pair<int, vector<STATIONID> > > mapPrecursor;

const int nINFINITY = 0x7FFFFFFF;

//������������㷨
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
����˵������������վ���յ�վ������·��
����ԭ�ͣ�int SearchBestPathes(unsigned int SrcStation,
unsigned int DesStation,
unsigned int *pPathNum,
unsigned int* pPathLen,
unsigned int** ppPathes);
���������
SrcStation ���վ��
DesStation �յ�վ��
Output Param
pPathNum ����·������;
pPathLen  ���·�߳���;
ppPathes �洢���·�ߵ��ڴ��ַ���ڴ��ʽ����ͼ,�ڴ�ռ��ڱ����������룬�������ͷţ�
����ֵ ��
0���ɹ�
-1���κγ������������·�߲����ڡ�վ�㲻���ڡ������յ��ص��ȵȣ�
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

			//�����վ����ԭ����������·�ϣ�������һվ�Ѿ������ˣ���˵���ڱ�վ����Ҫ������
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
����˵����������е���·��Ϣ
����ԭ�ͣ�void Clear();
�����������
�����������
����ֵ  ����
**************************************************************************************************/
void Clear()
{

	/* ������ʵ�ֹ��� */
	
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
