package Task;

import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.assertTrue;

class TaskTest {
    // Test Task class under "normal" parameters
    @Test
    void testTaskClass() {
        Task testTask = new Task("12345", "New Task", "This is a task for testing");
        assertTrue(testTask.getTaskID().equals("12345"));
        assertTrue(testTask.getTaskName().equals("New Task"));
        assertTrue(testTask.getTaskDesc().equals("This is a task for testing"));
    }


    /*
     * LONG INPUT TESTS
     */

    // Test if ID > 10 chars
    @Test
    void testLongID(){
        Assertions.assertThrows(IllegalArgumentException.class, () ->{
            new Task("12345678910", "New Task", "Test task"); });
    }

    // Test if name > 20 chars
    @Test
    void testLongName(){
        Assertions.assertThrows(IllegalArgumentException.class, () ->{
                new Task("12345", "Won't lovers revolt now?", "Test task"); });
    }

    // Test if description > 50 chars
    @Test
    void testLongDesc(){
        Assertions.assertThrows(IllegalArgumentException.class, () ->{
            new Task("12345", "New Task", "Rats live on no evil star. Race fast safe car. Madam, I'm Adam."); });
    }



    /*
     * NULL INPUT TESTS
     */

    // Test if null ID
    @Test
    void testNullId(){
        Assertions.assertThrows(IllegalArgumentException.class, () ->{
            new Task(null, "New Task", "Task Description"); });
    }

    // Test if null name
    @Test
    void testNullName(){
        Assertions.assertThrows(IllegalArgumentException.class, () ->{
            new Task("12345", null, "Task Description"); });
    }

    // Test if null description
    @Test
    void testNullDesc(){
        Assertions.assertThrows(IllegalArgumentException.class, () ->{
            new Task("12345", "New Task", null); });
    }


    /*
     * TEST FOR MUTATORS
     */

    // Test for changed name
    @Test
    void testChangedName(){
        Task testTask = new Task("12345", "New Task", "Desc");
        testTask.setTaskName("Changed Task");
        assertTrue(testTask.getTaskName().equals("Changed Task"));
    }

    // Test for changed description
    @Test
    void testChangedDesc(){
        Task testTask = new Task("12345", "New Task", "Desc");
        testTask.setTaskDesc("New Desc");
        assertTrue(testTask.getTaskDesc().equals("New Desc"));
    }


    /*
     * TEST FOR LONG MUTATORS
     */

    // Test for changed long name
    @Test
    void testChangeLongName(){
        Assertions.assertThrows(IllegalArgumentException.class, () ->{
            Task testTask = new Task("12345", "New Task", "Desc");
            testTask.setTaskName("Won't lovers revolt now?"); });
    }

    // Test for changed long description
    @Test
    void testChangeLongDesc(){
        Assertions.assertThrows(IllegalArgumentException.class, () ->{
            Task testTask = new Task("12345", "New Task", "Desc");
            testTask.setTaskDesc("Rats live on no evil star. Race fast safe car. Madam, I'm Adam."); });
    }


    /*
     * TEST FOR NULL MUTATORS
     */

    // Test for changed null name
    @Test
    void testChangeNullName(){
        Assertions.assertThrows(IllegalArgumentException.class, () ->{
            Task testTask = new Task("12345", "New Task", "Desc");
            testTask.setTaskName(null); });
    }

    // Test for changed null description
    @Test
    void testChangeNullDesc(){
        Assertions.assertThrows(IllegalArgumentException.class, () ->{
            Task testTask = new Task("12345", "New Task", "Desc");
            testTask.setTaskDesc(null); });
    }
}