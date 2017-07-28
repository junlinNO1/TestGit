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
//����˵���� ����ĳ��������·
//����ԭ�ͣ� void AddLine(unsigned int LineNo, unsigned int StationNum ,unsigned  int *pStationArray)��
//���������
//LineNo        ������·�ţ�
//StationNum    �����������е�վ����Ŀ���ɵ����߱�֤��С��2��
//pStationArray ���������ߵ�����վ����Ϣ��pStationArrayָ��Ĵ洢�ռ��ں�����ᱻ�ͷţ�����������洢�ռ䣻
//��������� ��
//����ֵ  �� ��
//********************************************************************************************************************/
//void AddLine(unsigned int LineNo, unsigned int StationNum, unsigned  int *pStationArray)
//{
//	/* ������ʵ�ֹ��� */
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
//����˵������������վ���յ�վ�����·�߳���
//����ԭ�ͣ�int CalcMinPathLen(unsigned int SrcStation, unsigned int DesStation)��
//���������
//SrcStation  ���վ��
//DesStation �յ�վ��
//�����������
//����ֵ  ��
//���վ���յ�վ�����·�߳���
//-1���κγ������������·�߲����ڡ�վ�㲻���ڡ������յ��ص��ȵȣ�
//**********************************************************************************************************************/
//int CalcMinPathLen(unsigned int SrcStation, unsigned int DesStation)
//{
//
//	/* ������ʵ�ֹ��� */
//	if (SrcStation == DesStation)return -1;
//	int i, j, newsta;
//	int minlen = 1, count = 0;
//	queue<int>qsta;
//	/*
//	for(i=1;i<11;i++)
//	{
//	cout<<i<<"վ"<<":";
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
//����˵������������վ���յ�վ�����·��
//����ԭ�ͣ�int SearchMinPathes(unsigned int SrcStation,
//unsigned int DesStation,
//unsigned int* pPathNum,
//unsigned int* pPathLen,
//unsigned int **ppPathes);
//���������
//SrcStation ���վ��
//DesStation �յ�վ��
//Output Param
//pPathNum ���·������;
//pPathLen  ���·�߳���;
//ppPathes �洢���·�ߵ��ڴ��ַ���ڴ�ռ��ڱ����������룬�������ͷţ��ڴ�ռ�Ĵ洢��ʽ���PPTҪ��
//����ֵ  ��
//0 ���ɹ�
//-1���κγ������������·�߲����ڡ�վ�㲻���ڡ������յ��ص��ȵȣ�
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
//	/* ������ʵ�ֹ��� */
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
//	cout<<i<<"վ��";
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
//����˵������������վ���յ�վ������·��
//����ԭ�ͣ�int SearchBestPathes(unsigned int SrcStation,
//unsigned int DesStation,
//unsigned int *pPathNum,
//unsigned int* pPathLen,
//unsigned int** ppPathes);
//���������
//SrcStation ���վ��
//DesStation �յ�վ��
//Output Param
//pPathNum ����·������;
//pPathLen  ���·�߳���;
//ppPathes �洢���·�ߵ��ڴ��ַ���ڴ��ʽ����ͼ,�ڴ�ռ��ڱ����������룬�������ͷţ�
//����ֵ ��
//0���ɹ�
//-1���κγ������������·�߲����ڡ�վ�㲻���ڡ������յ��ص��ȵȣ�
//**************************************************************************************************/
//int SearchBestPathes(unsigned int SrcStation,
//	unsigned int DesStation,
//	unsigned int *pPathNum,
//	unsigned int* pPathLen,
//	unsigned int** ppPathes)
//{
//	/* ������ʵ�ֹ��� */
//
//	return 0;
//}
//
///*************************************************************************************************
//����˵����������е���·��Ϣ
//����ԭ�ͣ�void Clear();
//�����������
//�����������
//����ֵ  ����
//**************************************************************************************************/
//void Clear()
//{
//
//	/* ������ʵ�ֹ��� */
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
