package library;

import java.util.List;

public abstract class Book {
	private String ISBN;
	private String title;
	private String summary;
	private String publisher;
	private String publicationDate;
	private int numPages;
	private String language;
	private List<Author> authors;
	
	public Book(String iSBN, String title, String summary, String publisher, String publicationDate, int numPages,
			String language, List<Author> authors) {
		super();
		ISBN = iSBN;
		this.title = title;
		this.summary = summary;
		this.publisher = publisher;
		this.publicationDate = publicationDate;
		this.numPages = numPages;
		this.language = language;
		this.authors = authors;
	}

	public String getISBN() {
		return ISBN;
	}

	public void setISBN(String iSBN) {
		ISBN = iSBN;
	}

	public String getTitle() {
		return title;
	}

	public void setTitle(String title) {
		this.title = title;
	}

	public String getSummary() {
		return summary;
	}

	public void setSummary(String summary) {
		this.summary = summary;
	}

	public String getPublisher() {
		return publisher;
	}

	public void setPublisher(String publisher) {
		this.publisher = publisher;
	}

	public String getPublicationDate() {
		return publicationDate;
	}

	public void setPublicationDate(String publicationDate) {
		this.publicationDate = publicationDate;
	}

	public int getNumPages() {
		return numPages;
	}

	public void setNumPages(int numPages) {
		this.numPages = numPages;
	}

	public String getLanguage() {
		return language;
	}

	public void setLanguage(String language) {
		this.language = language;
	}

	public List<Author> getAuthors() {
		return authors;
	}

	public void setAuthors(List<Author> authors) {
		this.authors = authors;
	}

}
