gcov: gcov_report
	@$(OPENOS) ./$(GCOV_DIR)/gcov_report.html

gcov_report: $(LIB) test run $(GCOV_DIR)/gcov_report.html

$(GCOV_DIR)/gcov_report.html: $(LIB) test
	@mkdir -p gcov_report
	gcovr -r . --gcov-executable $(GCOV) --html --html-details -o $(GCOV_DIR)/gcov_report.html

.PHONY: gcov gcov_report
