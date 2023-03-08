#include <stdio.h>
#include <stdlib.h>                     /* malloc */
#include <string.h>                     /* strlen... */
#include <locale.h>
#include <wchar.h>
//
void main( int argc , char *argv[])
{
    #   ifdef _WIN32
        system("chcp 65001 > nul");
    #   endif
	
    printf("%s", "►");  /* right triangle */
    printf("%s\n", "\u25BA");  /* right triangle */
    // wprintf(L"%ls\n", L"こんにちは世界"); // prints UTF-8 characters
    // wprintf(L"%ls\n", L"test"); // prints UTF-8 characters

}