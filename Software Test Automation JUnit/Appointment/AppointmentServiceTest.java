package Appointment;

import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.Test;

import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Date;

import static org.junit.jupiter.api.Assertions.*;

class AppointmentServiceTest {
    // "Correct" variables for easy testing
    // Date
    Date date1 = new Date(2022, 11, 15);
    // Descriptions
    String description1 = "Is there life on mars?";
    String description2 = "I've got my own theme music, plays wherever I are";
    String description3 = "there are millions of cephalophores";
    String description4 = "Time wounds all heels";

    // "Wrong" variables for easy testing

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
    String longDescription = "Don't don't don't let's start, this is the worst part. Could believe for all the world that you're my precious little girl";

    /*
     * STANDARD OPERATING CIRCUMSTANCES
     */

    // Create test under "normal" parameters
    @Test
    void testAppointmentClass(){
        // Add appointments to apptList
        AppointmentService.addAppt(date1, description1);
        AppointmentService.addAppt(date1, description2);
        AppointmentService.addAppt(date1, description3);
        AppointmentService.addAppt(date1, description4);

        // Match values with ID 1001 (should be date1) and check for matching date and description
        assertTrue(date1.compareTo(AppointmentService.findApptID("1001").getApptDate()) == 0);
        assertTrue(AppointmentService.findApptID("1001").getApptDesc().equals(description1));
    }

    // Test unique IDs
    @Test
    void testUniqueIDs() {
        // Add appointments to apptList
        AppointmentService.addAppt(date1, description1);
        AppointmentService.addAppt(date1, description2);
        AppointmentService.addAppt(date1, description3);
        AppointmentService.addAppt(date1, description4);

        // Match values with IDs (desc1 should be 1001, desc2 1002, and so on)
        assertTrue(AppointmentService.apptList.get(0).getApptID().equals("1001"));
        assertTrue(AppointmentService.apptList.get(1).getApptID().equals("1002"));
        assertTrue(AppointmentService.apptList.get(2).getApptID().equals("1003"));
    }


    /*
     * NEW APPOINTMENT TESTS
     */

    // Create test w/ wrong date
    @Test
    void testWrongDateInitial(){
        Assertions.assertThrows(IllegalArgumentException.class, () -> {
            // Add appointments to apptList
            AppointmentService.addAppt(date1, description1);
            AppointmentService.addAppt(date1, description2);
            AppointmentService.addAppt(date1, description3);
            AppointmentService.addAppt(date1, description4);
            AppointmentService.addAppt(wrongDate, description1); });
    }

    // Create test w/ long description
    @Test
    void testLongDescInitial(){
        Assertions.assertThrows(IllegalArgumentException.class, () -> {
            // Add appointments to apptList
            AppointmentService.addAppt(date1, description1);
            AppointmentService.addAppt(date1, description2);
            AppointmentService.addAppt(date1, description3);
            AppointmentService.addAppt(date1, description4);
            AppointmentService.addAppt(date1, longDescription); });
    }

    // Create test w/ null date
    @Test
    void testNullDateInitial(){
        Assertions.assertThrows(IllegalArgumentException.class, () -> {
            // Add appointments to apptList
            AppointmentService.addAppt(date1, description1);
            AppointmentService.addAppt(date1, description2);
            AppointmentService.addAppt(date1, description3);
            AppointmentService.addAppt(date1, description4);
            AppointmentService.addAppt(null, description1); });
    }

    // Create a test with null description
    @Test
    void testNullDescInitial(){
        Assertions.assertThrows(IllegalArgumentException.class, () -> {
            // Add appointments to apptList
            AppointmentService.addAppt(date1, description1);
            AppointmentService.addAppt(date1, description2);
            AppointmentService.addAppt(date1, description3);
            AppointmentService.addAppt(date1, description4);
            AppointmentService.addAppt(date1, null); });
    }


    /*
     * EXISTING APPOINTMENT TESTS
     */

    // Test deleting an appointment ID
    @Test
    void testDeleteAppt(){

        // Populate appointment list
        AppointmentService.addAppt(date1, description1);
        AppointmentService.addAppt(date1, description2);
        AppointmentService.addAppt(date1, description3);
        AppointmentService.addAppt(date1, description4);
        AppointmentService.addAppt(date1, description3);

        // delete appointment "1003"
        AppointmentService.deleteAppt("1003");
    }

    // Test deleting an appointment that doesn't exist
    @Test
    void testDeleteWrongApptID(){
        Assertions.assertThrows(IllegalArgumentException.class, () ->{
            AppointmentService.deleteAppt("20000"); });
    }
}