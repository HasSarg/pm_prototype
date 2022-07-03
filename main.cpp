#include<iostream>
#include"project.hpp"
#include<vector>
#include<fstream>

void read_from_db(std::vector<Project> &projects, std::string db_name)
{
  std::string line;
  std::ifstream data(db_name);
  if(data.is_open())
  {
    while(getline(data, line))
    {
      Project project(line);
      projects.push_back(project);
    }
  }
  data.close();
}

bool edit_project(std::vector<Project> &projects
                , std::string project_name
                , std::string project_new_name)
{
  for(int i = 0; i < projects.size(); ++i)
  {
    if(project_name == projects[i].get_name()) {
      projects[i].set_name(project_new_name);
      return true;
    }
  }
  return false;
}

void delete_project(std::vector<Project> &projects, std::string &name)
{
  for(int i = 0; i < projects.size(); ++i)
  {
    if(name == projects[i].get_name()) {
      projects.erase(projects.begin() + i);
    }
  }
}

void display_projects(std::vector<Project> &projects)
{
  for(int i = 0; i < projects.size(); ++i)
  {
    std::cout << projects[i].get_name() << std::endl;
  }
}

void update_db(std::vector<Project> &projects, std::string db_name)
{
  std::ofstream file;
  file.open(db_name);
  for(int i = 0; i < projects.size(); ++i) {
    file << projects[i].get_name();
    file << "\n";
  }
  file.close();
}

bool is_repeated_project_name(std::vector<Project> &projects
                            , std::string project_name)
{
  for(int i = 0; i < projects.size(); ++i)
  {
    if(project_name == projects[i].get_name()) {
      return true;
    }
  }
  return false;
}

int main()
{
  std::vector<Project> projects = {};
  std::string db_name = "db.txt";
  read_from_db(projects, db_name);
  char project_delimiter = '\n';
  std::string project_name = "name1";
  //create project
  if(!is_repeated_project_name(projects, project_name)) {
    Project project(project_name);
    projects.push_back(project);
    update_db(projects, db_name);
  }

  //create 2nd project
  project_name = "name2";
  if(!is_repeated_project_name(projects, project_name)) {
    Project project1(project_name);
    projects.push_back(project1);
    update_db(projects, db_name);
  }

  //create 3rd project
  project_name = "name3";
  if(!is_repeated_project_name(projects, project_name)) {
    Project project1(project_name);
    projects.push_back(project1);
    update_db(projects, db_name);
  }

  //delete project
  project_name = "name1";
  delete_project(projects, project_name);
  update_db(projects, db_name);

  //edit project
  project_name = "name2";
  std::string project_new_name = "edited_name2";
  if(is_repeated_project_name(projects, project_name) &&
     !is_repeated_project_name(projects, project_new_name) &&
     edit_project(projects, project_name, project_new_name)) {
     update_db(projects, db_name);
  }
  display_projects(projects);
  return 0;
}
