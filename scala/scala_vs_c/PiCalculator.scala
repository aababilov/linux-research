object PiCalculator extends App {
   val startTime = System.currentTimeMillis
   val start = 0
   val nrOfElements = 1000 * 1000 * 100
   var acc: Double = 0
   for (i <- start until (start + nrOfElements))
        acc += 4.0 * (1 - (i % 2) * 2) / (2 * i + 1)
   println((System.currentTimeMillis - startTime) + " ms")
   println(acc)
}
