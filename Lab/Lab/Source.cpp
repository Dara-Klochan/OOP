#include "Header.h"

Container::Container() {
    Head = new Node();
    Head->Cont = NULL;
    Head->Next = Head->Prev = Head;
}

void Container::In_Container(ifstream& ifst) {
    Node* Inserted, * Curr;
    Curr = Inserted = NULL;

    while (!ifst.eof()) {
        Inserted = new Node();
        if ((Inserted->Cont = Matrix::In_Matrix(ifst))) {
            if (!Len) {
                Head->Cont = Inserted->Cont;
            }
            else {
                Curr = Head->Next;
                Head->Next = Inserted;
                Inserted->Next = Curr;
                Inserted->Prev = Head;
                Curr->Prev = Inserted;
                Head = Inserted;
            }

            Len++;
        }
    }

    Head = Head->Next;
}

void Container::Out_Container(ofstream& ofst) {
    ofst << "Container contains " << Len
        << " elements." << endl << endl;

    Node* Temp = Head;

    for (int i = 0; i < Len; i++) {
        ofst << i << ": ";
        Temp->Cont->Out_Array(Temp->Cont->Get_N(), ofst);
        ofst << endl;
        Temp = Temp->Next;
    }
}

void Container::Clear_Container() {
    for (int i = 0; i < Len; i++) {
        free(Head->Cont);
        Head = Head->Next;
    }

    Len = 0;
}

Matrix* Matrix::In_Matrix(ifstream& ifst) {
    Matrix* M = NULL; //������� ��������� �� �������
    int K;

    ifst >> K; //��������� ������������� �������

    if (K == 1) {
        M = new Two_dimensional_array(); //������� ��������� ������
    }
    else if (K == 2) {
        M = new Diagonal_matrix(); //������� ������������ �������
    }
    else if (K == 3) {
        M = new Triangular_matrix(); //������� ����������� �������
    }
    else {
        return 0;
    }

    ifst >> M->N; //C�������� ����������� �������

    M->In_Array(M->N, ifst); //��������� �������� �������

    return M;
}

int Matrix::Get_N() {
    return N;
}

void Two_dimensional_array::In_Array(int N, ifstream& ifst) {
    Array = new int* [N]; //��������� ������ ��� ������

    for (int i = 0; i < N; i++) {
        Array[i] = new int[N]; //��������� ������ ��� ������
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            ifst >> Array[i][j]; //���� �������
        }
    }
}

void Two_dimensional_array::Out_Array(int N, ofstream& ofst)
{
    ofst << "It's two dimensional matrix with dimension = " << N << endl; //������� ����������� �������

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            ofst << Array[i][j] << " "; //����� �������
        }

        ofst << endl;
    }
}

void Diagonal_matrix::In_Array(int N, ifstream& ifst) {
    Array = new int[N]; //�������� ������ ��� ������������ �������

    for (int i = 0; i < N; i++) {
        ifst >> Array[i]; //���� �������
    }
}

void Diagonal_matrix::Out_Array(int N, ofstream& ofst)
{
    ofst << "It's diagonal matrix with dimension = " << N << endl; //������� ����������� �������

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (i == j) {
                ofst << Array[i] << " "; //������� ������� �������; (i == j) -> ������ �� ���������
            }
            else {
                ofst << "0 "; //(i != j) -> �� ���������, ������� ����
            }
        }

        ofst << endl;
    }
}

void Triangular_matrix::In_Array(int N, ifstream& ifst) {
    int Temp_N = N;
    int Array_size = 0;

    while (Temp_N) {
        Array_size += Temp_N;
        Temp_N--;
    }

    Array = new int[Array_size];

    for (int i = 0; i < Array_size; i++) {
        ifst >> Array[i];
    }
}

void Triangular_matrix::Out_Array(int N, ofstream& ofst) {
    ofst << "It's triangular matrix with dimension = " << N << endl;

    int index = 0;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
        {
            if (i >= j) {
                ofst << Array[index] << " ";
                index++;
            }
            else {
                ofst << 0 << " ";
            }
        }

        ofst << endl;
    }
}