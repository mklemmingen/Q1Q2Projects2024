package src;

public class Car {
    private String carId;
    private String carType;

    private int streetQuadrant;
    private int goalQuadrant;

    private boolean moving;

    private boolean usedByProducer;

    public Car(String carId, String carType, int goalQuadrant) {
        this.carId = carId;
        this.carType = carType;
        this.streetQuadrant = 0;
        this.moving = true;
        this.usedByProducer = true;
        this.goalQuadrant = goalQuadrant;
    }

    public String getCarId() {
        return carId;
    }

    public String getCarType() {
        return carType;
    }

    public void setCarId(String carId) {
        this.carId = carId;
    }

    public void setCarType(String carType) {
        this.carType = carType;
    }

    @Override
    public String toString() {
        return "Car{" +
                "carId='" + carId + '\'' +
                ", carType='" + carType + '\'' +
                '}';
    }

    public void start() {
        System.out.println("Car started");
        moving = true;
    }

    public void stop() {
        System.out.println("Car stopped");
        moving = false;
    }

    public void move() {
        moving = true;
        streetQuadrant++;
    }

    public int getStreetQuadrant() {
        return streetQuadrant;
    }

    public boolean getMoving() {
        return moving;
    }

    public boolean isUsedByProducer() {
        return usedByProducer;
    }

    public void setUsedByProducer(boolean usedByProducer) {
        this.usedByProducer = usedByProducer;
    }

    public int getGoalQuadrant() {
        return goalQuadrant;
    }

    public int createRandomGoalQuadrant(int numberQuadrants) {
        return (int) (Math.random() * numberQuadrants);
    }

    public void setStreetQuadrant(int streetQuadrant) {
        this.streetQuadrant = streetQuadrant;
    }

    public void setMoving(boolean moving) {
        this.moving = moving;
    }
}