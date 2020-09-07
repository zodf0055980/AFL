#include "parse.h"

static void
parseVariable(xmlDocPtr doc, xmlNode *cur_node)
{
    char *element;
    char *name;
    if (variable_count >= variable_array_size)
    {
        exit(1);
    }
    while (cur_node != NULL)
    {
        if ((!xmlStrcmp(cur_node->name, (const xmlChar *)"NAME")))
        {

            name = ((char *)(xmlNodeListGetString(doc, cur_node->xmlChildrenNode, 1)));
            if (strlen(name) < variable_strings_long)
            {
                strncpy(variable[variable_count].name, name, strlen(name));
            }
            else
            {
                exit(1);
            }
        }
        else if ((!xmlStrcmp(cur_node->name, (const xmlChar *)"ELEMENT")))
        {
            element = ((char *)(xmlNodeListGetString(doc, cur_node->xmlChildrenNode, 1)));

            if (strlen(element) < variable_strings_long)
            {
                int p = variable[variable_count].count;
                strncpy(variable[variable_count].variable[p], element, strlen(element));
            }
            else
            {
                exit(1);
            }

            variable[variable_count].count++;
        }
        else if ((!xmlStrcmp(cur_node->name, (const xmlChar *)"text")))
        {
        }
        cur_node = cur_node->next;
    }
    variable_count++;
}

static void
parseParameter(xmlDocPtr doc, xmlNode *cur_node)
{
    char *must = NULL;
    char *element = NULL;
    while (cur_node != NULL)
    {
        if ((!xmlStrcmp(cur_node->name, (const xmlChar *)"MUST")))
        {
            must = ((char *)(xmlNodeListGetString(doc, cur_node->xmlChildrenNode, 1)));
        }
        else if ((!xmlStrcmp(cur_node->name, (const xmlChar *)"ELEMENT")))
        {
            element = ((char *)(xmlNodeListGetString(doc, cur_node->xmlChildrenNode, 1)));
            if (strlen(element) < variable_strings_long)
            {
                if (must == NULL)
                {
                    exit(1);
                }
                if (strcmp("true", must) == 0)
                {
                    if (must_parameter_count < parameter_array_size)
                    {
                        strncpy(must_parameter[must_parameter_count], element, strlen(element));
                        must_parameter_count++;
                    }
                    else
                    {
                        printf("must_parameter_count max\n");
                        exit(1);
                    }
                }
                else if (strcmp("false", must) == 0)
                {
                    if (not_must_parameter_count < parameter_array_size)
                    {
                        strncpy(not_must_parameter[not_must_parameter_count], element, strlen(element));
                        not_must_parameter_count++;
                    }
                    else
                    {
                        printf("not_must_parameter_count max\n");
                        exit(1);
                    }
                }
            }
            else
            {
                printf("too long\n");
                exit(1);
            }
        }
        else if ((!xmlStrcmp(cur_node->name, (const xmlChar *)"text")))
        {
        }
        cur_node = cur_node->next;
    }
}

static void
parseRoot(xmlDocPtr doc, xmlNode *a_node)
{
    a_node = a_node->children;
    xmlNode *cur_node = NULL;

    for (cur_node = a_node; cur_node; cur_node = cur_node->next)
    {
        if (!(xmlStrcmp(cur_node->name, (const xmlChar *)"VARIABLE")))
        {
            parseVariable(doc, cur_node->xmlChildrenNode);
        }
        else if (!(xmlStrcmp(cur_node->name, (const xmlChar *)"PARAMETER")))
        {
            parseParameter(doc, cur_node->xmlChildrenNode);
        }
        else if (!(xmlStrcmp(cur_node->name, (const xmlChar *)"text")))
        {
        }
    }
    return;
}

void print_parse_result()
{
    printf("must :\n");
    int i;
    int j;
    for (i = 0; i < must_parameter_count; i++)
    {
        printf("%s\n", must_parameter[i]);
    }

    printf("not must :\n");
    for (i = 0; i < not_must_parameter_count; i++)
    {
        printf("%s\n", not_must_parameter[i]);
    }

    printf("variable :\n");
    for (i = 0; i < variable_count; i++)
    {
        printf("name = %s\n", variable[i].name);
        for (j = 0; j < variable[i].count; j++)
        {
            printf("%s\n", variable[i].variable[j]);
        }
    }
}

void parse_xml(char *xml_posion)
{
    xmlDoc *doc = NULL;
    xmlNode *root_element = NULL;

    LIBXML_TEST_VERSION

    /*parse the file and get the DOM */
    doc = xmlReadFile(xml_posion, NULL, 0);

    if (doc == NULL)
    {
        printf("error: could not parse file %s\n", xml_posion);
    }
    /*Get the root element node */
    root_element = xmlDocGetRootElement(doc);

    parseRoot(doc, root_element);

    xmlFreeDoc(doc);
    xmlCleanupParser();
    print_parse_result();
}