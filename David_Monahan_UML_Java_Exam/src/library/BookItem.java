package library;

import java.util.List;

public class BookItem extends Book {
	private String barcode;
	private String rfid;
	private Library library;
	private boolean isReferenceOnly = true;

	public BookItem(Library library, String iSBN, String title, String summary, String publisher, String publicationDate, int numPages,
			String language, List<Author> authors, String barcode, String rfid, boolean isReferenceOnly) {
		super(iSBN, title, summary, publisher, publicationDate, numPages, language, authors);
		
		this.barcode=barcode;
		this.rfid=rfid;
		this.isReferenceOnly = isReferenceOnly;
	}


}
