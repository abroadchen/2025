//
// Created by Psy.C on 2025/11/27.
//

read n
n_squared=$((n * n))
three_n_squared=$((3 * n_squared))
sub_res=$((three_n_squard - n))
res=$((sub_res / 2))
echo $res