style: 
	@clang-format -n -style=Google *.h *.c
	@echo =STYLE CHECK COMPLETED=

style-fix: 
	@clang-format -i -style=Google *.h *.c
	@echo =STYLE FIX COMPLETED=

cppcheck:
	@cppcheck --enable=all --suppress=missingIncludeSystem *.c

.PHONY: style style-fix cppcheck
