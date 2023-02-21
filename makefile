template_test:
	@echo "\n Running sample test flow..." 
	@gcc src/test_eg.c -o bin/test -lcunit
	@cd cunit_results && ../bin/test

test:
	@echo "\n Running all tests flow..." 
#   repeat for all test files
	# @gcc src/test_eg.c -o bin/test -lcunit
	# @cd cunit_results && ../bin/test

# exe:
# 	@echo "\nCOMPILING..."
# 	@gcc $(src) -g -lm
# 	@echo "\nCOMPILED SUCCESSFULLY... $(src)"
# 	@echo "\n Run the file as ./a.out <testcase file> <asm file>"
