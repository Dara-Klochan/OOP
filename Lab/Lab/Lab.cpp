#include "Header.h"
#include <iostream>

int main(int argc, char* argv[])
{
    if (argc != 3) {
        cout << "incorrect command line! "
            "Waited: command in_file out_file"
            << endl;
        exit(1);
    }

    ifstream ifst(argv[1]);
    ofstream ofst(argv[2]);

    cout << "Start" << endl;

    Container C;

    C.In_Container(ifst);

    C.Sort();

    ofst << "Filled and sorted container. " << endl;

    C.Out_Container(ofst);

    C.Clear_Container();

    ofst << "Empty container. " << endl;

    C.Out_Container(ofst);

    cout << "Stop" << endl;

    system("pause");
    return 0;
}