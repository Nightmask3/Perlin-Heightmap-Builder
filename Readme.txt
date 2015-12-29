Perlin-Heightmap-Builder
A C++ project that allows creation of heightmaps using Perlin noise. These heightmaps can be imported into popular game engines and used to create terrain

Getting this to work is quite simple. The project is built using two open source libraries, and the application L3DT.

INSTRUCTIONS TO EXECUTE:

1) Install L3DT
2) Run "Gridgeneration.exe"
3) Choose mode of operation as necessary (description of modes provided below)
4) Recommended to use the machine learning mode.
5) When L3DT opens up, and the user must select which heightmap to import. Navigate to the directory of 'gridgeneration.exe'. By default the heightmap is called 'output.bmp'. After selection, the heightmap is displayed as is.
6) The last icon on the right of the toolbar is a '3D' button.
7) When clicked, it shows the user a 3D visualization of the heightmap itself.
8) Use this visualization to determine whether the output is satisfactory.
9) Close L3DT and the program will ask if the output is satisfactory or not.
10) If 'Yes' is selected, the program refines the output, and repeats steps 5 - 9.
11) If 'No' is selected, the program will ask what changes should be made to the heightmap. The changes are described in the nature of terrain desired i.e. Flat, Hilly, Mountainous.
After this, the steps 5 - 9 are repeated.
12) If 'Finalize' is selected L3DT opens up once again, asks which heightmap to import, and then what to name the exported Photoshop RAW file. 
13) The exported RAW file can be imported into Unreal, Unity etc. and used to create terrain.

Note : Whenever a change is made (Flat, Hilly, Mountainous) the initial output can look quite rough due to the random values being generated. 
This can be improved by selecting 'Yes' when presented the option. The machine learning kicks in here and adjusts values accordingly, smoothening out the randomness 

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