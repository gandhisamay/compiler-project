# Group 22
# Samay Gandhi 2020A7PS0299P
# Mohit Makwana 2020A7PS0048P
# Kathan Patel 2020A7PS0058P
# Aditya Sheth 2020A7PS1511P
# Aryan Chavan 2020A7PS1692P

target:
	 gcc driver.c -o compiler
	 @echo "Run command: ./compiler <testfile> <file_name_to_store_parse_tree> <buffer_size>"
	 @echo "Run 'make test' for running testcases"

test:
	 gcc driver.c -o compiler
	 ./compiler testcase_code_gen.txt parse.txt 100
	 nasm -f elf64 code.asm  
	 ld -m elf_x86_64 -s -o out code.o && ./out

run:
	 nasm -f elf64 code.asm  
	 ld -m elf_x86_64 -s -o out code.o && ./out

code_gen:
	 gcc driver.c -o compiler
	 ./compiler ./Code_Generation_testcases/c1.txt parse.txt 100
	 ./compiler ./Code_Generation_testcases/c2.txt parse.txt 100
	 ./compiler ./Code_Generation_testcases/c3.txt parse.txt 100
	 ./compiler ./Code_Generation_testcases/c4.txt parse.txt 100
	 ./compiler ./Code_Generation_testcases/c5.txt parse.txt 100
	 ./compiler ./Code_Generation_testcases/c6.txt parse.txt 100
	 ./compiler ./Code_Generation_testcases/c7.txt parse.txt 100
	 ./compiler ./Code_Generation_testcases/c8.txt parse.txt 100
	 ./compiler ./Code_Generation_testcases/c10.txt parse.txt 100
	 ./compiler ./Code_Generation_testcases/c11.txt parse.txt 100


