
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
  /* Read the YAML file. */
  BIOMESH_LINFO ("Input XML file path: " + m_file_path);
  BIOMESH_LINFO ("XML file read begin.");

  xmlInitParser ();

  xmlDocPtr m_file = xmlReadFile (m_file_path.c_str (), nullptr, 0);

  xmlNode *m_root = xmlDocGetRootElement (m_file);

  for (xmlNode *node = m_root->children; node; node = node->next)
    {
      if (node->type == XML_ELEMENT_NODE)
        {

          if (xmlStrcmp (node->name, BAD_CAST "fibers") == 0)
            {
              for (xmlNode *sub_node = node->children; sub_node;
                   sub_node = sub_node->next)
                {
                  if (xmlStrcmp (sub_node->name, BAD_CAST "vertex_count") == 0)
                    {
                      int vertex_count = std::stoi (
                          (const char *)xmlNodeGetContent (sub_node));
                      m_settings.insert ({ "vertex_count", vertex_count });
                    }
                  if (xmlStrcmp (sub_node->name, BAD_CAST "fiber_count") == 0)
                    {
                      int fiber_count = std::stoi (
                          (const char *)xmlNodeGetContent (sub_node));
                      m_settings.insert ({ "fiber_count", fiber_count });
                    }
                  if (xmlStrcmp (sub_node->name, BAD_CAST "integration_scheme")
                      == 0)
                    {
                      std::string integration_scheme
                          = (const char *)xmlNodeGetContent (sub_node);
                      m_settings.insert (
                          { "integration_scheme", integration_scheme });
                    }
                  if (xmlStrcmp (sub_node->name, BAD_CAST "adaptive_steps_max")
                      == 0)
                    {
                      int adaptive_steps_max = std::stoi (
                          (const char *)xmlNodeGetContent (sub_node));
                      m_settings.insert (
                          { "adaptive_steps_max", adaptive_steps_max });
                    }
                  if (xmlStrcmp (sub_node->name, BAD_CAST "strategy") == 0)
                    {
                      std::string strategy
                          = (const char *)xmlNodeGetContent (sub_node);
                      m_settings.insert ({ "strategy", strategy });
                    }
                }
            }

          if (xmlStrcmp (node->name, BAD_CAST "seed_points") == 0)
            {
              for (xmlNode *sub_node = node->children; sub_node;
                   sub_node = sub_node->next)
                {
                  if (xmlStrcmp (sub_node->name, BAD_CAST "seed_count") == 0)
                    {
                      int seed_count = std::stoi (
                          (const char *)xmlNodeGetContent (sub_node));
                      m_settings.insert ({ "seed_count", seed_count });
                    }
                  if (xmlStrcmp (sub_node->name, BAD_CAST "point") == 0)
                    {
                      double x = std::stod (
                          (const char *)xmlGetProp (sub_node, BAD_CAST "x"));
                      double y = std::stod (
                          (const char *)xmlGetProp (sub_node, BAD_CAST "y"));
                      double z = std::stod (
                          (const char *)xmlGetProp (sub_node, BAD_CAST "z"));

                      m_settings.insert (
                          { "point",
                            std::tuple<double, double, double>{ x, y, z } });
                    }
                  if (xmlStrcmp (sub_node->name, BAD_CAST "normal") == 0)
                    {
                      double x = std::stod (
                          (const char *)xmlGetProp (sub_node, BAD_CAST "x"));
                      double y = std::stod (
                          (const char *)xmlGetProp (sub_node, BAD_CAST "y"));
                      double z = std::stod (
                          (const char *)xmlGetProp (sub_node, BAD_CAST "z"));

                      m_settings.insert (
                          { "normal",
                            std::tuple<double, double, double>{ x, y, z } });
                    }
                  if (xmlStrcmp (sub_node->name, BAD_CAST "seed_file") == 0)
                    {
                      xmlChar *val = xmlNodeGetContent (sub_node);
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
                    }
                }
            }
        }
    }

  xmlFreeDoc (m_file);
  xmlCleanupParser ();

  BIOMESH_LINFO ("XML file read end.");
}

auto
configuration::operator[] (std::string &parameter)
{
  if (parameter == "vertex_count")
    {
      return std::any_cast<int> (m_settings["vertex_count"]);
    }
  else if (parameter == "fiber_count")
    {
      return std::any_cast<int> (m_settings["fiber_count"]);
    }
  else if (parameter == "integration_scheme")
    {
      return std::any_cast<std::string> (m_settings["integration_scheme"]);
    }
  else if (parameter == "adaptive_steps_max")
    {
      return std::any_cast<int> (m_settings["adaptive_steps_max"]);
    }
  else if (parameter == "strategy")
    {
      return std::any_cast<std::string> (m_settings["strategy"]);
    }
  else if (parameter == "seed_count")
    {
      return std::any_cast<int> (m_settings["seed_count"]);
    }
  else if (parameter == "point")
    {
      return std::any_cast<std::tuple<double, double, double> > (
          m_settings["point"]);
    }
  else if (parameter == "normal")
    {
      return std::any_cast<std::tuple<double, double, double> > (
          m_settings["normal"]);
    }
  else if (parameter == "seed_file")
    {
      return std::any_cast<std::string> (m_settings["seed_file"]);
    }
  else
    {
      return std::string ("Invalid Parameter.");
    }
}

void
configuration::print () const
{
  // std::cout << m_data << std::endl;
}

}