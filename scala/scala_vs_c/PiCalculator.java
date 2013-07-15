class PiCalculator {
	public static void main(String []args) {
		long startTime = System.currentTimeMillis();
		int start = 0;
		int nrOfElements = 1000 * 1000 * 100;
		double acc = 0;
		for (int i = start; i < nrOfElements; ++i) {
			acc += (4.0 * (1 - (i % 2) * 2)) / (2 * i + 1);
		}
		System.out.println((System.currentTimeMillis() - startTime) + " ms");
		System.out.println(acc);
	}
}

