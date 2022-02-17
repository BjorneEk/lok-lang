#ifndef _LOK_COMPILER_H_
#define _LOK_COMPILER_H_


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



#endif /* _LOK_COMPILER_H_ */
