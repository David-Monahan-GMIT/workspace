package library;

import java.util.List;

public class Author {
	private String name;
	private String biography;
	List<Book> books;
	
	Author(String name, String biography) {
		this.name = name;
		this.biography = biography;
	}

	public String getName() {
		return name;
	}

	public void setName(String name) {
		this.name = name;
	}

	public String getBiography() {
		return biography;
	}

	public void setBiography(String biography) {
		this.biography = biography;
	}

	public List<Book> getBooks() {
		return books;
	}

	public void setBooks(List<Book> books) {
		this.books = books;
	}
	// Adds new Books to the author
	public void addBooks(List<Book> books) {
		this.books.addAll(books);
	}
	

}
