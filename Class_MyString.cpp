//****************************************************************************************
// Основы c++ для начинающих. Свой класс string. | (Стрим) 
// Класс "MyString"
// https://www.youtube.com/watch?v=Y3GGqqXlPQI&list=PLQOaTSbfxUtCw_ms8UJk5Dibdocup2eDa
//---------------------------------------------------------------------------------------
// С++ | Visual Studio 2019 (correct C2664)
// Журавлёв Сергей | #SimpleCode | Udemy
// https://www.udemy.com/user/zhuravliov-sergei/
// 2022 @ sgiman
//****************************************************************************************

#include <iostream>
#include <string>
#include "utils.h"

using namespace std;

class MyString
{

public:
	// --- К О Н С Т Р У К Т О Р Ы ---

	// к о н с т р у к т о р  
	// без параметров
	MyString()
	{
		str = nullptr;
		length = 0;
	}

	// к о н с т р у к т о р  с  п а р а м е т р а м и
	// при создании объекта класса необходимо передать строку которую он будет хранить
	MyString(char* str)				//  C2664 - VS2019
	{

		length = strlen(str);			// функция strlen получает количество символов в строке которую мы передаём в объект

		// выделяем память для динамического массива где будет храниться наша строка 
		// +1 символ так как нужно место в массиве под терминирующий 0
		this->str = new char[length + 1];

		for (int i = 0; i < length; i++)	// копируем символы строки в массив нашего класса
		{
			this->str[i] = str[i];
		}

		this->str[length] = '\0';		//закрываем строку терминирующим нулём

	}

	// к о н с т р у к т о р  к о п и р о в а н и я 
	// необходим для создании точной копии объекта класса, но в другой области памяти
	MyString(const MyString& other)
	{
		length = strlen(other.str);

		this->str = new char[length + 1];

		for (int i = 0; i < length; i++)
		{
			this->str[i] = other.str[i];
		}

		this->str[length] = '\0';
	}

	// деструктор, отвечает за освобождение ресурвов занятых объектом, вызывается при уничтожении объекта класса
	~MyString()
	{
		delete[] this->str;
	}

	// --- П Е Р Е Г Р У З К А   О П Е Р А Т О Р О В ---

	MyString(MyString&& other)
	{
		this->length = other.length;
		this->str = other.str;
		other.str = nullptr;
	}

	// перегруженый оператор присваивания (=), вызывается когда необходимо присвоить значение одного объекта другому
	MyString& operator = (const MyString& other)
	{
		// здесь логика похожа на ту которая реализована в конструкторе, за исключением того, что нам нужно позаботиться
		// об освобождении ресурсов объекта если до копирования в него новой строки он уже содержал код 
		// + страндартный синтаксис перегрузки оператора =
		if (this->str != nullptr)
		{
			delete[] str;
		}

		length = strlen(other.str);

		this->str = new char[length + 1];

		for (int i = 0; i < length; i++)
		{
			this->str[i] = other.str[i];
		}

		this->str[length] = '\0';

		return *this;
	}

	// перегруженный оператор сложения (+), в текущей реализации класса String необходим для конкатенации строк
	MyString operator + (const MyString& other)
	{
		// создаём новый пустой объект где будим хранить результат конкатенации строк и который будет результатом работы
		// перегруженного оператора +
		MyString newStr;

		// получаем количество символов в обеих строках для конкатенации
		int thisLength = strlen(this->str);
		int otherLength = strlen(other.str);
		newStr.length = thisLength + otherLength;

		// выделяем место в динамической памяти под новую строку
		newStr.str = new char[newStr.length + 1];

		// копируем данные из 2х конкатенируемых строк в новую строку
		int i = 0;	// Corretion cikle2 "for"    -  j,i-index
		for (; i < thisLength; i++)
		{
			newStr.str[i] = this->str[i];
		}

		for (int j = 0; j < otherLength; j++, i++)
		{
			newStr.str[i] = other.str[j];
		}

		newStr.str[thisLength + otherLength] = '\0';	// ограничение строки 

		// возвращаем результат конкатенации
		return newStr;
	}

	// перегруженный оператор "=="
	bool operator == (const MyString& other)
	{
		if (this->length != other.length)
		{
			return false;
		}

		for (int i = 0; i < this->length; i++)
		{
			if (this->str[i] != other.str[i])
			{
				return false;
			}
		}
		return true;
	}

	// перегруженный оператор "!="
	bool operator != (const MyString& other)
	{
		return !(this->operator==(other));
	}

	// перегруженный оператор "[]" - массив
	char& operator [] (int index)
	{
		return this->str[index];
	}

	// --- М Е Т О Д Ы --- 

	// выводит строку в консоль, в идеале для этого необходима перегрузка оператора <<
	void Print()
	{
		cout << str;
	}

	int Length()
	{
		return length;
	}

	// --- C В О Й С Т В А ---

private:
	// Указатель на массив char, хранит символы, которые мы передали в наш объект. 
	char* str;
	int length;

};


/***********************
           MAIN
************************/
int main()
{
	setlocale(LC_ALL, "ru");

	cout << "*********************************************\n" << endl;
	MyString str1((char*) " Hello");					// C2664 - correct (char*)
	MyString str2((char*) " World!");					// C2664 - correct (char*)
	MyString str3((char*) "\t - My String Class");				// C2664 - correct (char*)
	MyString result;

	result = str1 + str2 + str3;
	result.Print();
	cout << endl << endl;

	cout << "*********************************************\n" << endl;
	string s1 = " Hello";
	string s2 = " World!";
	string s3 = " \t - Standard String Class\n";
	cout << s1 + s2 + s3 << endl;
	cout << "*********************************************\n" << endl;

	//=== END ===
	cout << endl;
	MyDate();
	system("pause");
	return 0;

}
