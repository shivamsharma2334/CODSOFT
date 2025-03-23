#include <iostream>
#include <vector>
#include <string>
#include <limits>

class Task {
private:
    std::string description;
    bool completed;

public:
    // Constructor
    Task(const std::string& desc) : description(desc), completed(false) {}

    // Getters
    std::string getDescription() const {
        return description;
    }

    bool isCompleted() const {
        return completed;
    }

    // Methods
    void markAsCompleted() {
        completed = true;
    }

    void display(int index) const {
        std::cout << index << ". [" << (completed ? "X" : " ") << "] " << description << std::endl;
    }
};

class ToDoList {
private:
    std::vector<Task> tasks;

public:
    // Methods
    void addTask(const std::string& description) {
        tasks.push_back(Task(description));
        std::cout << "Task added successfully!" << std::endl;
    }

    void viewTasks() const {
        if (tasks.empty()) {
            std::cout << "No tasks in the list." << std::endl;
            return;
        }

        std::cout << "\n===== TO-DO LIST =====\n";
        for (size_t i = 0; i < tasks.size(); ++i) {
            tasks[i].display(i + 1);
        }
        std::cout << "=====================\n" << std::endl;
    }

    bool markTaskAsCompleted(int taskIndex) {
        if (taskIndex >= 1 && taskIndex <= static_cast<int>(tasks.size())) {
            tasks[taskIndex - 1].markAsCompleted();
            std::cout << "Task marked as completed!" << std::endl;
            return true;
        }
        std::cout << "Invalid task number!" << std::endl;
        return false;
    }

    bool removeTask(int taskIndex) {
        if (taskIndex >= 1 && taskIndex <= static_cast<int>(tasks.size())) {
            tasks.erase(tasks.begin() + (taskIndex - 1));
            std::cout << "Task removed successfully!" << std::endl;
            return true;
        }
        std::cout << "Invalid task number!" << std::endl;
        return false;
    }

    size_t getTaskCount() const {
        return tasks.size();
    }
};

void displayMenu() {
    std::cout << "\nTO-DO LIST MANAGER\n";
    std::cout << "1. Add a new task\n";
    std::cout << "2. View all tasks\n";
    std::cout << "3. Mark a task as completed\n";
    std::cout << "4. Remove a task\n";
    std::cout << "5. Exit\n";
    std::cout << "Enter your choice (1-5): ";
}

int getValidChoice(int min, int max) {
    int choice;
    while (!(std::cin >> choice) || choice < min || choice > max) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid input. Please enter a number between " << min << " and " << max << ": ";
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return choice;
}

int main() {
    ToDoList todoList;
    std::string taskDescription;
    int taskIndex;
    int choice;
    bool running = true;

    std::cout << "Welcome to the To-Do List Manager!" << std::endl;

    while (running) {
        displayMenu();
        choice = getValidChoice(1, 5);

        switch (choice) {
            case 1: // Add a new task
                std::cout << "Enter task description: ";
                std::getline(std::cin, taskDescription);
                todoList.addTask(taskDescription);
                break;

            case 2: // View all tasks
                todoList.viewTasks();
                break;

            case 3: // Mark a task as completed
                if (todoList.getTaskCount() == 0) {
                    std::cout << "No tasks available to mark as completed." << std::endl;
                } else {
                    todoList.viewTasks();
                    std::cout << "Enter the task number to mark as completed: ";
                    taskIndex = getValidChoice(1, todoList.getTaskCount());
                    todoList.markTaskAsCompleted(taskIndex);
                }
                break;

            case 4: // Remove a task
                if (todoList.getTaskCount() == 0) {
                    std::cout << "No tasks available to remove." << std::endl;
                } else {
                    todoList.viewTasks();
                    std::cout << "Enter the task number to remove: ";
                    taskIndex = getValidChoice(1, todoList.getTaskCount());
                    todoList.removeTask(taskIndex);
                }
                break;

            case 5: // Exit
                std::cout << "Thank you for using the To-Do List Manager. Goodbye!" << std::endl;
                running = false;
                break;
        }
    }

    return 0;
}
