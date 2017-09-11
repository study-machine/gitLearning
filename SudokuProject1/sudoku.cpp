#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<ctime>
#include<vector>
#include<fstream>
#include"text.h"
using namespace std;

/*
���û��ݷ���������
�޸���num[0][0]�ĸ�ֵ��ֻ���ڿ�ʼ����ʱ��ֵ���������ڱ�����ʱ���ж��Ƿ��λ��Ϊ[0][0]�����Ч�ʣ���������ʱ��
*/

const int SIZE = 9;
vector<vector <int> > num(SIZE, vector<int>(SIZE));

IsS IsSu;
Gen Gene;
ofstream ocout;//�����������һ������


bool IsS::IsSuitable(int row, int col) {
	int n = num[row][col];
	for (int i = 0; i < row; i++) {
		if (num[i][col] == n) return false;
	}   												//�ж�n�Ƿ��Ѿ����������� 
	for (int i = 0; i < col; i++) {
		if (num[row][i] == n) return false;
	}  													//�ж�n�Ƿ��Ѿ����������� 
	int RowStart = (row / 3) * 3;
	int RowEnd = RowStart + 2;
	int ColStart = (col / 3) * 3;
	int ColEnd = ColStart + 2;
	int r = RowStart, c = ColStart;  					//RowStart,RowEnd,ColStart,ColEnd��־��λ�����ڵľŹ������ʼ	

	for (int k = 0; k < 9; k++) {
		if (row != r || col != c) {
			if (num[r][c] == n) return false;
		}
		else  return true;                                 //�б����������Ƿ���Ź����е����ִ��ڳ�ͻ 
		if (c == ColEnd) {
			c = ColStart;
			r++;
		}
		else {
			c++;
		}
	}  return true;
}  																	//�б�������ڸ�λ���Ƿ���� 

bool Gen::generate(int row, int col) {
	int nextrow, nextcol;
	vector<int> number;
		for (int i = 1; i <= 9; i++)
			number.push_back(i);										//��1-9װ������ 
	while (!number.empty()) {
		int randindex = rand() % number.size();  				//�������1��(size-1)��� 1 �� ����randindex
		number.erase(number.begin() + randindex);  				//ɾ������λ�õ����� 
		num[row][col] = number[randindex];  					//���������ڵ�row�У���col�� 
		if (!IsSu.IsSuitable(row, col))  continue;  //��� randnum��������number[row][col]���λ�ã������ѭ����һ�����ʵ��� 
		if (row == SIZE - 1 && col == SIZE - 1) {
			return true;
		}  														//��������½ǵĿ�Ҳ�����ˣ�����ture���ɹ�������������  
		if (col == SIZE - 1) {
			nextrow = ++row;
			nextcol = 0;
		}  														//���̽�������һ�У����� 
		else {
			nextrow = row;
			nextcol = ++col;
		}  														//nextrow��nextcolָ����һ���ո� 
		bool next = generate(nextrow, nextcol);						//�ݹ����������������  
		if (next)  return true; 								 	//������tureʱ ����ɹ�����
	}
	if (number.empty()) {
		return false;
	} 															//���ɵ�ʱ��ס�˱������һ��
}

/*
void outputTocmd() {
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			printf(" %d", num[i][j]);
		}
		printf("\n");
	}
	printf("\n");
	
}*/
//��ӡ�������Ļ
void outputTotext() {


	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			ocout << num[i][j] << " ";
		}
		ocout << "\n";
	}
	ocout << "\n";
	
}
//��ӡ������ļ�

int main() {

	//clock_t start, finish;

	//double totaltime;

	//start = clock();

	int N;
	ocout.open("sudotext.txt");
	//printf("��������Ҫ���ɵ������������:\n");
	int CharJduge = scanf_s("%d", &N);
	if (!CharJduge) {
		printf("����ֻ��Ϊ����,����������\n");
		system("pause");
		return 0;
	}
	//srand((unsigned)time(NULL));

	ocout << "����������ɵ�" << N << "�����������������:" << endl;
	for (int i = 0; i<N; i++) {
		num[0][0] = 6;
		Gene.generate(0, 1); 													//��0,0λ�ÿ�ʼ������������������� 
		outputTotext();
	//	outputTocmd();
	}
	ocout.close();

	//finish = clock();

	//totaltime = (double)(finish - start) / CLOCKS_PER_SEC;

	//cout << "\n�˳��������ʱ��Ϊ" << totaltime<<endl;

	//system("pause");

	return 0;
}