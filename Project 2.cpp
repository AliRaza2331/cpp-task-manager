// ALI RAZA 
// Note: Please use High, Normal and Low when adding task priority for user input

# include <iostream>
# include <stack>
# include <queue>
# include <string>
using namespace std;


// Task Class for creating an object task

class Task {
public:
    string name, description;
    string priority, status;

    // Constructor for initializing task object
    Task(string n, string d, string p) {
        name = n;
        description = d;
        priority = p;
        status = "pending"; // Initializing tasks that are to be completed
    }

    // Display function
    void display() const {
        cout << name << " [" << status << ", Priority" << " : " << priority << "]" << endl;
    }
}; 


// Managing tasks using TaskManager class using Queues and Stacks

class TaskManager {
private:
    stack<Task> highPriorityStack; // Stacking for high-priority tasks
    queue<Task> normalPriorityQueue; // Queueing for normal-priority tasks

    public:
    // Adding a new task based on its priority
    void addTask(Task task) {
        if (task.priority == "High")
            highPriorityStack.push(task);
        else
            normalPriorityQueue.push(task);

        cout << "Task '" << task.name << "' was added successfully!" << endl;
    }

    // View all current tasks that are stacked and queued
    void viewTasks() {
        cout << "\nPriority Stack (High Priority):" << endl;
        if (highPriorityStack.empty()) {
            cout << "[Empty]" << endl;
        } else {
            stack<Task> tempStack = highPriorityStack; // temporary copy to safely iterate through original stack
            while (!tempStack.empty()) {
                tempStack.top().display(); // views the top element of the stack, top task
                tempStack.pop(); // removes the top task in the stack, to move to next element
            }
        }
        cout << "\nNormal Queue (Normal Priority):" << endl;
        if (normalPriorityQueue.empty()) {
            cout << "[Empty]" << endl;
        } else {
            queue<Task> tempQueue = normalPriorityQueue; // temporary copy to safely iterate through original queue
            while (!tempQueue.empty()) {
                tempQueue.front().display(); // views the front element of the queue, first task
                tempQueue.pop(); // removes the first task in the queue, to move to next element
            }
        }
    }

    // Complete the next task based on priority

    void completeTask() {
        if (!highPriorityStack.empty()) {
            Task &task = highPriorityStack.top(); // Reference to "directly" access the top stack task
            task.status = "Completed";
            cout << "Task '" << task.name << "' marked as completed!" << endl;

        } else if (!normalPriorityQueue.empty()) {
            Task &task = normalPriorityQueue.front(); // Reference to "directly" access the front queue task
            task.status = "Completed";
            cout << "Task '" << task.name << "' marked as completed!" << endl;

        } else {
            cout << "No tasks available to complete!" << endl;
        }
    }

    // Remove all completed tasks from the stack and the queue
    void removeCompleted() {
        stack<Task> tempStack; // temporary stack to hold only pending tasks
        while (!highPriorityStack.empty()) {  // loops through the stack till it is empty
            if (highPriorityStack.top().status != "Completed") 
                tempStack.push(highPriorityStack.top()); // push pending tasks into temporary stack
            highPriorityStack.pop(); // remove completed task from the temporary stack
        }
        highPriorityStack.swap(tempStack); // changes original stack with temporary stack, with only pending tasks

        queue<Task> tempQueue; // temporary queue to hold only pending tasks
        while (!normalPriorityQueue.empty()) { // loops through the queue till it is empty 
            if (normalPriorityQueue.front().status != "Completed") 
                tempQueue.push(normalPriorityQueue.front()); // keep pending tasks in temporary queue
            normalPriorityQueue.pop(); // remove completed tasks from the temporary queue
        }
        normalPriorityQueue.swap(tempQueue); // swap original queue with temporary queue, with only pending tasks

        cout << "Completed tasks removed successfully." << endl;
    }

    // Move a task from queue to the stack to give it higher priority

    void increasePriority(int task_id) {
        queue<Task> tempQueue; // temporary queue for remaining tasks not being moved
        bool found = false;

        while (!normalPriorityQueue.empty()) {
            Task t = normalPriorityQueue.front(); // retrieves task from the front of the queue
            normalPriorityQueue.pop(); // removes it from the queue to ensure proper searching( till task_id == 1)

            if (task_id == 1 && !found) {
                t.priority = "High"; // update the priority of the task 
                highPriorityStack.push(t); // moves task to high priority stack
                found = true; // ensures only one task is moved even is tasks have same task_id after moving
                cout << "Task '" << t.name << "' moved to high priority!" << endl;
            } else {
                tempQueue.push(t); // if taskid doesn't match it is moved to temporary queue to preserve other tasks
            }
            task_id--; // decrements task_id 
        }
        normalPriorityQueue.swap(tempQueue); // updates the original queue after shifting a task to high priority 
    }
};

// Main function for the Task Management System
int main() {

    TaskManager manager;
    int choice;

    cout << "Task Management System" << endl;

    while (true) {
        cout << "\nCommands:\n";
        cout << "1. Add a task\n";
        cout << "2. View tasks\n";
        cout << "3. Complete a task\n";
        cout << "4. Increase priority\n";
        cout << "5. Remove completed tasks\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            string name, description, priority;
            cout << "Enter task name: ";
            cin.ignore();  // Clears input buffer
            getline(cin, name);
            cout << "Enter task description: ";
            getline(cin, description);
            cout << "Enter task priority (High/Normal/Low): ";
            getline(cin, priority);

            manager.addTask(Task(name, description, priority));
        } 
        
        else if (choice == 2) {
            manager.viewTasks();
        } 
        
        else if (choice == 3) {
            manager.completeTask();
        } 
        
        else if (choice == 4) {
            int task_id;
            cout << "Enter task ID to increase priority: ";
            cin >> task_id;
            manager.increasePriority(task_id);
        } 
        
        else if (choice == 5) {
            manager.removeCompleted();
        } 
        
        else if (choice == 6) {
            cout << "Thank you for using the Task Management System!" << endl;
            break;
        } 
        
        else {
            cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}



