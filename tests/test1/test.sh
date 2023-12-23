make gen
make correct
make minkowskiSumTwoConvex

for ((i = 0;; ++i)); do
    echo $i
    ./gen $i > in
    ./correct < in > out1
    ./minkowskiSumTwoConvex  < in > out2
    diff out1 out2 || break
done