/*
 * Library seek testing program
 *
 * Copyright (C) 2015-2016, Joachim Metz <joachim.metz@gmail.com>
 *
 * Refer to AUTHORS for acknowledgements.
 *
 * This software is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this software.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <common.h>
#include <file_stream.h>

#if defined( HAVE_STDLIB_H ) || defined( WINAPI )
#include <stdlib.h>
#endif

#include "phdi_test_libcerror.h"
#include "phdi_test_libcstring.h"
#include "phdi_test_libcsystem.h"
#include "phdi_test_libphdi.h"
#include "phdi_test_unused.h"

/* Define to make phdi_test_seek generate verbose output
#define PHDI_TEST_SEEK_VERBOSE
 */

/* Tests libphdi_handle_seek_offset
 * Returns 1 if successful, 0 if not or -1 on error
 */
int phdi_test_seek_offset(
     libphdi_handle_t *handle,
     off64_t input_offset,
     int input_whence,
     off64_t output_offset )
{
	libcerror_error_t *error  = NULL;
	const char *whence_string = NULL;
	off64_t result_offset     = 0;
	int result                = 0;

	if( handle == NULL )
	{
		return( -1 );
	}
	if( input_whence == SEEK_CUR )
	{
		whence_string = "SEEK_CUR";
	}
	else if( input_whence == SEEK_END )
	{
		whence_string = "SEEK_END";
	}
	else if( input_whence == SEEK_SET )
	{
		whence_string = "SEEK_SET";
	}
	else
	{
		whence_string = "UNKNOWN";
	}
	fprintf(
	 stdout,
	 "Testing seek of offset: %" PRIi64 " and whence: %s\t",
	 input_offset,
	 whence_string );

	result_offset = libphdi_handle_seek_offset(
	                 handle,
	                 input_offset,
	                 input_whence,
	                 &error );

	if( result_offset == output_offset )
	{
		result = 1;
	}
	if( result != 0 )
	{
		fprintf(
		 stdout,
		 "(PASS)" );
	}
	else
	{
		fprintf(
		 stdout,
		 "(FAIL)" );
	}
	fprintf(
	 stdout,
	 "\n" );

	if( error != NULL )
	{
		if( result != 1 )
		{
			libcerror_error_backtrace_fprint(
			 error,
			 stderr );
		}
		libcerror_error_free(
		 &error );
	}
	return( result );
}

/* Tests seeking in a handle
 * Returns 1 if successful, 0 if not or -1 on error
 */
