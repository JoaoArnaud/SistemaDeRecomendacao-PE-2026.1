from setuptools import setup
from pybind11.setup_helpers import Pybind11Extension, build_ext


ext_modules = [
    Pybind11Extension(
        "solver",
        [
            "solver.cpp",
            "../src/lista_compras.cpp",
            "../src/similaridade.cpp",
            "../src/recomendacao.cpp",
        ],
        cxx_std=17,
    ),
]


setup(
    name="solver",
    version="0.1.0",
    description="Integracao Python e C++ do sistema de recomendacao",
    ext_modules=ext_modules,
    cmdclass={"build_ext": build_ext},
    zip_safe=False,
)