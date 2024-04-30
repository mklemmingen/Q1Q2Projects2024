
import Consumer;
import Producer;
import ParkingLot;
import Car;

// GUI
import java.awt.*;
import java.awt.event.*;
import java.awt.image.*;

// parking lot list reading
import java.util.List;
import java.util.ArrayList;

public class Main {

    // Declaring the components of the GUI
    private Frame mainFrame;
    private Label headerLabel;
    private WidePanel parkingLotGUI;
    private Label statusLabel;
    private Panel controlPanel;

    // declaring the parking lot
    private static ParkingLot parkingLot;
    private int numberQuadrants;

    // images
    private static Image carImage;
    private static Image statusC;
    private static Image statusP;

    public Main() {
        prepareGUI();
    }

    public static void main(String[] args) {

        // parking lot size (influences layout of the GUI)
        int numberQuadrants = 10;
        int capacity = numberQuadrants/2;

        // loading images
        carImage = Toolkit.getDefaultToolkit().getImage("carImage.jpg");
        statusC = Toolkit.getDefaultToolkit().getImage("statusC.jpg");
        statusP = Toolkit.getDefaultToolkit().getImage("statusP.jpg");

        parkingLot = new ParkingLot(numberQuadrants, capacity);

        // create the producer and consumer objects with parkingLot object shared between them
        Producer producer = new Producer(parkingLot);
        Consumer consumer = new Consumer(parkingLot);

        // create the producer and consumer threads
        producer.start();
        consumer.start();

        // ----- GUI ------

        Main main = new Main();
        main.showParkingLot();

    }

    private void prepareGUI() {
        // Creating main frame with size and layout
        mainFrame = new Frame("Parking Lot Simulation");
        mainFrame.setSize(400, 400);
        mainFrame.setLayout(new GridLayout(4, 1));

        // Adding a window listener to the main frame to close the application when the close button is clicked
        mainFrame.addWindowListener(
            new WindowAdapter() {

                public void windowClosing(WindowEvent windowEvent) {
                    System.exit(0);
                }
            }
        );
        
        // Creating the header label and setting its alignment
        headerLabel = new Label();
        headerLabel.setAlignment(Label.CENTER);

        // Creating the status label and setting its alignment and size
        statusLabel = new Label();
        statusLabel.setAlignment(Label.CENTER);
        statusLabel.setSize(350, 100);

        // Creating the control panel and setting its layout
        controlPanel = new Panel();
        controlPanel.setLayout(new FlowLayout());

        // creating parkingLOTGUI
        parkingLotGUI = new WidePanel();

        // Adding the header label, control panel, and status label to the main frame
        mainFrame.add(headerLabel);
        mainFrame.add(parkingLotGUI);
        mainFrame.add(controlPanel);
        mainFrame.add(statusLabel);

        // Making the main frame visible
        mainFrame.setVisible(true);
    }

    private void showParkingLot() {
        // Set the text of the header label
        headerLabel.setText("Parking Lot Simulation Ongoing...");

        // Create the buttons and add action listeners to them
        Button exitButton = new Button("EXIT");

        exitButton.addActionListener(
            new ActionListener() {

                public void actionPerformed(ActionEvent e) {
                    // Close the application when the EXIT button is clicked
                    System.exit(0);
                }
            }
        );

        Button cancelButton = new Button("Cancel");

        cancelButton.addActionListener(
            new ActionListener() {

                public void actionPerformed(ActionEvent e) {
                    // Set the text of the status label when the Cancel button is clicked
                    statusLabel.setText("Cancel Button clicked.");
                }
            }
        );
        // Add buttons to the control panel
        controlPanel.add(exitButton);
        // CANCEL BUTTON NOT ADDED, KEPT AS EXAMPLE FOR STATUS LABEL

        // create ParkingLotUpdater object
        ParkingLotUpdater parkingLotUpdater = new ParkingLotUpdater();
        parkingLotUpdater.start();

        // Set the visibility of the main frame to true
        mainFrame.setVisible(true);
    }

    // class that runs in its own thread and updates a GUI component of the parking lot
    class ParkingLotUpdater extends Thread {
        public void run() {

            // runs every 0.5 seconds
            try {
                Thread.sleep(500);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }

            // get list object of parkingLot
            List<Car> parkingLotList = parkingLot.getParkingLotList();

            // clear the parkingLOTGUI
            parkingLotGUI.removeAll();

            // iterate through parking lot quadrants, if card, draw car with image and image statusC->statusConsumer, 
            // else draw image statusP->statusProducer
            // all the objects that are not parked get a +1 in their streetQuadrant
            for (int i = 0; i < numberQuadrants; i++) {
                // create a LayeredImagesPanel object
                int number = i+1;
                boolean hasCar = false;
                boolean hasStatus = false;
                if (parkingLotList.get(i) != null) {
                    Car car = parkingLotList.get(i);
                    // draw car with image
                    hasCar = true;

                    if (car.getStreetQuadrant() == car.getGoalQuadrant()) {
                        car.stop();
                    } else {
                        car.move();
                        hasStatus = true;
                    }
                }

                LayeredImagesPanel layeredImagesPanel = new LayeredImagesPanel(number, hasCar, hasStatus, i);

                // add this to the object of WidePanel
                parkingLotGUI.add(layeredImagesPanel);
            }
        }
        
    }

    class WidePanel extends Panel {
        // consists out of numberQuadrants*LayeredImagesPanel
        // and fills up an entire row of the main frame

        private List<LayeredImagesPanel> layeredImagesPanels = new ArrayList<>();

        public WidePanel() {
        }

        // clear list
        public void removeAll() {
            layeredImagesPanels.clear();
        }

        // add a LayeredImagesPanel object to the list
        public void add(LayeredImagesPanel layeredImagesPanel) {
            layeredImagesPanels.add(layeredImagesPanel);
        }

        public void paint(Graphics g) {
            for (LayeredImagesPanel layeredImagesPanel : layeredImagesPanels) {
                layeredImagesPanel.paint(g);
            }
        }
    }

    class LayeredImagesPanel extends Panel {
        private int x;
        private Image imageCar;
        private Image imageStatus;

        private Textpanel numberTXTPanel;

        public LayeredImagesPanel(int number, boolean hasCar, boolean hasStatus, int quadrant) {
            this.numberTXTPanel = new Textpanel(number);
            this.imageCar = carImage;
            this.imageStatus = hasStatus ? statusC : statusP;
            this.x = (Main.this.numberQuadrants - quadrant)*mainFrame.getWidth()/Main.this.numberQuadrants;
        }

        public void paint(Graphics g) {
            numberTXTPanel.paint(g, x);
            g.drawImage(imageCar, x, 0, this);
            g.drawImage(imageStatus, x, 0, this);
        }
    }

    class Textpanel extends Panel {
        // just a text inside the layeredImagesPanel that displays the number of the quadrant
        private String numberString;

        public Textpanel(int number) {
            this.numberString = Integer.toString(number);
        }

        public void paint(Graphics g, int x) {
            g.drawString(numberString, x, 0);
        }
    }
}
