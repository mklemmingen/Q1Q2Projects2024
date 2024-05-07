package src;

public class Consumer implements Runnable{

    private ParkingLot parkingLot;

    private Car currentlyControlling;

    private boolean isControlling;

    public Consumer(ParkingLot parkingLot) {
        this.parkingLot = parkingLot;
    }

    @Override
    public void run() {
        // if controlling car
            // move the current car a step closer to going over the buffer size 
            // by calling the move method of the car
                // if the car has overstepped, remove its controlled status, and remove it from the parking lot
                // and set controlling variable of this class to false

        // else
            // call the consume method of the parking lot

    }
}
