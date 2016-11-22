import java.awt.BorderLayout;
import java.awt.Container;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.*;

public class MainFrame extends JFrame implements ActionListener{
	static int count = 0;
	JButton but1 ;
	JButton but2 ;
	JButton but3 ;
	JButton but4 ;
	JButton but5 ;
	
	public MainFrame() {
		super("My title goes here");
		setSize(300,300);
		
		but1 = new JButton("" + count);
		but2 = new JButton("" + count);
		but3 = new JButton("" + count);
		but4 = new JButton("" + count);
		but5 = new JButton("" + count);
		Container cp = this.getContentPane();
		but1.addActionListener(this);
		but2.addActionListener(this);
		but3.addActionListener(this);
		but4.addActionListener(this);
		but5.addActionListener(this);
		
		cp.add(but1,BorderLayout.NORTH);
		cp.add(but2,BorderLayout.CENTER);
		cp.add(but3,BorderLayout.SOUTH);
		cp.add(but4,BorderLayout.EAST);
		cp.add(but5,BorderLayout.WEST);
	}
	
	public void actionPerformed(ActionEvent e) {
		count++;
		but1.setText("" + count);	
		but2.setText("" + count);
		but3.setText("" + count);	
		but4.setText("" + count);	
		but5.setText("" + count);		
	}
}


