g++ -std=c++17 $1.cpp -o $1 && g++ -std=c++17 $2.cpp -o $2 && g++ -std=c++17 $3.cpp -o $3 && for ((i=0;i<1000;i++)) \
do
echo $i
./$1 > in
./$2 < in > out1
./$3 < in > out2
diff out1 out2
if [ $? -ne 0 ]
then
echo "------Input------" cat in
echo "------Output-----" cat out1
echo "-----Accepted----" cat out2
break
fi
done