package classes;

public class Percussion implements Instrument{

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
		return "Percussion";
	}

	@Override
	public int getPlayCount() {
		
		return playCount;
	}
	

}
