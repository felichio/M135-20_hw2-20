# M135-20_hw2-20



## Build ##
#### 1. JavaFaster-C++Slower ####
##### Java #####
```shell
javac Ajava.java Node.java && java -Xmx10G LinkedList
```
##### C++ #####
```shell
g++ Ac++.cpp -o Ac++ && ./Ac++
```
#### 2. JavaSlower-C++Faster ####
##### Java #####
```shell
javac Bjava.java Node.java && java -Xmx10G LinkedList
```
##### C++ #####
```shell
g++ Bc++.cpp -o Bc++ && ./Bc++
```
#### 3. Java GC experiments ####
##### Java #####
```shell
javac Cjava.java Node.java && java -Xmx12G LinkedList
```
##### C++ #####
```shell
g++ Cc++.cpp -o Cc++ && ./Cc++
```

