#ifndef HELLO_TYPE_H_
#define HELLO_TYPE_H_

#include <Python.h>
#include <structmember.h>
#include "hello_class.h"

typedef struct {
    PyObject_HEAD  // this will include all the attributes of PyObject in C
    int m_val;
    Hello* m_hello;
} HelloObject;

int Hello_init(PyObject* self, PyObject* args, PyObject* kwds);
PyObject* Hello_new(PyTypeObject* subtype, PyObject* args, PyObject* kwds);
void Hello_dealloc(HelloObject* self);
PyObject* Hello_addOne(PyObject* self, PyObject* args);
PyObject* Hello_getValue(PyObject* self, PyObject* args);
PyObject* Hello_setValue(PyObject* self, PyObject* args);

static PyMethodDef Hello_methods[] = {
    {"addOne", (PyCFunction)Hello_addOne, METH_NOARGS, PyDoc_STR("Add 1 to private value")},
    {"getValue", (PyCFunction)Hello_getValue, METH_NOARGS, PyDoc_STR("Get private value from Hello object")},
    {"setValue", (PyCFunction)Hello_setValue, METH_VARARGS, PyDoc_STR("Set private value for Hello object")},
    {NULL, NULL}
};

static struct PyMemberDef Hello_members[] = {
    {"value", T_INT, offsetof(HelloObject, m_val)},
    {NULL}
};

static PyType_Slot Hello_slots[] = {
    {Py_tp_new, (void*)Hello_new},
    {Py_tp_init, (void*)Hello_init},
    {Py_tp_dealloc, (void*)Hello_dealloc},
    {Py_tp_members, Hello_members},
    {Py_tp_methods, Hello_methods},
    {0, NULL}
};

static PyType_Spec specs_hello = {
    "Hello",
    sizeof(HelloObject) + sizeof(Hello),
    0,
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,
    Hello_slots
};

#endif