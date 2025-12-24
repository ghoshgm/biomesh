
#include <biomesh_configuration.hpp>
#include <libxml/parser.h>
#include <libxml/tree.h>

namespace biomesh
{

configuration::configuration (const std::string &file_path)
    : m_file_path{ file_path }
{
}

configuration::~configuration () {}

void
configuration::read_config_file ()
{
  xmlDocPtr doc = xmlReadFile (m_file_path.c_str (), nullptr, 0);
  if (!doc)
    throw std::runtime_error ("Failed to parse XML file");

  xmlNodePtr root = xmlDocGetRootElement (doc);
  if (!root || xmlStrcmp (root->name, BAD_CAST "fiber_set") != 0)
    {
      xmlFreeDoc (doc);
      throw std::runtime_error ("Missing <fiber_set> root element");
    }

  // Iterate over children of <fiber_set>
  for (xmlNodePtr node = root->children; node; node = node->next)
    {
      if (node->type != XML_ELEMENT_NODE)
        continue;

      std::string key (reinterpret_cast<const char *> (node->name));

      // Handle vector nodes
      if (key == "point" || key == "normal")
        {
          double x = 0.0, y = 0.0, z = 0.0;

          for (xmlNodePtr sub = node->children; sub; sub = sub->next)
            {
              if (sub->type != XML_ELEMENT_NODE)
                continue;

              std::string axis (reinterpret_cast<const char *> (sub->name));
              xmlChar *content = xmlNodeGetContent (sub);
              if (!content)
                throw std::runtime_error ("Missing value in " + key);

              double value
                  = std::stod (reinterpret_cast<const char *> (content));
              xmlFree (content);

              if (axis == "x")
                x = value;
              else if (axis == "y")
                y = value;
              else if (axis == "z")
                z = value;
            }

          m_settings[key] = std::tuple<double, double, double>{ x, y, z };
        }
      else if (key == "seed_file")
        {
          xmlChar *val = xmlNodeGetContent (node);
          std::string path;
          if (val != nullptr)
            {
              path = (const char *)val;
              std::cout << path << std::endl;
            }
          else
            {
              path = "";
              std::cout << path << std::endl;
            }
          m_settings[key] = path;
        }
      else
        {
          // Scalar nodes
          xmlChar *content = xmlNodeGetContent (node);
          if (!content)
            throw std::runtime_error ("Missing value for " + key);

          std::string text (reinterpret_cast<const char *> (content));
          xmlFree (content);

          if (key == "vertex_count" || key == "fiber_count"
              || key == "adaptive_steps_max" || key == "seed_count")
            {
              m_settings[key] = std::stoi (text);
            }
          else
            {
              m_settings[key] = text;
            }
        }
    }

  xmlFreeDoc (doc);
  xmlCleanupParser ();
}

}