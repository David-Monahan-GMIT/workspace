import java.awt.BorderLayout;
import java.util.ArrayList;
import java.util.List;

import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;

import net.miginfocom.swing.MigLayout;

public class Main {

	public static void main(String[] args) {
		JFrame frame = new JFrame("Gui Demo 0 - The concept of Mig");
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.setLocation(300, 400);
		List<JLabel> labels = new ArrayList<JLabel>();
		for(int i=1; i <= 10; i++) {
			labels.add(new JLabel("Label #" + i));
		}
/*		JLabel lab1 = new JLabel("Label #1");
		JLabel lab2 = new JLabel("Label #2");
		JLabel lab3 = new JLabel("Label #3");
		JLabel lab4 = new JLabel("Label #4");
		JLabel lab5 = new JLabel("Label #5");
		JLabel lab6 = new JLabel("Label #6");
		JLabel lab7 = new JLabel("Label #7");
		JLabel lab8 = new JLabel("Label #8");
		JLabel lab9 = new JLabel("Label #9");
		//JLabel lab10 = new JLabel("Label #10");
*/		
		JPanel panel = new JPanel(new MigLayout("debug"));
		int i=0;
		for (JLabel label : labels) {
			i++;
			if(i%3 == 0) {
				panel.add(label,"wrap");
			} else {
				panel.add(label);
			}
		}
		
/*		panel.add(lab1);
		panel.add(lab2);
		panel.add(lab3, "wrap");
		
		panel.add(lab4, "");
		panel.add(lab5, "wrap");
		panel.add(lab6, "span, center, wrap");
		
		panel.add(lab7);
		panel.add(lab8);
		panel.add(lab9, "wrap");*/
		
		frame.add(panel, BorderLayout.CENTER);
		frame.pack();
		frame.setVisible(true);
		

	}

}