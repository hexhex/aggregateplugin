EXTRA_DIST = \
    example1/count1.hex \
    example2/min1.hex \
    example3/min2.hex \
    example4/minmax1.hex \
    example5/max1.hex \
    example6/nomask_min.hex \
    example7/nomask_max.hex \
    example8/nomask_count.hex \
    tests/aggregates.test \
    tests/count1.out \
    tests/max1.out \
    tests/min1.out \
    tests/min2.stderr \
    tests/minmax1.out \
		tests/nomask_count.out \
		tests/nomask_max.stderr \
		tests/nomask_min.stderr \
    ../testsuite/run-dlvhex-tests.sh \
    ../testsuite/answerset_compare.py

TESTS = $(top_srcdir)/testsuite/run-dlvhex-tests.sh

TESTS_ENVIRONMENT = \
        TOP_SRCDIR=$(top_srcdir) \
        DLVHEX="$(DLVHEX_BINDIR)/dlvhex2 -s --plugindir=!$(top_builddir)/src/.libs" \
        EXAMPLESDIR=$(top_srcdir)/examples \
        TESTDIR=$(top_builddir)/examples/tests \
        OUTDIR=$(top_srcdir)/examples/tests
        
