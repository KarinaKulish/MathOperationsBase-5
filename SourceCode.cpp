// sistemy_ischisleniya.cpp: определяет точку входа для консольного приложения.
//

#define _CRT_SECURE_NO_WARNINGS
#include "stdafx.h"
#include <iostream>
#include <string>
#include <cstdio>
#include <stdlib.h>
#include <iomanip>
#include "stdlib.h"
using namespace std;

const int size_max = 1000;

class F_s
{private:
	int *Value;
	int Size;
	int Base;
public:
	F_s()
	{
		Value = NULL;
		Size = 0; 
		Base = 0;
		cout << "Конструктор." << endl;
	}
	F_s(char s[size_max])
	{
		Base = 5;
		Size = strlen(s);
		Value = new int[Size];
		int j = 0;
		for (int i = Size-1; i >=0; i--)
		{
			char t= s[i];
			Value[j] = atoi(&t);
			j++;
		}
		//запись в массив в обратном порядке
		//cout << "Конструктор инициализации." << endl;
	}
	F_s(int S)
	{
		Size = S;
		Base = 5;
		Value = new int[Size];
		for (int i = 0; i < Size; i++)
			Value[i] = 0;
		//cout << "Конструктор с размером" << endl;
	}
	F_s(const F_s & obj)
	{
		Value = new int[obj.Size];
		if (!Value) exit(1);
		for (int i = 0; i < obj.Size; i++)
			Value[i] = obj.Value[i];
		cout << "Конструктор копирования." << endl;
	}
	~F_s()
	{
		
		//cout << "Деструктор." << endl;
	}
	void Destroy(){
		//delete[] Value;
		//Size = 0;
	}
	void show()
	{
		for (int i = Size-1; i >=0; i--)
			cout << Value[i];
		cout << endl;
	}
	void reverse(){//зеркально отражаем массив
		for (int i = 0, j = Size - 1; i < j; ++i, --j) 
		{
			int t = Value[i];
			Value[i] = Value[j];
			Value[j] = t;
		}
	}
	void to_five()//перевод из 10-ричной в 5-ричную
	{
		reverse();
		F_s *Modulo = new F_s(size_max);
		Modulo->Size = 1;
		int whole=Value[0];//для целой части
		while (Size >=1) 
		{
			if (Size == 1 && Value[0] < Base)//1,2,3,4
			{
				whole = Value[0];
				break;
			}
			int count = 0;
			int temp = Value[0];
			
			for (int i = 0; i < Size; i++)//внутри одного числа
			{
				if (temp < Base)
				{
					if (i == 0)
						i++;
					temp = temp * 10 + Value[i];
				}
				
					whole = temp / Base;
					Value[count] = whole;
					count++;
					temp = temp % Base;
					
				
			}
			Size = count;
			Modulo->Value[Modulo->Size - 1] = temp;
			Modulo->Size++;
			if ((Size == 1) && (Value[0]<Base))//достигли конца
				break;
		} 
		Modulo->Value[Modulo->Size - 1] = whole;//последний элемент
		Size = Modulo->Size;
		for (int i = 0; i < Size; i++)
			Value[i] = Modulo->Value[i];
		cout << "Число в 5-ричной системе счисления: ";
		show();
		
	}
	void to_ten()
	{
		int s = 0;
		char temp[size_max];
		for (int i = 0; i<Size; i++)
		{
	     _itoa(( Value[i]*pow(Base, i)), temp, 10);
		 int l = strlen(temp);
		 s = l;
		 F_s Te(temp);
		 Value[i] = 0;
		 for (int j = 0; j <l; j++)
		 {
			 Value[j] += Te.Value[j];
			
			 if (Value[j] >= 10)
			 {
				 if (j == l - 1)
					 s++;
					Value[j+1] += Value[j] /10;
					Value[j] = Value[j] %10;
				}
			}
		}
		Size = s;
		cout << "Число в 10-тичной системе счисления: ";
		show();
	}
	char *to_string()
	{
		char my_str[size_max];
		char s[size_max];
		_itoa(Value[Size-1], my_str, Base);
		for (int i = Size-2; i >=0; i--)
		{
		_itoa(Value[i], s, Base);
		strcat(my_str,s);
		}
		cout << my_str << endl;
		return my_str;
		
	}
	F_s & operator = (F_s const & obj)
	{
		delete[] Value;
		Size = obj.Size;
		Base = obj.Base;
		Value = new int[Size];

		for (int i = 0; i < Size; i++)
			Value[i] = obj.Value[i];
		return *this;
	}
	int &operator[](int i)
	{
		return Value[i];
	}

	
	friend ostream &operator<<(ostream &stream, const F_s& obj);
	friend istream &operator>>(istream &input, F_s &num);
	friend const F_s operator+(const F_s& obj, const F_s& obj2);
	friend const F_s operator-(const F_s& obj, const F_s& obj2);
	friend const F_s operator*(const F_s& obj, const F_s& obj2);
	friend const F_s operator/(const F_s& obj, const F_s& obj2);
};

