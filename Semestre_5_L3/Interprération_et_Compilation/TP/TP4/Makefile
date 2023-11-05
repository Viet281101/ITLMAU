

all: tp4


tp4:
	$ ocamlbuild -use-ocamlfind -r test.byte

run: 
	$ ./test.byte

clean:
	$ rmdir --ignore-fail-on-non-empty _build
	$ rm -r test.byte

