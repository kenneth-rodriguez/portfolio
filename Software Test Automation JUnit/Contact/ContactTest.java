package Contact;

import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.Test;
import static org.junit.jupiter.api.Assertions.*;

class ContactTest {

    // Test Contact class under "normal" parameters
    @Test
    void testContactClass(){
        Contact testContact = new Contact("12345", "Robert", "Zimmerman", "5558675309",
                "1060 W Addison, Chicago, IL");
        assertTrue(testContact.getContactID().equals("12345"));
        assertTrue(testContact.getFirstName().equals("Robert"));
        assertTrue(testContact.getLastName().equals("Zimmerman"));
        assertTrue(testContact.getPhone().equals("5558675309"));
        assertTrue(testContact.getAddress().equals("1060 W Addison, Chicago, IL"));
    }


    /*
     * LENGTH TESTS
     */

    // Test w/ ID > 10 characters
    @Test
    void testLongID(){
        Assertions.assertThrows(IllegalArgumentException.class, () ->{
            new Contact("12345678910", "Robert", "Zimmerman", "5558675309", "1060 W Addison, Chicago, IL"); });
    }

    // Test w/ firstName > 10 characters
    @Test
    void testLongFirstName(){
        Assertions.assertThrows(IllegalArgumentException.class, () ->{
            new Contact("1234567890", "Bob Allen Dylan", "Zimmerman", "5558675309", "1060 W Addison, Chicago, IL"); });
    }

    // Test w/ lastName > 10 characters
    @Test
    void testLongLastName(){
        Assertions.assertThrows(IllegalArgumentException.class, () ->{
            new Contact("123456789", "Robert", "Bob Allen Dylan", "5558675309", "1060 W Addison, Chicago, IL"); });
    }

    // Test w/ phone > 10 characters
    @Test
    void testLongPhone(){
        Assertions.assertThrows(IllegalArgumentException.class, () ->{
            new Contact("123456789", "Robert", "Bob Allen Dylan", "555867530910",  "1060 W Addison, Chicago, IL"); });
    }

    // Test w/ phone < 10 characters
    @Test
    void testShortPhone(){
        Assertions.assertThrows(IllegalArgumentException.class, () ->{
            new Contact("123456789", "Robert", "Bob Allen Dylan", "8675309", "1060 W Addison, Chicago, IL"); });
    }

    // Test W/ Address Too long
    @Test
    void testLongAddress(){
        Assertions.assertThrows(IllegalArgumentException.class, () ->{
            new Contact("123456789", "Robert", "Bob Allen Dylan", "5558675309", "Llanfairpwllgwyngyllgogerychwyrndrobwllllantysiliogogogoch"); });
    }


    /*
     * TEST FOR NULL VALUES
     */

    // Test for null ID
    @Test
    void testNullID(){
        Assertions.assertThrows(IllegalArgumentException.class, () ->{
            new Contact(null, "Robert", "Zimmerman", "5558675309", "1060 W Addison, Chicago, IL"); });
    }

    // Test for null firstName
    @Test
    void testNullFirstName(){
        Assertions.assertThrows(IllegalArgumentException.class, () ->{
            new Contact("12345", null, "Zimmerman", "5558675309", "1060 W Addison, Chicago, IL"); });
    }

    // Test for null lastName
    @Test
    void testNullLastName(){
        Assertions.assertThrows(IllegalArgumentException.class, () ->{
            new Contact("12345", "Robert", null, "5558675309", "1060 W Addison, Chicago, IL"); });
    }

    // Test for null phone
    @Test
    void testNullPhone(){
        Assertions.assertThrows(IllegalArgumentException.class, () ->{
            new Contact("12345", "Robert", "Zimmerman", null, "1060 W Addison, Chicago, IL"); });
    }

    // Test for null Address
    @Test
    void testNullAddress(){
        Assertions.assertThrows(IllegalArgumentException.class, () ->{
            new Contact("12345", "Robert", "Zimmerman", "5558675309", null); });
    }


    /*
     * TEST FOR MUTATORS
     */

    // Test for changed firstName
    @Test
    void testChangeFirstName(){
            Contact testContact = new Contact("12345", "Robert", "Zimmerman", "5558675309",
                    "1060 W Addison, Chicago, IL");
            testContact.setFirstName("Bob");
            assertTrue(testContact.getFirstName().equals("Bob"));
    }