const F_s operator+(const F_s& obj, const F_s& obj2)
{
	F_s Temp(size_max);
	if (obj.Size > obj2.Size)
	{
		Temp.Size = obj.Size;
		for (int i = obj2.Size; i < obj.Size; i++)
			obj2.Value[i] = 0;
	}
	else
	{
		Temp.Size = obj2.Size;
		for (int i = obj.Size; i < obj2.Size; i++)
			obj.Value[i] = 0;
	}
	for (int i = 0; i < Temp.Size; i++)
		 Temp.Value[i] = 0;
	for (int i = 0; i < Temp.Size; i++)
	{
		Temp.Value[i] += obj2.Value[i] + obj.Value[i];
		if (Temp.Value[i] >= Temp.Base)
		{
			Temp.Value[i + 1] += Temp.Value[i] / Temp.Base;
			Temp.Value[i] %= Temp.Base;
		}
	}
	if (Temp.Value[Temp.Size - 1] == 0)
		Temp.Size--; 
	Temp.show();
	return Temp;

	}
const F_s operator-(const F_s& obj, const F_s& obj2)
{
	int k = 3;//флаг сравнения длин
	F_s Temp(size_max);
	F_s T1(obj.Size);
	T1 = obj;
	F_s T2(obj2.Size);
	T2 = obj2;
	if (T1.Size > T2.Size)
	{
		Temp.Size = T1.Size;
		k = 1;

		for (int i = T2.Size; i<T1.Size; i++)
			T2.Value[i] = 0;
	}
	else if (T2.Size > T1.Size)
	{
		
		Temp.Size = T2.Size;
		k = 2;
		for (int i = T1.Size; i<T2.Size; i++)
			T1.Value[i] = 0;
	}
	else
	{
		Temp.Size = T1.Size;
		for (int i = Temp.Size - 1; i >=0; i--)//поразрядое сравнение
		{
			if (T1.Value[i] > T2.Value[i])
			{
				k = 1;
				break;
			}
			if (T2.Value[i] > T1.Value[i])
			{
				k = 2;
				break;
			}
		}
	}
	if (k==3)
	{
		Temp.Size = 1;
		Temp.Value[0] = 0;
		return Temp;
	}
	for (int i = 0; i < Temp.Size; i++)
		Temp.Value[i] = 0;
	if (k == 1)
	{
		for (int i = 0; i < Temp.Size; i++)
		{
			if (i < (Temp.Size - 1))
			{
				if (T1.Value[i] < T2.Value[i])
				{
					T1.Value[i + 1]--;
					T1.Value[i] += Temp.Base;
				}
				Temp.Value[i] = T1.Value[i] - T2.Value[i];
			}
			else
			{
				Temp.Value[i] = T1.Value[i] - T2.Value[i];
			}
		}
		
	}
	else if (k == 2)
	{
		for (int i = 0; i < Temp.Size; i++)
		{
			if (i < (Temp.Size - 1))
			{
				if (T2.Value[i] < T1.Value[i])
				{
					T2.Value[i + 1]--;
					T2.Value[i] += Temp.Base;
				}
				Temp.Value[i] = T2.Value[i] - T1.Value[i];
			}
			else
			{
				Temp.Value[i] = T2.Value[i] - T1.Value[i];
			}
		}
	}
	if (Temp.Value[Temp.Size - 1] == 0)
		Temp.Size--;
	Temp.show();

	return Temp;
}
const F_s operator*(const F_s& obj, const F_s& obj2)
{
	F_s T1(obj.Size + obj2.Size);
	for (int i = 0; i < T1.Size; i++)
		T1.Value[i] = 0;
	F_s T(T1.Size);
	for (int i = 0; i <obj2.Size; i++)
	{
		for (int w = 0; w < T.Size; w++)
			T.Value[w] = 0;
		int w = 0;
		for (int j = i; j < obj.Size+i; j++)
		{
			//cout << obj.Value[w] << " * ";
			//cout << obj2.Value[i]<<endl;
			T.Value[j] += obj2.Value[i] * obj.Value[w];
			 if (T.Value[j] >= T.Base)
			{
				T.Value[j + 1] += T.Value[j] / T.Base;
				T.Value[j] %= T.Base;
			}
			 w++;
		}
		//cout << endl;
		for (int q = 0; q < T1.Size; q++)
		{
			T1.Value[q] +=T.Value[q] ;
			if (T1.Value[q] >= T1.Base)
			{
				T1.Value[q+1] += T1.Value[q] / T1.Base;
				T1.Value[q] %= T1.Base;
			}
		}
	//	T.show();
		//T1.show();
	}
	for (int i = T1.Size - 1; i >= 0; i--)
	{
		if (T1.Value[i] != 0)
			break;
		else
		T1.Size--;
	}
	T1.show();
	return T1;
}
const F_s operator/(const F_s& obj, const F_s& obj2)
{
	int whole = obj.Value[0];//для целой части
	F_s Temp(obj.Size);
	for (int i = 0; i < Temp.Size; i++)
	{
		Temp.Value[i] = obj.Value[i];
	}
	while (Temp.Size >= 1)
	{
		if (Temp.Size == 1 && Temp.Value[0] < obj2.Value[0])//1,2,3,4
		{
			whole = Temp.Value[0];
			break;
		}
		int count = 0;
		int temp = Temp.Value[0];

		for (int i = 0; i < Temp.Size; i++)//внутри одного числа
		{
			if (temp < 5)
			{
				if (i == 0)
					i++;
				temp = temp * 10 + Temp.Value[i];
			}

			whole = temp / Temp.Base;
			Temp.Value[count] = whole;
			count++;
		}

		Temp.Size = count;
	}
		Temp.show();
		return Temp;
	}
ostream &operator<<(ostream &stream, const F_s& obj)
{
	int i;
	for (i = obj.Size-1; i>=0; i--)
	{
		stream << obj.Value[i];
	}
	
	return stream;
}
istream &operator>>(istream &input, F_s &num)
{
	for (int i = 0; i<num.Size; i++)
		input >> num.Value[i];
	return input;
}


int _tmain(int argc, _TCHAR* argv[])
{
	setlocale(0, "");
	char s[size_max];
	cout << "Введите число: "<<endl;
	cin >> s;
	cout << s<<endl;
	F_s x;
	x = s;
	x.to_five();
	cout << x << endl;
	cout << "Введите число: "<<endl;
	cin >> s;
	F_s q(s);
	q.to_five();
	F_s sum;
	sum = x + q;
	cout << sum;
	/*F_s x(s);
	x.to_five();
	cout << "Введите число: ";
	cin >> s;
	F_s u(s);
	u.to_five();
	cout << "Сумма: ";
	x + u;
	cout << "Разница: ";
	x - u;
	cout << "Произведение: ";
	x*u;
	cout << "Введите число от 1 до 4";
	
	cin >> s;
	F_s q(s);
	x / q;

	*/
	system("pause");
	return 0;
}

