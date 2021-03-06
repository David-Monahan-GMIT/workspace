package ticTacToe;

/**
 * David Monahan, Client Server Programming assignment 4
 * This is a server program for allowing to clients to play the game of TicTacToe
 * against each other. Both clients are handled as two separate threads which will 
 * take turns making moves until a draw happens or one wins. Either client can then
 * reset the game to start over by clicking on a reset button.
 */
import java.awt.*;
import java.awt.event.*;
import java.net.*;
import java.util.ArrayList;
import java.util.List;
import java.util.logging.FileHandler;
import java.util.logging.Level;
import java.util.logging.Logger;
import java.util.logging.SimpleFormatter;
import java.io.*;
import javax.swing.*;

public class TicTacToeServer extends JFrame {
	private char[] board;
	private JTextArea outputArea;
	private Player[] players;
	private ServerSocket server;
	private int currentPlayer, moveCount = 0;
	private final int PLAYER_X = 0, PLAYER_O = 1;
	private final char X_MARK = 'X', O_MARK = 'O';

	public static final Logger logger = Logger.getLogger(TicTacToeServer.class.getName());

	// set up tic-tac-toe server and GUI that displays messages
	public TicTacToeServer() {
		super("Tic-Tac-Toe Server");

		try {
			FileHandler fh = new FileHandler("c:\\Users\\Dave\\Desktop\\serverlog.log", true);
			fh.setFormatter(new SimpleFormatter());
			logger.addHandler(fh);

		} catch (java.io.IOException IOE) {
			logger.log(Level.SEVERE, IOE + "");
			IOE.printStackTrace();
		}

		board = new char[9];
		players = new Player[2];
		currentPlayer = PLAYER_X;

		// set up ServerSocket
		try {
			logger.log(Level.SEVERE, "Creating socket.");
			server = new ServerSocket(12345, 2);
		}

		// process problems creating ServerSocket
		catch (IOException ioException) {
			logger.log(Level.SEVERE, ioException + "");
			ioException.printStackTrace();
			System.exit(1);
		}

		// set up JTextArea to display messages during execution
		outputArea = new JTextArea();
		getContentPane().add(outputArea, BorderLayout.CENTER);
		outputArea.setText("Server awaiting connections\n");

		setSize(300, 300);
		setVisible(true);

	} // end TicTacToeServer constructor

	// wait for two connections so game can be played
	public void execute() {
		// wait for each client to connect
		for (int i = 0; i < players.length; i++) {

			// wait for connection, create Player, start thread
			try {
				players[i] = new Player(server.accept(), i);
				players[i].start();
			}

			// process problems receiving connection from client
			catch (IOException ioException) {
				logger.log(Level.SEVERE, ioException + "");
				ioException.printStackTrace();
				System.exit(1);
			}
		}

		// Player X is suspended until Player O connects.
		// Resume player X now.
		synchronized (players[PLAYER_X]) {
			players[PLAYER_X].setSuspended(false);
			players[PLAYER_X].notify();
		}

	} // end method execute

	// utility method called from other threads to manipulate
	// outputArea in the event-dispatch thread
	private void displayMessage(final String messageToDisplay) {
		// display message from event-dispatch thread of execution
		SwingUtilities.invokeLater(new Runnable() { // inner class to ensure GUI
													// updates properly

			public void run() // updates outputArea
			{
				outputArea.append(messageToDisplay);
				outputArea.setCaretPosition(outputArea.getText().length());
			}

		} // end inner class

		); // end call to SwingUtilities.invokeLater
	}

	// Determine if a move is valid. This method is synchronized because
	// only one move can be made at a time.
	public synchronized boolean validateAndMove(int location, int player) {
		// boolean moveDone = false;

		// while not current player, must wait for turn
		while (player != currentPlayer) {

			// wait for turn
			try {
				wait();
			}

			// catch wait interruptions
			catch (InterruptedException interruptedException) {
				logger.log(Level.SEVERE, interruptedException + "");
				interruptedException.printStackTrace();
			}
		}

		// if location not occupied, make move
		if (!isOccupied(location)) {
			// increment the move counter
			moveCount++;

			// set move in board array
			board[location] = currentPlayer == PLAYER_X ? X_MARK : O_MARK;

			// change current player
			currentPlayer = (currentPlayer + 1) % 2;

			if (!isGameOver())
				players[currentPlayer].otherPlayerMoved(location);
			else {
				if (gameWinner(X_MARK) || gameWinner(O_MARK)) {
					players[currentPlayer].gameOver(location);
				} else
					players[currentPlayer].draw(location);
			}

			notify(); // tell waiting player to continue

			// tell player that made move that the move was valid
			return true;
		} // tell player that made move that the move was not valid
		else
			return false;

	} // end method validateAndMove

	// determine whether location is occupied
	public boolean isOccupied(int location) {
		if (board[location] == X_MARK || board[location] == O_MARK)
			return true;
		else
			return false;
	}

	// place code in this method to determine whether game over
	public boolean isGameOver() {
		if (gameWinner(X_MARK) || gameWinner(O_MARK)) {
			return true;
		} else if (moveCount == 9) {
			return true;
		} else {
			return false;
		}
	}

