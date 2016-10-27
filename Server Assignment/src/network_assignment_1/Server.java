package network_assignment_1;

/**
 *  David Monahan Client Server Programming Assignment
 *  This is a modification of the server code to run on a background thread 
 *  and publish any information to be sent. Also implements Socket Timeout.
 */

import java.io.*;
import java.net.*;
import java.util.List;
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

public class Server extends JFrame {
	private JTextField enterField;
	private JTextArea displayArea;
	private ObjectOutputStream output;
	private ObjectInputStream input;
	private ServerSocket server;
	private Socket connection;
	private int counter = 1;

	// set up GUI
	public Server() {
		super("Server");

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

	} // end Server constructor

	/**
	 * Uses SwingWorker to generate a background thread and then publish out any
	 * data to be transmitted
	 */
	public void runServer() {
		new SwingWorker<String, String>() {
			protected String doInBackground() {
				enterField.addActionListener(new ActionListener() {
					// send message to client
					public void actionPerformed(ActionEvent event) {
						publish(event.getActionCommand());
						enterField.setText("");
					}
				});

				// set up server to receive connections; process connections
				try {

					// Step 1: Create a ServerSocket.
					server = new ServerSocket(12345, 100);

					while (true) {

						try {
							// wait for connection to arrive, then display
							// connection info
							displayMessage("Waiting for connection\n");
							server.setSoTimeout(5000);
							int i = 0;
							while (true) {
								try {
									connection = server.accept();// allow server
																	// to accept
																	// connection
									break;
								} catch (SocketTimeoutException e) {
									System.out.println(e);
									i++;
									displayMessage("\nSocket Timed Out: " + i);
								}
							}
							displayMessage("Connection " + counter + " received from: "
									+ connection.getInetAddress().getHostName());

							// get streams to send and receive data
							// set up output stream for objects
							output = new ObjectOutputStream(connection.getOutputStream());
							output.flush(); // flush output buffer to send
											// header information

							// set up input stream for objects
							input = new ObjectInputStream(connection.getInputStream());

							displayMessage("\nGot I/O streams\n");

							// process connection with client
							// send connection successful message to client
							String message = "Connection successful";
							publish(message);

							// enable enterField so server user can send
							// messages
							setTextFieldEditable(true);

							do { // process messages sent from client

								// read message and display it
								try {
									message = (String) input.readObject();
									displayMessage("\n" + message);
								}

								// catch problems reading from client
								catch (ClassNotFoundException classNotFoundException) {
									displayMessage("\nUnknown object type received");
								}

							} while (!message.equals("CLIENT>>> TERMINATE"));

							// end method processConnection

						}

						// process EOFException when client closes connection
						catch (EOFException eofException) {
							System.err.println("Server terminated connection");
						}

						finally {
							closeConnection(); // Step 5: Close connection.
							++counter;
						}

					} // end while

				} // end try

				// process problems with I/O
				catch (IOException ioException) {
					ioException.printStackTrace();
				}

				return "";
			}

			// close streams and socket
			private void closeConnection() {
				displayMessage("\nTerminating connection\n");
				setTextFieldEditable(false); // disable enterField

				try {
					output.close();
					input.close();
					connection.close();
				} catch (IOException ioException) {
					ioException.printStackTrace();
				}
			}

			// send message to client
			protected void process(List<String> messages) {
				for (String message : messages) {
					// send object to client
					try {
						output.writeObject("SERVER>>> " + message);
						output.flush();
						displayMessage("\nSERVER>>> " + message);
					}

					// process problems sending object
					catch (IOException ioException) {
						displayArea.append("\nError writing object");
					}
				}
			}
		}.execute();
	} // end method runServer

	/**
	 * utility method called from other threads to manipulate displayArea in the
	 * event-dispatch thread
	 * 
	 * @param messageToDisplay
	 */
	private void displayMessage(final String messageToDisplay) {
		// display message from event-dispatch thread of execution
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

	/**
	 * utility method called from other threads to manipulate enterField in the
	 * event-dispatch thread
	 * 
	 * @param editable
	 */
	private void setTextFieldEditable(final boolean editable) {
		// display message from event-dispatch thread of execution
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
		Server application = new Server();
		application.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		application.runServer();
	}

} // end class Server
