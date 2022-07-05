//PROJECT_HPP
#ifndef PROJECT_HPP
#define PROJECT_HPP
#include<iostream>
#include<vector>
#include"task.hpp"

class Project
{
  public:
    Project(std::string);
    ~Project(){};
  public:
    void set_name(std::string);
    std::string get_name() const;
    void add_task(std::string, std::string, std::string);
    void edit_task(std::string, std::string, std::string, std::string);
    std::string get_task_data() const;
    void display_tasks() const;
    std::vector<Task> tasks;
  private:
    std::string m_name;
};
#endif
