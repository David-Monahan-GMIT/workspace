package library;

import java.util.ArrayList;
import java.util.List;

public class Catalog implements Search, Manage {
	private List<Book> books;
	private Library library;
	
	public Catalog(List<Book> books, Library library) {
		this.books = books;
		this.library = library;
	}

	@Override
	public void addBook(Book book) {
		books.add(book);
		
	}

	@Override
	public void removeBook(Book book) {
		if (books.contains(book)) {
			books.remove(book);
		}		
	}

	@Override
	public List<Book> findBookByAuthor(String author) {
		List<Book> foundBooks = new ArrayList();
		for (Book book : books) {
			if (book.getAuthors().contains(author)){
				foundBooks.add(book);
			}
		}
		return foundBooks;
	}

	@Override
	public Book findBookByISBN(String ISBN) {
		Book foundBook = null;
		for (Book book : books) {
			if (book.getISBN().contains(ISBN)){
				foundBook=book;
			}
		}
		return foundBook;
	}

	@Override
	public List<Book> findBookByTitle(String title) {
		List<Book> foundBooks = new ArrayList();
		for (Book book : books) {
			if (book.getTitle().contains(title)){
				foundBooks.add(book);
			}
		}
		return foundBooks;
	}

}
