package library;

import java.util.List;

public class Librarian implements Manage, Search {

	private String name;
	private String address;
	private String position;

	public Librarian(String name, String address, String position) {
		super();
		this.name = name;
		this.address = address;
		this.position = position;
	}

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

	public String getPosition() {
		return position;
	}

	public void setPosition(String position) {
		this.position = position;
	}

	// Implemented Interfaces
	// Alternatively associate the Librarian with a Library or Catalog and
	// access these methods through them
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

	@Override
	public void addBook(Book book) {
		// TODO Auto-generated method stub

	}

	@Override
	public void removeBook(Book book) {
		// TODO Auto-generated method stub

	}

}
