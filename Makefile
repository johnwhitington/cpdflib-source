CAMLBASE = /Users/john/.opam/4.01.0/lib/

mklib: cpdflib.mli cpdflib.ml cpdflibwrapper.c
	ocamlfind ocamlc -package cpdf cpdflib.mli;
	ocamlfind ocamlopt -package cpdf -c cpdflib.ml;
	ocamlfind ocamlc cpdflibwrapper.c;
	ocamlfind ocamlopt -I $(CAMLBASE)cpdf -I $(CAMLBASE)camlpdf \
          -output-obj -o cpdflib.o \
          camlpdf.cmxa cpdf.cmxa cpdflib.cmx;
	cp $(CAMLBASE)ocaml/libasmrun.a libcpdf.a;
	ar -x $(CAMLBASE)camlpdf/libcamlpdf_stubs.a;
	ar -x $(CAMLBASE)cpdf/libcpdf_stubs.a;
	ar r libcpdf.a *.o 

test:   libcpdf.a cpdflibtest.c
	cc cpdflibtest.c -o cpdflibtest -L. -lcpdf

clean:
	rm -f __.SYMDEF\ SORTED *.o *.cmx *.cmi *.a cpdflibtest *.aux *.idx \
*.log *.out *.toc; rm -r testoutputs

