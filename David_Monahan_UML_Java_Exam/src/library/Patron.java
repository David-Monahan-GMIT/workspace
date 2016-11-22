package library;

import java.util.List;

public class Patron implements Search {
	private String name;
	private String address;
	private Account account;
	public Patron(String name, String address, Account account) {
		super();
		this.name = name;
		this.address = address;
		this.account = account;
	}
	
	// Extra fancy way of implementing without actually implementing
/*	// Show implementation of interfaces and association back through the classes
	public Book findBookByISBN(String ISBN) {
		return account.getLibrary().getCatalog().findBookByISBN(ISBN);
	}
	public List<Book> findBooksByAuthor(String author) {
		return account.getLibrary().getCatalog().findBookByAuthor(author);
	}
	*/
	
	
	public String getName() {
		return name;
	}
	public void setName(String name) {
		this.name = name;
	}
	public String getAddress() {
		return address;
	}
	public void setAddress(String address) {
		this.address = address;
	}
	public Account getAccount() {
		return account;
	}
	public void setAccount(Account account) {
		this.account = account;
	}

	// Implement Interfaces
	@Override
	public List<Book> findBookByTitle(String title) {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public List<Book> findBookByAuthor(String author) {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public Book findBookByISBN(String ISBN) {
		// TODO Auto-generated method stub
		return null;
	}

	

}
