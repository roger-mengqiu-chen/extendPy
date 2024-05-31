#include <Python.h>
#include "hello_type.h"
#include <exception>


PyObject* Hello_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    HelloObject* self;
    self = (HelloObject*) type->tp_alloc(type, 0);
    if(self != NULL) {
        self->m_val = 0;
        self->m_hello = NULL;
    }
    return (PyObject*) self;
}

int Hello_init(PyObject* self, PyObject* args, PyObject* kwds) {
    HelloObject* m = (HelloObject*) self;

    m->m_val = -1;
    m->m_hello = (Hello*)PyObject_Malloc(sizeof(Hello));

    if(!m->m_hello) {
        PyErr_SetString(PyExc_RuntimeError, "Memory allocation failed");
        return -1;
    }

    try{
        new (m->m_hello)Hello();
    } catch(const std::exception& ex) {
        PyObject_Free(m->m_hello);
        m->m_hello = NULL;
        m->m_val = 0;
        PyErr_SetString(PyExc_RuntimeError, ex.what());
        return -1;
    } catch(...) {
        PyObject_Free(m->m_hello);
        m->m_hello = NULL;
        m->m_val = 0;
        PyErr_SetString(PyExc_RuntimeError, "Initialization failed");
        return -1;
    }
    return 0;
}

void Hello_dealloc(HelloObject* self) {
    PyTypeObject* tp = Py_TYPE(self);
    HelloObject* m = reinterpret_cast<HelloObject*>(self);

    if(m->m_hello){
        m->m_hello->~Hello();
        PyObject_Free(m->m_hello);
    }

    tp->tp_free(self);
    Py_DECREF(tp);
}

PyObject* Hello_addOne(PyObject* self, PyObject* args) {
    HelloObject* _self = reinterpret_cast<HelloObject*>(self);
    _self->m_hello->addOne();
    Py_RETURN_NONE;  // void return type from Hello::addOne
}

PyObject* Hello_getValue(PyObject* self, PyObject* args) {
    HelloObject* _self = reinterpret_cast<HelloObject*>(self);
    int v = _self->m_hello->getValue();
    return PyLong_FromLong(v);
}

PyObject* Hello_setValue(PyObject* self, PyObject* args) {
    HelloObject* _self = reinterpret_cast<HelloObject*>(self);
    int v;

    if(!PyArg_ParseTuple(args, "i", &v)) {
        // raise error if the user didn't give the required argument
        PyErr_SetString(PyExc_TypeError, "Expected a single interger argument");
        return NULL;
    }

    _self->m_hello->setValue(v);
    Py_RETURN_NONE;
}
