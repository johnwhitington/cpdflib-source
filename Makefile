# Build the camlpdf library as byte code and, if available, native code
SOURCES = auto.ml

RESULT = auto
PACKS = camlpdf

CFLAGS = -o2
OCAMLFLAGS = -bin-annot
OCAMLNCFLAGS = -g -safe-string
OCAMLBCFLAGS = -g -safe-string
OCAMLLDFLAGS = -g

TARGETS := native-code

all : $(TARGETS)

clean ::
	rm -rf doc foo foo2 out.pdf out2.pdf *.ps *.cmt *.cmti *.zlib

-include OCamlMakefile
