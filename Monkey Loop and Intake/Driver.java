import java.util.ArrayList;
import java.util.Scanner;

public class Driver {

    //Initialize empty arrays to store new Dogs and Monkeys.
    private static ArrayList<Dog> dogList = new ArrayList<Dog>();
    private static ArrayList<Monkey> monkeyList = new ArrayList<Monkey>();

    //Initialize variables (if needed)
    static Scanner scnr = new Scanner(System.in);
    static int menuLoop = 0;

    //Main method
    public static void main(String[] args) {

        initializeDogList();
        initializeMonkeyList();

        //Create menu loop. If menuLoop == 1, quit.
        while (menuLoop != 1) {
            displayMenu();
        }
    }


    //Method to print menu options and accept user input to determine which functions to execute.
    public static void displayMenu() {
        //Prompt user input
        System.out.println("\n\n");
        System.out.println("\t\t\t\tRescue Animal System Menu");
        System.out.println("[1] Intake a new dog");
        System.out.println("[2] Intake a new monkey");
        System.out.println("[3] Reserve an animal");
        System.out.println("[4] Print a list of all dogs");
        System.out.println("[5] Print a list of all monkeys");
        System.out.println("[6] Print a list of all animals that are not reserved");
        System.out.println("[q] Quit application");
        System.out.println();
        System.out.println("Enter a menu selection");

        //Scan user input as a string, then executing the appropriate function.
        //If input is invalid, inform the user and prompt input again.
        String menuSelection = scnr.nextLine();
        switch (menuSelection) {
            case "1":
                intakeNewDog(scnr);
                break;
            case "2":
                intakeNewMonkey(scnr);
                break;
            case "3":
                reserveAnimal(scnr);
                break;
            case "4":
                printAnimals(1);
                break;
            case "5":
                printAnimals(2);
                break;
            case "6":
                printAnimals(3);
                break;
            case "q":
            case "Q":
                menuLoop = 1;
                break;
            default:
                System.out.println("Invalid input.");
                break;
        }
    }


    //List of dogs for testing
    public static void initializeDogList() {
        Dog dog1 = new Dog("Spot", "German Shepherd", "male", "1", "25.6", "05-12-2019", "United States", "in service", false, "United States");
        Dog dog2 = new Dog("Rex", "Great Dane", "male", "3", "35.2", "02-03-2020", "United States", "Phase I", false, "United States");
        Dog dog3 = new Dog("Bella", "Chihuahua", "female", "4", "25.6", "12-12-2019", "Canada", "in service", true, "Canada");
        Dog dog4 = new Dog("Bart", "Doberman", "male", "4", "300", "12-12-2019", "Mexico", "in service", true, "United States");


        dogList.add(dog1);
        dogList.add(dog2);
        dogList.add(dog3);
        dogList.add(dog4);
    }

    //List of monkeys for testing
    public static void initializeMonkeyList() {
        Monkey monkey1 = new Monkey("Bobo", "male", "Capuchin", "15", "20", "10 inches", "30 inches", "50 inches", "10-25-95", "United States", "Phase V", true, "United States");
        Monkey monkey2 = new Monkey("Sheila", "female", "Marmoset", "12", "500", "8 inches", "36 inches", "60 inches", "10-25-2016", "Canada", "in service", false, "Mexico");
        Monkey monkey3 = new Monkey("Rin Tin Tin", "male", "Macaque", "12", "200", "9 inches", "22 inches", "75 inches", "10-25-2016", "Mexico", "in service", false, "Canada");


        monkeyList.add(monkey1);
        monkeyList.add(monkey2);
        monkeyList.add(monkey3);
    }


