#  ////////////////////  DOCUMENTATION  /////////////////////
$(DOC_DIR)/$(LIB:.a=_doxyfile):
	@sed -i 's/PROJECT_NAME           = "My Project"/PROJECT_NAME           = "$(LIB:.a=)"/g' $(DOC_DIR)/$(LIB:.a=_doxyfile)

doxygen-gen: $(DOC_DIR)/$(LIB:.a=_doxyfile)
	doxygen $(DOC_DIR)/$(LIB:.a=_doxyfile)

doxygen: doxygen-gen
	@$(OPENOS) ./doc/html/index.html


report_online:
	@sudo rm -rf /var/www/69.tw-team.com/public_html/*
	$(MAKE) clean
	$(MAKE) doxygen-gen
	$(MAKE) gcov_report
	@sudo cp -R ./gcov_report /var/www/69.tw-team.com/public_html/
	@sudo cp -R ./doc/html/* /var/www/69.tw-team.com/public_html/
	$(MAKE) clean
	@echo =Use https://69.tw-team.com/ for browsing reports!=
# https://www.digitalocean.com/community/tutorials/how-to-set-up-apache-virtual-hosts-on-ubuntu-16-04
# https://www.digitalocean.com/community/tutorials/how-to-secure-apache-with-let-s-encrypt-on-ubuntu-22-04

.PHONY: doxygen doxygen-gen report_online