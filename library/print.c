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

// Stream: Error, custom, warning, notice, log, file

// Prototypes
// print(format, variables)
// print(stream, format, variables)
// print(error, "%s", var1,var2)
// print("format")
// print("text")
// print("text")

// log() //logarithm? not great.
// log - prints to both stdout stream and a file.


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
	va_list variadic_arguments;
	va_start(variadic_arguments, format);
	
	int errcode = implementation_print(stdout, format, variadic_arguments);
	
	va_end(variadic_arguments);
	return errcode;
}

void print_error(const char* format, ...){
	va_list variadic_arguments;
	va_start(variadic_arguments, format);
	
	implementation_print(stderr, format, variadic_arguments);
	
	va_end(variadic_arguments);
}


void print_notice(const char* format, ...){
	va_list variadic_arguments;
	va_start(variadic_arguments, format);
	
	implementation_print(stdout, format, variadic_arguments);
	
	va_end(variadic_arguments);
}

void print_warning(const char* format, ...){
	va_list variadic_arguments;
	va_start(variadic_arguments, format);
	
	implementation_print(stdout, format, variadic_arguments);
	
	va_end(variadic_arguments);
}

void implementation_log_this(const char* file, const char* format, va_list variadic_arguments){
	FILE *file_pointer = fopen(file, "a");  
	implementation_print(file_pointer, format, variadic_arguments);
	fclose(file_pointer);
}

void log_this(const char* file, const char* format, ...){
	va_list variadic_arguments;
	va_start(variadic_arguments, format);

	implementation_log_this(file, format, variadic_arguments);
	
	va_end(variadic_arguments);
}

// TODO: Make a separate variadic arguments function that
//  handles reset of variadic arguments after its use.
void print_and_log(const char* file, const char* format, ...){
    va_list variadic_arguments;
    va_start(variadic_arguments, format);


    va_list log_arguments;
    va_copy(log_arguments, variadic_arguments);
    implementation_log_this(file, format, log_arguments);
	va_end(log_arguments);

    va_list print_arguments;
    va_copy(print_arguments, variadic_arguments);
    implementation_print(stdout, format, print_arguments);
    va_end(print_arguments);

	va_end(variadic_arguments);
}



// log already reserved by C language library
// log log_error log_info
// ECHO
// print_and_log()




int main(){
	char * test = "Outhere";
	print("Hellows %s\n", test);
	printf("Hellows %s\n", test);
	fprintf(stdout,"Hellows %s\n", test);
	
	print_notice("notice %s\n", test);
	print_error("error %s\n", test);
	print_warning("warning %s\n", test);
	print_and_log(".//file.txt", "print and log: %s\n", test);
	log_this(".//file.txt", "only_log output2: %s\n", test);
	return 0;

}