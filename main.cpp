#include<iostream>
#include"project.hpp"
#include<vector>
#include<fstream>
#include<sstream>

std::vector<std::string> menu = {"To create new project - C\n"
                               , "To add task - A\n"
                               , "To update/rename project - U\n"
                               , "To edit task - E\n"
                               , "To delete project - D\n"
                               , "To remove task - R\n"
                               , "To view projects - V\n"
                               , "To show all data - S\n"
                               , "To exit - X\n"};
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

void read_from_db(std::vector<Project> &projects, const std::string db_name)
{
  std::string line;
  std::ifstream data(db_name);
  if(data.is_open())
  {
    while(getline(data, line))
    {
      std::string task_name = "";
      std::string task_status = "";
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
           task_status = data[j];
         }
         if(i == 3) {
           task_date = data[j];
         }
         if(i == 4) {
           task_user = data[j];
           i = 0;
           project.add_task(task_name, task_status, task_date, task_user);
         }
      }
      projects.push_back(project);
    }
  }
  data.close();
}

int display_menu()
{
  std::cout << "Below see the list of options.\n";
  for(int i = 0; i < menu.size(); ++i)
  {
    std::cout << menu[i];
  }
}

char make_input()
{
  char input;
  do {
    std::cout << "Please enter the capital letter of the appropriate option (C, A, ...X).\n";
    std::cout << "Only the first letter/sign of the input will be accepted as your choice: ";
    std::cin >> input;
  } while(std::cin.fail());
  std::cout << "You have entered " << input;
  std::cin.clear();
  std::cin.ignore(256, '\n');
  return input;
}

