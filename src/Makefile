target:
	 gcc driver.c -o compiler
	 @echo "Run command: ./compiler <testfile> <file_name_to_store_parse_tree> <buffer_size>"

test:
	 gcc driver.c -o compiler
	# ./compiler ../tests/test_cases_stage_1/t1.txt test.txt 100
	./compiler ../tests/test_cases_stage_1/t2.txt test.txt 100
	./compiler ../tests/test_cases_stage_1/t3.txt test.txt 100
	./compiler ../tests/test_cases_stage_1/t4.txt test.txt 100
	./compiler ../tests/test_cases_stage_1/t5.txt test.txt 100
	./compiler ../tests/test_cases_stage_1/t6_syntax_errors.txt test.txt 100

