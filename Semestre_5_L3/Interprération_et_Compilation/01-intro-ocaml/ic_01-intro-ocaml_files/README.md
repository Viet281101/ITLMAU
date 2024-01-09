This project is a tiny compiler for a very simple language consisting of boolean expression.

The language has two constants: `1` for true and `0` for false, and 4 logic gates:
`!` (not), `&` (and), `|` (or), and `^` (xor).

It can also use parentheses to manage priorities.

Here is its grammar in BNF format:

    expr ::= "0" | "1"
           | "!" expr
           | expr "&" expr
           | expr "|" expr
           | expr "^" expr
           | "(" expr ")"

The goal is to compile it to a virtual machine bytecode.

The virual machine has two registers (`acc` and `tmp`) and memory stack.

The bytecode consists in 6 instructions:

- `t`: sets the acc register to 1
- `f`: sets the acc register to 0
- `s`: pushes the value of the acc register onto the stack
- `l`: pops the top value of the stack and write it to the acc register
- `h`: copies the value of the acc register into the tmp register
- `n`: sets the acc register to the value of acc nand tmp

This is sufficient because the nand gate is functionally complete:
https://en.wikipedia.org/wiki/Functional_completeness

After lexing and parsing, we do not need any semantic analysis or type checking
because there are no names (e.g., no variables) and a single type.

This is why we do not keep source location information in the parser's output.
In a more complex language (e.g., adding support for assignment to variables),
we would need an additional front-end pass after the parser.
This is not a lot to add, I could make it if asked to.

The compilation strategy is to first use known formulas to translate the parsed
boolean expression into an equivalent expression that only uses `nand` gates.
(See https://en.wikipedia.org/wiki/NAND_logic)

In a second pass, this (functional) expression is compiled down to (imperative)
bytecode instructions.

This is were we can see actual compilation work: the paradigm shift from
functional "high level" to imperative "low level" forces us to implement
our language's abstractions (here, function call) using more primitive
constructs (stack and register manipulation).

We can also see that the approach we use will generate non-optimal code,
because our compiler will always treat `nand` gates in the same way without
regard to the context (e.g. we would manually translate "!1" into "thn" but
our compiler will generate "tsthln"). An additional optimization pass that
look for such patterns and replace them with manually optimized ones would
be quite easy to make. I could also provide it if asked to.

The VM is implemented in C.

The compiler is implemented in OCaml.

The lexer uses ocamllex, the parser uses menhir.

Files need to be renamed without the numbers and underscore at the beginging of
their names, which are here so that they appear in the desired order in this gist.

To compile the compiler: `ocamlbuild -use-menhir main.byte`.

To compile the vm: `gcc nandvm.c -o nandvm`.

Then you can for example run:

- `./main.byte <<<"1" | ./nandvm`
- `./main.byte <<<"!(0 ^ 1)" | ./nandvm`
- `./main.byte <<<"0 ^ (0 | 1) & !(1 ^ 1)" | ./nandvm`
