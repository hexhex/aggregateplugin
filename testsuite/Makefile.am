EXTRA_DIST = \
    tests/aggregates.test \
    example1/count1.hex \
    tests/count1.out \
    example2/min1.hex \
    tests/min1.out \
    example3/min2.hex \
    tests/min2.out \
    example4/minmax1.hex \
    tests/minmax1.out \
    ../testsuite/run-dlvhex-tests.sh \
    ../testsuite/answerset_compare.py

TESTS = $(top_srcdir)/testsuite/run-dlvhex-tests.sh

TESTS_ENVIRONMENT = \
        TOP_SRCDIR=$(top_srcdir) \
        DLVHEX="$(DLVHEX_BINDIR)/dlvhex -s --plugindir=!$(top_builddir)/src" \
        EXAMPLESDIR=$(top_srcdir)/examples \
        TESTDIR=$(top_builddir)/examples/tests \
        OUTDIR=$(top_srcdir)/examples/tests

