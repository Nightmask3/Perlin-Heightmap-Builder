/*
 * Heightmap.cpp
 *
 *  Created on: 26-Feb-2015
 *      Author: Nightmask3
 */

#include <iostream.h>
#include <stdio.h>
#include <noise.h>
#include <noiseutils.h>
#include <System.hpp>
#include <Graphics.hpp>
#include <Main.hpp>
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

using namespace noise; // Sets reference for usage of the the noise class objects
using namespace std;
using namespace sf;

struct Bound  // Holds the bounding rectangle values
{
	int LX;
	int LY;
	int UX;
	int UY;
};

void machine(int size)
{
	 srand(time(NULL)); // INITIALIZE RANDOM SEED.

	 module::Perlin Module; // Instantiates the Perlin class object to be used as the source for the noise generation.

	 module::RidgedMulti mountainTerrain; // Instantiates the Mountain Terrain class object.

	 module::Billow baseFlatTerrain; // Instantiates the Flat Terrain class object.
	 baseFlatTerrain.SetFrequency (2.0); // Increases the number of bumps or hills in the flat terrain which are subsequently smoothed.

	 module::ScaleBias flatTerrain; // The modifier class that flattens the baseFlatTerrain object.
	 flatTerrain.SetSourceModule (0, baseFlatTerrain);
	 flatTerrain.SetScale (0.125); // Compresses the noise output to a narrow range, resembling flat terrain.
	 flatTerrain.SetBias (-0.75); // Moves the noise output down along the y-scale.

	 utils::NoiseMap heightMap; // Creation of the 2D empty noise map.
	 utils::NoiseMapBuilderPlane heightMapBuilder; // Used to fill the noise map with the noise values taken from an (x,y) plane.

	 int differencex, differencey;
	 int temp,choice;
	 int it = 0; // Holds the number of iterations of the machine learning function.
	 int state = 0; // Holds the index of the structure object being accessed.

	 Bound B[20];
	 tag3:  // Start of the bounding value generation process.
	 if(state == 0)
		 heightMapBuilder.SetSourceModule (Module); // Sets the Perlin module as the source for noise generation.

	 B[state].LX =  rand() % 40 + 0; // Creates value for lower X.
	 tag1: // UX Generation
	 temp =  rand() % 40 + 0; // Creates value for higher X.

	  if(temp > B[state].LX) // Checks if higher x value is correctly assigned, if not repeats.
		 B[state].UX = temp;

	  else
		 goto tag1;

	  if(it>0)  // Performs the adaptation from previous outputs
	  {
		  if (B[state].UX - B[state].LX > differencex)
			  goto tag1;
	  }

	 B[state].LY =  rand() % 40 + 0; // Creates value for lower Y.
	 tag2: // UY Generation
	 temp =  rand() % 40 + 0; // Creates value for higher Y.

	 if(temp > B[state].LY) // Checks if higher x value is correctly assigned, if not repeats.
		 B[state].UY = temp;
	 else
		 goto tag2;

	  if(it>0)
	  {
		  if (B[state].UY - B[state].LY > differencey)
			  goto tag2;
	  }

	 cout<<"Bounding values generated!\n";
	 cout<<"Lower X: "<< B[state].LX;
	 cout<<"\nLower Y: "<< B[state].LY;
	 cout<<"\nUpper X: "<< B[state].UX;
	 cout<<"\nUpper Y: "<< B[state].UY;

	 heightMapBuilder.SetDestNoiseMap (heightMap); // Sets the empty noise map as the target for the output of the planar noise map builder.
	 heightMapBuilder.SetDestSize(size,size); // Sets the size of the output noise map.

	 heightMapBuilder.SetBounds ( B[state].LX,  B[state].UX,  B[state].LY,  B[state].UY); // Defines the vertices of the bounding rectangle from which the noise values are produced. lower x, upper x, lower y, upper y.

	 heightMapBuilder.Build (); // Builds the noise map.
	 cout<<"\nNoise map built!\n";
	 // RENDERING THE TERRAIN HEIGHT MAP

	 utils::RendererImage renderer;  // Initializes the renderer module to convert the noise map to image information.
	 utils::Image image; 	// Initializes the image object to hold the height map output image.

	 renderer.SetSourceNoiseMap(heightMap);
	 renderer.SetDestImage(image);
	 renderer.Render();

	 // WRITING THE HEIGHT MAP IMAGE TO AN OUTPUT FILE

	 utils::WriterBMP writer;	// Initializes the writerBMP class object to write the image information to an output bitmap file.
	 writer.SetSourceImage(image);
	 writer.SetDestFilename("output.bmp");
	 writer.WriteDestFile ();

	 system("pause");

	 // EXPORT OPERATION TO L3DT.

	 system("C:\\Import.zs");

	 // Machine Learning stage.

	 cout<<"Is the output satisfactory?\n1.Yes\n2.No\n3.Finalise\n";
	 cin>>choice;
	 switch(choice)
	 {
		 case 1:
			 differencex =  B[state].UX -  B[state].LX;
			 differencey =  B[state].UY -  B[state].LY;
			 it++;
			 state++;
			 goto tag3;
			 break;
		 case 2:
			 cout<<"What kind of modification do you wish to make?:\n1: Flat and plain.\n2: Hilly and moderate.\n3: Mountainous and sharp.\n";
			 cin>>choice;
			 switch(choice)
			 {
				 case 1:
					 //Module.SetPersistence (0.25);
					 heightMapBuilder.SetSourceModule (flatTerrain); // Sets the Flat terrain module as the source for noise generation.
					 break;
				 case 2:
					//Module.SetPersistence (0.5);
					heightMapBuilder.SetSourceModule (Module); // Sets the Perlin module as the source for noise generation.
					break;
				 case 3:
					//Module.SetPersistence (0.75);
					heightMapBuilder.SetSourceModule (mountainTerrain); // Sets the Mountain terrain module as the source for noise generation.
					break;
				 default:
					cout<<"Incorrect input! Please try again.\n";
					goto tag3;
					break;
			  }
			 state++;
			 goto tag3;
			 break;
		 case 3:
			  // EXPORT OPERATION AS A PHOTOSHOP RAW FILE.
			  system("C:\\Export.zs");
			  return;
			  break;
	 }
}


