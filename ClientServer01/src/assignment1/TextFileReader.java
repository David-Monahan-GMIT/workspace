package assignment1;

/**
 * David Monahan Client Server Programming Assignment 2 08/10/2016
 * A simple program to create 4 JTextAreas and 4 buttons, 
 * Pressing the first button is the same as the last assignment - read in a text file and display it.
 * Pressing the second button reverses the contents of the first panel
 * Pressing the third button takes the text from the second panel and reverses each pair of words.
 * Pressing the fourth button will take the text from the first panel, remove all non alphabetic characters,
 * convert all words to lower case then count and display the number of times each word appears.
 */
import javax.swing.*;
import java.awt.*;
import java.util.List;
import java.util.Map;
import java.util.TreeMap;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;

public class TextFileReader extends JPanel implements ActionListener {

	static private final String newline = "\n";
	JButton openButton, reverseContentsButton, reversePairButton, countButton; // Declare
																				// the
																				// buttons
	JTextArea textLog, textLog2, textLog3, textLog4; // Declare the TextAreas

	File file;
	final JFileChooser fc = new JFileChooser();

	public TextFileReader() {
		super(new BorderLayout());

		// Create the log first, because the action listeners
		// need to refer to it.
		textLog = new JTextArea(40, 27);
		textLog.setMargin(new Insets(2, 2, 2, 2));
		textLog.setEditable(false);
		JScrollPane logScrollPane = new JScrollPane(textLog);

		// Create the log first, because the action listeners
		// need to refer to it.
		textLog2 = new JTextArea(40, 27);
		textLog2.setMargin(new Insets(2, 2, 2, 2));
		textLog2.setEditable(false);
		JScrollPane logScrollPane2 = new JScrollPane(textLog2);

		// Create the log first, because the action listeners
		// need to refer to it.
		textLog3 = new JTextArea(40, 27);
		textLog3.setMargin(new Insets(2, 2, 2, 2));
		textLog3.setEditable(false);
		JScrollPane logScrollPane3 = new JScrollPane(textLog3);

		// Create the log first, because the action listeners
		// need to refer to it.
		textLog4 = new JTextArea(40, 27);
		textLog4.setMargin(new Insets(2, 2, 2, 2));
		textLog4.setEditable(false);
		JScrollPane logScrollPane4 = new JScrollPane(textLog4);

		// Button to open a text file to display
		openButton = new JButton("Open A Text File");
		openButton.addActionListener(this);

		reverseContentsButton = new JButton("Reverse Contents");
		reverseContentsButton.addActionListener(this);

		reversePairButton = new JButton("Reverse Pair");
		reversePairButton.addActionListener(this);

		countButton = new JButton("Count");
		countButton.addActionListener(this);

		// For layout purposes, put the buttons in a separate panel
		JPanel buttonPanel = new JPanel();
		buttonPanel.add(openButton);
		buttonPanel.add(reverseContentsButton);
		buttonPanel.add(reversePairButton);
		buttonPanel.add(countButton);

		JPanel leftPanel = new JPanel();
		JPanel rightPanel = new JPanel();
		leftPanel.add(logScrollPane, BorderLayout.LINE_START);
		leftPanel.add(logScrollPane2, BorderLayout.LINE_END);
		rightPanel.add(logScrollPane3, BorderLayout.LINE_START);
		rightPanel.add(logScrollPane4, BorderLayout.LINE_END);

		// Add the buttons and the log to this panel.
		add(buttonPanel, BorderLayout.PAGE_START);
		add(leftPanel, BorderLayout.LINE_START);
		add(rightPanel, BorderLayout.LINE_END);

	}

