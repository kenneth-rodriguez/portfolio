package Appointment;

import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.Test;

import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Calendar;
import java.util.Date;

import static org.junit.jupiter.api.Assertions.*;

class AppointmentTest {
    // Correct parameter variables
    String testID = "12345";
    Date testDate = new Date(2022, Calendar.MARCH, 1);
    String testDesc = "Test appt.";

    // Create a new wrong date by parsing a string with SimpleDateFormat
    String wrongDateString = "10/25/1995";
    SimpleDateFormat formatter = new SimpleDateFormat("MM/DD/YYYY");
    Date wrongDate;
    {
        try {
            wrongDate = formatter.parse(wrongDateString);
        } catch (ParseException e) {
            e.printStackTrace();
        }
    }


    // Test Appointment class under "normal" parameters
    @Test
    void testAppointmentClass(){
        Appointment testAppt = new Appointment(testID, testDate, testDesc);
        assertTrue(testAppt.getApptID().equals(testID));
        assertTrue(testAppt.getApptDate().equals(testDate));
        assertTrue(testAppt.getApptDesc().equals(testDesc));
    }

    /*
     * LONG/WRONG DATE INPUT TESTS
     */
    // Test if ID > 10 characters
    @Test
    void testLongID(){
        Assertions.assertThrows(IllegalArgumentException.class, () ->{
            new Appointment("12345678910", testDate, testDesc); });
    }

    // Test if date is before the current date
    @Test
    void testWrongDate(){
        System.out.print("Is wrongDate before today's date?");
        Assertions.assertThrows(IllegalArgumentException.class, () ->{
            new Appointment(testID, wrongDate, testDesc); });
    }

    // Test if description is too long
    @Test
    void testLongDesc(){
        Assertions.assertThrows(IllegalArgumentException.class, () ->{
            new Appointment(testID, testDate, "Don't don't don't let's start, this is the worst part. Could believe for all the world that you're my precious little girl"); });
    }


    /*
     * NULL INPUT TESTS
     */
    // Test null ID
    @Test
    void testNullID(){
        Assertions.assertThrows(IllegalArgumentException.class, () ->{
            new Appointment(null, testDate, testDesc); });
    }

    // Test null date
    @Test
    void testNullDate(){
        Assertions.assertThrows(IllegalArgumentException.class, () ->{
            new Appointment(testID, null, testDesc); });
    }

    // Test null desc
    @Test
    void testNullDesc(){
        Assertions.assertThrows(IllegalArgumentException.class, () ->{
            new Appointment(testID, testDate, null); });
    }


    /*
     * TEST FOR MUTATORS
     */
    // NOTE: ID shall not be changed, as per specification.

    // Test for correct changed date
    @Test
    void testChangedDate(){
        // Create new date for testing
        Date newTestDate = new Date(2023, 05, 15);

        Appointment testAppt = new Appointment(testID, testDate, testDesc);
        testAppt.setApptDate(newTestDate);
        assertTrue(testAppt.getApptDate().equals(newTestDate));
    }

    // Test for correct changed description
    @Test
    void testChangedDesc(){
        Appointment testAppt = new Appointment(testID, testDate, testDesc);
        testAppt.setApptDesc("New desc");
        assertTrue(testAppt.getApptDesc().equals("New desc"));
    }


    /*
     * TEST FOR WRONG/LONG MUTATORS
     */

    @Test
    void testChangeWrongDate(){
        Assertions.assertThrows(IllegalArgumentException.class, () ->{
            Appointment testAppt = new Appointment(testID, testDate, testDesc);
            testAppt.setApptDate(wrongDate); });
    }

    @Test
    void testChangeLongDesc(){
        Assertions.assertThrows(IllegalArgumentException.class, () ->{
            Appointment testAppt = new Appointment(testID, testDate, testDesc);
            testAppt.setApptDesc("Don't don't don't let's start, this is the worst part. Could believe for all the world that you're my precious little girl"); });
    }

}