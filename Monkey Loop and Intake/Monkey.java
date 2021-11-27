
public class Monkey extends RescueAnimal {

    //Initialize new variables exclusive to the "Monkey" class
    private String tailLength;
    private String height;
    private String bodyLength;
    private String species;


    //Constructor: collects user input during the creation of a new Monkey object,
    //and then sets those values to that input.
    public Monkey(String name, String gender, String species, String age,
                  String weight, String tailLength, String height, String bodyLength,
                  String acquisitionDate, String acquisitionCountry,
                  String trainingStatus, boolean reserved, String inServiceCountry) {
        setName(name);
        setSpecies(species);
        setGender(gender);
        setAge(age);
        setWeight(weight);
        setTailLength(tailLength);
        setHeight(height);
        setBodyLength(bodyLength);
        setAcquisitionDate(acquisitionDate);
        setAcquisitionLocation(acquisitionCountry);
        setTrainingStatus(trainingStatus);
        setReserved(reserved);
        setInServiceCountry(inServiceCountry);
    }

    //Accessor Method for Tail Length
    public String getTailLength() {
        return tailLength;
    }

    //Mutator Method for Tail Length
    public void setTailLength(String tailLength){
        this.tailLength = tailLength;
    }

    //Accessor Method for Height
    public String getHeight() {
        return height;
    }

    ///Mutator Method for Height
    public void setHeight(String height){
        this.height = height;
    }

    //Accessor Method for Body Length
    public String getBodyLength() {
        return bodyLength;
    }

    //Mutator Method for Body Length
    public void setBodyLength(String bodyLength){
        this.bodyLength = bodyLength;
    }

    // Accessor Method for Species
    public String getSpecies() {
        return species;
    }

    // Mutator Method for Species
    public void setSpecies(String species) {
        this.species = species;
    }


}
