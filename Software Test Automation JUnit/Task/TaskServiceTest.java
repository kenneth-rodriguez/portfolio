package Task;

import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.assertTrue;

class TaskServiceTest {
    // Test TaskService under "normal" circumstances and populate the initial array
    @Test
    void testTaskServiceClass(){
        // Add tasks to taskList
        TaskService.addTask("Task1", "Test1");
        TaskService.addTask("Task2", "Test2");
        TaskService.addTask("Task3", "Test3");
        TaskService.addTask("Task4", "Test4");
        TaskService.addTask("Task5", "Test5");

        // Match values with ID 1001 (should be Task1) and check for matching name and descriptions
        assertTrue(TaskService.findTaskID("1001").getTaskName().equals("Task1"));
        assertTrue(TaskService.findTaskID("1001").getTaskDesc().equals("Test1"));
    }

    /*
     * NEW TASK TESTS
     */

    // Test TaskService with long name
    @Test
    void testLongNameInitial() {
        Assertions.assertThrows(IllegalArgumentException.class, () -> {
            TaskService.addTask("Task1", "Test1");
            TaskService.addTask("Task2", "Test2");
            TaskService.addTask("Task3", "Test3");
            TaskService.addTask("Task4", "Test4");
            TaskService.addTask("Task5", "Test5");
            TaskService.addTask("Won't lovers revolt now?", "Test1"); });
    }

    // Test TaskService with null desc
    @Test
    void testLongDescInitial() {
        Assertions.assertThrows(IllegalArgumentException.class, () -> {
            TaskService.addTask("Task1", "Test1");
            TaskService.addTask("Task2", "Test2");
            TaskService.addTask("Task3", "Test3");
            TaskService.addTask("Task4", "Test4");
            TaskService.addTask("Task5", "Test5");
            TaskService.addTask("Task1", "Rats live on no evil star. Race fast safe car. Madam, I'm Adam."); });
    }

    // Test TaskService with null name
    @Test
    void testNullNameInitial() {
        Assertions.assertThrows(IllegalArgumentException.class, () -> {
            TaskService.addTask("Task1", "Test1");
            TaskService.addTask("Task2", "Test2");
            TaskService.addTask("Task3", "Test3");
            TaskService.addTask("Task4", "Test4");
            TaskService.addTask("Task5", "Test5");
            TaskService.addTask(null, "Test1"); });
    }

    // Test TaskService with null desc
    @Test
    void testNullDescInitial() {
        Assertions.assertThrows(IllegalArgumentException.class, () -> {
            TaskService.addTask("Task1", "Test1");
            TaskService.addTask("Task2", "Test2");
            TaskService.addTask("Task3", "Test3");
            TaskService.addTask("Task4", "Test4");
            TaskService.addTask("Task5", "Test5");
            TaskService.addTask("Task1", null); });
    }

    // Test unique IDs
    @Test
    void testUniqueIDs(){
        // Add tasks to taskList
        TaskService.addTask("Task1", "Test1");
        TaskService.addTask("Task2", "Test2");
        TaskService.addTask("Task3", "Test3");
        TaskService.addTask("Task4", "Test4");
        TaskService.addTask("Task5", "Test5");

        // Match values with ID 1001 (should be Task1) and check for matching name and descriptions
        assertTrue(TaskService.taskList.get(0).getTaskID().equals("1001"));
        assertTrue(TaskService.taskList.get(1).getTaskID().equals("1002"));
        assertTrue(TaskService.taskList.get(2).getTaskID().equals("1003"));
    }

    // Test deleting tasks that exist
    @Test
    void testDeleteTasks(){
        // Add tasks to taskList
        TaskService.addTask("Task1", "Test1");
        TaskService.addTask("Task2", "Test2");
        TaskService.addTask("Task3", "Test3");
        TaskService.addTask("Task4", "Test4");
        TaskService.addTask("Task5", "Test5");

        // Delete task w/ ID "1005"
        TaskService.deleteTask("1005");

        // Check if ID "1005" returns null to ensure its deletion
        assertTrue(TaskService.findTaskID("1005") == null);
    }

    // Test deleting tasks that don't exist
    @Test
    void testDeleteNonTasks() {
        Assertions.assertThrows(IllegalArgumentException.class, () -> {
            // Attempt to delete task that doesn't exist
            TaskService.deleteTask("5000"); });
    }


    /*
     * TEST UPDATING FIELDS
     */

    // Test updating task name for non-extant tasks exist
    @Test
    void testUpdateNonTaskName() {
        Assertions.assertThrows(IllegalArgumentException.class, () -> {
            // Attempt to delete task that doesn't exist
            TaskService.updateTaskName("5000", "No task?"); });
    }

    // Test updating task name for non-extant tasks exist
    @Test
    void testUpdateNonTaskDesc() {
        Assertions.assertThrows(IllegalArgumentException.class, () -> {
            // Attempt to delete task that doesn't exist
            TaskService.updateTaskDesc("5000", "No Task?"); });
    }

    // Test changing name
    @Test
    void testChangeName(){
        // add tasks to taskList for testing
        TaskService.addTask("Task1", "Test1");
        TaskService.addTask("Task2", "Test2");
        TaskService.addTask("Task3", "Test3");
        TaskService.addTask("Task4", "Test4");
        TaskService.addTask("Task5", "Test5");

        // Update the name of "1002" w/ method
        TaskService.updateTaskName("1002", "Success!");

        // Check if first name of 1002 was updated
        assertTrue(TaskService.findTaskID("1002").getTaskName().equals("Success!"));
    }

    // Test changing description
    @Test
    void testChangeDesc(){
        // add tasks to taskList for testing
        TaskService.addTask("Task1", "Test1");
        TaskService.addTask("Task2", "Test2");
        TaskService.addTask("Task3", "Test3");
        TaskService.addTask("Task4", "Test4");
        TaskService.addTask("Task5", "Test5");

        // Update the name of "1002" w/ method
        TaskService.updateTaskDesc("1002", "Success!");

        // Check if first name of 1002 was updated
        assertTrue(TaskService.findTaskID("1002").getTaskDesc().equals("Success!"));
    }


    /*
     * TEST CHANGING NULL FIELDS
     */

    // Test changing w/ null name
    @Test
    void testChangeNullName() {
        Assertions.assertThrows(IllegalArgumentException.class, () -> {
            // add tasks for testing
            TaskService.addTask("Task1", "Test1");
            TaskService.addTask("Task2", "Test2");
            TaskService.addTask("Task3", "Test3");
            TaskService.addTask("Task4", "Test4");
            TaskService.addTask("Task5", "Test5");

            // update the first name of 1002 w/ null
            TaskService.updateTaskName("1002", null); });
    }

    // Test changing w/ null description
    @Test
    void testChangeNullDesc() {
        Assertions.assertThrows(IllegalArgumentException.class, () -> {
            // add tasks for testing
            TaskService.addTask("Task1", "Test1");
            TaskService.addTask("Task2", "Test2");
            TaskService.addTask("Task3", "Test3");
            TaskService.addTask("Task4", "Test4");
            TaskService.addTask("Task5", "Test5");

            // update the first name of 1002 w/ null
            TaskService.updateTaskDesc("1002", null); });
    }
}