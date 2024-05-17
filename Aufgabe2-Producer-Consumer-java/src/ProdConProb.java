public class ProdConProb {

    // declaring the parking lot
    protected static ParkingLot parkingLot;
    protected static int numberQuadrants;

    protected static int numberOfConsumers;
    protected static int numberOfProducers;

    protected static int capacity;

    public static void main(String[] args) {

        // parking lot size (influences layout of the GUI)
        numberQuadrants = 10; // keep hardcoded for awtFrontend
        capacity = numberQuadrants/2;

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

    public static void createParkingLot() {
        // creating the parking lot
        parkingLot = new ParkingLot(numberQuadrants, capacity, numberOfProducers, numberOfConsumers);
    }

    public static void startParkingLot() {
        // starting the parking lot
        parkingLot.start();
    }

    // getter

    public static ParkingLot getParkingLot() {
        return parkingLot;
    }

    public static int getNumberQuadrants() {
        return numberQuadrants;
    }

    public static int getCapacity() {
        return capacity;
    }

    public static int getNumberOfConsumers() {
        return numberOfConsumers;
    }

    public static void setParkingLot(ParkingLot parkingLot) {
        ProdConProb.parkingLot = parkingLot;
    }

    public static void setNumberQuadrants(int numberQuadrants) {
        ProdConProb.numberQuadrants = numberQuadrants;
    }

    public static void setCapacity(int capacity) {
        ProdConProb.capacity = capacity;
    }

    public static void setNumberOfConsumers(int numberOfConsumers) {
        ProdConProb.numberOfConsumers = numberOfConsumers;
    }

    public static void setNumberOfProducers(int numberOfProducers) {
        ProdConProb.numberOfProducers = numberOfProducers;
    }

    // ------------------ Parking Lot ------------------




}