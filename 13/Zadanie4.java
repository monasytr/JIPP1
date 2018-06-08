package pl.poznan.put.lab12;

public class Zadanie4 {

	public static void main(String args[]) throws InterruptedException {
		Producer producer = new Producer();
		Consumer consumer1 = new Consumer("Consumer 1 ", producer);
		Consumer consumer2 = new Consumer("Consumer 2 ", producer);

		Thread p = new Thread(producer);
		Thread c1 = new Thread(consumer1);
		Thread c2 = new Thread(consumer2);

		p.start();
		c1.start();
		c2.start();

		Thread.sleep(3000);
		p.interrupt();
		p.join();
		System.out.println("\nProduced " + producer.getMessageCount()
				  + " messages.");

		Thread.sleep(500);
		c1.interrupt();
		c2.interrupt();
		c1.join();
		c2.join();
		System.out.println("\nConsumed " + (consumer1.getMessageCount()
				  + consumer2.getMessageCount()) + " messages.");

		System.out.println("\nMain thread stopped.");
	}
}
