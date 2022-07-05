#include<iostream>
#include"task.hpp"

Task::Task(std::string name, std::string status
         , std::string date, std::string user)
{
  set_name(name);
  set_status(status);
  set_date(date);
  set_user(user);
}

void Task::set_name(std::string name)
{
  //todo validation
  m_name = name;
}

std::string Task::get_name() const
{
  return m_name;
}

void Task::set_status(std::string status)
{
  //todo validation
  m_status = status;
}

std::string Task::get_status() const
{
  return m_status;
}

void Task::set_date(std::string date)
{
  //todo validation
  m_date = date;
}

std::string Task::get_date() const
{
  return m_date;
}

void Task::set_user(std::string user)
{
  //todo validation
  m_user = user;
}

std::string Task::get_user() const
{
  return m_user;
}

void Task::display_task_data() const
{
  std::cout << get_name() << " "
            << get_status() << " "
            << get_date() << " "
            << get_user() << std::endl;
}
