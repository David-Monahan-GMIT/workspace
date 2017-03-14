package classes;

public class Wind implements Instrument{
	
	protected int playCount = 0; // Protected to allow subclasses to access

	@Override
	public void play() {
		playCount ++;
		
	}

	@Override
	public void adjust() {
		playCount = 0;
		
	}
	
	@Override
	public String What() {
		// TODO Auto-generated method stub
		return "Wind";
	}

	@Override
	public int getPlayCount() {
		
		return playCount;
	}
}
