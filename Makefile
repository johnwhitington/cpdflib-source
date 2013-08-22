CAMLBASE = /Users/john/.opam/4.00.1/lib/

mklib: cpdflib.mli cpdflib.ml cpdflibwrapper.c
	ocamlfind ocamlc -package cpdf cpdflib.mli;
	ocamlfind ocamlopt -package cpdf -c cpdflib.ml;
	ocamlfind ocamlc cpdflibwrapper.c;
	ocamlfind ocamlopt -I $(CAMLBASE)cpdf -I $(CAMLBASE)camlpdf \
          -output-obj -o cpdflib.o \
          unix.cmxa bigarray.cmxa camlpdf.cmxa cpdf.cmxa cpdflib.cmx;
	ar -x $(CAMLBASE)camlpdf/libcamlpdf_stubs.a;
	ar -x $(CAMLBASE)ocaml/libasmrun.a;
	ar cr cpdflib.a *.o 

test:   cpdflib.a cpdflibtest.c
	cc cpdflibtest.c cpdflib.a -o test -L $(CAMLBASE)ocaml -lbigarray -lunix

clean:
	rm __.SYMDEF\ SORTED *.o *.cmx *.cmi *.a test

