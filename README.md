#Hu Shell  

A basic shell implementation which recognizes commands, arguments, pipe and the && keyword  
To exit give ^d  

###Examples  

    >> ls -lart
Runs ls -lart

    >> ls && hush
Runs ls, runs an inner hush shell  

    >> ls -lart|wc &&ls
Runs ls, pipes to wc, later runs ls again
