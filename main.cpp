#include<iostream>
#include"project.hpp"
#include<vector>
#include<fstream>
#include<sstream>

std::string get_project_name_from_db(std::string line)
{
  int i = 0;
  std::string result = "";
  while(line[i] != '|')
  {
    result += line[i];
    ++i;
  }
  return result;
}

std::vector<std::string> split(const std::string &s, char delim)
{
  std::vector<std::string> result;
  std::stringstream ss(s);
  std::string item;

  while(getline(ss, item, delim)) {
    result.push_back(item);
  }
  return result;
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

void create_project(std::vector<Project> &projects
                  , std::string project_name)
{
  if(!is_repeated_project_name(projects, project_name)) {
    Project project(project_name);
    projects.push_back(project);
    std::cout << "Done: <" << project_name
              << " has successfully created!\n";
    return;
  }
  std::cout << "Fail: <" << project_name
            << "> the project has already created!\n";
}

void read_from_db(std::vector<Project> &projects, std::string db_name)
{
  std::string line;
  std::ifstream data(db_name);
  if(data.is_open())
  {
    while(getline(data, line))
    {
      //std::string project_name = get_project_name_from_db(line);
      std::vector<std::string> data = split(line, '|');
      std::string project_name = data[0];
      //create_project(project_name, projects)
      Project project(project_name);
      std::string task_name = "";
      std::string task_date = "";
      std::string task_user = "";

      for(int j = 1, i = 1; j < data.size(); ++i, ++j)
      {
         if(i == 1) {
           task_name = data[j];
         }
         if(i == 2) {
           task_date = data[j];
         }
         if(i == 3) {
           task_user = data[j];
           i = 0;
           project.add_task(task_name, task_date, task_user);
         }
      }
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
    if(project_name == projects[i].get_name() &&
       !is_repeated_project_name(projects, project_new_name)) {
      projects[i].set_name(project_new_name);
      std::cout << "Done: <" << project_name
                << "> project has renamed to <"
                << project_new_name << ">.\n";
      return true;
    }
  }
  std::cout << "Fail: <" << project_name << "> not found.\n";
  return false;
}

void delete_project(std::vector<Project> &projects, std::string &name)
{
  for(int i = 0; i < projects.size(); ++i)
  {
    if(name == projects[i].get_name()) {
      projects.erase(projects.begin() + i);
      std::cout << "Done: <" << name
                << "> project has successfully deleted!\n";
      return;
    }
  }
  std::cout << "Fail: <" << name << "> not found.\n";
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
  std::string delimiter = " | ";
  std::ofstream file;
  file.open(db_name);
  for(int i = 0; i < projects.size(); ++i) {
    //std::cout << projects[i].get_name();
    //file << projects[i].get_name();
    //file << " | ";
    file << projects[i].get_task_data();
    //std::cout << projects[i].get_task_data();
    //file << projects[i].
    //file << "\n";
  }
  file.close();
}

void add_task_to_project(std::vector<Project> &projects
                       , std::string project_name
                       , std::string task_name
                       , std::string task_date
                       , std::string task_user)
{
  for(int i = 0; i < projects.size(); ++i)
  {
    if(project_name == projects[i].get_name()) {
      for(int j = 0; j < projects[i].tasks.size(); ++j)
      {
        if(task_name == projects[i].tasks[j].get_name()) {
          std::cout << "Fail: <" << task_name
                    << "> task in <" << project_name
                    << "> project has already added!\n";
          return;
        }
      }
      Task task(task_name, task_date, task_user);
      std::cout << "Done: <" << task_name << "> task is added to <"
                << project_name << "> project.\n";
      projects[i].tasks.push_back(task);
    }
  }
}

void edit_task_in_projects(std::vector<Project> &projects
                         , std::string project_name
                         , std::string task_name
                         , std::string task_new_name
                         , std::string task_new_date
                         , std::string task_new_user)
{
  for(int i = 0; i < projects.size(); ++i)
  {
    if(project_name == projects[i].get_name())
    {
      for(int j = 0; j < projects[i].tasks.size(); ++j)
      {
        if(task_name == projects[i].tasks[j].get_name()) {
          for(int k = 0; k < projects[i].tasks.size(); ++k)
          {
            if(task_new_name == projects[i].tasks[k].get_name()) {
              std::cout << "Fail: <" << task_new_name
                        << "> task new name has already existed!\n";
              return;
            }
          }
          projects[i].tasks[j].set_name(task_new_name);
          projects[i].tasks[j].set_date(task_new_date);
          projects[i].tasks[j].set_user(task_new_user);
          std::cout << "Done: <" << task_name
                    << "> of <" << project_name
                    << "> project is edited successfully!\n";
          return;
        }
      }
    }
  }
  std::cout << "Fail: <" << task_name << "> wasn't edited!\n";
}

void delete_task_from_project(std::vector<Project> &projects
                            , std::string project_name
                            , std::string task_name)
{
  for(int i = 0; i < projects.size(); ++i)
  {
    if(project_name == projects[i].get_name()) {
      for(int j = 0; j < projects[i].tasks.size(); ++j)
      {
        if(task_name == projects[i].tasks[j].get_name()) {
          projects[i].tasks.erase(projects[i].tasks.begin() + j);
          return;
        }
      }
    }
  }
}

void show_all(std::vector<Project> &projects)
{
  for(int i = 0; i < projects.size(); ++i)
  {
    std::cout << projects[i].get_name() << std::endl;
    for(int j = 0; j < projects[i].tasks.size(); ++j)
    {
      std::cout << projects[i].tasks[j].get_name() << std::endl;
      std::cout << projects[i].tasks[j].get_date() << std::endl;
      std::cout << projects[i].tasks[j].get_user() << std::endl;
    }
  }
}

int run()
{
  std::vector<Project> projects = {};
  std::string db_name = "db.txt";
  read_from_db(projects, db_name);

  std::string project_name = "name1";
  //create project
  create_project(projects, project_name);

  std::string task_name = "task1";
  std::string task_date = "10.09.23";
  std::string task_user = "user3";
  add_task_to_project(projects, project_name
                    , task_name, task_date, task_user);
  //create 2nd project
  project_name = "name2";
  create_project(projects, project_name);
  task_name = "task22";
  task_date = "12.02.23";
  task_user = "user3";
  add_task_to_project(projects, project_name
                    , task_name, task_date, task_user);
  //edit task in project2
  task_name = "task22";
  std::string task_new_name = "task24";
  std::string task_new_date = "12.03.23";
  std::string task_new_user = "user2";
  edit_task_in_projects(projects, project_name
                      , task_name, task_new_name
                      , task_new_date, task_new_user);

  //create 3rd project
  project_name = "name3";
  create_project(projects, project_name);
  task_name = "task32";
  task_date = "10.02.2023";
  task_user = "user2";

  add_task_to_project(projects, project_name
                    , task_name, task_date, task_user);
  task_new_name = "edited_task32";
  task_new_date = "11.08.22";
  task_new_user = "Hasmik";
  edit_task_in_projects(projects, project_name
                      , task_name, task_new_name
                      , task_new_date, task_new_user);
  //delete project
  project_name = "name1";
  delete_project(projects, project_name);

  //edit project
  project_name = "name2";
  std::string project_new_name = "edited_name2";
  edit_project(projects, project_name, project_new_name);
  //delete task in project edited_name2
  delete_task_from_project(projects, project_new_name, "edited_task22");
  update_db(projects, db_name);
  show_all(projects);
}

int main()
{
  run();
  return 0;
}
