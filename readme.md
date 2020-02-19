# AP BST implementation in modern C++

Authors: Matilde Castelli, Paolo Pulcini

Folder ```include``` contains all the header files for the binary search tree implementation:

* ```bst.h``` defines the ```bst``` class and contains the declaration of all the function and the implementation of the shortest ones so to inline them.
* ```iterator.h``` implements the class ```Iterator ``` and its methods
* ```Node.h``` defines the ```Node``` class and its methods
* ```methods.h``` contains the implementation of the bst's methods 

Folder `test` contains the file  ```main.cpp```  which task is to check almost all ```bst``` methods. 

Folder `documentation` contains a `doxygen` file used to generate the documentation in a `html` format.

File `benchmark.cpp` was removed after the meeting, but a picture is available in the report. 

A ```Makefile``` is used to compile automatically.  To obtain the executables `main` and the documentation, simply type ```make```. 

