#ifndef HEADER_H
#define HEADER_H

#include <fstream>

using namespace std;

class Matrix {
	int N;
public:
	int Get_N(); //������� ��������� ����������� ������� (����� ��������)

	static Matrix* In_Matrix(ifstream& ifst); //������� ����� �������
	virtual void In_Array(int N, ifstream& ifst) = 0; //����� ����������� ������� ����� �������,
											  //��� ����� ���������� ������� ������ �������
	virtual void Out_Array(int N, ofstream& ofst) = 0; //����� ����������� ������� ������ �������,
											  //��� ����� ���������� ������� ������ �������
	virtual void Out_Only_Two_Dim(int N, ofstream& ofst); //������� ������ ������ �������� ���������� �������
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
	void Out_Only_Two_Dim(ofstream& ofst); //������� ������ ������ �������� ���������� �������
    Container(); //�����������
    ~Container() { Clear_Container(); } //����������
};

class Two_dimensional_array : public Matrix {
	int** Array; //������
public:
	void In_Array(int N, ifstream& ifst);  //������� ����� �������
	void Out_Array(int N, ofstream& ofst); //������� ������ �������
	void Out_Only_Two_Dim(int N, ofstream& ofst); //������� ������ ������ �������� ���������� �������
	Two_dimensional_array() {};
};

class Diagonal_matrix : public Matrix {
	int* Array; //�������
public:
	void In_Array(int N, ifstream& ifst); //������� ����� �������
	void Out_Array(int N, ofstream& ofst); //������� ������ �������
	Diagonal_matrix() {};
};



#endif //HEADER_H