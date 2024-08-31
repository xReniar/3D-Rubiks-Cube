#include"Solver.hpp"

Solver::Solver(){
    Py_Initialize();
    PySys_SetPath(L".:/usr/lib/python3.10");
    PyRun_SimpleString("import sys; sys.path.append('./src/solver/');");
    //PyRun_SimpleString("import os, sys; sys.path.append(os.path.abspath('./src/solver')); print(sys.path)");
}

Solver::~Solver(){
    freeMemory();
} 

void Solver::kociemba(const char* cubeState){
    // loading solver module
    name = PyUnicode_FromString((char *)"kociemba");
    load_module = PyImport_Import(name);

    // getting function that returns solution
    func = PyObject_GetAttrString(load_module, (char*)"main");

    // creating arguments and passing to main function
    args = PyTuple_Pack(1, PyUnicode_FromString(cubeState));
    callfunc = PyObject_CallObject(func, args);

    std::string result = PyUnicode_AsUTF8(callfunc);
    std::stringstream stringStream(result);
    std::string word;

    while (stringStream >> word)
        solution.push_back(word);
    solutionReady = true;

    freeMemory();
}

void Solver::freeMemory(){
    Py_DECREF(name);
    Py_DECREF(load_module);
    Py_DECREF(func);
    Py_DECREF(args);
    Py_DECREF(callfunc);
}