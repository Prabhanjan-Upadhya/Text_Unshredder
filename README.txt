------------------------
TEXT UNSCRAMBLER
------------------------
List of Files
------------------------
- input.txt - Contains scrambled input data.
- input3.txt- Contains a second scrambled input data.
- dict.txt  - Contains the dataset for computing 4-gram dictionary.
- big.txt   - An alternate dataset for computing 4-gram dictionary. (optional)
- test.cpp  - Source code.
- Makefile  - To compile and clean up.


----------------------
Command Line Arguments
----------------------

- To compile:
             $make
- To run:
	     ./test.out


----------------------
Approach
----------------------

Algorithm used: Greedy.
Time Complexity: O(MN^2)
Space Complexity: O(MN) - Where M and N is the number of rows and columns in the scrambled input data.
                          Used for matrix transposition.

- As part of the precomputation, the size of the dictionary depends on the size of the dataset used.
- In order to have a reference of the valid words in English language, I used a reference dataset found
  from various online resources. Links can be found in the reference section.
- From the dataset, I created a 4-gram dictionary, and its associated frequency. This preprocessing takes
  majority computational time. 
- Initially, I select 2 strips which when joined has maximum probability of forming a valid 4-gram word.
- I find the best strip to be joined to the left or right of the intermediate result data.
- I repeat the above step until there are no other strips remaining.
- From the reordered data, I display the output.


---------------------
Extras
---------------------
- I also created additional 4-gram dictionaries using larger data sets, and tested the code using different 
  scrambled data, one of which I have included in the submissions.


--------------------
References
--------------------
http://textfiles.com/directory.html
http://norvig.com/big.txt