	/**
	 * Declare a List of 3 element Integer arrays to enumerate all possible
	 * winning moves
	 * 
	 * @param mark
	 *            The character mark being used by the current active player
	 * @return True if someone has won, False otherwise
	 */
	public boolean gameWinner(char mark) {

		List<Integer[]> winners = new ArrayList<Integer[]>();
		winners.add(new Integer[] { 0, 1, 2 });
		winners.add(new Integer[] { 3, 4, 5 });
		winners.add(new Integer[] { 6, 7, 8 });
		winners.add(new Integer[] { 0, 3, 6 });
		winners.add(new Integer[] { 1, 4, 7 });
		winners.add(new Integer[] { 2, 5, 8 });
		winners.add(new Integer[] { 0, 4, 8 });
		winners.add(new Integer[] { 2, 4, 6 });
		for (Integer[] win : winners) {
			if (board[win[0]] == mark && board[win[1]] == mark && board[win[2]] == mark) {
				return true;
			}
		}
		return false; // this is left as an exercise
	}

	/**
	 * Resets the game board at the end of the game
	 */
	public void resetBoard() {
		for (int i = 0; i < board.length; i++)
			board[i] = '\u0000';
		moveCount = 0;
		logger.log(Level.SEVERE, "Board was reset at end of game");

	}

	public boolean resetPressed() {
		if (players[0].checkInput()) {
			if (players[0].readInput() == "reset") {
				players[1].sendString("reset");
				return true;
			}
		} else if (players[1].checkInput()) {
			if (players[1].readInput() == "reset") {
				players[0].sendString("reset");
				return true;
			}
		}
		return false;
	}

	public static void main(String args[]) {
		TicTacToeServer application = new TicTacToeServer();
		application.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		application.execute();
	}

	// private inner class Player manages each Player as a thread
	private class Player extends Thread {
		private Socket connection;
		private DataInputStream input;
		private DataOutputStream output;
		private int playerNumber;
		private char mark;
		protected boolean suspended = true;

		// set up Player thread
		public Player(Socket socket, int number) {
			playerNumber = number;

			// specify player's mark
			mark = (playerNumber == PLAYER_X ? X_MARK : O_MARK);

			connection = socket;

			// obtain streams from Socket
			try {
				input = new DataInputStream(connection.getInputStream());
				output = new DataOutputStream(connection.getOutputStream());
			}

			// process problems getting streams
			catch (IOException ioException) {
				ioException.printStackTrace();
				System.exit(1);
			}

		} // end Player constructor

		// send message that other player moved
		public void otherPlayerMoved(int location) {
			// send message indicating move
			try {
				output.writeUTF("Opponent moved");
				output.writeInt(location);
			}

			// process problems sending message
			catch (IOException ioException) {
				ioException.printStackTrace();
			}
		}

		public void gameOver(int location) {
			try {
				output.writeUTF("You Lose");
				output.writeInt(location);
			} catch (IOException ioException) {
				ioException.printStackTrace();
			}
		}

		public void draw(int location) {
			try {
				output.writeUTF("Draw");
				output.writeInt(location);
			} catch (IOException ioException) {
				ioException.printStackTrace();
			}
		}

		// control thread's execution
		public void run() {
			// send client message indicating its mark (X or O),
			// process messages from client
			try {
				displayMessage("Player " + (playerNumber == PLAYER_X ? X_MARK : O_MARK) + " connected\n");

				output.writeChar(mark); // send player's mark

				// send message indicating connection
				output.writeUTF(
						"Player " + (playerNumber == PLAYER_X ? "X connected\n" : "O connected, please wait\n"));

				// if player X, wait for another player to arrive
				if (mark == X_MARK) {
					output.writeUTF("Waiting for another player");

					// wait for player O
					try {
						synchronized (this) {
							while (suspended)
								wait();
						}
					}

					// process interruptions while waiting
					catch (InterruptedException exception) {
						exception.printStackTrace();
					}

					// send message that other player connected and
					// player X can make a move
					output.writeUTF("Other player connected. Your move.");
				}

				// while game not over
				while (!isGameOver()) {

					// get move location from client
					int location = input.readInt();

					if (validateAndMove(location, playerNumber)) {
						displayMessage("\nlocation: " + location);
						output.writeUTF("Valid move.");

					} else
						output.writeUTF("Invalid move, try again");
				}
				if (isGameOver()) {
					if (gameWinner(X_MARK) || gameWinner(O_MARK)) {
						output.writeUTF("You Win");
					} else {
						output.writeUTF("Draw");
					}

					//while (!resetPressed());

					resetBoard();

					// Reset The Players
					players = new Player[2];
					for (int i = 0; i < players.length; i++) {

						// wait for connection, create Player, start thread
						try {
							players[i] = new Player(server.accept(), i);
							players[i].start();
							currentPlayer = PLAYER_X;
						}

						// process problems receiving connection from client
						catch (IOException ioException) {
							ioException.printStackTrace();
							System.exit(1);
						}
					}

					// Player X is suspended until Player O connects.
					// Resume player X now.
					synchronized (players[PLAYER_X]) {
						players[PLAYER_X].setSuspended(false);
						players[PLAYER_X].notify();
					}
				}

			} // end try

			// process problems communicating with client
			catch (IOException ioException) {
				ioException.printStackTrace();
				System.exit(1);
			}
		}

		// end method run
		// set whether or not thread is suspended
		public boolean checkInput() {
			int temp = 0;
			try {
				temp = input.available();
			} catch (IOException e) {
				logger.log(Level.SEVERE, "" + e);
			}
			return (temp == 0 ? false : true);
		}

		// end method run
		// set whether or not thread is suspended
		public String readInput() {
			String temp = "";
			try {
				temp = input.readUTF();
			} catch (IOException e) {
				logger.log(Level.SEVERE, "" + e);
			}
			return temp;
		}

		// end method run
		// set whether or not thread is suspended
		public void sendString(String msg) {
			try {
				output.writeUTF(msg);
				;
			} catch (IOException e) {
				logger.log(Level.SEVERE, "" + e);
			}
		}

		public void setSuspended(boolean status) {
			suspended = status;
		}
	} // end class Player

}