bool is_found_project_name(std::vector<Project> &projects
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

void display_projects(std::vector<Project> &projects)
{
  std::cout << "Below see the projects...\n\n";
  for(int i = 0; i < projects.size(); ++i)
  {
    std::cout << projects[i].get_name() << std::endl;
  }
}

void create_project(std::vector<Project> &projects
                  , std::string project_name)
{
  Project project(project_name);
  projects.push_back(project);
  std::cout << "Done: <" << project_name
            << "> project has successfully created!\n";
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

std::string data_input(std::string str)
{
  std::string input = "";
  std::cout << "Please enter " << str << " ('|' and spaces will be ignored): ";
  getline(std::cin, input);
  input = ignore_symbol(ignore_symbol(input, delimiter), space);
  std::cout << "You have entered: " << input << std::endl;
  return input;
}

void update_db(std::vector<Project> &projects, std::string db_name)
{
  std::ofstream file;
  file.open(db_name, std::ios_base::out);
  if(file.is_open())
  {
    for(int i = 0; i < projects.size(); ++i) {
      file << projects[i].get_name();
      file << delimiter;
      for(int j = 0; j < projects[i].tasks.size(); ++j)
      {
        file << projects[i].tasks[j].get_name();
        file << delimiter;
        file << projects[i].tasks[j].get_date();
        file << delimiter;
        file << projects[i].tasks[j].get_user();
        file << delimiter;
      }
      file << "\n";
    }
  }
  else
  {
    std::cerr << "Error: Unable to open file: " << db_name << std::endl;
  }
  file.close();
}

void project_creation(std::vector<Project> &projects)
{
  std::cout << " - PROJECT CREATION\n";
  std::cout << "You should enter a name of the project. ";
  std::string project_name = data_input("project name");
  if(is_found_project_name(projects, project_name))
  {
    std::cerr << "Error: The entered <" << project_name
              << "> has already created.\n";
    return;
  }
  create_project(projects, project_name);
  update_db(projects, db_name);
}

bool is_found_task_name(std::vector<Project> &projects
                         , std::string project_name
                         , std::string task_name)
{
  for(int i = 0; i < projects.size(); ++i)
  {
    if(project_name == projects[i].get_name()) {
      for(int j = 0; j < projects[i].tasks.size(); ++j)
      {
        if(task_name == projects[i].tasks[j].get_name()) {
          return true;
        }
      }
    }
  }
  return false;
}

void add_task_to_project(std::vector<Project> &projects
                       , std::string project_name
                       , std::string task_name
                       , std::string task_status
                       , std::string task_date
                       , std::string task_user)
{
  for(int i = 0; i < projects.size(); ++i)
  {
    if(project_name == projects[i].get_name()) {
      for(int j = 0; j < projects[i].tasks.size(); ++j)
      {
        if(task_name == projects[i].tasks[j].get_name()) {
          std::cerr << "Error: <" << task_name
                    << "> task in <" << project_name
                    << "> project has already added!\n";
          return;
        }
      }
      Task task(task_name, task_status, task_date, task_user);
      std::cout << "Done: <" << task_name << "> task is added to <"
                << project_name << "> project.\n";
      projects[i].tasks.push_back(task);
    }
  }
}

void task_addition(std::vector<Project> &projects)
{
  if(projects.empty())
  {
    std::cerr << "Error: There aren't any projects. You should create a project at first.\n";
    return;
  }
  std::cout << " - TASK ADDITION\n";
  display_projects(projects);
  std::cout << "\nEnter the project name from the list to add a task. ";
  std::string project_name = data_input("project name");
  if(!is_found_project_name(projects, project_name)) {
    std::cerr << "Error: The entered project name doesn't exist.\n";
    return;
  }
  std::cout << "Good! Now please enter task name to be added. ";
  std::string task_name = data_input("task name");
  if(is_found_task_name(projects, project_name, task_name))
  {
    std::cerr << "Error: The entered <" << task_name << "> task has already added to <"
              << project_name << "> project.\n";
    return;
  }
  std::cout << "Good! Now please enter task status. ";
  std::string task_status = data_input("task status");
  std::cout << "Good! Now please enter task date. ";
  std::string task_date = data_input("task date");
  std::cout << "Good! Now please enter user name. ";
  std::string task_user = data_input("user name");
  add_task_to_project(projects, project_name, task_name, task_status
                    , task_date, task_user);
  update_db(projects, db_name);
}

bool edit_project(std::vector<Project> &projects
                , std::string project_name
                , std::string project_new_name)
{
  for(int i = 0; i < projects.size(); ++i)
  {
    if(project_name == projects[i].get_name() &&
       !is_found_project_name(projects, project_new_name)) {
      projects[i].set_name(project_new_name);
      std::cout << "Done: <" << project_name
                << "> project has renamed to <"
                << project_new_name << ">.\n";
      return true;
    }
  }
  std::cerr << "Error: <" << project_name << "> not found.\n";
  return false;
}

void project_update(std::vector<Project> &projects)
{
  if(projects.empty())
  {
    std::cerr << "Error: There aren't any projects. You should create a project at first.\n";
    return;
  }
  std::cout << " - PROJECT UPDATE/RENAME\n";
  display_projects(projects);
  std::cout << "Please enter the project name, you need to edit/rename.";
  std::string project_name = data_input("project name from the list, ");
  if(!is_found_project_name(projects, project_name))
  {
    std::cerr << "Error: The entered <" << project_name
              << "> project name not found.\n";
    return;
  }
  std::cout << "Good! Now please enter new project name: ";
  std::string project_new_name = data_input("new project name");
  if(is_found_project_name(projects, project_new_name))
  {
    std::cerr << "Error: The entered <" << project_new_name
              << "> new name has already exist.\n";
    return;
  }
  edit_project(projects, project_name, project_new_name);
  std::cout << "Good! You have successfully changed <"
            << project_name << "> project to <"
            << project_new_name << "> project.\n";
  update_db(projects, db_name);
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
              std::cerr << "Error: <" << task_new_name
                        << "> task new name has already existed!\n";
              return;
            }
          }
          projects[i].tasks[j].set_name(task_new_name);
          projects[i].tasks[j].set_date(task_new_date);
          projects[i].tasks[j].set_user(task_new_user);
          std::cout << "Done: <" << task_name
                    << "> task of <" << project_name
                    << "> project is edited successfully!\n";
          return;
        }
      }
    }
  }
  std::cerr << "Error: <" << task_name << "> wasn't edited!\n";
}

bool project_has_task(std::vector<Project> &projects, std::string project_name)
{
  for(int i = 0; i < projects.size(); ++i)
  {
    if(project_name == projects[i].get_name())
    {
      if(projects[i].tasks.empty())
      {
        return false;
      }
    }
  }
  return true;
}

