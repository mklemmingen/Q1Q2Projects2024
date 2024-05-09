/*
 Buffer as Queue
 */

package src;

import java.util.Queue;
import java.util.LinkedList;

import java.util.List;

public class ParkingLot{
    private Queue<Car> parkingLot;

    private List<Car> parkingLotList;

    private int numberQuadrants;

    private int capacity;

    private int currentNumberOfCars;

    private Thread producer;
    private Thread consumer;

    public ParkingLot(int numberQuadrants, int capacity) {

        // QUEUE
        parkingLot = new LinkedList<Car>();

        // LIST
        parkingLotList = new LinkedList<Car>();

        this.numberQuadrants = numberQuadrants;

        this.capacity = capacity;
    }

    // producer and consumer inner classes ------------------- BUFFER callable METHODS + ACCESS CONTROLL METHOD 

    class Producer extends Thread {

        // variable to store the current car thats being moved till its goal
        private Car currentCar;
        private boolean isCarMoving = false;

        public void run() {
            while (true) {
                if(isCarMoving && currentCar != null) {

                    // if car is moving, move it till its goal
                    currentCar.move();
                    System.out.println("PRODUCER: Car " + currentCar.getCarId() + " is moving to quadrant " + currentCar  .getStreetQuadrant());

                    // if car is at goal, remove it from parking lot
                    if (currentCar.getStreetQuadrant() == currentCar.getGoalQuadrant()) {
                        isCarMoving = false;
                        // stop car, so its boolean isMoving is false
                        currentCar.stop();
                        // set the car to not used by producer
                        currentCar.setUsedByProducer(false);

                        // notify the consumer that a car has reached its goal
                        synchronized (this) {
                        notify();
                        }
                    }

                } else {
                    // ask buffer
                    try {
                        currentCar = produce();
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                    }
                    currentCar.start();
                    currentCar.setUsedByProducer(true);
                    isCarMoving = true;
                }

                // sleep for 1 second
                try {
                    Thread.sleep(1000);
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }
        }
    }

    public Car produce() throws InterruptedException {
        synchronized (this) {
            while (currentNumberOfCars >= capacity) {
                // wait for the consumer
                wait();
                System.out.println("Parking lot is full. Producer has to wait.");
                Thread.sleep(500);
            }
    
            // create a new car
            Car car = new Car(numberQuadrants);
            synchronized (car) {
                park(car);
                System.out.println("Car " + car.getCarId() + " is parked in quadrant " + car.getStreetQuadrant());
                car.setUsedByProducer(true);
            }
    
            // notify the consumer
            notify();
            Thread.sleep(1000);
    
            return car;
        }
    }

    class Consumer extends Thread {

        // variable to store the current car thats being moved till its beyond the parking lot
        private Car currentCar;
        private boolean isCarMoving = false;

        public void run() {
            while (true) {
                if (currentNumberOfCars > 0) {

                    // if no car is moving, get the first car from the parking lot
                    if (!isCarMoving) {

                        // call consume method to check buffer
                        try {
                            currentCar = consume();
                        } catch (InterruptedException e) {
                            e.printStackTrace();
                        }
                        currentCar.start();
                        currentCar.setUsedByProducer(false);
                        isCarMoving = true;

                    } else {
                        // if car is moving, move it till its beyond the parking lot (last quadrant)
                        currentCar.move();
                        System.out.println("CONSUMER: Car " + currentCar.getCarId() + " is moving to quadrant " + currentCar.getStreetQuadrant());

                        // if car is at last quadrant or above, remove it from parking lot
                        if (currentCar.getStreetQuadrant() >= numberQuadrants){
                            // call removeCar method to remove car from parking lot
                            currentCar.stop();
                            removeCar(currentCar);
                            isCarMoving = false;
                        }
                    }
                }

                // sleep for 1 second
                try {
                    Thread.sleep(1000);
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }
        }
    }

    public Car consume() throws InterruptedException {
        while (true) {
            synchronized (this) {
                while (parkingLot.size() == 0){
                    // wait for the producer
                    wait();
                }
    
                // go through the queue and check if any car has reached its goal, is not moving and
                // is not used by the producer

                for (Car car : parkingLot) {
                    synchronized(car){
                        if (car.hasReachedGoal() && !car.getIsMoving() && !car.isUsedByProducer()) {
                            // notify the producer
                            notify();
                            return car;
                        }
                    }
                }

                // sleep for 1 second
                Thread.sleep(1000);
            }
        }
    }

    // ------------------ Parking Lot ------------------

    public void start() {

        producer = new Producer();
        producer.start();

        consumer = new Consumer();
        consumer.start();
    }

    private void park(Car car) {

        parkingLot.add(car);
        parkingLotList.add(car);
        
        currentNumberOfCars++;
    }

    private void removeCar(Car car) {
        parkingLot.remove(car);
        parkingLotList.remove(car);
        currentNumberOfCars--;
    }

    // --------------------------------------------------

    public void addCar(Car car) {
        parkingLot.add(car);
        parkingLotList.add(car);
        currentNumberOfCars++;
    }

    public void printParkingLot() {
        for (Car car : parkingLot) {
            System.out.println(car);
        }
    }

    public int getNumberQuadrants() {
        return numberQuadrants;
    }

    public int getCapacity() {
        return capacity;
    }

    public List<Car> getParkingLotList() {
        return parkingLotList;
    }
}