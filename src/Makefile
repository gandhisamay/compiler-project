target:
	 gcc driver.c -o compiler
	 @echo "Run command: ./compiler <testfile> <file_name_to_store_parse_tree> <buffer_size>"

test:
	 gcc driver.c -o compiler
	./compiler t1.txt parse_tree.txt 100
	./compiler t2.txt parse_tree.txt 100
	./compiler t3.txt parse_tree.txt 100
	./compiler t4.txt parse_tree.txt 100
	./compiler t5.txt parse_tree.txt 100
	./compiler t6_syntax_errors.txt parse_tree.txt 100

extra:
	 gcc driver.c -o compiler
	./compiler test_extra_1.txt parse_tree.txt 100
	./compiler test_extra_2.txt parse_tree.txt 100
	./compiler test_extra_3.txt parse_tree.txt 100
	./compiler test_extra_4.txt parse_tree.txt 100
	./compiler test_extra_5.txt parse_tree.txt 100
	./compiler test_extra_6.txt parse_tree.txt 100
	./compiler test_extra_7.txt parse_tree.txt 100

