package Appointment;

import java.util.Date;

public class Appointment {
    // Declare variables
    private String apptID;
    private String apptDesc;
    private Date apptDate;

    // Create local variable for current date
    Date currDate = new Date();


    // Appointment Constructor
    // Take an ID String, an appointment Date, and an desc String
    public Appointment(String ID, Date newDate, String description){
        // If ID is null or longer than 10 characters, throw exceptions
        if (ID == null || ID.length() > 10) {
            throw new IllegalArgumentException("Invalid ID");
        }

        // If newDate is null or before the current date, throw exception
        if ((newDate == null) || newDate.before(currDate)){
            throw new IllegalArgumentException("Invalid date");
        }

        // If description is null or greater than 50 characters, throw exception
        if (description == null || description.length() > 50){
            throw new IllegalArgumentException("Invalid description");
        }

        // If all conditions are met, create an object with the given inputs.
        this.apptID = ID;
        this.apptDate = newDate;
        this.apptDesc = description;
    }


    // Accessors
    public String getApptID(){return apptID;}
    public Date getApptDate(){return apptDate;}
    public String getApptDesc(){return apptDesc;}


    // Mutators
    // NOTE: apptID shall not be updatable, as per specifications

    // Set appointment date
    public void setApptDate(Date newDate){
        // Create local variable for current date
        Date currDate = new Date();

        // If newDate is null or before the current date, throw exception
        if ((newDate == null) || newDate.before(currDate)){
            throw new IllegalArgumentException("Invalid date");
        }

        // If newDate is otherwise valid, update appointment date
        this.apptDate = newDate;
    }

    public void setApptDesc(String description){
        // If description is null or greater than 50 characters, throw exception
        if (description == null || description.length() > 50){
            throw new IllegalArgumentException("Invalid description");
        }

        // If the description is other valid, update appointment description
        this.apptDesc = description;
    }


}
