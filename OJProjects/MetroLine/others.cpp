//#include<iostream>
////#include<string>
////#include<algorithm>
////#include<cmath>
//#include<vector>
//#include<queue>
////#include<stack>
////#include<iomanip>
//using namespace std;
//
//#define MAX 535
//int flag[MAX];
//vector<int>station_reach[MAX];
//static vector<int>myfront[MAX];
///*******************************************************************************************************************
//函数说明： 增加某条地铁线路
//函数原型： void AddLine(unsigned int LineNo, unsigned int StationNum ,unsigned  int *pStationArray)；
//输入参数：
//LineNo        地铁线路号；
//StationNum    该条地铁线中的站点数目，由调用者保证不小于2；
//pStationArray 该条地铁线的所有站点信息，pStationArray指向的存储空间在函数外会被释放，请自行申请存储空间；
//输出参数： 无
//返回值  ： 无
//********************************************************************************************************************/
//void AddLine(unsigned int LineNo, unsigned int StationNum, unsigned  int *pStationArray)
//{
//	/* 在这里实现功能 */
//
//	int i;
//	for (i = 1; i<StationNum; i++)
//	{
//		station_reach[pStationArray[i]].push_back(pStationArray[i - 1]);
//		station_reach[pStationArray[i - 1]].push_back(pStationArray[i]);
//	}
//
//	return;
//
//}
//
///*********************************************************************************************************************
//函数说明：计算从起点站到终点站的最短路线长度
//函数原型：int CalcMinPathLen(unsigned int SrcStation, unsigned int DesStation)；
//输入参数：
//SrcStation  起点站；
//DesStation 终点站；
//输出参数：无
//返回值  ：
//起点站到终点站的最短路线长度
//-1：任何出错情况（包括路线不存在、站点不存在、起点和终点重叠等等）
//**********************************************************************************************************************/
//int CalcMinPathLen(unsigned int SrcStation, unsigned int DesStation)
//{
//
//	/* 在这里实现功能 */
//	if (SrcStation == DesStation)return -1;
//	int i, j, newsta;
//	int minlen = 1, count = 0;
//	queue<int>qsta;
//	/*
//	for(i=1;i<11;i++)
//	{
//	cout<<i<<"站"<<":";
//	for(j=0;j<station_reach[i].size();j++)
//	cout<<station_reach[i][j]<<" ";
//	cout<<endl;
//	}
//	cout<<endl;
//	*/
//	memset(flag, 0, sizeof(flag));
//
//	for (i = 0; i<station_reach[SrcStation].size(); i++)
//	{
//		if (station_reach[SrcStation][i] == DesStation)return minlen;
//		qsta.push(station_reach[SrcStation][i]);
//		//count++;
//	}
//	flag[SrcStation] = 1;
//	int ss = qsta.size();
//	while (!qsta.empty())
//	{
//
//		minlen++;
//		count = qsta.size();
//		while (count--){
//			newsta = qsta.front();
//			flag[newsta] = 1;
//			for (i = 0; i<station_reach[newsta].size(); i++)
//			{
//				if (station_reach[newsta][i] == DesStation)return minlen;
//				if (flag[station_reach[newsta][i]] == 0)qsta.push(station_reach[newsta][i]);
//			}
//			qsta.pop();
//		}
//	}
//	if (qsta.empty()) return -1;
//
//	return 0;
//
//};
//
//
//
//
///**********************************************************************************************************
//函数说明：输出从起点站到终点站的最短路线
//函数原型：int SearchMinPathes(unsigned int SrcStation,
//unsigned int DesStation,
//unsigned int* pPathNum,
//unsigned int* pPathLen,
//unsigned int **ppPathes);
//输入参数：
//SrcStation 起点站；
//DesStation 终点站；
//Output Param
//pPathNum 最短路线条数;
//pPathLen  最短路线长度;
//ppPathes 存储最短路线的内存地址，内存空间在本函数内申请，调用者释放，内存空间的存储格式请见PPT要求；
//返回值  ：
//0 ：成功
//-1：任何出错情况（包括路线不存在、站点不存在、起点和终点重叠等等）
//
//************************************************************************************************************/
//void dfs(unsigned int SrcStation,
//	unsigned int DesStation,
//	unsigned int minlen,
//	unsigned int *pPathLen,
//	unsigned int* pPathNum,
//	unsigned int **pPathes
//	)
//{
//	int i, j;
//
//	if (minlen == 1)
//	{
//		if (myfront[DesStation][0] == SrcStation)
//		{
//			(*pPathNum)++;
//			pPathes[(*pPathNum) - 1] = (unsigned int *)malloc((*pPathLen + 1)*sizeof(unsigned int));
//			memset(pPathes[(*pPathNum) - 1], 0, (*pPathLen + 1)*sizeof(unsigned int));
//			pPathes[(*pPathNum) - 1][minlen - 1] = SrcStation;
//			pPathes[(*pPathNum) - 1][minlen] = DesStation;
//
//			//cout<<DesStation<<" "<<minlen<<" "<<*pPathNum<<endl;
//		}
//		return;
//	}
//
//	for (i = 0; i<myfront[DesStation].size(); i++)
//	{
//		j = myfront[DesStation][i];
//		//cout<<j<<" "<<minlen-1<<endl;
//		dfs(SrcStation, j, minlen - 1, pPathLen, pPathNum, pPathes);
//		pPathes[(*pPathNum) - 1][minlen] = DesStation;
//		if (*pPathNum>1 && pPathes[(*pPathNum) - 2][minlen] == 0)
//			pPathes[(*pPathNum) - 2][minlen] = DesStation;
//	}
//}
//
//int SearchMinPathes(unsigned int SrcStation,
//	unsigned int DesStation,
//	unsigned int* pPathNum,
//	unsigned int* pPathLen,
//	unsigned int **ppPathes)
//{
//	/* 在这里实现功能 */
//
//	if (SrcStation == DesStation)return -1;
//	int i, j, newsta, findflag = 0;
//	int minlen = 1, count = 0;
//	int pathnum = 0;
//	int sum = 0;
//	queue<int>qsta;
//
//
//	for (i = 0; i<MAX; i++)
//		myfront[i].clear();
//
//	memset(flag, 0, sizeof(flag));
//
//	for (i = 0; i<station_reach[SrcStation].size(); i++)
//	{
//		myfront[station_reach[SrcStation][i]].push_back(SrcStation);
//		if (station_reach[SrcStation][i] == DesStation)
//		{
//			*pPathNum = 1;
//			*pPathLen = 1;
//			*ppPathes = (unsigned int *)malloc(2 * sizeof(unsigned int));
//			(*ppPathes)[0] = SrcStation;
//			(*ppPathes)[1] = DesStation;
//			return 0;
//		}
//		qsta.push(station_reach[SrcStation][i]);
//		//count++;
//	}
//	flag[SrcStation] = 1;
//
//	findflag = 0;
//	while (!qsta.empty() && !findflag)
//	{
//
//		minlen++;
//		count = qsta.size();
//		while (count--){
//			newsta = qsta.front();
//			flag[newsta] = 1;
//			for (i = 0; i<station_reach[newsta].size(); i++)
//			{
//				if (flag[station_reach[newsta][i]] == 0)
//					for (j = 0; j<myfront[station_reach[newsta][i]].size(); j++)
//						if (myfront[station_reach[newsta][i]][j] == newsta)break;
//				if (j == myfront[station_reach[newsta][i]].size())
//					myfront[station_reach[newsta][i]].push_back(newsta);
//				if (station_reach[newsta][i] == DesStation)
//				{
//					findflag = 1;
//					break;
//					/*
//					*ppPathes=(unsigned int *)malloc((minlen+1)*sizeof(unsigned int));
//					(*ppPathes)[minlen]=DesStation;
//					for(j=minlen-1,k=DesStation;j>=0;j--)
//					(*ppPathes)[j]=front[(*ppPathes)[j+1]];
//					pathnum++;
//					*/
//				}
//				if (flag[station_reach[newsta][i]] == 0)qsta.push(station_reach[newsta][i]);
//			}
//			qsta.pop();
//		}
//	}
//
//	//if(qsta.empty()) return -1;
//	/*
//	for(i=1;i<12;i++){
//	cout<<i<<"站：";
//	for(j=0;j<myfront[i].size();j++)
//	cout<<myfront[i][j]<<" ";
//	cout<<endl;
//	}
//	*/
//	if (findflag)
//	{
//		*pPathLen = minlen;
//		*pPathNum = 0;
//		dfs(SrcStation, DesStation, minlen, pPathLen, pPathNum, ppPathes);
//
//	}
//	else return -1;
//	//cout<<minlen<<" "<<DesStation<<" "<<sum<<endl;
//	return 0;
//}
//
//
///*************************************************************************************************
//函数说明：输出从起点站到终点站的最优路线
//函数原型：int SearchBestPathes(unsigned int SrcStation,
//unsigned int DesStation,
//unsigned int *pPathNum,
//unsigned int* pPathLen,
//unsigned int** ppPathes);
//输入参数：
//SrcStation 起点站；
//DesStation 终点站；
//Output Param
//pPathNum 最优路线条数;
//pPathLen  最短路线长度;
//ppPathes 存储最短路线的内存地址，内存格式见下图,内存空间在本函数内申请，调用者释放；
//返回值 ：
//0：成功
//-1：任何出错情况（包括路线不存在、站点不存在、起点和终点重叠等等）
//**************************************************************************************************/
//int SearchBestPathes(unsigned int SrcStation,
//	unsigned int DesStation,
//	unsigned int *pPathNum,
//	unsigned int* pPathLen,
//	unsigned int** ppPathes)
//{
//	/* 在这里实现功能 */
//
//	return 0;
//}
//
///*************************************************************************************************
//函数说明：清空所有的线路信息
//函数原型：void Clear();
//输入参数：无
//输出参数：无
//返回值  ：无
//**************************************************************************************************/
//void Clear()
//{
//
//	/* 在这里实现功能 */
//	//	vector<int>station_reach[MAX];
//	for (int i = 0; i<MAX; i++)
//		station_reach[i].clear();
//	return;
//
//};
//int main_others()
//{
//	unsigned int Line1[] = { 1, 2, 3, 4, 5 };
//	unsigned int Line2[] = { 1, 10, 9, 7, 6 };
//	unsigned int Line3[] = { 5, 7, 8 };
//	unsigned int Line4[] = { 11, 5 };
//	int Ret, i;
//	unsigned int pPathNum, pPathLen, *ppPathes[70] = { NULL };
//	AddLine(1, 5, &Line1[0]);
//	AddLine(2, 5, &Line2[0]);
//	AddLine(3, 3, &Line3[0]);
//	AddLine(4, 2, &Line4[0]);
//
//	cout << CalcMinPathLen(1, 11) << endl;
//	SearchMinPathes(1, 11, &pPathNum, &pPathLen, ppPathes);
//	cout << pPathLen << " " << pPathNum << endl;
//	for (Ret = 0; Ret<pPathNum; Ret++)
//	{
//		for (i = 0; i <= pPathLen; i++)
//			cout << ppPathes[Ret][i] << " ";
//		cout << endl;
//	}
//	Clear();
//	if (SearchMinPathes(1, 11, &pPathNum, &pPathLen, ppPathes) == -1)cout << "NO" << endl;
//	cout << CalcMinPathLen(1, 11) << endl;
//	return 0;
//}
