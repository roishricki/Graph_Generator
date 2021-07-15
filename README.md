# Graph_Generator


C++ program to create Random Graphs according to a given Arrays of probabilities --> 3 different Arrays for 3 different attributes - Connectivity, Diamter, Isolated Vertex.

Values in the Array are chosen accroding to thresholds:

Threshold1 = Threshold3 = ln(v)/v.

Threshold2 = sqrt(2*threshold1).

Each Array has 10 values --> 5 values are smaller then the threshold & the other 5 are larger.

After creating a graph it will check 3 attributes:

Connectivity --> Chekcs how many graphs are connected.
Diameter --> Finds the diamter of a graph using BFS & counts how many graphs has diameter smaller or equal to 2.
Isolated Vertex  --> checks and counts how many graphs has at least 1 isolted vertex.
All results will be printed into a CSV files.

Example CSV files results: //500 graphs of 1000 vertices

![image](https://user-images.githubusercontent.com/66624113/125755507-da8b8b44-0efe-40ba-8ba6-b91e826cd6b6.png)
![image](https://user-images.githubusercontent.com/66624113/125755537-695b4c49-cf2e-4e1c-9d5d-971124bad992.png)
![image](https://user-images.githubusercontent.com/66624113/125755572-05ef9c84-bcfd-4668-9c62-a784cc17b6ac.png)
