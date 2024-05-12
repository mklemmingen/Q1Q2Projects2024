/*
 Buffer as Queue
 */

import java.util.Queue;
import java.util.LinkedList;
import java.util.ArrayList;

import java.util.List;

public class ParkingLot{
    private Queue<Car> parkingLot;

    private List<Car> parkingLotList;

    private int numberQuadrants;

    private int capacity;

    private int currentNumberOfCars;

    // list of producer Threads
    private ArrayList<Thread> producerThreads;

    // list of consumer Threads
    private ArrayList<Thread> consumerThreads;


    public ParkingLot(int numberQuadrants, int capacity, int numberOfProducers, int numberOfConsumers) {

        // QUEUE
        parkingLot = new LinkedList<Car>();

        // LIST
        parkingLotList = new LinkedList<Car>();

        // create the producer and consumer ArrayList Threads of the given size
        producerThreads = new ArrayList<Thread>(numberOfProducers);

        // for each member of the producerThreads arraylist, create a new producer thread
        for (int i = 0; i < numberOfProducers; i++) {
            producerThreads.add(new Producer());
        }


        consumerThreads = new ArrayList<Thread>(numberOfConsumers);

        // for each member of the consumerThreads arraylist, create a new consumer thread
        for (int i = 0; i < numberOfConsumers; i++) {
            consumerThreads.add(new Consumer());
        }

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
                    Thread.sleep(500);
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
            Thread.sleep(175);
    
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
                    Thread.sleep(500);
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
                Thread.sleep(175);
            }
        }
    }

    // ------------------ Parking Lot ------------------

    public void start() {

        // for each member of the thread arraylists, start the thread

        System.out.println("Starting parking lot threads");

        for (Thread producerThread : producerThreads) {
            producerThread.start();
            System.out.println(" started a producer thread ");;
        }

        for (Thread consumerThread : consumerThreads) {
            consumerThread.start();
            System.out.println(" started a consumer thread ");
        }

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