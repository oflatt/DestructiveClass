from distutils.core import setup, Extension

module1 = Extension('DestructiveClass',
                    sources = ['src_c/destructiveclass.c'])


setup (name = 'DestructiveClass',
       version = '1.0',
       description = 'todo',
       ext_modules = [module1])
