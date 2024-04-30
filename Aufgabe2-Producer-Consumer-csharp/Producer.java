public class Producer extends Thread{
    private ParkingLot parkingLot;

    // thread ----------------------------------

    // the producer produces cars and sticks with one till it reaches 
    // its goal quadrant
    // if the capacity of the parking lot is reached, the producer waits to create a new car
    // if start is called, the producer starts its thread in regard to parkingLot-Buffer

    @Override
    public void start() {
        super.start();
    }

    // ---------------


    public Producer(ParkingLot parkingLot, boolean produceStandalone) {
        this.parkingLot = parkingLot;
    }

    public void produceCar(String carId, String carType) {
        Car car = new Car(carId, carType, parkingLot.getNumberQuadrants() - 1);
        parkingLot.park(car);
    }

    public void produceCar() {
        Car car = new Car(createCarID(), createCarType(), getGoalQuadrant());
        parkingLot.park(car);
    }

    private String createCarID() {
        return "Car" + (int) (Math.random() * 1000);
    }

    private String createCarType() {
        String[] carTypes = {"Sedan", "SUV", "Truck"};
        return carTypes[(int) (Math.random() * 3)];
    }

    private int getGoalQuadrant() {
        // randomize the goal quadrant
        return (int) (Math.random() * parkingLot.getNumberQuadrants());
    }
}
