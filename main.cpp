#include<iostream>
#include"project.hpp"
#include<vector>
#include<fstream>
#include<sstream>

std::vector<std::string> menu = {"To create new project\n"
                               , "To add task\n"
                               , "To edit/rename project\n"
                               , "To edit task\n"
                               , "To delete project\n"
                               , "To delete task\n"
                               , "To display projects\n"
                               , "To display all data\n"};
const char delimiter = '|';
const char space= ' ';
const  std::string db_name = "db.txt";

std::string get_project_name_from_db(std::string line)
{
  int i = 0;
  std::string result = "";
  while(line[i] != delimiter)
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
              << "> project has successfully created!\n";
    return;
  }
  std::cout << "Fail: <" << project_name
            << "> project has already created!\n";
}

void read_from_db(std::vector<Project> &projects, const std::string db_name)
{
  std::string line;
  std::ifstream data(db_name);
  if(data.is_open())
  {
    while(getline(data, line))
    {
      std::string task_name = "";
      std::string task_date = "";
      std::string task_user = "";
      std::string project_name = get_project_name_from_db(line);
      std::vector<std::string> data = split(line, '|');
      Project project(project_name);

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
  //std::string delimiter = "|";
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

bool is_repeated_task_name(std::vector<Project> &projects
                         , std::string project_name
                         , std::string task_name)
{
  for(int i = 0; i < projects.size(); ++i)
  {
    if(project_name == projects[i].get_name()) {
    }
  }
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
    std::cout << "Project: " << projects[i].get_name() << std::endl;
    for(int j = 0; j < projects[i].tasks.size(); ++j)
    {
      std::cout << "Task name: " << projects[i].tasks[j].get_name() << std::endl;
      std::cout << "Task date: " << projects[i].tasks[j].get_date() << std::endl;
      std::cout << "Task user: " << projects[i].tasks[j].get_user() << std::endl;
    }
  }
}

std::string ignore_symbol(std::string str, char symbol)
{
  std::string result = "";
  for(int i = 0; i < str.size(); ++i)
  {
    if(symbol != str[i]) {
      result += str[i];
    }
  }
  return result;
}

int display_menu(std::vector<std::string> &menu)
{
  for(int i = 0; i < menu.size(); ++i)
  {
    std::cout << i+1 << ") " << menu[i];
  }
}

int make_choice(std::vector<std::string> &menu)
{
  int id = 1;
  std::cout << "Please enter the ID of the selected operation [1, 8]: ";
  std::cin >> id;
  std::cout << std::endl;

  while(std::cin.fail() || id < 1 || id > 8) {
    std::cout << "Fail: Please enter an integer in [1-8] range: ";
    std::cin.clear();
    std::cin.ignore();
    std::cin >> id;
  }
  std::cout << "You have entered " << id << ", i.e. ";
  std::cout << menu[id - 1] << std::endl;
  return id;
}



std::string input()
{
  std::string input = "";
  std::cout << "Please enter ('|' and spaces will be ignored): ";
  std::getline(std::cin >> std::ws, input);
  //getline(std::cin, input);
  input = ignore_symbol(ignore_symbol(input, delimiter), space);
  while(std::cin.fail()) {
    std::cin.clear();
    std::cin.ignore(1000, '\n');
    std::cout << "Try  again: ";
    std::cin >> input;
    input = ignore_symbol(input, delimiter);
  }
  std::cout << "You have entered: " << input << std::endl;
  return input;
}

void option(int id, std::vector<Project> &projects)
{
  switch(id)
  {
    case 1: {
      std::cout << "PROJECT CREATION\n";
      std::string project_name = input();
      create_project(projects, project_name);
      }
      break;
    case 2: {
      std::cout << "TASK ADDITION\n";
      if(projects.empty()) {
        std::cout << "Fail: There in no project. You should create a project at first.\n";
      } else {
        std::cout << "Below see the projects...\n";
        display_projects(projects);
        std::cout << "\nEnter the project name to add a task. ";
        std::string project_name = input();
        //std::cout << "You have entered - " << project_name << std::endl;
        if(is_repeated_project_name(projects, project_name)) {
           std::cout << "Good! Now please enter task name to be added. ";
           std::string task_name = input();
           if(is_repeated_task_name(projects, project_name, task_name)) {
             std::cout << "Fail: The entered task new name has already added to <"
                       << project_name << "> project.\n";
             return;
           }
           std::cout << "Good! Now please enter task date. ";
           std::string task_date = input();
           std::cout << "Good! Now please enter user name. ";
           std::string task_user = input();
           add_task_to_project(projects, project_name, task_name, task_date, task_user);
        } else {
          std::cout << "Fail: The entered project name doesn't exist.\n";
        }
      }
      }
      break;
    case 3: {
        std::cout << "PROJECT EDIT/RENAME\n";
        if(!projects.empty()) {
          std::cout << "Below see projects' list: \n";
          display_projects(projects);
          std::cout << "Please enter the project name, you need to edit/rename.";
          std::string project_name = input();
          if(is_repeated_project_name(projects, project_name)) {
            std::cout << "Good! Now please enter project new name: ";
            std::string project_new_name = input();
            if(!is_repeated_project_name(projects, project_new_name)) {
              edit_project(projects, project_name, project_new_name);
              std::cout << "Good! You have successfully changed <"
                        << project_name << "> project to <"
                        << project_new_name << "> project.\n";
            }
          } else {
            std::cout << "Fail: The entered project_name not found.\n";
          }
         } else {
           std::cout << "Fail: There aren't any projects.\n";
         }
      }
      break;
    case 4: {
        std::cout << "TASK UPDATE\n";
        if(projects.empty()) {
          std::cout << "Fail: There is no project. You should create a project at first.\n";
        } else {
          std::cout << "Please enter project name.\n";
          std::cout << "Below see the projects.\n";
          display_projects(projects);
          std::string project_name = input();
          if(is_repeated_project_name(projects, project_name)) {
            for(int i = 0; i < projects.size(); ++i)
            {
              if(project_name == projects[i].get_name()) {
                if(projects[i].tasks.size() > 0) {
                  std::cout << "Below see the tasks of the selected project:\n";
                  for(int j = 0; j < projects[i].tasks.size(); ++j)
                  {
                    std::cout << projects[i].tasks[j].get_name() << std::endl;
                  }
                  std::cout << "Please enter task name: ";
                  std::string task_name = input();
                  std::cout << "You have entered: " << input << std::endl;
                  for(int k = 0; k < projects[i].tasks.size(); ++k)
                  {
                    if(task_name == projects[i].tasks[k].get_name()) {
                      std::cout << "Please enter new task name: ";
                      std::string task_new_name = input();
                      std::cout << "Please enter new task date: ";
                      std::string task_new_date = input();
                      std::cout << "Please enter new task user: ";
                      std::string task_new_user = input();
                      edit_task_in_projects(projects, project_name, task_name
                                          , task_new_name, task_new_date, task_new_user);
                      return;
                    }
                  }
                }

              }
            }
        }
        std::cout << "Fail: You have entered <" << project_name
                  << "> project name, that doesn't exist.\n";
      }
      }
      break;
    case 5: {
        std::cout << "PROJECT DELETION\n";
        if(projects.empty()) {
          std::cout << "Fail: There is no project.\n";
        } else {
          std::cout << "Below see projects.\n";
          display_projects(projects);
          std::cout << "To delete a project, you should enter a project name: ";
          std::string project_name = input();
          if(is_repeated_project_name(projects, project_name)) {
            delete_project(projects, project_name);
            std::cout << "Done: <" << project_name << "> project has successfully deleted.\n";
          }
        }
      }
      break;
    case 6: {
        std::cout << "TASK DELETION\n";
        if(projects.empty()) {
          std::cout << "Fail: There aren't any projects.\n";
        }else {
          std::cout << "Below see all projects: \n";
          display_projects(projects);
          std::cout << "Please enter the project name, which task you want to delete: ";
          std::string project_name = input();
          if(is_repeated_project_name(projects, project_name)) {
            std::cout << "Below see the mentioned project's task(s): \n";
            for(int i = 0; i < projects.size(); ++i) {
              if(project_name == projects[i].get_name()) {
                for(int j = 0; j < projects[i].tasks.size(); ++j)
                {
                  std::cout << projects[i].tasks[j].get_name() << std::endl;
                }
                std::cout << "Please enter task name: ";
                std::string task_name = input();
                for(int j = 0; j < projects[i].tasks.size(); ++j)
                {
                  if(task_name == projects[i].tasks[j].get_name()) {
                    projects[i].tasks.erase(projects[i].tasks.begin() + j);
                    std::cout << "Done: <" << task_name << "> task name of <"
                              << project_name << "> project has been deleted.\n";
                  }
                }
              }
            }
          }
        }
      }
      break;
    case 7: {
        std::cout << "DISPLAY PROJECTS\n";
        if(projects.empty()) {
          std::cout << "Fail: There aren't any projects.\n";
        } else {
          display_projects(projects);
        }
      }
      break;
    case 8: {
        std::cout << "DISPLAY ALL DATA (Project(s) with task(s))\n";
        if(projects.empty()) {
          std::cout << "Fail: There aren't any projects.\n";
        } else {
          show_all(projects);
        }
      }
      break;
    //default:
    //  std::cout << "????????";
  }
  update_db(projects, db_name);
}

void run()
{
  std::vector<Project> projects = {};
  read_from_db(projects, db_name);
  display_menu(menu);
  int id = make_choice(menu);
  option(id, projects);
}

int main()
{
  run();
  return 0;
}
