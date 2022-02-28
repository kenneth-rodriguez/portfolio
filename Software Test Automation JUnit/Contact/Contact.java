package Contact;

public class Contact {
    // Declare Variables
    private String contactID;
    private String firstName;
    private String lastName;
    private String phone;
    private String address;


    // Contact Constructor
    // Takes an ID, a firstName, a lastName, a phone number, and an address.
    public Contact(String ID, String firstName, String lastName, String phone, String address){

        // If ID is null or longer than 10 characters, throw exception.
        if(ID == null || ID.length() > 10) {
            throw new IllegalArgumentException("Invalid ID");
        }

        // If firstName is null or longer than 10 characters, throw exception.
        if(firstName == null || firstName.length() > 10) {
            throw new IllegalArgumentException("Invalid first name");
        }

        // If lastName is null or longer than 10 characters, throw exception.
        if(lastName == null || lastName.length() > 10) {
            throw new IllegalArgumentException("Invalid last name");
        }

        // If the inputted phone number is null or not equal to 10 characters, throw exception.
        if(phone == null || phone.length() != 10) {
            throw new IllegalArgumentException("Invalid phone number");
        }

        // If address is null or longer than 30 characters, throw exception.
        if(address == null || address.length() > 30) {
            throw new IllegalArgumentException("Invalid address");
        }

        // If all conditions are met, create an object with the given inputs.
        this.contactID = ID;
        this.firstName = firstName;
        this.lastName = lastName;
        this.phone = phone;
        this.address = address;
    }


    // Accessors
    public String getContactID() {
        return contactID;
    }

    public String getFirstName(){
        return firstName;
    }

    public String getLastName(){
        return lastName;
    }

    public String getPhone() {
        return phone;
    }

    public String getAddress(){
        return address;
    }


    // Mutators
    // NOTE: contactID shall not be updatable, as per specifications.
    public void setFirstName(String firstName){
        // If firstName is null or longer than 10 characters, throw exception.
        if(firstName == null || firstName.length() > 10) {
            throw new IllegalArgumentException("Invalid first name");
        }

        // Else, update firstName
        this.firstName = firstName;
    }

    public void setLastName(String lastName){
        // If lastName is null or longer than 10 characters, throw exception.
        if(lastName == null || lastName.length() > 10) {
            throw new IllegalArgumentException("Invalid last name");
        }

        // Else, update lastName
        this.lastName = lastName;
    }

    public void setPhone(String phone) {
        // If the inputted phone number is null or not equal to 10 characters, throw exception.
        if(phone == null || phone.length() != 10) {
            throw new IllegalArgumentException("Invalid phone number");
        }

        // Else, update phone
        this.phone = phone;
    }

    public void setAddress(String address){
        // If address is null or longer than 30 characters, throw exception.
        if(address == null || address.length() > 30) {
            throw new IllegalArgumentException("Invalid address");
        }

        // Else, update address
        this.address = address;
    }
}
