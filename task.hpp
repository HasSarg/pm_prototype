//TASK_HPP
#ifndef TASK_HPP
#define TASK_HPP
#include<iostream>

class Task
{
  public:
    Task(std::string, std::string, std::string);
    ~Task(){};
  public:
    void set_name(std::string);
    std::string get_name() const;
    void set_date(std::string);
    std::string get_date() const;
    void set_user(std::string);
    std::string get_user() const;
    void display_task_data() const;
  private:
    std::string m_name;
    std::string m_date;
    std::string m_user;
};
#endif
