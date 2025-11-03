//
// Created by Psy.C on 2025/11/3.
//

A := File standardInput readLine asNumber
B := A % 2
C := A % 4
if(B == 1,
  "no" println
)
if(B + 2 * C == 4,
  "yes" println
)
if(B + 2 * C == 0,
  "no" println
)
