#include <iostream>
#include <libxml/parser.h>
#include <libxml/tree.h>

int
main ()
{

  xmlInitParser ();
  xmlDocPtr m_file = xmlReadFile ("/home/ghoshgm/Desktop/dev/biomesh/test/config.xml", nullptr, 0);
  xmlCleanupParser ();

  return 0;
}