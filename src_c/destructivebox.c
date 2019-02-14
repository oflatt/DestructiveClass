#include <Python.h>
#include "destructivebox.h"

// ####################### destructivebox

typedef struct destructbox_t {
    PyObject_HEAD
    /* Type-specific fields go here. */
} DestructiveBox;

static PyTypeObject DestructiveBoxType = {
    PyVarObject_HEAD_INIT(NULL, 0)
    .tp_name = "destructiveclass.DestructiveBox",
    .tp_doc = "Custom objects",
    .tp_basicsize = sizeof(DestructiveBox),
    .tp_itemsize = 0,
    .tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,
    .tp_new = PyType_GenericNew,
};

static PyModuleDef destructiveboxmodule = {
    PyModuleDef_HEAD_INIT,
    .m_name = "DestructiveBox",
    .m_doc = "Module holding the DestructiveBox wrapper class.",
    .m_size = -1,
};
