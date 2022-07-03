#include<iostream>
#include"project.hpp"

Project::Project(std::string name)
{
  set_name(name);
}

void Project::set_name(std::string name)
{
  //todo validation
  m_name = name;
}

std::string Project::get_name() const
{
  return m_name;
}
