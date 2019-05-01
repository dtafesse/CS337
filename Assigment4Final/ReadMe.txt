Assignment 4

When expanding, program ends with this error 
	"terminate called after throwing an instance of 'std::out_of_range'
  	what():  basic_string::substr: __pos (which is 1) > this->size() (which is 0)
	Aborted"

I could not figure out why these keep happening, however I do not see any negative impacts, it archiving as planned. 

To run create archive text file do the following 
	./arch -c <source> <destination to place file to be created>

	(For my tests i just places to destination file in the current working directory.)

To expand archive,
	.arch -e <source where archive resides> <destination to create directory recursively>

