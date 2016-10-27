package network_assignment_1;

/**
 *  David Monahan Client Server Programming Assignment
 *  This is a modification of the client code to run on a background thread 
 *  and publish any information to be sent
 */
import java.io.*;
import java.net.*;
import java.util.List;
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

public class Client extends JFrame {
	private JTextField enterField;
	private JTextArea displayArea;
	private ObjectOutputStream output;
	private ObjectInputStream input;
	private String message = "";
	private String chatServer;
	private Socket client;

	// initialize chatServer and set up GUI
	public Client(String host) {
		super("Client");

		chatServer = host; // set server to which this client connects

		Container container = getContentPane();

		// create enterField and register listener
		enterField = new JTextField();
		enterField.setEditable(false);

		container.add(enterField, BorderLayout.NORTH);

		// create displayArea
		displayArea = new JTextArea();
		container.add(new JScrollPane(displayArea), BorderLayout.CENTER);

		setSize(300, 150);
		setVisible(true);

	} // end Client constructor

	// connect to server and process messages from server
	private void runClient() {
		new SwingWorker<String, String>() {
			protected String doInBackground() {

				enterField.addActionListener(new ActionListener() {

					// send message to server
					public void actionPerformed(ActionEvent event) {
						publish(event.getActionCommand());
						enterField.setText("");
					}
				});

				// connect to server, get streams, process connection
				try {
					displayMessage("Attempting connection\n");

					// create Socket to make connection to server
					client = new Socket(InetAddress.getByName(chatServer), 12345);

					// display connection information
					displayMessage("Connected to: " + client.getInetAddress().getHostName());

					// getStreams()

					// set up output stream for objects
					output = new ObjectOutputStream(client.getOutputStream());
					output.flush(); // flush output buffer to send header
									// information

					// set up input stream for objects
					input = new ObjectInputStream(client.getInputStream());

					displayMessage("\nGot I/O streams\n");

					// processConnection()
					// enable enterField so client user can send messages
					setTextFieldEditable(true);

					do { // process messages sent from server

						// read message and display it
						try {
							message = (String) input.readObject();
							displayMessage("\n" + message);
						}

						// catch problems reading from server
						catch (ClassNotFoundException classNotFoundException) {
							displayMessage("\nUnknown object type received");
						}

					} while (!message.equals("SERVER>>> TERMINATE"));

				}

				// server closed connection
				catch (EOFException eofException) {
					System.err.println("Client terminated connection");
				}

				// process problems communicating with server
				catch (IOException ioException) {
					ioException.printStackTrace();
				}

				finally {
					closeConnection(); // Step 4: Close connection
				}

				return "";
			}

			// close streams and socket
			private void closeConnection() {
				displayMessage("\nClosing connection");
				setTextFieldEditable(false); // disable enterField

				try {
					output.close();
					input.close();
					client.close();
				} catch (IOException ioException) {
					ioException.printStackTrace();
				}
			}

			// send message to server
			@Override
			protected void process(List<String> messages) {
				for (String message : messages) {
					// send object to server
					try {
						output.writeObject("CLIENT>>> " + message);
						output.flush();
						displayMessage("\nCLIENT>>> " + message);
					}

					// process problems sending object
					catch (IOException ioException) {
						displayArea.append("\nError writing object");
					}
				}
			}
		}.execute();
	} // end method runClient

	// utility method called from other threads to manipulate
	// displayArea in the event-dispatch thread
	private void displayMessage(final String messageToDisplay) {
		// display message from GUI thread of execution
		SwingUtilities.invokeLater(new Runnable() { // inner class to ensure GUI
													// updates properly

			public void run() // updates displayArea
			{
				displayArea.append(messageToDisplay);
				displayArea.setCaretPosition(displayArea.getText().length());
			}

		} // end inner class

		); // end call to SwingUtilities.invokeLater
	}

	// utility method called from other threads to manipulate
	// enterField in the event-dispatch thread
	private void setTextFieldEditable(final boolean editable) {
		// display message from GUI thread of execution
		SwingUtilities.invokeLater(new Runnable() { // inner class to ensure GUI
													// updates properly

			public void run() // sets enterField's editability
			{
				enterField.setEditable(editable);
			}

		} // end inner class

		); // end call to SwingUtilities.invokeLater
	}

	public static void main(String args[]) {
		Client application;

		if (args.length == 0)
			application = new Client("127.0.0.1");
		else
			application = new Client(args[0]);

		application.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		application.runClient();
	}

} // end class Client

/**************************************************************************
 * (C) Copyright 1992-2003 by Deitel & Associates, Inc. and * Prentice Hall. All
 * Rights Reserved. * * DISCLAIMER: The authors and publisher of this book have
 * used their * best efforts in preparing the book. These efforts include the *
 * development, research, and testing of the theories and programs * to
 * determine their effectiveness. The authors and publisher make * no warranty
 * of any kind, expressed or implied, with regard to these * programs or to the
 * documentation contained in these books. The authors * and publisher shall not
 * be liable in any event for incidental or * consequential damages in
 * connection with, or arising out of, the * furnishing, performance, or use of
 * these programs. *
 *************************************************************************/
