cpdflib-source
==============

(Binaries are at http://github.com/coherentgraphics/cpdflib-binary )

Cpdflib is a library version of the Coherent PDF Command Line Tools, which are
available from http://www.coherentpdf.com/

It is licensed free for non-commercial use (see the file LICENSE in this
directory).

Prerequisites for building:

1. OCaml
2. Ocamlfind
3. CamlPDF, same versino as cpdflib
4. CPDF, same version as cpdflib

To build, just run ./build. This makes the static library libcpdf.a and, on
Windows, the dynamic library libcpdf.dll. In addition, it builds the
libcpdftest binary using static linking. This contains tests which exercise
every libcpdf function.

The build script also outputs suitable linker flags.

contact@coherentgraphics.co.uk
