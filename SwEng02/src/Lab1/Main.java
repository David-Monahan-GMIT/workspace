package Lab1;
import java.awt.*;
import java.awt.geom.Ellipse2D;
import java.awt.geom.Line2D;

import javax.swing.*;

public class Main {
	public static void main(String[] args) {

		JFrame frame = new JFrame();
		frame.setSize(300,300);
		frame.setTitle("An Empty Frame");
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		//frame.add(new RectangleComponent());
		String input = JOptionPane.showInputDialog("Enter a Number:");
		JPanel panel = new JPanel();
		panel.add(new JLabel("Your Number is: "+ input));
		frame.add(panel);
		frame.setVisible(true);		
	}
	
	@SuppressWarnings("serial")
	public static class RectangleComponent extends JComponent {
		public void paint(Graphics g) {
			Graphics2D g2 = (Graphics2D) g;
			Rectangle box = new Rectangle(50,50,80,40);
			Rectangle box2 = new Rectangle(100,100,50,100);
			g2.setColor(Color.BLUE);
			g2.draw(box);
			g2.fill(box);
			g2.setColor(Color.MAGENTA);
			g2.draw(box2);
			g2.fill(box2);
			g2.setColor(Color.RED);
			Ellipse2D.Double ellipse = new Ellipse2D.Double(150, 150, 100, 45);
			g2.draw(ellipse);
			g2.fill(ellipse);

			Line2D.Double line = new Line2D.Double(10,10, 100, 10);
			g2.draw(line);

			g2.drawString("Hello", 40, 10);
		}
	}	
}