void display_projects_tasks(std::vector<Project> &projects)
{
  std::cout << "Below see all data...\n\n";
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

void task_edit(std::vector<Project> &projects)
{
  if(projects.empty())
  {
    std::cerr << "Error: There aren't any projects. You should create a project at first.\n";
    return;
  }
  std::cout << " - TASK UPDATE\n";
  std::cout << "Please enter project name, to edit task of it.\n";
  display_projects_tasks(projects);
  std::string project_name = data_input("project name");
  if(!is_found_project_name(projects, project_name))
  {
    std::cerr << "Error: You have entered <" << project_name
              << "> project name, that doesn't exist.\n";
    return;
  }
  if(!project_has_task(projects, project_name))
  {
    std::cerr << "Error: The entered <" << project_name
              << "> hasn't got any tasks.\n";
    return;
  }
  std::cout << "Please enter task name to update. ";
  std::string task_name = data_input("task name");
  if(!is_found_task_name(projects, project_name, task_name))
  {
    std::cerr << "Error: The entered <" << task_name
              << "> doesn't exist in <" << project_name
              << "> project.\n";
    return;
  }
  std::cout << "Please enter new task name: ";
  std::string task_new_name = data_input("task name");
  if(is_found_task_name(projects, project_name, task_new_name))
  {
    std::cerr << "Error: The entered <" << task_new_name
              << "> has already existed in <" << project_name
              << "> project.\n";
    return;
  }
  std::cout << "Please enter new task date: ";
  std::string task_new_date = data_input("date");
  std::cout << "Please enter new task user: ";
  std::string task_new_user = data_input("user name");
  edit_task_in_projects(projects, project_name, task_name
                      , task_new_name, task_new_date, task_new_user);
  update_db(projects, db_name);
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
  std::cerr << "Error: <" << name << "> not found.\n";
}

void project_deletion(std::vector<Project> &projects)
{
  if(projects.empty())
  {
    std::cerr << "Error: There aren't any projects. You should create a project at first.\n";
    return;
  }
  std::cout << " - PROJECT DELETION\n";
  display_projects(projects);
  std::cout << "To delete a project, you should enter a project name: ";
  std::string project_name = data_input("project name");
  if(!is_found_project_name(projects, project_name))
  {
    std::cerr << "Error: The entered <" << project_name
              << "> not found.\n";
    return;
  }
  delete_project(projects, project_name);
  update_db(projects, db_name);
}

void task_remove(std::vector<Project> &projects)
{
  if(projects.empty())
  {
    std::cerr << "Error: There aren't any projects. You should create a project at first.\n";
    return;
  }
  std::cout << " - TASK DELETION\n";
  display_projects_tasks(projects);
  std::cout << "Please enter the project name, if you want to delete its task: ";
  std::string project_name = data_input("project name");
  if(!is_found_project_name(projects, project_name))
  {
    std::cerr << "Error: The entered <" << project_name << "> not found.\n";
    return;
  }

  std::cout << "Below see the mentioned project's task(s): \n";
  for(int i = 0; i < projects.size(); ++i)
  {
    if(project_name == projects[i].get_name())
    {
      if(0 == projects[i].tasks.size()) {
        std::cerr << "Error: There aren't any tasks in <" << project_name
                  << "> project.\n";
        return;
      }
      for(int j = 0; j < projects[i].tasks.size(); ++j)
      {
        std::cout << projects[i].tasks[j].get_name() << std::endl;
      }
      std::cout << "Please enter task name. ";
      std::string task_name = data_input("task name");
      bool deleted = false;
      for(int h = 0; h < projects[i].tasks.size(); ++h)
      {
        if(task_name == projects[i].tasks[h].get_name())
        {
          projects[i].tasks.erase(projects[i].tasks.begin() + h);
          std::cout << "Done: <" << task_name << "> task <"
                    << project_name << "> project has been deleted.\n";
          deleted = true;
        }
      }
      if(!deleted) std::cerr << "Error: The entered <" << task_name
                             << "> not found.\n";
    }
  }
  update_db(projects, db_name);
}

void view_projects(std::vector<Project> &projects)
{
  if(projects.empty())
  {
    std::cerr << " - Error: There aren't any projects. You should create a project at first.\n";
    return;
  }
  std::cout << " - DISPLAY PROJECTS\n";
  display_projects(projects);
}

void show_all(std::vector<Project> &projects)
{
  if(projects.empty())
  {
    std::cerr << " - Error: There aren't any projects. You should create a project at first.\n";
    return;
  }
  std::cout << " - DISPLAY ALL DATA (Project(s)&task(s))\n";
  display_projects_tasks(projects);
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

void make_choice(char input, std::vector<Project> &projects)
{
  switch(input)
  {
    case 'C':
      project_creation(projects);
      break;
    case 'A':
      task_addition(projects);
      break;
    case 'U':
      project_update(projects);
      break;
    case 'E':
      task_edit(projects);
      break;
    case 'D':
      project_deletion(projects);
      break;
    case 'R':
      task_remove(projects);
      break;
    case 'V':
      view_projects(projects);
      break;
    case 'S':
      show_all(projects);
      break;
    case 'X':
      return;
      break;
    default:
      std::cout << "The option for the entered letter doesn't exist.\n";
  }
  std::cout << "******************************\n";
  std::cout << "To exit, please enter any 'X', or please enter the other symbol to continue: ";
  std::cin >> input;
  if(input != 'X')
  {
    display_menu();
    input = make_input();
    make_choice(input, projects);
  }
}

void run()
{
  std::vector<Project> projects = {};
  read_from_db(projects, db_name);
  display_menu();
  char input = make_input();
  make_choice(input, projects);
  std::cout << "The application has been closed.\n";
}

int main()
{
  run();
  return 0;
}
