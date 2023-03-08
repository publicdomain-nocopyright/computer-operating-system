/** @file print.c 
 * 	@brief A wrapper library for printf function.
 *	
 *	At the core: vfprintf instead of printf is used 
 *	to allow streams and variadic arguments 
 *	Print is also extended into helper functions 
 *   error() warning() notice() info() 
 */

// Standard way to compile and run: gcc -Wall -Wextra -Q  print.c && a


#include <stdio.h>
#include <stdarg.h>

/** @brief Uses vfprintf() C Standard Library function to print to the standard stream.
 * 
 *	Major output functions like print() and print_error() depend on this implementation.
 *  Can be used to made additional wrappers.
 *  Three standard streams are supported:
 *   standard input (stdin)
 *   standard output (stdout)
 *   standard error (stderr)
 *
 */
int implementation_print(FILE * stream, const char* format, va_list variadic_arguments){
	return vfprintf(stream, format, variadic_arguments);	
}

/** @brief frontend of print() function that accepts variadic arguments.
 *  
 *	Depends on implementation_print() that uses vfprintf() of C Standard Library
 *   
 *  @return Error code of vfprintf
 *
 */
int print(const char* format, ...){
	int errcode = 0;

	va_list variadic_arguments;
	va_start(variadic_arguments, format);
	
	errcode = implementation_print(stdout, format, variadic_arguments);
	
	va_end(variadic_arguments);
	return errcode;
}

int print_error(const char* format, ...){
	int errcode = 0;

	va_list variadic_arguments;
	va_start(variadic_arguments, format);
	
	errcode = implementation_print(stderr, format, variadic_arguments);
	
	va_end(variadic_arguments);
	return errcode;
}


int print_notice(const char* format, ...){
	int errcode = 0;

	va_list variadic_arguments;
	va_start(variadic_arguments, format);
	
	errcode = implementation_print(stdout, format, variadic_arguments);
	
	va_end(variadic_arguments);
	return errcode;
}

int print_warning(const char* format, ...){
	int errcode = 0;

	va_list variadic_arguments;
	va_start(variadic_arguments, format);
	
	errcode = implementation_print(stdout, format, variadic_arguments);
	
	va_end(variadic_arguments);
	return errcode;
}

int implementation_log_to_file(const char* file, const char* format, va_list variadic_arguments){
	int errcode = 0;

	FILE *file_pointer = fopen(file, "a");  
	errcode = implementation_print(file_pointer, format, variadic_arguments);
	fclose(file_pointer);
	return errcode;
}

int log_to_file(const char* file, const char* format, ...){
	int errcode = 0;

	va_list variadic_arguments;
	va_start(variadic_arguments, format);

	errcode = implementation_log_to_file(file, format, variadic_arguments);
	
	va_end(variadic_arguments);
	return errcode;
}


// TODO: Make a separate variadic arguments function that
//  handles reset of variadic arguments after its use.

// Function could be named: notate()
#define notate print_and_log
int print_and_log(const char* file, const char* format, ...){
	int errcode = 0;

    va_list variadic_arguments;
    va_start(variadic_arguments, format);

    va_list log_arguments;
    va_copy(log_arguments, variadic_arguments);
    errcode = implementation_log_to_file(file, format, log_arguments);
	va_end(log_arguments);
	if (errcode < 0){
		va_end(variadic_arguments);
		return errcode;
	}

    va_list print_arguments;
    va_copy(print_arguments, variadic_arguments);
    errcode = implementation_print(stdout, format, print_arguments);
    va_end(print_arguments);
	if (errcode < 0){
		va_end(variadic_arguments);
		return errcode;
	}

	va_end(variadic_arguments);
	return errcode;
}

#include <assert.h>

int main(){
	char * test = "Outhere";
	print("print function %s\n", test);
	printf("printf function %s\n", test);
	fprintf(stdout,"fprintf function %s\n", test);
	
	assert(print_notice("notice %s\n", test) != 0 );
	assert(print_error("error %s\n", test) != 0 );
	assert(print_warning("warning %s\n", test) != 0 );
	assert(print_and_log(".//file.txt", "print and log: %s\n", test) != 0 );
	assert(log_to_file(".//file.txt", "only_log output2: %s\n", test) != 0 );
	assert(notate(".//file.txt", "Alias: notate: print and log: %s\n", test) != 0 );
	return 0;

}