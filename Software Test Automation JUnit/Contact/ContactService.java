package Contact;

import java.util.ArrayList;

public class ContactService {
    // Create the first ID number. This will be incremented to ensure unique IDs for each contact.
    static int idNumber = 1000;

    // Create ArrayList object for variably-sized Contact storage
    static ArrayList<Contact> contactList = new ArrayList<Contact>();

    // reusable ID search function
    public static Contact findContactID(String ID){
        // Go through each Contact in contactList
        for (Contact contact : contactList) {
            // If searched ID matches, return Contact object
            if (ID.compareTo(contact.getContactID()) == 0) {
                return contact;
            }
        }
        // If searched ID isn't found, return null
        return null;
    }

    // Add new contact
    public static void addContact(String newFirstName, String newLastName, String newPhone, String newAddress){
        // Increment ID number to account for a new contact to provide a unique ID. Then, convert to string
        idNumber++;
        String newID = Integer.toString(idNumber);

        // Create new contact with unique ID
        Contact newContact = new Contact(newID, newFirstName, newLastName, newPhone, newAddress);

        // Add contact to contactList array
        contactList.add(newContact);
    }

    // Delete contact with contactID that matches ID
    public static void deleteContact(String ID){
        // Use search method to find contact and remove it
        if (findContactID(ID) != null){
            contactList.remove(findContactID(ID));
        }
        // If contact is not found, throw exception.
        else
            throw new IllegalArgumentException("Contact ID not found");
    }

    // Search for a contact ID, then update contact firstName
    public static void updateFirstName(String ID, String newFirstName){
        // Use search method to find contact to change first name
        if (findContactID(ID) != null){
            findContactID(ID).setFirstName(newFirstName);
        }
        // If contact is not found, throw exception.
        else
            throw new IllegalArgumentException("Contact ID not found");
    }

    // Search for contact ID, then update contact lastName
    public static void updateLastName(String ID, String newLastName){
        // Use search method to find contact to change last name
        if (findContactID(ID) != null){
            findContactID(ID).setLastName(newLastName);
        }
        // If contact is not found, throw exception.
        else
            throw new IllegalArgumentException("Contact ID not found");
    }

    // Search for contact ID, then update phone number
    public static void updatePhone(String ID, String newPhone){
        // Use search method to find contact to change phone
        if (findContactID(ID) != null) {
            findContactID(ID).setPhone(newPhone);
        }
        // If contact is not found, throw exception.
        else
            throw new IllegalArgumentException("Contact ID not found");
    }

    // Search for contact ID, then update address
    public static void updateAddress(String ID, String newAddress){
        // Use search method to find contact to change address
        if (findContactID(ID) != null) {
            findContactID(ID).setAddress(newAddress);
        }
        // If contact is not found, throw exception.
        else
            throw new IllegalArgumentException("Contact ID not found");
    }
}
