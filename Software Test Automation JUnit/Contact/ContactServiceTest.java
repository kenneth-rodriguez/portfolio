package Contact;
import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.Test;

import java.util.Objects;

import static org.junit.jupiter.api.Assertions.*;

// Perform tests in set order to ensure correct variables

class ContactServiceTest {

    // Test ContactService under "normal" circumstances by populating the list
    @Test
    void testContactServiceClass(){
        // Add contacts to contactList
        ContactService.addContact("Robert", "Zimmerman", "5558675309",
                "1060 W Addison");
        ContactService.addContact("John", "Denver", "5556345789",
                "1410 S. Museum Campus Dr");
        ContactService.addContact("Paul", "Simon", "5555880300",
                "1901 W Madison St");
        ContactService.addContact("Ted", "Logan", "5558675309",
                "San Dimas, CA");
        ContactService.addContact("Bill S.", "Preston", "5558675309",
                "San Dimas, CA");

        // Match values with ID 1001 (should be Robert Zimmerman in all cases)
        assertTrue(ContactService.findContactID("1001").getFirstName().equals("Robert"));
        assertTrue(ContactService.findContactID("1001").getLastName().equals("Zimmerman"));
        assertTrue(ContactService.findContactID("1001").getPhone().equals("5558675309"));
        assertTrue(ContactService.findContactID("1001").getAddress().equals("1060 W Addison"));
    }

    // Test unique IDs
    @Test
    void testUniqueIDs(){
        // Add contacts to contactList
        ContactService.addContact("Robert", "Zimmerman", "5558675309",
                "1060 W Addison");
        ContactService.addContact("John", "Denver", "5556345789",
                "1410 S. Museum Campus Dr");
        ContactService.addContact("Paul", "Simon", "5555880300",
                "1901 W Madison St");
        ContactService.addContact("Ted", "Logan", "5558675309",
                "San Dimas, CA");
        ContactService.addContact("Bill S.", "Preston", "5558675309",
                "San Dimas, CA");

        // Check if first three IDs are unique
        assertTrue(ContactService.contactList.get(0).getContactID().equals("1001"));
        assertTrue(ContactService.contactList.get(1).getContactID().equals("1002"));
        assertTrue(ContactService.contactList.get(2).getContactID().equals("1003"));
    }

    // Test deleting contacts
    @Test
    void testDeleteContacts(){
        // Add contacts to contactList
        ContactService.addContact("Robert", "Zimmerman", "5558675309",
                "1060 W Addison");
        ContactService.addContact("John", "Denver", "5556345789",
                "1410 S. Museum Campus Dr");
        ContactService.addContact("Paul", "Simon", "5555880300",
                "1901 W Madison St");
        ContactService.addContact("Ted", "Logan", "5558675309",
                "San Dimas, CA");
        ContactService.addContact("Bill S.", "Preston", "5558675309",
                "San Dimas, CA");

        // Delete contact w/ ID "1005"
        ContactService.deleteContact("1005");

        // Check if ID "1005" returns null to ensure its deletion
        assertTrue(ContactService.findContactID("1005") == null);
    }


    /*
     * TEST UPDATING FIELDS
     */

    // Test changing first name
    @Test
    void testChangeFirstName(){
        // Add contacts for testing
        ContactService.addContact("Robert", "Zimmerman", "5558675309",
                "1060 W Addison");
        ContactService.addContact("John", "Denver", "5556345789",
                "1410 S. Museum Campus Dr");

        // Update first name of ID 1002 w/ method
        ContactService.updateFirstName("1002", "Bob");

        // Check if first name of ID 1002 was updated
        assertTrue(ContactService.findContactID("1002").getFirstName().equals("Bob"));
    }

    // Test changing last name
    @Test
    void testChangeLastName(){
        // Add contacts for testing
        ContactService.addContact("Robert", "Zimmerman", "5558675309",
                "1060 W Addison");
        ContactService.addContact("John", "Denver", "5556345789",
                "1410 S. Museum Campus Dr");

        // Update last name of ID 1002 w/ method
        ContactService.updateLastName("1002", "Dylan");

        // Check if last name of ID 1002 was updated
        assertTrue(ContactService.findContactID("1002").getLastName().equals("Dylan"));
    }