	/**
	 * Implement the Action Listener Interface, Works by catching the event
	 * triggered from a button press and performing a different action for each
	 * one.
	 * 
	 * @return void
	 */
	public void actionPerformed(ActionEvent e) {

		/**
		 * Triggers when the Open Button is pressed, Opens a JFileChooser to
		 * pick the file to be read, then starts a SwingWorker to read in the
		 * file, line by line,in the background and publishes the results every
		 * 200 lines
		 */
		if (e.getSource() == openButton) {
			textLog.setText(""); // Clear the Text Area

			// use JFileChooser to get a file path
			int returnVal = fc.showOpenDialog(this);
			if (returnVal == JFileChooser.APPROVE_OPTION) {
				file = fc.getSelectedFile();
			}
			// create a SwingWorker
			new SwingWorker<String, String>() {
				// runs on a background thread.
				@Override
				protected String doInBackground() {
					// Use a buffered reader to read in a file line by line
					// and pass each line to process
					int count = 0;
					String lines = "";
					if (file != null) { // Fix null pointer exception
						try (BufferedReader br = new BufferedReader(new FileReader(file))) {
							String line;
							while ((line = br.readLine()) != null) {
								count++;
								lines += (line + newline);
								if (count >= 200) {
									publish(lines.toString());
									count = 0;
									lines = "";
								}
								// Thread.sleep(0,1); // Added 1ns sleep to the
								// thread to make it easier to see
							}
							publish(lines.toString());
						} catch (Exception e) {
							System.out.println("Exception: " + e.toString() + " Was Thrown");
						}
					}
					return ""; // Return an empty String
				}

				// runs on EDT, allowed to update gui
				protected void process(List<String> chunk) {
					// Appends each line of the txt file passed to the text log
					// area
					for (String line : chunk) {
						textLog.append(line);
					}

				}
			}.execute();
		}

		/**
		 * Triggers when the Reverse Contents Button is pressed, Takes the text
		 * from the first panel and splits it into lines, each line is then
		 * reversed and published in chunks of 200 to the second panel.
		 */
		if (e.getSource() == reverseContentsButton) {
			textLog2.setText(""); // Clear the Text Area
			// create a SwingWorker
			new SwingWorker<String, String>() {
				// runs on a background thread.

				@Override
				protected String doInBackground() {
					String[] lines = textLog.getText().split(newline);
					String chunk = "";
					int i = 0;
					for (String line : lines) {
						chunk += (new StringBuilder(line).reverse().toString()) + newline;
						i++;
						// Every 200 lines publish and reset
						if (i == 199) {
							publish(chunk);
							i = 0;
							chunk = "";
						}
					}
					publish(chunk); // Publish whatever is left
					return ""; // Return an empty String
				}

				// runs on EDT, allowed to update GUI
				protected void process(List<String> chunk) {
					// Appends each line of the txt file passed to the text log
					// area
					for (String line : chunk) {
						textLog2.append(line);
					}

				}
			}.execute();
		}

		/**
		 * Triggers when the Reverse Pair Button is pressed. Takes the text from
		 * the second JTextArea and splits it into lines, Each line is split
		 * into words and each pair of words is then reversed and appended to a
		 * new line. Lines are then pulished in chunks of 200.
		 */
		if (e.getSource() == reversePairButton) {
			textLog3.setText(""); // Clear the Text Area
			// create a SwingWorker
			new SwingWorker<String, String>() {
				// runs on a background thread.
				@Override
				protected String doInBackground() {
					if (textLog2.getText() != null) {
						String[] lines = textLog2.getText().split(newline);
						String chunk = "";
						int i = 0;
						for (String text : lines) {
							String[] words = text.split(" ");
							String pair = "";
							String line = "";
							int pairChecker = 1;
							for (String word : words) {
								if (!word.isEmpty() && word != "") {
									word = word.trim();
									pair += word + " ";
									if (pairChecker % 2 == 0) {
										line += (new StringBuilder(pair).reverse().toString());
										pair = "";
									}
									pairChecker++;
								}
							}
							chunk += (line += " " + pair + newline);
							pairChecker = 1;
							pair = "";
							line = "";
							i++;
							if (i == 199) {
								publish(chunk);
								chunk = "";
								i = 0;
							}
						}
						publish(chunk);
					}
					return ""; // Return an empty String
				}

				// runs on EDT, allowed to update gui
				protected void process(List<String> chunk) {
					// Appends each line of the txt file passed to the text log
					// area
					for (String line : chunk) {
						textLog3.append(line);
					}

				}

			}.execute();
		}
		/**
		 * Triggers when the Count Button is pressed. This will take the text
		 * from the first JTextArea and replace all characters that are not
		 * letters or a space with an empty string. The text is then split into
		 * words and each word is converted to lowercase. A comparison is then
		 * done using a TreeMap to see if the word has already been found. If it
		 * has increment its value by one otherwise create a new key with that
		 * word and initialise its value to 1. As before this is published in
		 * chunks of 200.
		 * 
		 */
		if (e.getSource() == countButton) {
			textLog4.setText(""); // Clear the Text Area
			// create a SwingWorker
			new SwingWorker<String, String>() {
				// runs on a background thread.
				@Override
				protected String doInBackground() {
					if (textLog.getText() != null) {
						String text = textLog.getText();
						// Replace all non alphabetic characters
						text = text.replaceAll("[^A-Za-z ]", " ");
						// Split out all the words using space as a delimiter
						String[] words = text.split(" ");
						
						TreeMap<String, Integer> treemap = new TreeMap<String, Integer>();
						for (String word : words) {
							// Make all Words lowercase
							word = word.toLowerCase();
							if (word.isEmpty()) {
								continue;
							} // Ignore any empty strings
							if (treemap.containsKey(word)) {
								// If the word has been seen already increment
								// its value
								treemap.put(word, (treemap.get(word) + 1));
							} else {
								// Otherwise create a key with that word and
								// start its value at 1
								treemap.put(word, 1);
							}
						}
						/**
						 * Publish the treeMap of key value pairs in 200 line
						 * chunks, The TreeMap will automatically sort them in a
						 * natural order, ie alphabetically by key.
						 */
						String chunk = "";
						int i = 0;
						for (Map.Entry<String, Integer> entry : treemap.entrySet()) {
							chunk += (entry.getKey() + " : " + entry.getValue() + newline);
							i++;
							if (i == 199) {
								publish(chunk);
								chunk = "";
								i = 0;
							}
						}
						publish(chunk);
					}
					return "";
				}

				protected void process(List<String> chunk) {
					// Appends each line of the txt file passed
					// to the text log area
					for (String line : chunk) {
						textLog4.append(line);
					}
				}
			}.execute();
		}
	}

	/**
	 * Create the GUI and show it. For thread safety, this method should be
	 * invoked from the event dispatch thread.
	 */
	private static void createAndShowGUI() {
		// Create and set up the window.
		JFrame frame = new JFrame("Text File Reader");
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

		// Add content to the window.
		frame.add(new TextFileReader());

		// Display the window.
		frame.pack();
		frame.setVisible(true);
	}

	public static void main(String[] args) {
		// Schedule a job for the event dispatch thread:
		// creating and showing this application's GUI.
		SwingUtilities.invokeLater(new Runnable() {
			public void run() {
				// Turn off metal's use of bold fonts
				UIManager.put("swing.boldMetal", Boolean.FALSE);
				createAndShowGUI();

			}
		});
	}

}