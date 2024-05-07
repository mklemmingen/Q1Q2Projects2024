package src;

public class Producer implements Runnable{

    private ParkingLot parkingLot;

    private Car currentlyControlling;

    private boolean isControlling;

    public Producer(ParkingLot parkingLot) {
        this.parkingLot = parkingLot;
    }

    @Override
    public void run() {

        // if controlling car
            // move the current car a step closer to its parking spot by calling the move method of the car
                // if the car has reached its parking spot, remove its controlled status
                // and set is controlling variable of this class to false

        // else
            // call the produce method of the parking lot
    }
}
