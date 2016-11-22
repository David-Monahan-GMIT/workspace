import java.awt.BorderLayout;

import javax.swing.*;
public class HelloWorldSwing {

	public static void main(String[] args) {
		
		JFrame frame = new JFrame("HelloWorldSwing");
		final JLabel label = new JLabel("Hello World");
		final JLabel label2 = new JLabel("Goodbye World");
		frame.getContentPane().add(label, BorderLayout.PAGE_START);
		frame.getContentPane().add(label2, BorderLayout.PAGE_END);
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.pack();
		frame.setVisible(true);	
		
		Object[] options = {"Yes!", "No, I'll pass", "Well if I must"};
		int n = JOptionPane.showOptionDialog(
				frame, "Duke is a cartoon mascot. \n" +
				"Do you still want to cast your vote?",
				"A follow-up Question",
				JOptionPane.YES_NO_CANCEL_OPTION,
				JOptionPane.QUESTION_MESSAGE,
				null,
				options,
				options[2]);
		

				

	}

}
