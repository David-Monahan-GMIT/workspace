package classes;

public class Stringed implements Instrument{

	private int playCount = 0;

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
		return "Stringed";
	}

	@Override
	public int getPlayCount() {
		
		return playCount;
	}

}