    // Test for changed lastName
    @Test
    void testChangeLastName(){
        Contact testContact = new Contact("12345", "Robert", "Zimmerman", "5558675309",
                "1060 W Addison, Chicago, IL");
        testContact.setFirstName("Dylan");
        assertTrue(testContact.getFirstName().equals("Dylan"));
    }

    // Test for changed phone
    @Test
    void testChangePhone(){
        Contact testContact = new Contact("12345", "Robert", "Zimmerman", "5558675309",
                "1060 W Addison, Chicago, IL");
        testContact.setFirstName("5558675308");
        assertTrue(testContact.getFirstName().equals("5558675308"));
    }

    // Test for changed address
    @Test
    void testChangeAddress(){
        Contact testContact = new Contact("12345", "Robert", "Zimmerman", "5558675309",
                "1060 W Addison, Chicago, IL");
        testContact.setAddress("1410 Museum Campus Dr, IL");
        assertTrue(testContact.getAddress().equals("1410 Museum Campus Dr, IL"));
    }


    /*
     * TEST FOR LONG MUTATORS
     */

    // Test for long changed firstName
    @Test
    void testChangeNullFirstName(){
        Assertions.assertThrows(IllegalArgumentException.class, () ->{
            Contact testContact = new Contact("12345", "Robert", "Zimmerman", "5558675309",
                    "1060 W Addison, Chicago, IL");
            testContact.setFirstName(null); });
    }

    // Test for long changed lastName
    @Test
    void testChangeNullLastName(){
        Assertions.assertThrows(IllegalArgumentException.class, () ->{
            Contact testContact = new Contact("12345", "Robert", "Zimmerman", "5558675309",
                    "1060 W Addison, Chicago, IL");
            testContact.setLastName(null); });
    }

    // Test for long changed phone
    @Test
    void testChangeLongPhone(){
        Assertions.assertThrows(IllegalArgumentException.class, () ->{
            Contact testContact = new Contact("12345", "Robert", "Zimmerman", "5558675309",
                    "1060 W Addison, Chicago, IL");
            testContact.setPhone("555867530910"); });
    }

    // Test for short changed phone
    @Test
    void testChangeShortPhone(){
        Assertions.assertThrows(IllegalArgumentException.class, () ->{
            Contact testContact = new Contact("12345", "Robert", "Zimmerman", "5558675309",
                    "1060 W Addison, Chicago, IL");
            testContact.setPhone("8675309"); });
    }

    // Test for long address
    @Test
    void testChangeLongAddress(){
        Assertions.assertThrows(IllegalArgumentException.class, () ->{
            Contact testContact = new Contact("12345", "Robert", "Zimmerman", "5558675309",
                    "1060 W Addison, Chicago, IL");
            testContact.setAddress("Llanfairpwllgwyngyllgogerychwyrndrobwllllantysiliogogogoch"); });
    }


    /*
     * TEST NULL MUTATORS
     */

    // Test for null changed firstName
    @Test
    void testChangeLongFirstName(){
        Assertions.assertThrows(IllegalArgumentException.class, () ->{
            Contact testContact = new Contact("12345", "Robert", "Zimmerman", "5558675309",
                    "1060 W Addison, Chicago, IL");
            testContact.setFirstName(null); });
    }

    // Test for null changed lastName
    @Test
    void testChangeLongLastName(){
        Assertions.assertThrows(IllegalArgumentException.class, () ->{
            Contact testContact = new Contact("12345", "Robert", "Zimmerman", "5558675309",
                    "1060 W Addison, Chicago, IL");
            testContact.setLastName(null); });
    }

    // Test for long changed phone
    @Test
    void testChangeNullPhone(){
        Assertions.assertThrows(IllegalArgumentException.class, () ->{
            Contact testContact = new Contact("12345", "Robert", "Zimmerman", "5558675309",
                    "1060 W Addison, Chicago, IL");
            testContact.setPhone(null); });
    }

    // Test for null address
    @Test
    void testChangeNullAddress(){
        Assertions.assertThrows(IllegalArgumentException.class, () ->{
            Contact testContact = new Contact("12345", "Robert", "Zimmerman", "5558675309",
                    "1060 W Addison, Chicago, IL");
            testContact.setAddress(null); });
    }
}