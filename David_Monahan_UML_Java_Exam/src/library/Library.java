package library;

import java.util.List;

public class Library {
	private String name;
	private String address;
	private List<Account> accounts;
	private Catalog catalog;
	public Library(String name, String address, List<Account> accounts, Catalog catalog) {
		super();
		this.name = name;
		this.address = address;
		this.accounts = accounts;
		this.catalog = catalog;
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
	public List<Account> getAccounts() {
		return accounts;
	}
	public void setAccounts(List<Account> accounts) {
		this.accounts = accounts;
	}
	public Catalog getCatalog() {
		return catalog;
	}
	public void setCatalog(Catalog catalog) {
		this.catalog = catalog;
	}


}
