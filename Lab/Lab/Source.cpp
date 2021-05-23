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
        ofst << "Sum of matrix elements = " << 
            Temp->Cont->Sum(Temp->Cont->Get_N()) << endl;
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

void Container::Sort() {
    if (Len > 1) {
        Node* First = Head;
        Node* Second = Head->Next;

        Node* Temp = new Node;

        for (int i = 0; i < Len - 1; i++) {
            for (int j = 0; j < Len - i - 1; j++) {
                if (First->Cont->Compare(Second->Cont)) {
                    Temp->Cont = First->Cont;
                    First->Cont = Second->Cont;
                    Second->Cont = Temp->Cont;
                }

                Second = Second->Next;
            }

            First = First->Next;
            Second = First->Next;
        }
    }
}

Matrix* Matrix::In_Matrix(ifstream& ifst) {
    Matrix* M = NULL; //Создаем указатель на матрицу
    int K;

    ifst >> K; //Считываем идентификатор матрицы

    if (K == 1) {
        M = new Two_dimensional_array(); //Создаем двумерный массив
    }
    else if (K == 2) {
        M = new Diagonal_matrix(); //Создаем диагональную матрицу
    }
    else {
        return 0;
    }

    ifst >> M->N; //Cчитываем размерность массива

    M->In_Array(M->N, ifst); //Считываем элементы матрицы

    return M;
}

int Matrix::Get_N() {
    return N;
}

bool Matrix::Compare(Matrix* Other) {
    return Sum(N) > Other->Sum(Other->N);
}

void Two_dimensional_array::In_Array(int N, ifstream& ifst) {
    Array = new int* [N]; //Выделение памяти под массив

    for (int i = 0; i < N; i++) {
        Array[i] = new int[N]; //Выделение памяти под массив
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            ifst >> Array[i][j]; //Ввод массива
        }
    }
}

void Two_dimensional_array::Out_Array(int N, ofstream& ofst) {
    ofst << "It's two dimensional matrix with dimension = " << N << endl; //Выводим размерность массива

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            ofst << Array[i][j] << " "; //Вывод массива
        }

        ofst << endl;
    }
}

int Two_dimensional_array::Sum(int N) {
    int Sum = 0;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            Sum += Array[i][j];
        }
    }

    return Sum;
}

void Diagonal_matrix::In_Array(int N, ifstream& ifst) {
    Array = new int[N]; //Выделяем память для диагональной матрицы

    for (int i = 0; i < N; i++) {
        ifst >> Array[i]; //Ввод матрицы
    }
}

void Diagonal_matrix::Out_Array(int N, ofstream& ofst) {
    ofst << "It's diagonal matrix with dimension = " << N << endl; //Выводим размерность матрицы

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (i == j) {
                ofst << Array[i] << " "; //Выводим элемент матрицы; (i == j) -> только по диагонали
            }
            else {
                ofst << "0 "; //(i != j) -> не диагональ, выводим нули
            }
        }

        ofst << endl;
    }
}

int Diagonal_matrix::Sum(int N) {
    int Sum = 0;

    for (int i = 0; i < N; i++) {
        Sum += Array[i];
    }

    return Sum;
}