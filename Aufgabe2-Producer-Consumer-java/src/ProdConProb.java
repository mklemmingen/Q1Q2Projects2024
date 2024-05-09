package src;

// GUI
import java.awt.*;

// parking lot list reading
import java.util.List;

import javax.swing.SwingUtilities;

import java.util.ArrayList;
import java.awt.Label;
import java.awt.Panel;
import java.awt.Image;
import java.awt.Toolkit;
import java.awt.Frame;
import java.awt.GridLayout;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import java.awt.Button;
import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;
import java.awt.FlowLayout;

public class ProdConProb {

    // Declaring the components of the GUI
    private Frame mainFrame;
    private Label headerLabel;

    private WidePanel parkingLotGUI;

    private Label statusLabel;
    private Panel controlPanel;

    // declaring the parking lot
    private static ParkingLot parkingLot;
    private static int numberQuadrants;

    // images
    private static Image carImage;
    private static Image statusC;
    private static Image statusP;

    // threads for the gui
    private static Thread parkingLotUpdater;

    public ProdConProb() {
        prepareGUI();
    }

    public static void main(String[] args) {

        // parking lot size (influences layout of the GUI)
        numberQuadrants = 10;
        int capacity = numberQuadrants/2;

        // loading images
        System.out.println("Loading images...");
        carImage = Toolkit.getDefaultToolkit().getImage("carImage.png");
        statusC = Toolkit.getDefaultToolkit().getImage("statusC.png");
        statusP = Toolkit.getDefaultToolkit().getImage("statusP.png");

        // system out if the images are null
        if (carImage == null || statusC == null || statusP == null) {
            System.out.println("Images are null.");
        } else {
            System.out.println("Images are not null. Images loaded.");
        }

        parkingLot = new ParkingLot(numberQuadrants, capacity);

        // start the parking lot. Starts the produce and consume threads of the parking lot.

        parkingLot.start();

        // ----- GUI ------

        ProdConProb main = new ProdConProb();
        main.showParkingLot();

        System.out.println("Starting GUI thread...");
        parkingLotUpdater.start();
    }

    private void prepareGUI() {
        // Creating main frame with size and layout
        mainFrame = new Frame("Parking Lot Simulation");
        mainFrame.setSize(800, 600);
        mainFrame.setLayout(new GridLayout(4, 1));

        // Adding a window listener to the main frame to close the application when the close button is clicked
        mainFrame.addWindowListener(
            new WindowAdapter() {

        // Add missing import for WidePanel if necessary

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
        parkingLotGUI.setLayout(new GridLayout(1, numberQuadrants));
        parkingLotGUI.setSize(800, 400);

        headerLabel.setVisible(true);
        statusLabel.setVisible(true);
        controlPanel.setVisible(true);
        parkingLotGUI.setVisible(true);

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
        parkingLotUpdater = new ParkingLotUpdater();

        // Set the visibility of the main frame to true
        mainFrame.setVisible(true);
    }

    // class that runs in its own thread and updates a GUI component of the parking lot
    class ParkingLotUpdater extends Thread {

        public void run() {

            while (true) {

                // clone the linked list of the parking lot
                List<Car> parkingLotList = parkingLot.getParkingLotList();

                // clear the parkingLOTGUI, so we can build a new one
                // using swingutilities to run the code in the event dispatch thread to avoid race conditions
                SwingUtilities.invokeLater(() -> {
                    parkingLotGUI.removeAll();

                    // iterate through parking lot quadrants, if card, draw car with image and image statusC->statusConsumer, 
                    // else draw image statusP->statusProducer
                    // all the objects that are not parked get a +1 in their streetQuadrant
                    for (int i = 0; i < numberQuadrants; i++) {
                        // create a LayeredImagesPanel object
                        int number = i+1;
                        boolean hasCar = false;
                        boolean hasStatus = false;
                        boolean producerStatus = false;

                        // iterate over the parking lot list
                        for (int j = 0; j < parkingLotList.size(); j++) {

                            // get the car object
                            Car car = parkingLotList.get(j);

                            // check if the car is parked in the current quadrant
                            if (car.getStreetQuadrant() == i) {
                                // draw car with image
                                hasCar = true;

                                // if car is being controlled by the producer, statusP true, 
                                // if car is not being controlled by the producer, and is moving, statusP false

                                if (car.isUsedByProducer()) {
                                    hasStatus = true;
                                    producerStatus = true;
                                } else {
                                    if (car.getIsMoving()) {
                                        hasStatus = true;
                                        producerStatus = false;
                                    }
                                }
                            }
                        }   

                        LayeredImagesPanel layeredImagesPanel = new LayeredImagesPanel(number, hasCar, 
                                                                    hasStatus, producerStatus, i);

                        // add this to the object of WidePanel
                        parkingLotGUI.add(layeredImagesPanel);
                    }

                
                    parkingLotGUI.revalidate();
                    parkingLotGUI.repaint();

                });
                // runs every 0.5 seconds
                try {
                    Thread.sleep(250);
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }
        }
    }

    class LayeredImagesPanel extends Container {
        private int x;
        private Image imageCar;
        private Image imageStatus;

        private Textpanel numberTXTPanel;

        public LayeredImagesPanel(int number, boolean hasCar, boolean hasStatus, boolean producerStatus,  int quadrant) {
            this.numberTXTPanel = new Textpanel(number);
            if(hasCar){
                this.imageCar = carImage;
            }
            if(hasStatus)
                this.imageStatus = producerStatus ? statusC : statusP;
            this.x = (numberQuadrants - quadrant)*mainFrame.getWidth()/numberQuadrants;
        }

        public void paint(Graphics g) {

            numberTXTPanel.paint(g, x);

            if(imageCar != null){
                g.drawImage(imageCar, x, 0, this);
            }

            if(imageStatus != null){
                g.drawImage(imageStatus, x, 0, this);
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

        @Override
        public void paint(Graphics g) {
            if(layeredImagesPanels.isEmpty()){
                return;
            }
            for (LayeredImagesPanel layeredImagesPanel : layeredImagesPanels) {
                layeredImagesPanel.paint(g);
            }
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
