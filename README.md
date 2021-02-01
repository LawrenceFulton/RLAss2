# RLAss2
There are different algorithms included in the code. First of all one can run the algorithm manually, meaning that one can adjust all the parameter in the terminal. Infromations how to do that can be seen in the terminal once running the program. To compile the code please run ``g++ -o a.out  main.cpp code/Agent.cpp code/Cat.cpp  code/World.cpp code/Location.cpp code/Mouse.cpp code/State.cpp`` and then one can run it with ``./a.out``. To replicate the data we are using for the analysis one has to set manual to false in line 651. This will run the function ``arena()`` which will then, using the optimal values for each agent and create a file called ``reward.txt`` which can then be used for post processing. The post processing is done in python using the files ``dataProcessing/processing.py`` and ``dataProcessing/processing_mean.py``.

## Summarise how to run:
compile: \
``g++ -o a.out  main.cpp code/Agent.cpp code/Cat.cpp  code/World.cpp code/Location.cpp code/Mouse.cpp code/State.cpp``

then run:\
``./a.out``
