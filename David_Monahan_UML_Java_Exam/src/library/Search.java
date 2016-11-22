package library;

import java.util.List;

public interface Search {
	List<Book> findBookByTitle(String title);
	List<Book> findBookByAuthor(String author);
	Book findBookByISBN(String ISBN);
	

}
