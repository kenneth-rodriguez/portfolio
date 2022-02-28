package Task;

public class Task {
    // Declare variables
    private String taskID;
    private String taskName;
    private String taskDesc;

    // Task Constructor
    // Takes an ID String, name String, and ID string
    public Task(String ID, String name, String description){

        // If ID is null or longer than 10 characters, throw exception
        if(ID == null || ID.length() > 10) {
            throw new IllegalArgumentException("Invalid ID");
        }

        // If name is null or longer than 20 characters, throw exception
        if(name == null || name.length() > 20){
            throw new IllegalArgumentException("Invalid name");
        }

        // If description is null or longer than 20 characters, throw exception
        if(description == null || description.length() > 50) {
            throw new IllegalArgumentException("Invalid description");
        }

        // If all conditions are met, create an object with the given inputs.
        this.taskID = ID;
        this.taskName = name;
        this.taskDesc = description;
    }

    // Accessors
    public String getTaskID(){return taskID;}
    public String getTaskName(){return taskName;}
    public String getTaskDesc(){return taskDesc;}

    // Mutators
    // NOTE: taskID shall not be updatable, as per specifications

    // Set task name
    public void setTaskName(String name){
        // If name is null or longer than 20 characters, throw exception
        if(name == null || name.length() > 20){
            throw new IllegalArgumentException("Invalid name");
        }

        // Else, update taskName
        this.taskName = name;
    }

    // Set task description
    public void setTaskDesc(String desc){
        // If description is null or longer than 50 characters, throw exception
        if(desc == null || desc.length() > 50){
            throw new IllegalArgumentException("Invalid description");
        }

        // Else, update taskDesc
        this.taskDesc = desc;
    }

}
