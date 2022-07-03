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
  private:
    std::string m_name;
    std::vector<Task> task;
};
#endif
