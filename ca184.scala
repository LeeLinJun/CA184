object ca184
{
   def main(args: Array[String])
   {
    val iteration= args(0).toInt
    val freewayLength= 15
    var freeway=Array(0, 0, 1, 0, 0, 1, 1, 0, 1, 1, 1, 0, 0, 0, 1)


    def update(location:Int,freeway:Array[Int] ) =
      Array(0,0,0,1,1,1,0,1)(
        Integer.parseInt(Array(
           ((location:Int,freeway:Array[Int])=> if (location==0) freeway(14) else freeway(location-1))(location,freeway),
           freeway(location),
           ((location:Int,freeway:Array[Int])=> if (location==14) freeway(0) else freeway(location+1))(location,freeway)).mkString,2))


    def newfreeway(Present:Array[Int])=for (location <-Range(0,freewayLength).toArray) yield update(location,Present)

    for(t<-0 until iteration)  {
      freeway=newfreeway(freeway)
       for(x<-freeway) print(x)
       println()
    }
  }
}
