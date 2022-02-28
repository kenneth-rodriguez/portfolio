package Appointment;

import java.util.ArrayList;
import java.util.Date;

public class AppointmentService {
    // Create first ID number. This will be incremented to ensure IDs are unique and sequential.
    static int apptID= 1000;

    // Create ArrayList object for variably-sized Array storage
    static ArrayList<Appointment> apptList = new ArrayList<>();

    // Reusable ID search function
    public static Appointment findApptID(String ID){
        // Go through each Appointment in apptList
        for (Appointment appt : apptList){
            // If searched ID matches, return Appointment object
            if (ID.compareTo(appt.getApptID()) == 0){
                return appt;
            }
        }
        // IF searched ID isn't found, return null
        return null;
    }

    // Add new appointment
    public static void addAppt(Date newDate, String description){
        // Increment standard ID variable, then change ID to string
        apptID++;
        String newID = Integer.toString(apptID);

        // Create a new appointment with unique ID
        Appointment newAppt = new Appointment(newID, newDate, description);

        // Add appointment to apptList array
        apptList.add(newAppt);
    }

    // Delete appointment with apptID that matches ID
    public static void deleteAppt(String ID){
        // Use search method to find appointment and remove it
        if (findApptID(ID) != null) {
            apptList.remove(findApptID(ID));
        }
        // If appointment is not found, throw exception
        else
            throw new IllegalArgumentException("Appointment ID not found");
    }
}
