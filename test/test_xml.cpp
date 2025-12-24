#include <iostream>
#include <libxml/parser.h>
#include <libxml/tree.h>

int main() {
    
    xmlInitParser ();
    xmlDocPtr m_file = xmlReadFile ("./config.xml", nullptr, 0);
    xmlCleanupParser ();

    return 0;
}