int phdi_test_seek_handle(
     libphdi_handle_t *handle,
     size64_t media_size )
{
	size64_t seek_offset = 0;
	int result           = 0;

	if( handle == NULL )
	{
		return( -1 );
	}
	if( media_size > (size64_t) INT64_MAX )
	{
		fprintf(
		 stderr,
		 "File size exceeds maximum.\n" );

		return( -1 );
	}
	/* Test: SEEK_SET offset: 0
	 * Expected result: 0
	 */
	seek_offset = 0;

	result = phdi_test_seek_offset(
	          handle,
	          seek_offset,
	          SEEK_SET,
	          seek_offset );

	if( result != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to test seek offset.\n" );

		return( result );
	}
	/* Test: SEEK_SET offset: <media_size>
	 * Expected result: <media_size>
	 */
	seek_offset = (off64_t) media_size;

	result = phdi_test_seek_offset(
	          handle,
	          seek_offset,
	          SEEK_SET,
	          seek_offset );

	if( result != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to test seek offset.\n" );

		return( result );
	}
	/* Test: SEEK_SET offset: <media_size / 5>
	 * Expected result: <media_size / 5>
	 */
	seek_offset = (off64_t) ( media_size / 5 );

	result = phdi_test_seek_offset(
	          handle,
	          seek_offset,
	          SEEK_SET,
	          seek_offset );

	if( result != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to test seek offset.\n" );

		return( result );
	}
	/* Test: SEEK_SET offset: <media_size + 987>
	 * Expected result: <media_size + 987>
	 */
	seek_offset = (off64_t) ( media_size + 987 );

	result = phdi_test_seek_offset(
	          handle,
	          seek_offset,
	          SEEK_SET,
	          seek_offset );

	if( result != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to test seek offset.\n" );

		return( result );
	}
	/* Test: SEEK_SET offset: -987
	 * Expected result: -1
	 */
	seek_offset = -987;

	result = phdi_test_seek_offset(
	          handle,
	          seek_offset,
	          SEEK_SET,
	          -1 );

	if( result != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to test seek offset.\n" );

		return( result );
	}
	/* Test: SEEK_CUR offset: 0
	 * Expected result: <media_size + 987>
	 */
	seek_offset = 0;

	result = phdi_test_seek_offset(
	          handle,
	          seek_offset,
	          SEEK_CUR,
	          (off64_t) ( media_size + 987 ) );

	if( result != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to test seek offset.\n" );

		return( result );
	}
	/* Test: SEEK_CUR offset: <-1 * (media_size + 987)>
	 * Expected result: 0
	 */
	seek_offset = -1 * (off64_t) ( media_size + 987 );

	result = phdi_test_seek_offset(
	          handle,
	          seek_offset,
	          SEEK_CUR,
	          0 );

	if( result != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to test seek offset.\n" );

		return( result );
	}
	/* Test: SEEK_CUR offset: <media_size / 3>
	 * Expected result: <media_size / 3>
	 */
	seek_offset = (off64_t) ( media_size / 3 );

	result = phdi_test_seek_offset(
	          handle,
	          seek_offset,
	          SEEK_CUR,
	          seek_offset );

	if( result != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to test seek offset.\n" );

		return( result );
	}
	seek_offset = -2 * (off64_t) ( media_size / 3 );

	if( media_size == 0 )
	{
		/* Test: SEEK_CUR offset: <-2 * (media_size / 3)>
		 * Expected result: 0
		 */
		result = phdi_test_seek_offset(
		          handle,
		          seek_offset,
		          SEEK_CUR,
		          0 );

		if( result != 1 )
		{
			fprintf(
			 stderr,
			 "Unable to test seek offset.\n" );

			return( result );
		}
	}
	else
	{
		/* Test: SEEK_CUR offset: <-2 * (media_size / 3)>
		 * Expected result: -1
		 */
		result = phdi_test_seek_offset(
		          handle,
		          seek_offset,
		          SEEK_CUR,
		          -1 );

		if( result != 1 )
		{
			fprintf(
			 stderr,
			 "Unable to test seek offset.\n" );

			return( result );
		}
	}
	/* Test: SEEK_END offset: 0
	 * Expected result: <media_size>
	 */
	seek_offset = 0;

	result = phdi_test_seek_offset(
	          handle,
	          seek_offset,
	          SEEK_END,
	          (off64_t) media_size );

	if( result != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to test seek offset.\n" );

		return( result );
	}
	/* Test: SEEK_END offset: <-1 * media_size>
	 * Expected result: 0
	 */
	seek_offset = -1 * (off64_t) media_size;

	result = phdi_test_seek_offset(
	          handle,
	          seek_offset,
	          SEEK_END,
	          0 );

	if( result != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to test seek offset.\n" );

		return( result );
	}
	/* Test: SEEK_END offset: <-1 * (media_size / 4)>
	 * Expected result: <media_size - (media_size / 4)>
	 */
	seek_offset = (off64_t) ( media_size / 4 );

	result = phdi_test_seek_offset(
	          handle,
	          -1 * seek_offset,
	          SEEK_END,
	          (off64_t) media_size - seek_offset );

	if( result != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to test seek offset.\n" );

		return( result );
	}
	/* Test: SEEK_END offset: 542
	 * Expected result: <media_size + 542>
	 */
	seek_offset = 542;

	result = phdi_test_seek_offset(
	          handle,
	          seek_offset,
	          SEEK_END,
	          (off64_t) ( media_size + 542 ) );

	if( result != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to test seek offset.\n" );

		return( result );
	}
	/* Test: SEEK_END offset: <-1 * (media_size + 542)>
	 * Expected result: -1
	 */
	seek_offset = -1 * (off64_t) ( media_size + 542 );

	result = phdi_test_seek_offset(
	          handle,
	          seek_offset,
	          SEEK_END,
	          -1 );

	if( result != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to test seek offset.\n" );

		return( result );
	}
	/* Test: UNKNOWN (88) offset: 0
	 * Expected result: -1
	 */
	result = phdi_test_seek_offset(
	          handle,
	          0,
	          88,
	          -1 );

	if( result != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to test seek offset.\n" );

		return( result );
	}
	return( result );
}

/* Tests seeking in a handle
 * Returns 1 if successful, 0 if not or -1 on error
 */
