// Benjamin White
// CS210 Project Three
// 20220215

#include <Python.h>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>
#include <string>
#include <filesystem>
#define NOMINMAX
#undef NOMINMAX
#define RESET "\033[0m"
#define BOLDBLUE "\033[1m\033[34m"

using namespace std;

void CallProcedure(string pName)
{
    char *procname = new char[pName.length() + 1];
    std::strcpy(procname, pName.c_str());

    Py_Initialize();
    PyRun_SimpleString("import sys");
    PyRun_SimpleString("import os");
    PyRun_SimpleString("sys.path.append(os.getcwd())");

    PyObject* my_module = PyImport_ImportModule("python_modules.PythonCode");
    PyErr_Print();
    PyObject* my_function = PyObject_GetAttrString(my_module, procname);
    PyObject* my_result = PyObject_CallObject(my_function, NULL);
    Py_Finalize();

    delete[] procname;
}

int callIntFunc(string proc, string param)
{
    char *procname = new char[proc.length() + 1];
    std::strcpy(procname, proc.c_str());

    char *paramval = new char[param.length() + 1];
    std::strcpy(paramval, param.c_str());


    PyObject *pName, *pModule, *pDict, *pFunc, *pValue = nullptr, *presult = nullptr;
    // Initialize the Python Interpreter
    Py_Initialize();
    PyRun_SimpleString("import sys");
    PyRun_SimpleString("import os");
    PyRun_SimpleString("sys.path.append(os.getcwd())");
    // Build the name object
    pName = PyUnicode_FromString((char*)"python_modules.PythonCode");
    // Load the module object
    pModule = PyImport_Import(pName);
    // pDict is a borrowed reference
    pDict = PyModule_GetDict(pModule);
    // pFunc is also a borrowed reference
    pFunc = PyDict_GetItemString(pDict, procname);
    if (PyCallable_Check(pFunc))
    {
        pValue = Py_BuildValue("(z)", paramval);
        PyErr_Print();
        presult = PyObject_CallObject(pFunc, pValue);
        PyErr_Print();
    }
    else
    {
        PyErr_Print();
    }
    //printf("Result is %d\n", _PyLong_AsInt(presult));
    Py_DECREF(pValue);
    // Clean up
    Py_DECREF(pModule);
    Py_DECREF(pName);
    // Finish the Python Interpreter
    Py_Finalize();

    // clean
    delete[] procname;
    delete[] paramval;


    return _PyLong_AsInt(presult);
}

int menu() {
    // declaring and initializing variables for use in loop
    int userChoice = 0;
    int itemQuantity = 0;
    string inputFilePath, userItem, itemName;
    ifstream inputFile;

    // Main Loop
    while (userChoice != 4) { // loop while user has not entered 4
        cout << endl;
        // print menu
        cout << "[1] Calculate the number of times each item appears" << endl;
        cout << "[2] Calculate the frequency of a specific item" << endl;
        cout << "[3] Create a histogram based on appearances of each item" << endl;
        cout << "[4] Quit" << endl;
        cout << endl;

        cin >> userChoice; // getting user input

        while (cin.fail()) { // if user input is invalid
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Please input a valid selection: ";
            cin >> userChoice; // get new user input
        }
        // switch statement to evaluate user input and call appropriate Python function
        switch (userChoice) {
            case 1:
                CallProcedure("PrintList"); // calling Python function
                cout << endl;
                break;
            case 2:
                cout << endl;
                cout << "Enter an item: \n";
                cin >> userItem; // getting user input
                cout << endl;
                callIntFunc("PrintQuantity", userItem); // calling Python function
                cout << endl;
                break;
            case 3:
                CallProcedure("MakeList"); // calling Python function
                cout << endl;

                // read python file
                inputFile.open("frequency.dat");

                inputFile >> itemName; // store item name and quantity from frequency.dat separately
                inputFile >> itemQuantity;

                while (!inputFile.fail()) { // while frequency.dat is found

                    //Print item name and format for histogram
                    cout << setw(14) << left << itemName << setw(6);

                    //Print number of asterisks as item quantity
                    for (int i = 0; i < itemQuantity; i++) {
                        // format astericks
                        cout << right << BOLDBLUE << "*";
                        cout << RESET;
                    }
                    // new line + get next name and quantity
                    cout << endl;
                    inputFile >> itemName;
                    inputFile >> itemQuantity;
                }
                break;
            case 4:
                cout << endl;
                cout << "Goodbye!" << endl; // exit loop if user enters 4
                break;
            default:
                cout << "Please input a valid selection." << endl; // correct user input
                break;
        }
    }
    return 0;
}

int main()
{
    menu();
    return 0;
}