    // Test changing phone number
    @Test
    void testChangePhone(){
        // Add contacts for testing
        ContactService.addContact("Robert", "Zimmerman", "5558675309",
                "1060 W Addison");
        ContactService.addContact("John", "Denver", "5556345789",
                "1410 S. Museum Campus Dr");

        // Update phone number of ID 1002 w/ method
        ContactService.updatePhone("1002", "5556345789");

        // Check if phone number of ID 1002 was updated
        assertTrue(ContactService.findContactID("1002").getPhone().equals("5556345789"));
    }

    // Test changing address
    @Test
    void testChangeAddress(){
        // Add contacts for testing
        ContactService.addContact("Robert", "Zimmerman", "5558675309",
                "1060 W Addison");
        ContactService.addContact("John", "Denver", "5556345789",
                "1410 S. Museum Campus Dr");

        // Update address of ID 1002 w/ method
        ContactService.updateAddress("1002", "San Dimas, CA");

        // Check if address of ID 1002 was updated
        assertTrue(ContactService.findContactID("1002").getAddress().equals("San Dimas, CA"));
    }


    /*
     * TEST CHANGING NULL FIELDS
     */

    // Test changing w/ null first name
    @Test
    void testChangeNullFirstName(){
        Assertions.assertThrows(IllegalArgumentException.class, () -> {
            // Add contacts for testing
            ContactService.addContact("Robert", "Zimmerman", "5558675309",
                    "1060 W Addison");
            ContactService.addContact("John", "Denver", "5556345789",
                    "1410 S. Museum Campus Dr");

            // Update first name of ID 1002 w/ method
            ContactService.updateFirstName("1002", null); });
    }

    // Test changing w/ null last name
    @Test
    void testChangeNullLastName(){
        Assertions.assertThrows(IllegalArgumentException.class, () -> {
            // Add contacts for testing
            ContactService.addContact("Robert", "Zimmerman", "5558675309",
                    "1060 W Addison");
            ContactService.addContact("John", "Denver", "5556345789",
                    "1410 S. Museum Campus Dr");

            // Update first name of ID 1002 w/ method
            ContactService.updateLastName("1002", null); });
    }

    // Test changing w/ null phone number
    @Test
    void testChangeNullPhone(){
        Assertions.assertThrows(IllegalArgumentException.class, () -> {
            // Add contacts for testing
            ContactService.addContact("Robert", "Zimmerman", "5558675309",
                    "1060 W Addison");
            ContactService.addContact("John", "Denver", "5556345789",
                    "1410 S. Museum Campus Dr");

            // Update first name of ID 1002 w/ method
            ContactService.updatePhone("1002", null); });
    }

    // Test changing w/ null first name
    @Test
    void testChangeNullAddress(){
        Assertions.assertThrows(IllegalArgumentException.class, () -> {
            // Add contacts for testing
            ContactService.addContact("Robert", "Zimmerman", "5558675309",
                    "1060 W Addison");
            ContactService.addContact("John", "Denver", "5556345789",
                    "1410 S. Museum Campus Dr");

            // Update first name of ID 1002 w/ method
            ContactService.updateAddress("1002", null); });
    }


    /*
     * TEST DELETING/UPDATING W/ INVALID ID
     */

    // Test deleting contact w/ null ID
    @Test
    void testDeleteNullID(){
        Assertions.assertThrows(IllegalArgumentException.class, () ->{
            // Search nonexistent ID
            ContactService.deleteContact("5000"); });
    }

    // Test updating first name w/ null ID
    @Test
    void testUpdateNameNullID(){
        Assertions.assertThrows(IllegalArgumentException.class, () ->{
            // Search nonexistent ID
            ContactService.updateFirstName("5000", "Wrong"); });
    }

    // Test updating last name w/ null ID
    @Test
    void testUpdateLastNameNullID(){
        Assertions.assertThrows(IllegalArgumentException.class, () ->{
            // Search nonexistent ID
            ContactService.updateLastName("5000", "Wrong"); });
    }

    // Test updating phone w/ null ID
    @Test
    void testUpdatePhoneNullID(){
        Assertions.assertThrows(IllegalArgumentException.class, () ->{
            // Search nonexistent ID
            ContactService.updatePhone("5000", "5556345789"); });
    }

    // Test updating address w/ null ID
    @Test
    void testUpdateAddressNullID(){
        Assertions.assertThrows(IllegalArgumentException.class, () ->{
            // Search nonexistent ID
            ContactService.updateAddress("5000", "Wrong"); });
    }
}