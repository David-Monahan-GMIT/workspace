import java.awt.BorderLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.*;
public class SwingButtonExample {
	static JButton swingButton;
	static int numClicks =0;
	static JLabel label;
	final static String labelPrefix = "Number of Button Clicks: " ;

	public static void main(String[] args) {
		JFrame frame = new JFrame("Main");
		label = new JLabel(labelPrefix + numClicks);
		swingButton = new JButton("I'm a Swing button!");
		swingButton.addActionListener(new ActionListener() {		
		
				@Override
				public void actionPerformed(ActionEvent e) {
					if(e.getSource() == swingButton) {
						numClicks++;
						label.setText(labelPrefix +numClicks);
					}
					
				}
		});

		frame.getContentPane().add(label, BorderLayout.PAGE_END);
		frame.getContentPane().add(swingButton, BorderLayout.CENTER);
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.setSize(200,100);
		//frame.pack();
		frame.setVisible(true);	
		
	}


}
