#include "stdafx.h"
#include "Matrix.h"

CMatrix::CMatrix(long Row, long Col)
{
	this->Row = Row;
	this->Col = Col;

	dArr = new double*[Row];
	for (long i = 0; i < Row; i++)
	{
		dArr[i] = new double[Col];
	}
	for (long i = 0; i < Row; i++)
	{
		for (long j = 0; j < Col; j++)
		{
			dArr[i][j] = 0;
		}
	}
}

CMatrix::CMatrix()
{
}

CMatrix::CMatrix(long Row, long Col, double * dArr)
{
	this->Row = Row;
	this->Col = Col;

	this->dArr = new double*[Row];
	for (long i = 0; i < Row; i++)
	{
		this->dArr[i] = new double[Col];
	}
	long Length = sizeof(dArr) / sizeof(dArr[0]);//计算dArry长度
	if (Length < Row*Col) 
	{ 
		for (long i = 0; i < Row; i++)
		{
			for (long j = 0; j < Col; j++)
			{
				this->dArr[i][j] = 0;
			}
		}
	}
	else
	{
		for (long i = 0; i < Row; i++)
		{
			for (long j = 0; j < Col; j++)
			{
				this->dArr[i][j] = dArr[i*Col+j];
			}
		}
	}
}

CMatrix::CMatrix(long Row, long Col, double ** dArr)
{
	this->Row = Row;
	this->Col = Col;

	this->dArr = new double*[Row];
	for (long i = 0; i < Row; i++)
	{
		this->dArr[i] = new double[Col];
	}

	for (int i = 0; i < Row; i++)
	{
		for (int j = 0; j < Col; j++)
		{
			this->dArr[i][j] = dArr[i][j];
		}
	}
}

CMatrix::CMatrix(string dArr)
{
	 Row = 0;
	 long CountChar = 0;
	 for (long i = 0; i < dArr.length(); i++)
	 {
		if (dArr[i] == ';') { Row++; }
		if (dArr[i] != ';' && dArr[i] != ' ') { CountChar++; }
	 }
	 Row++;
	 Col = (dArr.length()+1 - CountChar)/Row;
	 this->dArr = new double*[Row];
	 for (long i = 0; i < Row; i++)
	 {
		 this->dArr[i] = new double[Col];
	 }
	 for (long i = 0; i < dArr.length(); i++)
	 {
		 if (dArr[i] == ';') { dArr[i] = ' '; }
	 }
	 vector<string> vecNumber = split(dArr, " ");
	 for (long i = 0; i < Row; i++)
	 {
		 for (long j = 0; j < Col; j++)
		 {
			 stringstream strStream;
			 strStream << vecNumber[i*Col + j];
			 strStream >> this->dArr[i][j];
		 }
	 } 
}

CMatrix::~CMatrix()
{
}

long CMatrix::IndexOfMax(long Row)
{
	long iPos = 0;
	double iFind = dArr[Row][0];
	//double temp=0;
	for (int i = 1; i < Col; i++)
	{
		if (dArr[Row][i]>iFind)
		{
			iFind = dArr[Row][i];
		}
	}
	for (int i = 1; i < Col; i++)
	{
		if (dArr[Row][i] == iFind)
		{
			iPos = i;
			break;
		}
	}
	return iPos;
}

