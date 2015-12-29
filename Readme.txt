Perlin-Heightmap-Builder
A C++ project that allows creation of heightmaps using Perlin noise. These heightmaps can be imported into popular game engines and used to create terrain

Getting this to work is quite simple. The project is built using two open source libraries, and the application L3DT.

INSTRUCTIONS TO EXECUTE:

1) Install L3DT
2) Run "Gridgeneration.exe"
3) Choose mode of operation as necessary (description of modes provided below)

Note : Whenever a change is made (Flat, Hilly, Mountainous) the initial output can look quite rough due to the random values being generated. 
This can be improved by selecting 'Yes' when presented the option. The machine learning kicks in here and adjusts values accordingly.

DOCUMENTATION:

1) Libnoise : http://libnoise.sourceforge.net/downloads/index.html

Follow the tutorial instructions as well to get a basic understanding of how to implement the library. As you might guess, libnoise provides the noise generating functions needed to create Perlin noise.

2) SFML : http://www.sfml-dev.org/

Used to create a GUI window to preview the created heightmaps.

3) L3DT : http://www.bundysoft.com/L3DT/downloads/standard.php

The free version is sufficient for the purposes of this project. It allows the user to preview the 3D model of their heightmap.

The application itself has two modes:

1) Machine Learning mode : The computer identifies the favourable category of content to be created using supervised learning methods (i.e. Yes or no response from the user) and refines the content to be created within that category alone. Suitable for use by novice or inexperienced users.

2) Advanced User mode : This mode allows the user to directly enter the argument values for the Perlin noise builder and creates the corresponding heightmap accordingly. Suitable for experienced users.

The noise builder function is explained here: http://libnoise.sourceforge.net/tutorials/tutorial3.html

Once the heightmap is generated, L3DT scripts Import and Export (which are included with the project) are executed respectively to import the heightmap to L3DT and allow the user to decide if it meets their needs.

If the output is not satisfactory the process reiterates. If it is found suitable L3DT terminates and the heightmap is generated in the build folder.