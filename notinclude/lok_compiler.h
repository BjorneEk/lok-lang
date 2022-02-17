#ifndef _LOK_COMPILER_H_
#define _LOK_COMPILER_H_

#include <stdbool.h>


#define NOFLAGS   0
#define CONST_FLAG 1



const char * INT_NAME    = "int";
const char * U8_NAME     = "u8";
const char * U16_NAME    = "u16";
const char * U32_NAME    = "u32";
const char * U64_NAME    = "u64";
const char * FLOAT_NAME  = "float";
const char * DOUBLE_NAME = "double";


typedef struct ll_node
{
	void * value;

	struct ll_node * next;

} node_t;

typedef struct vtype
{

	char * name;

	int flags;

	int typeinfo;

} vtype_t;

typedef struct variable
{

	char * name;

	vtype type;

	char * src;

} variable_t;



typedef struct parsed_function
{

	char * name;

	vtype_t return_type;

	int nparams;

	variable_t * params;

	int ntypeparams;

	char * type_params;

	char * src;

} function_t;



typedef struct parsed_struct_t
{

	char * name;

	int nmembrs;

	variable_t * membrs;

	function_t * operators;

	int ntypeparams;

	char * type_params;

	char * src;

} struct_t;

typedef struct parsed_namespace
{

	char * name;

	node_t * variables;

	node_t * structs;

	node_t * functions;

} parsed_namespace_t

#endif /* _LOK_COMPILER_H_ */
