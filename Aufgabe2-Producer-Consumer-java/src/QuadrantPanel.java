import java.awt.Panel;
import javax.swing.JLabel;
import javax.swing.BoxLayout; 

class QuadrantPanel extends Panel {

    public JLabel carImageLabel;
    public JLabel statusCLabel;
    public JLabel statusPLabel;
    public JLabel numberOfCarsLabel;

    public QuadrantPanel(JLabel carImage, JLabel statusC, JLabel statusP) {

        this.carImageLabel = carImage;
        this.statusCLabel = statusC;
        this.statusPLabel = statusP;

        this.setLayout(new BoxLayout(this, BoxLayout.Y_AXIS)); 

        // size setting
        this.setSize(100, 100);
        carImageLabel.setSize(100, 100);
        statusCLabel.setSize(100, 100);
        statusPLabel.setSize(100, 100);

        this.add(this.statusCLabel);
        this.add(this.statusPLabel);
        this.add(this.carImageLabel);

        // create a JLabel numberOfCars
        this.numberOfCarsLabel = new JLabel("0");
        // make it red, make it right-aligned, put it on top of the panel, and invisible
        this.numberOfCarsLabel.setForeground(java.awt.Color.RED);
        this.numberOfCarsLabel.setHorizontalAlignment(JLabel.RIGHT);
        this.numberOfCarsLabel.setVerticalAlignment(JLabel.TOP);
        this.numberOfCarsLabel.setVisible(false);
        this.add(this.numberOfCarsLabel);
    }

    public void revilioWcar(boolean producerinsteadofconsumer) {
        this.carImageLabel.setVisible(true);
        if(producerinsteadofconsumer) {
            this.statusPLabel.setVisible(true);
        } else {
            this.statusCLabel.setVisible(true);
        }
    }

    public void revilioOstatus() {
        this.carImageLabel.setVisible(true);
    }

    public void obscuro() {
        this.carImageLabel.setVisible(false);
        this.statusPLabel.setVisible(false);
        this.statusCLabel.setVisible(false);
        this.numberOfCarsLabel.setVisible(false);
    }
}