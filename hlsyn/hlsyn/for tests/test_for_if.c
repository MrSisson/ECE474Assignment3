input UInt32 a, b

output UInt32 gcd

variable UInt32 areg, breg, gcdIters
variable UInt1 aGTb, aLTb, aNEQb

areg = a
breg = b

aNEQb = 1

for ( gcdIters = 1; aNEQb == 1; gcdIters = gcdIters + 1 ) {

   aGTb = areg > breg
   aLTb = areg < breg
   aNEQb = aGTb + aLTb

   if ( aGTb ) {
      areg = areg - breg
   }

   if ( aLTb ) {
      breg = breg - areg
   }

   aGTb = areg > breg
   aLTb = areg < breg
   aNEQb = aGTb + aLTb
}
   
gcd = areg

