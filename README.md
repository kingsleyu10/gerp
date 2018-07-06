# gerp
Optimized implementation of grep

Data Structures and Algorithms Used:
The data structures that I used for my program are: Hash tables & vectors
So I have a hash table as the undelying structure and at each index, there
are vectors with word structs. These structs hold information like the word
(both insensitive and sensitive), file path, line #, and sentence. In the
case of collisions, I am chaining at each index using vectors. So overall,
I used a hash table with vectors of vectors with word structs. I decided to
use vectors because there is already a built in stl for this. I liked using
vectors because they don't have to expand too many times which helps to save
space and add at constant time which increases runtime.

How I tested:
The biggest and one of the hardest implementation of my code was my vector
class. I encountered some difficulties where trying to find queries in files.
So I focused mainly on testing these functions to make sure that they work. Could it be
more in depth, yes, but I just wanted a generalization to make sure that the 
main functions were working properly. When it comes to testing my program, I
ran a gazzillion outputs, comparing most to the output text files given to us.
Ultimately, I am very proud of this program.
