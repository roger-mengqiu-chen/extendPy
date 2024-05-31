#include <Python.h>
#include "hello_type.h"

PyModuleDef hello_module = {
    PyModuleDef_HEAD_INIT,
    "HelloModule",
    "Dummy module named hello",
    -1,
    NULL, 
    NULL,
    NULL,
    NULL,
    NULL
};

PyMODINIT_FUNC
PyInit_HelloModule(void) {  // Must use the same name as your module name
    PyObject* module = PyModule_Create(&hello_module);

    PyObject* helloClass = PyType_FromSpec(&specs_hello);
    if(helloClass == NULL) {
        return NULL;
    }
    Py_INCREF(helloClass);

    if(PyModule_AddObject(module, "Hello", helloClass) < 0) {
        Py_DECREF(helloClass);
        Py_DECREF(module);
        return NULL;
    }
    return module;
}
