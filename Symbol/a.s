	.file	"a.c"
	.text
	.globl	_symbol_test
	.def	_symbol_test;	.scl	2;	.type	32;	.endef
_symbol_test:
	pushl	%ebp
	movl	%esp, %ebp
	popl	%ebp
	ret
	.ident	"GCC: (i686-posix-sjlj, built by strawberryperl.com project) 4.9.2"
