#include <stdio.h>
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <stdlib.h>
#include <string.h>

#define parameter_array_size 50
#define parameter_strings_long 15

#define variable_array_size 10
#define variable_strings_size 30
#define variable_strings_long 15

char must_parameter[parameter_array_size][parameter_strings_long];
int must_parameter_count;
char not_must_parameter[parameter_array_size][parameter_strings_long];
int not_must_parameter_count;
struct variable_list
{
    char name[variable_strings_long];
    int count;
    char variable[variable_strings_size][variable_strings_long];
};

struct variable_list variable[variable_array_size];
int variable_count;
void parse_xml(char *xml_posion);