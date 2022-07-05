#include<iostream>
#include"project.hpp"

Project::Project(std::string name)
{
  set_name(name);
  //Task task("task1", "01.09.2022", "user1");
  //add_task("task1", "01.09.2022", "user1");
  //tasks.push_back(task);
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

void Project::add_task(std::string name, std::string date, std::string user)
{
  //todo validation
  if(0 < tasks.size()) {
    for(int i = 0; i < tasks.size(); ++i)
    {
      //std::cout << tasks[i].get_name() << std::endl;
  //    std::cout << "Project:" << get_name() << " "
  //              << "Task: " << tasks[i].get_name() << std::endl;
      if(name == tasks[i].get_name()) {
        std::cout << "Fail, " << name
                  << " task has already added to " << get_name()
                  <<" project.\n";
        return;
      }
    }
  }
  Task task(name, date, user);
  tasks.push_back(task);
}

void Project::display_tasks() const
{
  std::cout << "Task size:" << tasks.size() << std::endl;
  for(int i = 0; i < tasks.size(); ++i)
  {
    std::cout << "Task: " << i << " ";
    tasks[i].display_task_data();
  }
}

std::string Project::get_task_data() const
{
  std::string data = get_name();
  for(int i = 0; i < tasks.size(); ++i)
  {
    data += "|" + tasks[i].get_name();
    data += "|" + tasks[i].get_date();
    data += "|" + tasks[i].get_user();
  }
  data += "\n";
  return data;
}

void Project::edit_task(std::string task_name
                      , std::string task_new_name
                      , std::string task_new_date
                      , std::string task_new_user)
{
  //todo new data validation
  for(int i = 0; i < tasks.size(); ++i)
  {
    std::cout << "edit \n";
    if(task_name == tasks[i].get_name()) {
      tasks[i].set_name(task_new_name);
      tasks[i].set_date(task_new_date);
      tasks[i].set_user(task_new_user);
      return;
     }
  }
}
