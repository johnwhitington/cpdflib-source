#CAML_LD_LIBRARY_PATH requires OPAM. Otherwise, hard code it...
CAMLBASE = $(CAML_LD_LIBRARY_PATH)/../

mklib: cpdflib.mli cpdflib.ml cpdflibwrapper.c
	ocamlfind ocamlc -package cpdf cpdflib.mli;
	ocamlfind ocamlopt -package cpdf -c cpdflib.ml;
	ocamlfind ocamlc cpdflibwrapper.c;
	ocamlfind ocamlopt -verbose -I $(CAMLBASE)cpdf -I $(CAMLBASE)camlpdf \
          -output-obj -o mainlib.o \
          unix.cmxa bigarray.cmxa camlpdf.cmxa cpdf.cmxa cpdflib.cmx;
	cp $(CAMLBASE)ocaml/libasmrun.a libcpdf.a;
	cp $(CAMLBASE)ocaml/libunix.a .;
	cp $(CAMLBASE)ocaml/libbigarray.a .;
	ar -x $(CAMLBASE)camlpdf/libcamlpdf_stubs.a;
	ar r libcpdf.a *.o 

test:   libcpdf.a cpdflibtest.c
	cc cpdflibtest.c -o cpdflibtest -L. -lcpdf -lbigarray -lunix

simpletest:   libcpdf.a simpletest.c
	cc simpletest.c -o simpletest -L. -lcpdf -lbigarray -lunix

clean:
	rm -f __.SYMDEF\ SORTED *.o *.cmx *.cmi *.a cpdflibtest *.aux *.idx \
*.log *.out *.toc simpletest merged.pdf; rm -rf testoutputs

