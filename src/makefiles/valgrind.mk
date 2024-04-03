valgrind: test
	valgrind -s --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose ./test

valgrind_short: test
	valgrind -s --track-origins=yes --verbose ./test

.PHONY: valgrind valgrind_short
