/*
Name:Matrix
Author: wcb892534877@icloud.com
Description:�������
Date: 2018-08-19 15:00
Copyright:��̱� �й���ѧԺ������Ϣ�о�Ժ
*/
#pragma once
#include "stdafx.h"
#include <iomanip>
#include <string>
#include <vector>
#include <sstream>
#include <iostream>
using namespace std;
class _declspec(dllexport) CMatrix
{
private:
	long Row, Col;
	double **dArr;

public:
	CMatrix(long Row,long Col);		
	CMatrix();											//����վ���
	CMatrix(long Row, long Col, double *dArr);			//�������
	CMatrix(long Row, long Col, double **dArr);			//�������
	CMatrix(string dArr);								//ͨ��string����[1 2 3;4 5 6;7 8 9]
	~CMatrix();

public:
	inline long GetRow() { return Row; }
	inline long GetCol() { return Col; }
	inline double **GetArray() { return dArr; };

private:
	long IndexOfMax(long Row);

public:
	static CMatrix Inverse(CMatrix *);					//��������
	static CMatrix Transposition(CMatrix*);				//����ת��
	static CMatrix GaussElimination(CMatrix*);			//��˹��ȥ
	static CMatrix CreateIdentityMatrix(long Row);		//������λ����
	static double Det(CMatrix *);						//����ʽֵ
	static void Print(CMatrix *);						//��ӡ������Ϣ

	CMatrix operator *(CMatrix);					    //����˷�

	CMatrix operator +(CMatrix);					    //����ӷ�
	CMatrix operator -(CMatrix);					    //�������

	CMatrix operator =(CMatrix);						//����ֵ
	CMatrix* operator =(CMatrix*);						//����ֵ
	CMatrix ConstantMultiplication(double);				//����˷�(����)
public:
	void CreateEmptyMatrix(long Row, long Col);			//������(ȫ��)����
	void ClearMatrix();									//�����ÿ�
	void SwapRow(long r1,long r2);						//����r1,r2��
public:
	CMatrix(CMatrix &obj);								//��������
	CMatrix(CMatrix *obj);								//��������

public:
	vector<string> split(const string &s, const string &seperator);
	

};


