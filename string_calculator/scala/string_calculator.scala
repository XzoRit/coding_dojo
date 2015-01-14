/* run script with scala-2.11 <script-name> */
println("1,22,333".split(",").map(_.toInt).foldLeft(0)(_+_))
println("1,22,333".split(",").map{_.toInt}.foldLeft(0){_+_})
println("1,22,333".split(",").foldLeft(0)(_+_.toInt))
