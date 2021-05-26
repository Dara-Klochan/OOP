#ifndef HEADER_H
#define HEADER_H

#include <fstream>

using namespace std;

//������ ������ �������
enum Key_Out {
	BY_LINE, //�� �������
	BY_COLUMN, //�� ��������
	ONE_DIMENSIONAL //� ���� ����������� �������
};

class Matrix {
	int N;
	Key_Out K_O;
public:
	int Get_N(); //������� ��������� ����������� ������� (����� ��������)
	Key_Out Get_K_O(); //������� ��������� ������� ������ �������

	static Matrix* In_Matrix(ifstream& ifst); //������� ����� �������
	virtual void In_Array(int N, ifstream& ifst) = 0; //����� ����������� ������� ����� �������,
											  //��� ����� ���������� ������� ������ �������
	virtual void Out_Array(int N, Key_Out K_O, ofstream& ofst) = 0; //����� ����������� ������� ������ �������,
											  //��� ����� ���������� ������� ������ �������
	virtual int Sum(int N) = 0; //������� �������� ����� ��������� �������
	bool Compare(Matrix* Other); //������� ��������� ���� ��������� ������
protected:
	Matrix() {};
};

//���� ����������
struct Node {
    Node* Next, * Prev; //��������� �� ����. � ����. ���� ����������
    Matrix* Cont; //��������� �� ������������
};

//���������
class Container {
    Node* Head; //��������� �� ������ ������
    int Len; //����� ��������� ����������
public:
    void In_Container(ifstream& ifst); //������� ����� �������� � ���������
    void Out_Container(ofstream& ofst); //������� ������ �������� �� ����������
    void Clear_Container(); //������� �������� ����������
	void Sort(); //������� ���������� ����������
    Container(); //�����������
    ~Container() { Clear_Container(); } //����������
};

class Two_dimensional_array : public Matrix {
	int** Array; //������
public:
	void In_Array(int N, ifstream& ifst);  //������� ����� �������
	void Out_Array(int N, Key_Out K_O, ofstream& ofst); //������� ������ �������
	int Sum(int N); //������� ������� ����� ��������� �������
	Two_dimensional_array() {};
};

class Diagonal_matrix : public Matrix {
	int* Array; //�������
public:
	void In_Array(int N, ifstream& ifst); //������� ����� �������
	void Out_Array(int N, Key_Out K_O, ofstream& ofst); //������� ������ �������
	int Sum(int N); //������� ������� ����� ��������� �������
	Diagonal_matrix() {};
};

class Triangular_matrix : public Matrix {
	int* Array;
public:
	void In_Array(int N, ifstream& ifst); //������� ����� �������
	void Out_Array(int N, Key_Out K_O, ofstream& ofst); //������� ������ �������
	int Sum(int N); //������� ������� ����� ��������� �������
	Triangular_matrix() {};
};

#endif //HEADER_H