package guis;

import java.awt.BorderLayout;
import java.awt.Rectangle;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.File;

import javax.swing.*;

public class Main {

	static boolean toggle = false;
	final static JFileChooser fc = new JFileChooser();
	public static File file;

	public static void main(String[] args) {
		JFrame frame = new JFrame();
		frame.setTitle("GUI #1");
		frame.setSize(200,200);
		
		JPanel panel = new JPanel();
		JButton button = new JButton("Clicky!");
		button.addActionListener(
			new ActionListener() {
				@Override
				public void actionPerformed(ActionEvent arg0) {
					if(!toggle) {
						button.setLabel("Clicked!");
						toggle = !toggle;
					} else {
						button.setLabel("Clicky!");
						toggle = !toggle;
					}
					
				}
		});
		
		JButton button2 = new JButton("Click");
		button2.addActionListener(
			new ActionListener() {
				@Override
				public void actionPerformed(ActionEvent arg0) {
					if(!toggle) {
						button2.setLabel("Unclick");
						toggle = !toggle;
					} else {
						button2.setLabel("Click");
						toggle = !toggle;
					}
					
				}
		});
		
		JButton button3 = new JButton("Open File");
		button3.addActionListener(
			new ActionListener() {
				@Override
				public void actionPerformed(ActionEvent arg0) {
					int returnVal = fc.showOpenDialog(button3);
					if (returnVal == JFileChooser.APPROVE_OPTION) {
						file = fc.getSelectedFile();
					}
					
				}
		});


		frame.add(button, BorderLayout.NORTH);
		frame.add(button2, BorderLayout.SOUTH);
		frame.add(button3, BorderLayout.CENTER);
		//frame.setContentPane(panel);
		frame.setVisible(true);;
		
		button.setBounds(new Rectangle(10,10,100,50));
		//panel.setLayout(null);
		JLabel labelA = new JLabel("Hows it going GMIT?");
		JLabel labelB= new JLabel("Gows it going Galway?");

		frame.getContentPane();
			
	}

	
}
