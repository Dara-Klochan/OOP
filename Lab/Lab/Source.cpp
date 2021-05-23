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
        Temp->Cont->Out_Array(Temp->Cont->Get_N(), Temp->Cont->Get_K_O(), ofst);
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
    else {
        return 0;
    }

    int Key_Out = 0;

    ifst >> Key_Out;

    if (Key_Out == 1) {
        M->K_O = BY_LINE;
    }
    else if (Key_Out == 2) {
        M->K_O = BY_COLUMN;
    }
    else if (Key_Out == 3) {
        M->K_O = ONE_DIMENSIONAL;
    }

    ifst >> M->N; //C�������� ����������� �������

    M->In_Array(M->N, ifst); //��������� �������� �������

    return M;
}

int Matrix::Get_N() {
    return N;
}

Key_Out Matrix::Get_K_O() {
    return K_O;
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

void Two_dimensional_array::Out_Array(int N, Key_Out K_O, ofstream& ofst)
{
    ofst << "It's two dimensional matrix with dimension = " << N << endl; //������� ����������� �������

    if (K_O == BY_LINE) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                ofst << Array[i][j] << " ";
            }

            ofst << endl;
        }
    }
    else if (K_O == BY_COLUMN) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                ofst << Array[j][i] << " ";
            }

            ofst << endl;
        }
    }
    else if (K_O == ONE_DIMENSIONAL) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                ofst << Array[j][i] << " ";
            }
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

void Diagonal_matrix::Out_Array(int N, Key_Out K_O, ofstream& ofst)
{
    ofst << "It's diagonal matrix with dimension = " << N << endl; //������� ����������� �������

    int index = 0;

    if (K_O == BY_LINE) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (i == j) {
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
    else if (K_O == BY_COLUMN) {
        int** temp_matrix = new int* [N];

        for (int i = 0; i < N; i++) {
            temp_matrix[i] = new int[N];
        }

        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (i == j) {
                    temp_matrix[i][j] = Array[index];
                    index++;
                }
                else {
                    temp_matrix[i][j] = 0;
                }
            }
        }

        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                ofst << temp_matrix[j][i] << " ";
            }

            ofst << endl;
        }
    }
    else if (K_O == ONE_DIMENSIONAL) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (i == j) {
                    ofst << Array[index] << " ";
                    index++;
                }
                else {
                    ofst << 0 << " ";
                }
            }
        }

        ofst << endl;
    }
}