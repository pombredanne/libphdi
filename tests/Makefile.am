AM_CPPFLAGS = \
	-I$(top_srcdir)/include \
	-I$(top_srcdir)/common \
	@LIBCERROR_CPPFLAGS@ \
	@LIBCTHREADS_CPPFLAGS@ \
	@LIBCDATA_CPPFLAGS@ \
	@LIBCLOCALE_CPPFLAGS@ \
	@LIBCNOTIFY_CPPFLAGS@ \
	@LIBCSPLIT_CPPFLAGS@ \
	@LIBUNA_CPPFLAGS@ \
	@LIBCDIRECTORY_CPPFLAGS@ \
	@LIBCFILE_CPPFLAGS@ \
	@LIBCPATH_CPPFLAGS@ \
	@LIBBFIO_CPPFLAGS@ \
	@LIBFCACHE_CPPFLAGS@ \
	@LIBFDATA_CPPFLAGS@ \
	@PTHREAD_CPPFLAGS@ \
	@LIBPHDI_DLL_IMPORT@

if HAVE_PYTHON_TESTS
TESTS_PYPHDI = \
	test_python_module.sh
endif

TESTS = \
	test_library.sh \
	test_phdiinfo.sh \
	$(TESTS_PYPHDI)

check_SCRIPTS = \
	pyphdi_test_handle.py \
	pyphdi_test_support.py \
	test_library.sh \
	test_phdiinfo.sh \
	test_python_module.sh \
	test_runner.sh

EXTRA_DIST = \
	$(check_SCRIPTS)

check_PROGRAMS = \
	phdi_test_error \
	phdi_test_handle \
	phdi_test_io_handle \
	phdi_test_notify \
	phdi_test_support

phdi_test_error_SOURCES = \
	phdi_test_error.c \
	phdi_test_libphdi.h \
	phdi_test_macros.h \
	phdi_test_unused.h

phdi_test_error_LDADD = \
	../libphdi/libphdi.la

phdi_test_handle_SOURCES = \
	phdi_test_getopt.c phdi_test_getopt.h \
	phdi_test_handle.c \
	phdi_test_libcerror.h \
	phdi_test_libclocale.h \
	phdi_test_libcnotify.h \
	phdi_test_libphdi.h \
	phdi_test_libuna.h \
	phdi_test_macros.h \
	phdi_test_memory.c phdi_test_memory.h

phdi_test_handle_LDADD = \
	@LIBUNA_LIBADD@ \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCDATA_LIBADD@ \
	../libphdi/libphdi.la \
	@LIBCTHREADS_LIBADD@ \
	@LIBCERROR_LIBADD@ \
	@PTHREAD_LIBADD@

phdi_test_io_handle_SOURCES = \
	phdi_test_io_handle.c \
	phdi_test_libcerror.h \
	phdi_test_libphdi.h \
	phdi_test_macros.h \
	phdi_test_memory.c phdi_test_memory.h \
	phdi_test_unused.h

phdi_test_io_handle_LDADD = \
	../libphdi/libphdi.la \
	@LIBCERROR_LIBADD@

phdi_test_notify_SOURCES = \
	phdi_test_libphdi.h \
	phdi_test_macros.h \
	phdi_test_notify.c \
	phdi_test_unused.h

phdi_test_notify_LDADD = \
	../libphdi/libphdi.la

phdi_test_support_SOURCES = \
	phdi_test_getopt.c phdi_test_getopt.h \
	phdi_test_libbfio.h \
	phdi_test_libcerror.h \
	phdi_test_libclocale.h \
	phdi_test_libcnotify.h \
	phdi_test_libphdi.h \
	phdi_test_libuna.h \
	phdi_test_macros.h \
	phdi_test_support.c

phdi_test_support_LDADD = \
	@LIBBFIO_LIBADD@ \
	@LIBCPATH_LIBADD@ \
	@LIBCFILE_LIBADD@ \
	@LIBUNA_LIBADD@ \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCDATA_LIBADD@ \
	../libphdi/libphdi.la \
	@LIBCERROR_LIBADD@

MAINTAINERCLEANFILES = \
	Makefile.in

distclean: clean
	/bin/rm -f Makefile

