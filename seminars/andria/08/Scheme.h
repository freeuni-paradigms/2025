#ifndef _SCHEME_H_
#define _SCHEME_H_

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum
{
	Integer,
	String,
	List,
	Nil
} nodeType;

/**
recursively concats all string nodeTypes
*/
char *ConcatAll(nodeType *list);

#endif