# Traceroute command

<p>Traceroute discovers the path packets take from your PC to a destination host by incrementally increasing the TTL value of IP packets. </p>


```
mkdir build
cd build
cmake ..
make

```

## How to work traceroute command

```

|PC|     | Router 1|   | Router 2|  | Router 3|  | Router 4|

ttl 1  -------->
       <--------

ttl 2  ------------------->
       <-------------------

ttl 3  ------------------------------->
       <------------------------------- 

ttl 4  ---------------------------------------------->
       <---------------------------------------------- 

```


## Example Output

```

    Traceroute command clone - Developed by Thush 

    Traceroute to google.com (142.250.192.78), 64 max hops

    1  192.168.8.1  2.88175 ms
    2  *
    3  *
    4  *
    5  125.214.190.38  39.8837 ms
    6  *
    7  *
    8  125.214.162.103  42.3736 ms
    9  125.214.162.70  52.9584 ms
    10  142.250.172.106  61.2706 ms
    11  192.178.110.221  47.4693 ms
    12  108.170.226.131  50.9385 ms
    13  142.250.192.78  48.4267 ms  (destination reached)

```