public class Main {

    // declaring the parking lot
    protected static ParkingLot parkingLot;

    // variables needed for the creation of the parkingLot
    // which are changed by frontends before create and start
    protected static int numberQuadrants; // size of the parking lot
    protected static int numberOfConsumers; // number of consumers threads
    protected static int numberOfProducers; // number of producer threads
    protected static int capacity; // capacity of the parking lot in cars it can hold

    public static void main(String[] args) {

        // parking lot size (influences layout of the GUI)
        numberQuadrants = 10; // keep hardcoded for awtFrontend
        capacity = numberQuadrants/2; // declared for a standard creation, changed by frontends

        // ------ frontend start

        // deciding which frontend ti use:
        // simple: awtFrontend.AwtGUI.load();
        // advanced: javaFXFrontend.JavaFXGUI.load(); // TODO

        // ask user for one or two: one being awt, two being javafx

        /* TODO: ADD HERE IF BUILDING JAVAFX FRONTEND
        System.out.println("Please enter 1 for AWT or 2 for JavaFX: ");
        int frontend;
        while (true) {
            frontend = input.nextInt();
            if (frontend == 49 || frontend == 50) {
                break;
            }
        }
        */ // for now, its just awt

        System.out.println("Starting Frontend...");
        AwtGUI.load(numberQuadrants);
    }

    // ------------------ Parking Lot ------------------

    /**
     * Creates a parking lot with the current class variables: 
     * number of quadrants, capacity, number of producers, and number of consumers.
     */
    public static void createParkingLot() {
        // creating the parking lot
        parkingLot = new ParkingLot(numberQuadrants, capacity, numberOfProducers, numberOfConsumers);
    }

    /**
     * Starts the parking lot.
     */
    public static void startParkingLot() {
        // starting the parking lot
        parkingLot.start();
    }

    // getter ------------------------------------------

    /**
     * Returns the parking lot.
     * 
     * @return the parking lot
     */
    public static ParkingLot getParkingLot() {
        return parkingLot;
    }

    
    /**
     * Returns the number of quadrants.
     *
     * @return the number of quadrants
     */
    public static int getNumberQuadrants() {
        return numberQuadrants;
    }

    /**
     * Returns the currently set capacity of the parkingLot (buffer size)
     *
     * @return the capacity of the parkingLot
     */
    public static int getCapacity() {
        return capacity;
    }

    /**
     * Returns the number of consumers.
     *
     * @return the number of consumers
     */
    public static int getNumberOfConsumers() {
        return numberOfConsumers;
    }

    // setter ------------------------------------------

    /**
     * Sets the parking lot for the producer-consumer problem.
     * 
     * @param parkingLot the parking lot to be set
     */
    public static void setParkingLot(ParkingLot parkingLot) {
        Main.parkingLot = parkingLot;
    }

    /**
     * Sets the number of quadrants.
     *
     * @param numberQuadrants the number of quadrants to set
     */
    public static void setNumberQuadrants(int numberQuadrants) {
        Main.numberQuadrants = numberQuadrants;
    }

    /**
     * Sets the capacity of the producer-consumer problem.
     * 
     * @param capacity the new capacity value
     */
    public static void setCapacity(int capacity) {
        Main.capacity = capacity;
    }

    /**
     * Sets the number of consumers for the producer-consumer problem.
     *
     * @param numberOfConsumers the number of consumers to set
     */
    public static void setNumberOfConsumers(int numberOfConsumers) {
        Main.numberOfConsumers = numberOfConsumers;
    }

    /**
     * Sets the number of producers.
     *
     * @param numberOfProducers the number of producers to set
     */
    public static void setNumberOfProducers(int numberOfProducers) {
        Main.numberOfProducers = numberOfProducers;
    }
}