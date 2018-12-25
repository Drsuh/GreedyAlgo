#include <iostream>
using namespace std;
#include <vector>

/*
void who_is_theif()
{
	for (int x = 0; x < 4; x++)
	{
		int dis_a = (x != 0) ? 1 : 0;
		int dis_b = (x == 2) ? 1 : 0;
		int dis_c = (x == 3) ? 1 : 0;
		int dis_d = 1 - dis_c;

		if ((dis_a + dis_b + dis_c + dis_d) == 3)
		{
			char theif = 'A' + x;
			cout << "the theif is " << theif << endl;
			break;
		}
	}
}
int main()
{
	who_is_theif();
	system("pause");
	return 0;
}*/

//typedef struct{
//	int c;
//	int am;
//	int bm;
//}ITEM;
//
//int main()
//{
//	ITEM items;
//	int n;
//	if(n==0)
//	{
//		items.c = 1;
//		items.am = 0;
//		items.bm = 0;
//		return;
//	}
//	for (unsigned int i = 1; i <= n; i++)
//	{
//		unsigned int nc = i + 1;
//		items[nc - 1] = { 1,0,i };
//		for (unsigned int j = nc - 2; j > 0; j--)
//		{
//			unsigned int c = items[j].c + items[j - 1].c;
//			items[j] = { c, i - j, j };
//		}
//		items[0] = { 1, i, 0 }; //����
//	}
//
//}

/*
typedef�����Ͷ������˼
*/
//�����ѡ����Ľṹ������
typedef struct tagObject
{
	int weight;
	int price;
	int status;
}OBJECT;
//���屳������
typedef struct tagKnapsackProblem
{
	vector<OBJECT>objs;
	int totalC;
}KNAPSACK_PROBLEM;

typedef int(*SELECT_POLICY)(vector<OBJECT>& objs,int c);


//����û�б�ѡ��objs,����ѡ��price������Ʒ
int Choosefunc1(std::vector<OBJECT>& objs, int c)
{
	int index = -1;  //-1��ʾ������������
	int max_price = 0;
	for (int i = 0; i < static_cast<int>(objs.size()); i++)
	{
		//��objs[i].status == 0����Ʒ�������ѡobjs[i].price������Ʒ
		if ((objs[i].status == 0) && (objs[i].price > max_price))//objsû�б�ѡ,����price> mp
		{
			max_price = objs[i].price;
			index = i;
		}
	}

	return index;
}

int Choosefunc2(std::vector<OBJECT>& objs, int c)
{
	int index = -1;
	int min_weight = 10000;
	for (int i = 0; i < static_cast<int>(objs.size()); i++)
	{
		if ((objs[i].status == 0) && (objs[i].weight < min_weight))
		{
			min_weight = objs[i].weight;
			index = i;
		}
	}

	return index;
}
int Choosefunc3(std::vector<OBJECT>& objs, int c)
{
	int index = -1;
	double max_s = 0.0;
	for (int i = 0; i < static_cast<int>(objs.size()); i++)
	{
		if (objs[i].status == 0)
		{
			double si = objs[i].price;
			si = si / objs[i].weight;
			if (si > max_s)
			{
				max_s = si;
				index = i;
			}
		}
	}

	return index;
}

void PrintResult(std::vector<OBJECT>& objs)
{
	int totalW = 0;
	int totalP = 0;
	for (int i = 0; i < static_cast<int>(objs.size()); i++)
	{
		if (objs[i].status == 1)
		{
			totalW += objs[i].weight;
			totalP += objs[i].price;
			cout << "object " << i + 1 << ": weight=" << objs[i].weight <<
				", price=" << objs[i].price << endl;
		}
	}
	cout << "total weight : " << totalW << ", total price : " << totalP << endl;
}

void GreedyAlgo(KNAPSACK_PROBLEM *problem, SELECT_POLICY spFunc)
{
	int idx;
	int sum_weight_current = 0;
	//��ѡ
	while ((idx = spFunc(problem->objs, problem->totalC- sum_weight_current)) != -1)
	{	//�ټ�飬�Ƿ���װ��ȥ
		if ((sum_weight_current + problem->objs[idx].weight) <= problem->totalC)
		{
			problem->objs[idx].status = 1;//�������û��װ������������װ,�����װ��ȥ����Ʒ״̬Ϊ1
			sum_weight_current += problem->objs[idx].weight;//�����idx�����������װ��ȥ�����㵱ǰ������
		}
		else
		{
			//����ѡ�����Ʒ�ˣ��������2������ѡʣ�µ�
			problem->objs[idx].status = 2;
		}
	}
	PrintResult(problem->objs);
}


//const int MIN = 0x80000000;
//const int N = 7;
//const int V = 150;
//int f[N + 1][V + 1];
//
//////////////DP�㷨///////////////
//int Package(int *W, int *C, int N, int V)
//{
//	int i, j;
//	memset(f, 0, sizeof(f));  //��ʼ��Ϊ0//memset() �����������ڴ�ռ��ʼ��,��ʼ��Ϊ0
//
//	for (i = 0; i <= N; i++)
//		for (j = 1; j <= V; j++)               //�˲����ǽ���Ƿ�ǡ�����㱳��������
//			f[i][j] = MIN;                //����ǡ�á����㱳��������������װ������������ϴ˲��裬������Ҫ��ǡ�á������ʼ��Ϊ0
//
//	for (i = 1; i <= N; i++)
//		for (j = C[i]; j <= V; j++)
//		{
//			f[i][j] = (f[i - 1][j]>f[i - 1][j - C[i]] + W[i]) ? f[i - 1][j] : (f[i - 1][j - C[i]] + W[i]);
//			std::cout << "f[" << i << "][" << j << "]=" << f[i][j] << std::endl;
//		}
//	return f[N][V];
//}
//
//void DPAlgo()
//{
//	int W[8] = { 0,10,40,30,50,35,40,30 };      //��ƷȨ��
//	int C[8] = { 0,35,30,60,50,40,10,25 };      //��Ʒ��С
//	int result = Package(W, C, N, V);
//	if (result>0)
//	{
//		cout << endl;
//		cout << "the opt value:" << result << endl;
//		int i = N, j = V;
//		while (i)
//		{
//			if (f[i][j] == (f[i - 1][j - C[i]] + W[i]))
//			{
//				cout << i << ":" << "w=" << W[i] << ",c=" << C[i] << endl;
//				j -= C[i];
//			}
//			i--;
//		}
//	}
//	else
//		cout << "can not find the opt value" << endl;
//}

OBJECT objects[] = { { 35,10,0 },{ 30,40,0 },{ 60,30,0 },{ 50,50,0 },
					{ 40,35,0 },{ 10,40,0 },{ 25,30,0 } };

int main()
{
	KNAPSACK_PROBLEM problem;

	problem.objs.assign(objects, objects + 7);//assign��ֵ��std::vector::assign
	problem.totalC = 150;
	cout << "start to find the best way ,now" << endl;
	GreedyAlgo(&problem, Choosefunc3);
	//DPAlgo();

	system("pause");
	return 0;
}