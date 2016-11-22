package library;

import java.util.List;


public class Account {
	private int accountNumber;
	private String history;
	private String openedDate;
	private AccountState state = AccountState.Closed;
	private Patron patron;
	private Library library;
	
	private List<Book> booksBorrowed;
	private List<Book> booksReserved;
	public Account(Patron patron,Library library, int accountNumber, String history, String openedDate, AccountState state, List<Book> booksBorrowed,
			List<Book> booksReserved) {
		super();
		this.patron =patron;
		this.library=library;
		this.accountNumber = accountNumber;
		this.history = history;
		this.openedDate = openedDate;
		this.state = state;
		this.booksBorrowed = booksBorrowed;
		this.booksReserved = booksReserved;		
	}
	public Library getLibrary() {
		return library;
	}
	public void setLibrary(Library library) {
		this.library = library;
	}
	public int getAccountNumber() {
		return accountNumber;
	}
	public void setAccountNumber(int accountNumber) {
		this.accountNumber = accountNumber;
	}
	public String getHistory() {
		return history;
	}
	public void setHistory(String history) {
		this.history = history;
	}
	public String getOpenedDate() {
		return openedDate;
	}
	public void setOpenedDate(String openedDate) {
		this.openedDate = openedDate;
	}
	public AccountState getState() {
		return state;
	}
	public void setState(AccountState state) {
		this.state = state;
	}
	public Patron getPatron() {
		return patron;
	}
	public void setPatron(Patron patron) {
		this.patron = patron;
	}
	public List<Book> getBooksBorrowed() {
		return booksBorrowed;
	}
	public void setBooksBorrowed(List<Book> booksBorrowed) {
		this.booksBorrowed = booksBorrowed;
	}
	public List<Book> getBooksReserved() {
		return booksReserved;
	}
	public void setBooksReserved(List<Book> booksReserved) {
		this.booksReserved = booksReserved;
	}
		

}