CMatrix CMatrix::Inverse(CMatrix *obj)
{
	CMatrix *copy=new CMatrix(obj);
	CMatrix temp(CreateIdentityMatrix(copy->Row));
	int flag = 1;
	for (int i = 0; i < copy->Col; i++)//
	{
		for (int k = i + 1; k < copy->Row; k++)//
		{
			if (i != copy->Row - 1 && copy->dArr[i][i] == 0)//如果对角线元素为0
			{
				for (int m = i + 1; m < copy->Row; m++)//
				{
					for (int n = i; n < copy->Col; n++)//在为0行的下面行，找非0,并交换行
					{
						if (copy->dArr[m][i])
						{
							copy->SwapRow(i, m);
							temp.SwapRow(i, m);
							break;
						}
						else flag = 0;
					}
				}
			}
			if (i == copy->Row - 1 && copy->dArr[i][i] == 0) { break; }//如果最右下角元素为0，退出
			if (flag)
			{
				double Gas = copy->dArr[k][i] / copy->dArr[i][i];
				for (int m = 0; m < copy->Col; m++)
				{
					copy->dArr[k][m] = copy->dArr[k][m] - copy->dArr[i][m] * Gas;
					temp.dArr[k][m] = temp.dArr[k][m] - temp.dArr[i][m] * Gas;

				}
			}
		}
	}
	flag = 1;
	for (int i = copy->Col - 1; i >= 0; i--)//
	{
		for (int k = i - 1; k >= 0; k--)//
		{
			if (i != 0 && copy->dArr[i][i] == 0)//如果对角线元素为0
			{
				for (int m = i - 1; m >= 0; m--)//
				{
					for (int n = i; n >= 0; n--)//在为0行的下面行，找非0,并交换行
					{
						if (copy->dArr[m][i])
						{
							copy->SwapRow(i, m);
							temp.SwapRow(i, m);
							break;
						}
						else flag = 0;
					}
				}
			}
			if (i == 0 && copy->dArr[i][i] == 0) { break; }//如果最左上角元素为0，退出
			if (flag)
			{
				double Gas = copy->dArr[k][i] / copy->dArr[i][i];
				for (int m = copy->Col - 1; m >= 0; m--)
				{
					copy->dArr[k][m] = copy->dArr[k][m] - copy->dArr[i][m] * Gas;
					temp.dArr[k][m] = temp.dArr[k][m] - temp.dArr[i][m] * Gas;

				}
			}
		}
	}
	for (int i = 0; i < copy->Row; i++)
	{
		for (int k = 0; k < copy->Col; k++)
		{
			temp.dArr[i][k] = temp.dArr[i][k] / copy->dArr[i][i];
		}
		copy->dArr[i][i] = copy->dArr[i][i] / copy->dArr[i][i];
	}
	return temp;
}

CMatrix CMatrix::Transposition(CMatrix *obj)
{
	CMatrix Copy(obj->Col,obj->Row);
	for (int i = 0; i < obj->Row; i++)
	{
		for (int j = 0; j < obj->Col; j++)
		{
			Copy.dArr[j][i] = obj->dArr[i][j];
		}
	}
	return Copy;
}

CMatrix CMatrix::GaussElimination(CMatrix* obj)
{
	CMatrix temp(obj);
	int flag = 1;
	for (int i = 0; i < temp.Col; i++)//
	{
		for (int k = i + 1; k < temp.Row; k++)//
		{
			if (i != temp.Row - 1 && temp.dArr[i][i] == 0)//如果对角线元素为0
			{
				for (int m = i + 1; m < temp.Row; m++)//
				{
					for (int n = i; n < temp.Col; n++)//在为0行的下面行，找非0,并交换行
					{
						if (temp.dArr[m][i])
						{
							temp.SwapRow(i, m);
							break;
						}
						else flag = 0;
					}
				}
			}
			if (i == temp.Row - 1 && temp.dArr[i][i] == 0) { break; }//如果最右下角元素为0，退出
			if (flag)
			{
				double Gas = temp.dArr[k][i] / temp.dArr[i][i];
				for (int m = 0; m < temp.Col; m++)
				{
					temp.dArr[k][m] = temp.dArr[k][m] - temp.dArr[i][m] * Gas;
					if (fabs(temp.dArr[k][m]) <= 10e-8) { temp.dArr[k][m] = 0; }
				}
			}
		}
	}
	return temp;
}

CMatrix CMatrix::CreateIdentityMatrix(long Row)
{
	CMatrix temp;
	temp.CreateEmptyMatrix(Row, Row);
	for (int i = 0; i < Row; i++) temp.dArr[i][i] = 1;
	return temp;
}

double CMatrix::Det(CMatrix * obj)
{
	if (obj->Col != obj->Row)
	{
		return INFINITE;
	}
	CMatrix temp(obj);
	CMatrix::GaussElimination(&temp);
	double sum = 1.0;
	for (int i = 0; i < temp.Row; i++)
	{
		sum *= temp.dArr[i][i];
	}
	return sum;
}

void CMatrix::Print(CMatrix *obj)
{
	for (int i = 0; i < obj->Row; i++)
	{
		for (int j = 0; j < obj->Col; j++)
		{
			if (fabs(obj->dArr[i][j]) < 10e-8)obj->dArr[i][j] = 0;
			cout << setiosflags(ios::fixed) << setiosflags(ios::right) << setprecision(4) << obj->dArr[i][j] << "     ";
		}
		cout << endl;
	}
}

