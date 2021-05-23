#ifndef HEADER_H
#define HEADER_H

#include <fstream>

using namespace std;

class Matrix {
	int N;
public:
	int Get_N(); //Функция получения размерности массива (общее значение)

	static Matrix* In_Matrix(ifstream& ifst); //Функция ввода матрицы
	virtual void In_Array(int N, ifstream& ifst) = 0; //Чисто вирутальная функция ввода матрицы,
											  //она будет определена каждого класса массива
	virtual void Out_Array(int N, ofstream& ofst) = 0; //Чисто вирутальная функция вывода матрицы,
											  //она будет определена каждого класса массива
	virtual void Out_Only_Two_Dim(int N, ofstream& ofst); //Функция вывода только обычного двумерного массива
protected:
	Matrix() {};
};

//Узел контейнера
struct Node {
    Node* Next, * Prev; //Указатель на след. и пред. узлы контейнера
    Matrix* Cont; //Указатель на высказывание
};

//Контейнер
class Container {
    Node* Head; //Указатель на начало списка
    int Len; //Число элементов контейнера
public:
    void In_Container(ifstream& ifst); //Функция ввода элемента в контейнер
    void Out_Container(ofstream& ofst); //Функция вывода элемента из контейнера
    void Clear_Container(); //Функция очищения контейнера
	void Out_Only_Two_Dim(ofstream& ofst); //Функция вывода только обычного двумерного массива
    Container(); //Конструктор
    ~Container() { Clear_Container(); } //Деструктор
};

class Two_dimensional_array : public Matrix {
	int** Array; //Массив
public:
	void In_Array(int N, ifstream& ifst);  //Функция ввода массива
	void Out_Array(int N, ofstream& ofst); //Функция вывода массива
	void Out_Only_Two_Dim(int N, ofstream& ofst); //Функция вывода только обычного двумерного массива
	Two_dimensional_array() {};
};

class Diagonal_matrix : public Matrix {
	int* Array; //Массива
public:
	void In_Array(int N, ifstream& ifst); //Функция ввода массива
	void Out_Array(int N, ofstream& ofst); //Функция вывода массива
	Diagonal_matrix() {};
};



#endif //HEADER_H