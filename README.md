# A-Star-Search-on-TSP
Travelling Salesmen problem solved using A* Search algorithm for AI class.

# Running This Program

First off with the github basics:
```
* Clone this project into your local repository
* pull
```

There are two modes for this program.

1. User Interface Mode
2. Data Generator Mode

### The User Interface Mode

This mode allow you to specify which input you want to give to the algorithm.
You can choose from a list within randTSP folder.

Run these two commands from your shell.
```
* make ui
* ./ui
```

### The Data Generator Mode

This mode generates a list of number of nodes and the average node expanded for those many nodes.

Run these two commands from your shell.
```
* make data
* data
```

To generate both executable at the same time, you can just run
```
make
```

# Clean up

Now that you have ran the program, you might want to remove the executable and those pesky .d files.
Simply run
```
clean
```
