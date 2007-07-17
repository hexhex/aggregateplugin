AUTOMAKE_OPTIONS = gnu

EXTRA_DIST = \
    aggregates.test \
    min1.hex \
    count1.hex \
    count1.out \
	run-dlvhex-tests.sh

TESTS = run-dlvhex-tests.sh

TESTS_ENVIRONMENT = TESTDIR=$(top_srcdir)/testsuite DLVHEX=dlvhex PARAMETERS="-s --plugindir=$(top_builddir)/src/.libs"