CMatrix CMatrix::operator*(CMatrix obj)
{
	CMatrix Temp(Row, obj.Col);
	double sum = 0;
	for (int i = 0; i<Row; i++)
	{
		for (int j = 0; j<obj.Col; j++)
		{
			double sum = 0;
			for (int k = 0; k<Col; k++)
			{
				sum += dArr[i][k] * obj.dArr[k][j];
			}
			Temp.dArr[i][j] = sum;
		}
	}
	return Temp;
}

CMatrix CMatrix::operator+(CMatrix obj)
{
	CMatrix Temp(Row, Col);
	int i, j;
	for (i = 0; i < Row; i++)//行
		for (j = 0; j < Col; j++)//列
			Temp.dArr[i][j] = dArr[i][j] + obj.dArr[i][j];
	return Temp;
}

CMatrix CMatrix::operator-(CMatrix obj)
{
	CMatrix Temp(Row, Col);
	int i, j;
	for (i = 0; i < Row; i++)//行
		for (j = 0; j < Col; j++)//列
			Temp.dArr[i][j] = dArr[i][j] - obj.dArr[i][j];
	return Temp;
}

CMatrix CMatrix::operator=(CMatrix obj)
{
	CMatrix temp(obj);
	return temp;
}

CMatrix * CMatrix::operator=(CMatrix *obj)
{
	CMatrix *temp = new CMatrix(obj);
	return temp;
}

CMatrix CMatrix::ConstantMultiplication(double fac)
{
	CMatrix temp(this);
	for (int i = 0; i < temp.Row; i++)
	{
		for (int j = 0; j < temp.Col; j++)
		{
			dArr[i][j] *= fac;
		}
	}
	return temp;
}

void CMatrix::CreateEmptyMatrix(long Row, long Col)
{
	this->Row = Row;
	this->Col = Col;


	this->dArr = new double*[Row];
	for (int i = 0; i < Row; i++)
	{
		this->dArr[i] = new double[Col];
	}
	for (int i = 0; i < Row; i++)
	{
		for (int j = 0; j < Col; j++)
		{
			this->dArr[i][j] = 0;
		}
	}
}

void CMatrix::ClearMatrix()
{
}

void CMatrix::SwapRow(long r1, long r2)
{
}

CMatrix::CMatrix(CMatrix & obj)
{
	this->Row = obj.Row;
	this->Col = obj.Col;
	this->dArr = new double*[Row];
	for (int i = 0; i<Row; i++)
		dArr[i] = new double[Col];
	for (int i = 0; i<Row; i++)//行
		for (int j = 0; j<Col; j++)//列
			dArr[i][j] = obj.dArr[i][j];
}

CMatrix::CMatrix(CMatrix * obj)
{
	this->Row = obj->Row;
	this->Col = obj->Col;
	this->dArr = new double*[Row];
	for (int i = 0; i<Row; i++)
		dArr[i] = new double[Col];
	for (int i = 0; i<Row; i++)//行
		for (int j = 0; j<Col; j++)//列
			dArr[i][j] = obj->dArr[i][j];
}

vector<string> CMatrix::split(const string & s, const string & seperator)
{
	{
		vector<string> result;
		typedef string::size_type string_size;
		string_size i = 0;

		while (i != s.size()) {
			//找到字符串中首个不等于分隔符的字母；
			int flag = 0;
			while (i != s.size() && flag == 0) {
				flag = 1;
				for (string_size x = 0; x < seperator.size(); ++x)
					if (s[i] == seperator[x]) {
						++i;
						flag = 0;
						break;
					}
			}

			//找到又一个分隔符，将两个分隔符之间的字符串取出；
			flag = 0;
			string_size j = i;
			while (j != s.size() && flag == 0) {
				for (string_size x = 0; x < seperator.size(); ++x)
					if (s[j] == seperator[x]) {
						flag = 1;
						break;
					}
				if (flag == 0)
					++j;
			}
			if (i != j) {
				result.push_back(s.substr(i, j - i));
				i = j;
			}
		}
		return result;
	}
}