void main()
{
	// NOISE Objects initialization

  module::Perlin Module; // Instantiates the Perlin class object to be used as the source for the noise generation.

  module::RidgedMulti mountainTerrain; // Instantiates the Mountain Terrain class object.

  module::Billow baseFlatTerrain; // Instantiates the Flat Terrain class object.
  baseFlatTerrain.SetFrequency (2.0); // Increases the number of bumps or hills in the flat terrain which are subsequently smoothed.

  module::ScaleBias flatTerrain; // The modifier class that flattens the baseFlatTerrain object.
  flatTerrain.SetSourceModule (0, baseFlatTerrain);
  flatTerrain.SetScale (0.125); // Compresses the noise output to a narrow range, resembling flat terrain.
  flatTerrain.SetBias (-0.75); // Moves the noise output down along the y-scale.

  utils::NoiseMap heightMap; // Creation of the 2D empty noise map.
  utils::NoiseMapBuilderPlane heightMapBuilder; // Used to fill the noise map with the noise values taken from an (x,y) plane.

   // SFML Values Initialization

  sf::Texture img; // Initializes the texture object to hold the output bitmap file.

   // INTEGER Values Initialization

  int size; // Holds the size of the output bitmap file
  double lx, ly, ux, uy; // Holds the coordinates of the bounding rectangle to pass to the heightMapBuilder function.
  int choice;
  int mode;

  cout<<"Enter the mode you wish to use:\n1.Advanced User Mode\n2.Machine Learning Mode\n";
  cin>>mode;
  if(mode == 2)
  {
	  cout<<"Enter the size of the heightmap to generate (must be a multiple of 2) : ";
	  cin>>size;
	  machine(size);
	  exit(1);
  }
   // ACCEPTING USER INPUT

  tag3:

  cout<<"Enter the type of terrain you wish to create:\n1: Flat and plain.\n2: Hilly and moderate.\n3: Mountainous and sharp.\n";
  cin>>choice;
  switch(choice)
  {
	  case 1:
		//Module.SetPersistence (0.25);
		heightMapBuilder.SetSourceModule (flatTerrain); // Sets the Flat terrain module as the source for noise generation.
		break;
	  case 2:
		//Module.SetPersistence (0.5);
		heightMapBuilder.SetSourceModule (Module); // Sets the Perlin module as the source for noise generation.
		break;
	  case 3:
		//Module.SetPersistence (0.75);
		heightMapBuilder.SetSourceModule (mountainTerrain); // Sets the Mountain terrain module as the source for noise generation.
		break;
	  default:
		cout<<"Incorrect input! Please try again.\n";
		goto tag3;
		break;
  }
  cout<<"Enter the size of the heightmap to generate (must be a multiple of 2) : ";
  cin>>size;

  tag1:
  if( size%2 != 0 )
	{
		cout<<"Incorrect input! Please try again.\n";
		goto tag1;
	}

  tag2:

  cout<<"Enter the bottom-left and top-right coordinate values to form a bounding rectangle according to which noise is created: \nLower X :\t";
  cin>>lx;
  cout<<"Lower Y :\t";
  cin>>ly;
  cout<<"Upper X :\t";
  cin>>ux;
  cout<<"Upper Y : \t";
  cin>>uy;

  if( lx>=ux || ly>=uy )
  {
	  cout<<"Incorrect input! Please try again.\n";
	  goto tag2;
  }

  // CREATION OF THE NOISE MAP

  heightMapBuilder.SetDestNoiseMap (heightMap); // Sets the empty noise map as the target for the output of the planar noise map builder.
  heightMapBuilder.SetDestSize(size,size); // Sets the size of the output noise map.

  heightMapBuilder.SetBounds (lx, ux, ly, uy); // Defines the vertices of the bounding rectangle from which the noise values are produced. lower x, upper x, lower y, upper y.
  heightMapBuilder.Build (); // Builds the noise map.

  // RENDERING THE TERRAIN HEIGHT MAP

  utils::RendererImage renderer;  // Initializes the renderer module to convert the noise map to image information.
  utils::Image image; 	// Initializes the image object to hold the height map output image.

  renderer.SetSourceNoiseMap(heightMap);
  renderer.SetDestImage(image);
  renderer.Render();

  // WRITING THE HEIGHT MAP IMAGE TO AN OUTPUT FILE

  utils::WriterBMP writer;	// Initializes the writerBMP class object to write the image information to an output bitmap file.
  writer.SetSourceImage(image);
  writer.SetDestFilename("output.bmp");
  writer.WriteDestFile ();

  system("pause");

  // DISPLAYING THE HEIGHT MAP ON THE SFML WINDOW.

  sf::RenderWindow App(sf::VideoMode(size, size), "SFML window"); // Creates the SFML display window.
  img.loadFromFile("output.bmp"); // Points the texture object to the newly created bitmap file.
  sf::Sprite Sprite(img); // Converts the texture information into a drawable Sprite type.
  App.draw(Sprite); // Send the sprite to the hidden buffer.
  App.display(); // Draw to the SFML window from buffer.


  // EXPORT OPERATION TO L3DT.

  system("Import.zs");

  cout<<"Is the output satisfactory?\n1.Yes\n2.No\n";
  cin>>choice;
  switch(choice)
  {
	  case 1:
		  break;
	  case 2:
		  App.clear();
		  goto tag2;
  }

  // EXPORT OPERATION AS A PHOTOSHOP RAW FILE.

  system("Export.zs");

}







