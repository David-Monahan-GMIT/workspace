package guis;

import java.awt.BorderLayout;

import javax.swing.*;
public class HelloWorldSwing {

	public static void main(String[] args) {
		JFrame frame = new JFrame("HelloWorldSwing");
		final JLabel label = new JLabel("Hello World");
		final JLabel label2 = new JLabel("Hello World");
		frame.getContentPane().add(label, BorderLayout.PAGE_START);
		frame.getContentPane().add(label2, BorderLayout.PAGE_END);
		
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.pack();
		frame.setVisible(true);

	}

}