    //Method to add a new dog, then place it into the array dogList.
    public static void intakeNewDog(Scanner scanner) {

        //Collect a new dog's name. If the dog's name is already in the dogList array, return to the initial menu.
        System.out.println("What is the dog's name?");
        String name = scanner.nextLine();
        for (Dog dog : dogList) {
            if (dog.getName().equalsIgnoreCase(name)) {
                System.out.println("\n\nThis dog is already in our system\n\n");
                return;
            }
        }

        //Collect new dog's information, up to a branch regarding reservation status.
        System.out.println("What is the dog's breed?");
        String breed = scanner.nextLine();
        System.out.println("What is the dog's gender?");
        String gender = scanner.nextLine();
        System.out.println("What is the dog's age?");
        String age = scanner.nextLine();
        System.out.println("What is the dog's weight?");
        String weight = scanner.nextLine();
        System.out.println("What day was the dog acquired?");
        String acquisitionDate = scanner.nextLine();
        System.out.println("In what country was the dog acquired?");
        String acquisitionCountry = scanner.nextLine();
        System.out.println("What is the dog's training status?");
        String trainingStatus = scanner.nextLine();


        //Prompt user input for whether the new dog is in service, then assign that value to the boolean "isReserved".
        //A "while" loop has been implemented to ensure the user's input is valid.
        int serviceLoop = 0;
        boolean isReserved = false;
        while (serviceLoop != 1) {
            System.out.println("Is this dog reserved? [Y]/[N]");
            String reservedCheck = scanner.nextLine();
            if (reservedCheck.equalsIgnoreCase("Y")) {
                isReserved = true;
                serviceLoop = 1;
            } else if (reservedCheck.equalsIgnoreCase("N")) {
                serviceLoop = 1;
            } else {
                System.out.println("Invalid input.");
            }
        }

        System.out.println("What is the dog's service country?");
        String serviceCountry = scanner.nextLine();

        //Create a new instance of dog with the collected information, and put it into the dogList array.
        Dog dog = new Dog(name, breed, gender, age, weight, acquisitionDate, acquisitionCountry, trainingStatus, isReserved, serviceCountry);
        dogList.add(dog);
    }


    // Complete intakeNewMonkey
    //Instantiate and add the new monkey to the appropriate list
    // For the project submission you must also validate the input
    // to make sure the monkey doesn't already exist and the species type is allowed
    public static void intakeNewMonkey(Scanner scanner) {

        //Collect a new monkey's name. If the dog's name is already in the list, return to the initial menu.
        System.out.println("What is the monkey's name?");
        String name = scanner.nextLine();
        for (Monkey monkey : monkeyList) {
            if (monkey.getName().equalsIgnoreCase(name)) {
                System.out.println("\n\nThis monkey is already in our system\n\n");
                return;
            }
        }

        //Collect new monkey's information, up to a branch regarding reservation status.
        //Start by checking whether the monkey's species is valid.
        //A "while" loop has been implemented to ensure the monkey's species is valid.
        int speciesLoop = 0;
        String species = "Not set";
        while (speciesLoop != 1) {
            System.out.println("What is the monkey's species?");
            System.out.println("Accepted species are: Capuchin, Guenon, Macaque, Marmoset, Squirrel Monkey, and Tamarin.");
            String speciesCheck = scanner.nextLine();
            if (speciesCheck.equalsIgnoreCase("Capuchin") || speciesCheck.equalsIgnoreCase("Guenon") ||
                    speciesCheck.equalsIgnoreCase("Macaque") || speciesCheck.equalsIgnoreCase("Marmoset") ||
                    speciesCheck.equalsIgnoreCase("Squirrel Monkey") || speciesCheck.equalsIgnoreCase("Tamarin")) {
                species = speciesCheck;
                speciesLoop = 1;
            } else {
                System.out.println("Invalid input.");
                return;
            }
        }

        System.out.println("What is the monkey's gender?");
        String gender = scanner.nextLine();
        System.out.println("What is the monkey's age?");
        String age = scanner.nextLine();
        System.out.println("What is the monkey's weight?");
        String weight = scanner.nextLine();
        System.out.println("What is the monkey's tail length?");
        String tailLength = scanner.nextLine();
        System.out.println("What is the monkey's height?");
        String height = scanner.nextLine();
        System.out.println("What is the monkey's body length?");
        String bodyLength = scanner.nextLine();
        System.out.println("What day was the monkey acquired?");
        String acquisitionDate = scanner.nextLine();
        System.out.println("In what country was the monkey acquired?");
        String acquisitionCountry = scanner.nextLine();
        System.out.println("What is the monkey's training status?");
        String trainingStatus = scanner.nextLine();

        //Prompt user input for whether the new monkey is in service, then assign that value to the boolean "isReserved".
        //A "while" loop has been implemented to ensure the user's input is valid.
        int serviceLoop = 0;
        boolean isReserved = false;
        while (serviceLoop != 1) {
            System.out.println("Is this monkey reserved? [Y]/[N]");
            String reservedCheck = scanner.nextLine();

            if (reservedCheck.equalsIgnoreCase("Y")) {
                isReserved = true;
                serviceLoop = 1;
            } else if (reservedCheck.equalsIgnoreCase("N")) {
                serviceLoop = 1;
            } else {
                System.out.println("Invalid input.");
            }
        }

        System.out.println("What is the monkey's service country?");
        String serviceCountry = scanner.nextLine();

        //Create a new instance of monkey with the collected information, and put it into the monkeyList array.
        Monkey monkey = new Monkey(name, gender, species, age, weight, tailLength, height, bodyLength, acquisitionDate, acquisitionCountry, trainingStatus, isReserved, serviceCountry);
        monkeyList.add(monkey);
    }


