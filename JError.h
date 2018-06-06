#ifndef JERROR_H
#define JERROR_H

#include "JIncludes.h" // include std libs and define macros

//JError definition
#ifndef USEJERROR
#define throw(message) \
{printf("ERROR: %s\n	in file %s at line %d\n",message,__FILE__,__LINE__); throw(1);}
#else
struct JError{
	char* message;
	char* file;
	int line;
	JError(char* m, char*f, int l): message(m), file(f), line(l) {}
};
#define throw(message) throw(JError(message,__FILE__,__LINE__));
void JCatch(JError e) {
	printf("ERROR: %s\n    in file %s at line %d\n",e.message,e.file,e.line);
	exit(1);
}
#endif

#endif //JERROR_H