int phdi_test_seek(
     libcstring_system_character_t *source,
     libcerror_error_t **error )
{
	libphdi_handle_t *handle = NULL;
	size64_t media_size      = 0;
	int result               = 0;

	if( libphdi_handle_initialize(
	     &handle,
	     error ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to create handle.\n" );

		goto on_error;
	}
#if defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER )
	if( libphdi_handle_open_wide(
	     handle,
	     source,
	     LIBPHDI_OPEN_READ,
	     error ) != 1 )
#else
	if( libphdi_handle_open(
	     handle,
	     source,
	     LIBPHDI_OPEN_READ,
	     error ) != 1 )
#endif
	{
		fprintf(
		 stderr,
		 "Unable to open handle.\n" );

		goto on_error;
	}
	if( libphdi_handle_get_media_size(
	     handle,
	     &media_size,
	     error ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to retrieve media size.\n" );

		goto on_error;
	}
	result = phdi_test_seek_handle(
	          handle,
	          media_size );

	if( result == -1 )
	{
		fprintf(
		 stderr,
		 "Unable to seek in handle.\n" );

		goto on_error;
	}
	if( libphdi_handle_close(
	     handle,
	     error ) != 0 )
	{
		fprintf(
		 stderr,
		 "Unable to close handle.\n" );

		goto on_error;
	}
	if( libphdi_handle_free(
	     &handle,
	     error ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to free handle.\n" );

		goto on_error;
	}
	return( result );

on_error:
	if( handle != NULL )
	{
		libphdi_handle_close(
		 handle,
		 NULL );
		libphdi_handle_free(
		 &handle,
		 NULL );
	}
	return( -1 );
}

/* Tests seeking in a handle without opening it
 * Returns 1 if successful, 0 if not or -1 on error
 */
int phdi_test_seek_no_open(
     libcstring_system_character_t *source PHDI_TEST_ATTRIBUTE_UNUSED,
     libcerror_error_t **error )
{
	libphdi_handle_t *handle = NULL;
	off64_t result_offset    = 0;
	int result               = 0;

	PHDI_TEST_UNREFERENCED_PARAMETER( source );

	if( libphdi_handle_initialize(
	     &handle,
	     error ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to create handle.\n" );

		goto on_error;
	}
	fprintf(
	 stdout,
	 "Testing seek without open: \t" );

	result_offset = libphdi_handle_seek_offset(
	                 handle,
	                 0,
	                 SEEK_SET,
	                 error );

	if( result_offset == -1 )
	{
		result = 1;
	}
	if( result != 0 )
	{
		fprintf(
		 stdout,
		 "(PASS)" );
	}
	else
	{
		fprintf(
		 stdout,
		 "(FAIL)" );
	}
	fprintf(
	 stdout,
	 "\n" );

	if( ( error != NULL )
	 && ( *error != NULL ) )
	{
		if( result != 1 )
		{
			libcerror_error_backtrace_fprint(
			 *error,
			 stderr );
		}
		libcerror_error_free(
		 error );
	}
	if( libphdi_handle_free(
	     &handle,
	     error ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to free handle.\n" );

		goto on_error;
	}
	return( result );

on_error:
	if( handle != NULL )
	{
		libphdi_handle_free(
		 &handle,
		 NULL );
	}
	return( -1 );
}

/* The main program
 */
#if defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER )
int wmain( int argc, wchar_t * const argv[] )
#else
int main( int argc, char * const argv[] )
#endif
{
	libcerror_error_t *error              = NULL;
	libcstring_system_character_t *source = NULL;
	libcstring_system_integer_t option    = 0;
	int result                            = 0;

	while( ( option = libcsystem_getopt(
	                   argc,
	                   argv,
	                   _LIBCSTRING_SYSTEM_STRING( "" ) ) ) != (libcstring_system_integer_t) -1 )
	{
		switch( option )
		{
			case (libcstring_system_integer_t) '?':
			default:
				fprintf(
				 stderr,
				 "Invalid argument: %" PRIs_LIBCSTRING_SYSTEM ".\n",
				 argv[ optind - 1 ] );

				return( EXIT_FAILURE );
		}
	}
	if( optind == argc )
	{
		fprintf(
		 stderr,
		 "Missing source file or device.\n" );

		return( EXIT_FAILURE );
	}
	source = argv[ optind ];

#if defined( HAVE_DEBUG_OUTPUT ) && defined( PHDI_TEST_SEEK_VERBOSE )
	libphdi_notify_set_verbose(
	 1 );
	libphdi_notify_set_stream(
	 stderr,
	 NULL );
#endif
	if( phdi_test_seek(
	     source,
	     &error ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to seek in handle.\n" );

		goto on_error;
	}
	if( phdi_test_seek_no_open(
	     source,
	     &error ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to seek in handle without open.\n" );

		goto on_error;
	}
	return( EXIT_SUCCESS );

on_error:
	if( error != NULL )
	{
		libcerror_error_backtrace_fprint(
		 error,
		 stderr );
		libcerror_error_free(
		 &error );
	}
	return( EXIT_FAILURE );
}

