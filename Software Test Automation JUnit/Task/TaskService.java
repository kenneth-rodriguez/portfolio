package Task;

import java.sql.Array;
import java.util.ArrayList;

public class TaskService {
    // Create the first ID number. This will be incremented to ensure IDs are unique.
    static int taskID = 1000;

    // Create ArrayList object for variably-sized Task storage
    static ArrayList<Task> taskList = new ArrayList<>();

    // Reusable ID search function
    public static Task findTaskID(String ID){
        // Go through each Task in taskList
        for (Task task : taskList){
            // If searched ID matches, return Task object
            if (ID.compareTo(task.getTaskID()) == 0){
                return task;
            }
        }
        // IF searched ID isn't found, return null
        return null;
    }

    // Add new task
    public static void addTask(String name, String desc){
        // Increment standard ID variable, then change ID to string.
        taskID++;
        String newID = Integer.toString(taskID);

        // Create a new task with unique ID
        Task newTask = new Task(newID, name, desc);

        // Add task to taskList array
        taskList.add(newTask);
    }

    // Delete task with taskID that matches ID
    public static void deleteTask(String ID){
        // Use search method to find task and remove it
        if (findTaskID(ID) != null){
            taskList.remove(findTaskID(ID));
        }
        // If task is not found, throw exception
        else
            throw new IllegalArgumentException("Task ID not found");
    }

    // Search for a task ID, then update task name
    public static void updateTaskName(String ID, String newTaskName){
        // Use search method to find task to change name
        if (findTaskID(ID) != null) {
            findTaskID(ID).setTaskName(newTaskName);
        }
        // If the task is not found, throw exception
        else
            throw new IllegalArgumentException("Task ID not found");
    }

    // Search for a task ID, then update task description
    public static void updateTaskDesc(String ID, String newTaskDesc){
        // Use search method to find task to change desc
        if (findTaskID(ID) != null){
            findTaskID(ID).setTaskDesc(newTaskDesc);
        }
        // If the task is not found, throw exception
        else
            throw new IllegalArgumentException("Task ID not found");
    }
}
