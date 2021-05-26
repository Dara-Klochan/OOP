#ifndef HEADER_H
#define HEADER_H

#include <fstream>

using namespace std;

//Способ вывода матрицы
enum Key_Out {
	BY_LINE, //По строкам
	BY_COLUMN, //По столбцам
	ONE_DIMENSIONAL //В виде одномерного массива
};

class Matrix {
	int N;
	Key_Out K_O;
public:
	int Get_N(); //Функция получения размерности массива (общее значение)
	Key_Out Get_K_O(); //Функция получения способа вывода матрицы

	static Matrix* In_Matrix(ifstream& ifst); //Функция ввода матрицы
	virtual void In_Array(int N, ifstream& ifst) = 0; //Чисто вирутальная функция ввода матрицы,
											  //она будет определена каждого класса массива
	virtual void Out_Array(int N, Key_Out K_O, ofstream& ofst) = 0; //Чисто вирутальная функция вывода матрицы,
											  //она будет определена каждого класса массива
	virtual int Sum(int N) = 0; //Функция подсчета суммы элементов матрицы
	bool Compare(Matrix* Other); //Функция сравнения сумм элементов матриц
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
	void Sort(); //Функция сортировки контейнера
    Container(); //Конструктор
    ~Container() { Clear_Container(); } //Деструктор
};

class Two_dimensional_array : public Matrix {
	int** Array; //Массив
public:
	void In_Array(int N, ifstream& ifst);  //Функция ввода массива
	void Out_Array(int N, Key_Out K_O, ofstream& ofst); //Функция вывода массива
	int Sum(int N); //Функция подсчет суммы элементов матрицы
	Two_dimensional_array() {};
};

class Diagonal_matrix : public Matrix {
	int* Array; //Массива
public:
	void In_Array(int N, ifstream& ifst); //Функция ввода массива
	void Out_Array(int N, Key_Out K_O, ofstream& ofst); //Функция вывода массива
	int Sum(int N); //Функция подсчет суммы элементов матрицы
	Diagonal_matrix() {};
};

class Triangular_matrix : public Matrix {
	int* Array;
public:
	void In_Array(int N, ifstream& ifst); //Функция ввода массива
	void Out_Array(int N, Key_Out K_O, ofstream& ofst); //Функция вывода массива
	int Sum(int N); //Функция подсчет суммы элементов матрицы
	Triangular_matrix() {};
};

#endif //HEADER_H