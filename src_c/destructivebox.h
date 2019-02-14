#include <Python.h>

static PyTypeObject DestructiveBoxType;

static PyModuleDef destructiveboxmodule;

typedef struct destructbox_t DestructiveBox;