    //Method to change an animals' reservation status.
    public static void reserveAnimal(Scanner scanner) {
        //Initialize variables
        String reserveCheck;
        String nameCheck;
        int presentCheck = 0;

        //Check the animal type that the user would like to modify.
        System.out.println("Would you like to change the reservation status of a dog or monkey?");
        reserveCheck = scanner.nextLine();

        //If the animal is a dog, prompt user to input the dog's name.
        if (reserveCheck.equalsIgnoreCase("Dog")) {
            System.out.println("What is the name of the dog whose status you would like to change?");
            nameCheck = scanner.nextLine();

            //For each dog in the dogList, check if the user inputted name is present in the list.
            //If the inputted name is present, switch that dog's reservation status and return to initial menu.
            for (Dog dog : dogList) {
                if (dog.getName().equalsIgnoreCase(nameCheck)) {
                    if (!dog.getReserved()) {
                        dog.setReserved(true);
                        System.out.println("This dog is now reserved.");
                        return;
                    } else if (dog.getReserved()) {
                        dog.setReserved(false);
                        System.out.println("This dog is no longer reserved.");
                        return;
                    }
                }
            }
            System.out.println("There is no dog with that name.");
        }

        else if (reserveCheck.equalsIgnoreCase("Monkey")) {
            System.out.println("What is the name of the monkey whose status you would like to change?");
            nameCheck = scanner.nextLine();

            //For each monkey in the monkeyList, check if the user inputted name is present in the list.
            //If the inputted name is present, switch that monkey's reservation status and return to initial menu.
            for (Monkey monkey : monkeyList) {
                if (monkey.getName().equalsIgnoreCase(nameCheck)) {
                    if (!monkey.getReserved()) {
                        monkey.setReserved(true);
                        System.out.println("This monkey is now reserved.");
                        return;
                    } else if (monkey.getReserved()) {
                        monkey.setReserved(false);
                        System.out.println("This monkey is no longer reserved.");
                        return;
                    }
                }
            }
            System.out.println("There is no monkey with that name.");
        }
        else{
            System.out.println("invalid input.");
        }

    }


    //Method to print lists of animals in three different ways.
    //Lists of all dogs and monkeys will print the animals' names, status, acquisition country, and
    //reservation status as per specification.
    public static void printAnimals(int type) {

        System.out.println();
        switch(type){
            //Case 1: Print all dogs' names, training status, acquisition locations, and reservation status.
            case 1:
                System.out.println("All dogs:");
                System.out.println();
                for(Dog dog: dogList){
                    System.out.println("Name: " + dog.getName());
                    System.out.println("Training Status: " + dog.getTrainingStatus());
                    System.out.println("Acquisition Country: " + dog.getAcquisitionLocation());
                    if (!dog.getReserved()){
                        System.out.println("Available");
                    }
                    else if (dog.getReserved()){
                        System.out.println("Reserved");
                    }
                    System.out.println();
                }
                break;


            //Case 2: Print all monkeys' names, training status, acquisition locations, and reservation status.
            case 2:
                System.out.println("All monkeys:");
                System.out.println();
                for(Monkey monkey: monkeyList){
                    System.out.println("Name: " + monkey.getName());
                    System.out.println("Training Status: " + monkey.getTrainingStatus());
                    System.out.println("Acquisition Country: " + monkey.getAcquisitionLocation());
                    if (!monkey.getReserved()){
                        System.out.println("Available");
                    }
                    else if (monkey.getReserved()){
                        System.out.println("Reserved");
                    }
                    System.out.println();
                }
                break;


            //Case 3: Print all animals that are NOT reserved (or available) and fully trained
            case 3:
                System.out.println("All animals that are currently available and fully trained:");
                System.out.println();
                for (Dog dog: dogList){
                    if (!dog.getReserved()){
                        if (dog.getTrainingStatus().equalsIgnoreCase("in service")){
                            System.out.println("Name: " + dog.getName());
                            System.out.println("Training Status: " + dog.getTrainingStatus());
                            System.out.println("Acquisition Country: " + dog.getAcquisitionLocation());
                            System.out.println();
                        }
                    }
                }
                for (Monkey monkey: monkeyList){
                    if (!monkey.getReserved()){
                        if (monkey.getTrainingStatus().equalsIgnoreCase("in service")){
                            System.out.println("Name: " + monkey.getName());
                            System.out.println("Training Status: " + monkey.getTrainingStatus());
                            System.out.println("Acquisition Country: " + monkey.getAcquisitionLocation());
                            System.out.println();
                        }
                    }
                }
                break;
        }
    }
}

