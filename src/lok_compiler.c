

#include "lok_compiler.h"
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>


static void log_error(char * msg)
{
	fprintf(stderr, "\033[31;1;4m[Error]\033[0m %s | %s\n",msg, strerror( errno ));
}
static void log_file_error(char * msg, char * filename)
{
	fprintf(stderr, "\033[31;1;4m[Error]\033[0m %s: %s | %s\n",msg, filename, strerror( errno ));
}
static void log_wspace_error(char * msg, char c)
{
	fprintf(stderr, "\033[31;1;4m[Error]\033[0m %s: %c\n",msg, c);
}

int32_t index_of( const char * str, const char c )
{
	const char * ptr = strchr(str, c);
	return (ptr) ? (ptr - str) : -1
}

bool contains( const char * str, char c )
{
	return (indexOf(str, c) != -1)
}

bool str_equals(const char * str1, const char * str2)
{
	char * s = str2;
	for (int i = 0; *s != '\0'; i++, s++) if (*s != str1[i]) return false;
	return true;
}

char * trim(char * str)
{
	const char *ptr = strchr(str, '\n');
	if(ptr)
	{
		char    *res;
		uint16_t index;

		index = ptr - str;
		res   = malloc(index + 2);

		strncpy(res, str, index);
		return res;
	}
	return str;
}

int get_namespace_source(char ** sources, int filecount, char * name, char ** _buff)
{
	for (size_t i = 0; i < filecount; i++)
	{
		FILE * source;
		char * buff;
		int buff_len;
		int begin_idx;
		int end_idx;
		int ldng_ws;
		char wspce_chr;

		/* open a file */
		source = fopen(sources[i], "rb");
		if (source == NULL)
		{
			log_file_error("could not open file", filename);
			return;
		}

		/* get size of file */
		fseek(source, 0, SEEK_END);
		buff_len = ftell(source);
		fseek(source, 0, SEEK_SET);

		/* read file into a buffer and close it*/
		buff = malloc(buff_len + 1 * sizeof(char));
		fread(buff, buff_len, 1, source);
		fclose(source);

		/* create string 'def name : namespace' to match when searching */
		char searchword[1024] = "def ";
		strcat(searchword, name);
		char post[] = " : namespace";
		strcat(searchword, post);


		/* search for namespace defenition in buffer */
		for (size_t i = 0; i < buff_len; i++)
		{
			if (buff[i] == '\n')
			{

			}
			else if (str_equals(&buff[i], searchword))
			{
				/* set begin index since defenition was found */
				begin_idx = i;

				/* count leading whitespaces */
				if (i == 0 || buff[i-1] == '\n') ldng_ws = 0;
				else
				{
					wspce_chr = buff[i-1];
					if ( wspce_chr != ' ' || wspce_chr != '\t')
						log_wspace_error("not a whitespace char", wspce_chr);
					for(ldng_ws=1; i-ldng_ws >= 0 && buff[i-ldng_ws] == wspce_chr; j--, ldng_ws++);
				}
			}
		}
	}
}

int precompile_include(char * main, char ** sources, int filecount)
{
	FILE * files[filecount];
	char * buffer;
	size_t buffer_len;

		/* open the file */
	obj_file = fopen(filename, "rb");
	if (obj_file == NULL) {
		log_file_error("could not open file", filename);
		return -1;
	}

		/* 1. get size of file */
	fseek(obj_file, 0, SEEK_END);
	buffer_len = ftell(obj_file);
	fseek(obj_file, 0, SEEK_SET);

		/* 2. read file into a buffer and close it*/
	buffer = malloc(buffer_len + 1 * sizeof(char));
	fread(buffer, buffer_len, 1, obj_file);
	fclose(obj_file);

		/* count nuber of faces and vertecies and set the name*/
	char name[OBJ_MAX_DESCRIPTOR];
	for (size_t i = 0; i < buffer_len; i++) {
		switch ( buffer[i] ) {
			case OBJ_FACE_START:      face_count++;   break;
			case OBJ_VERTEX_START:    vertex_count++; break;
			case OBJ_DESCRIPTOR_START:
				strncpy(name, &buffer[i+2], OBJ_MAX_DESCRIPTOR-1); // from space after o
				char * res = malloc(OBJ_MAX_DESCRIPTOR);
				get_descriptor(&res, name);
				strncpy(obj->descriptor, res, strlen(res));
				if (contains(obj->descriptor, OBJ_FACE_START)) face_count--;
				if (contains(obj->descriptor, OBJ_VERTEX_START)) vertex_count--;
				break;
		}
	}
		/* 4. loop trough buffer and serch for vectors and faces */
	for (size_t i = 0; i < buffer_len; i++) {
		switch ( buffer[i] ) {
			case OBJ_VERTEX_START:
				vector_set[read_vertecies] = get_vec3d(&buffer[i+2]);
				i+=5;
				//printf("%s\n", v3d_to_str(vector_set[read_vertecies]));
				read_vertecies++;
				continue;
			case OBJ_FACE_START:
				faces[read_faces] = get_face(&buffer[i+2]);
				read_faces++;
				break;
		}
	}

		/* loop through and set the triangles to their correct values */
	for (size_t i = 0; i < obj->length; i += 1) {
		obj->tris[i] = (triangle3d_t){
			.p1=vector_set[faces[i].p1-1],
			.p2=vector_set[faces[i].p2-1],
			.p3=vector_set[faces[i].p3-1]
		};
	}
	return 0;
}
