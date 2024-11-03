
<!-- PROJECT LOGO -->
<br />
<div align="center">

  <h3 align="center">Disco Party </h3>

  <p align="center">
    A dance ring simulating different lightings
    <br />
   
  </p>
</div>



<!-- TABLE OF CONTENTS -->
<details>
  <summary>Table of Contents</summary>
  <ol>
    <li>
      <a href="#about-the-project">About The Project</a>
      <ul>
        <li><a href="#built-with">Built With</a></li>
      </ul>
    </li>
    <li>
      <a href="#getting-started">Getting Started</a>
      <ul>
        <li><a href="#prerequisites">Prerequisites</a></li>
      </ul>
    </li>
    <li><a href="#roadmap">Roadmap</a></li>
    <li><a href="#acknowledgments">Acknoledgments</a></li>
    
    
  </ol>
</details>



<!-- ABOUT THE PROJECT -->
## About The Project

A dance floor that will simulate the lighting coming from the floor, from a set of spotlights and from a disco globe attached to the ceiling. The dance floor will be surrounded by walls and in the center there will be some geometric shapes that will move randomly and represent the dancers.

![Dance floor](https://github.com/AndraCristiana07/Disco-Party/blob/main/images/1.png?raw=true)

* **Lighting coming from the dance floor** :
The floor of the dance floor consists of a grid of 8×8 cells, where each cell has a randomly chosen color. The illumination emitted by a single cell is simulated by using a point light source located in the center of the cell. The geometry of a cell is drawn with only the emissive component, without taking into account the other components of the light source used to approximate the illumination emitted by the cell. The emissive component has the same color as the light source associated with the cell.

In order not to include all the light sources on the dance floor in the calculation of the lighting of the walls and the dancers, certain constraints are introduced. It limits the distance that light from a cell light source can travel. Limiting the distance that light reaches from a source is done with the attenuation factor.

In order to be able to calculate the lighting coming from several light sources, all these sources are sent to the shader (position, color). The final illuminance is the sum of the illuminance of each individual light source.


![Spotlights](https://github.com/AndraCristiana07/Disco-Party/blob/main/images/2.png?raw=true)

* **Lighting from spotlights** :
To improve the visual effect, the light area of ​​the spotlights are simulated by drawing a transparent cone over the lighting direction of the spotlight.

To obtain the light cone, the geometry of a cone must be generated. For simplicity, the geometry of the cone is similar to that of a circular disc of radius 1, centered at position (0, -1, 0) and created in the XOZ plane. The only change from the circle disk is that the vertex at the center of the disk is at the origin of the coordinate system.

![Disco globe](https://github.com/AndraCristiana07/Disco-Party/blob/main/images/3.png?raw=true)

* **Lighting from a disco globe** :
The lighting of the disco c is simulated with a point light source for which the color will be obtained from a texture.

This texture is generated on the CPU from the code and contains a randomly chosen color for each pixel. For a better simulation of the disco ball, a resolution of 16×16 pixels is used. GL_TEXTURE_MAG_FILTER and GL_TEXTURE_MIN_FILTER properties are GL_NEAREST.

At the position of the disco globe a sphere is drawn where this texture is applied. The texture coordinates used for sampling are calculated from the fragment shader. The position of the point light source used to simulate the illumination of the disco globe is assumed to be at the center of this sphere. Texture coordinates can be calculated in fragment shader with a special mapping known as spherical mapping.


Calculating the illumination of the point light source on the rest of the objects in the scene will be done similarly to any other light of this type, except that the color of the light source is extracted from the generated texture. In this situation, color will be the color of the light source for world_position.

For an atmosphere closer to a dance floor, a continuous rotation of the disco globe is simulated, achieved by translating the texture coordinates.




### Built With

These are what I used to build the bot:

* ![C++](https://img.shields.io/badge/c++-%2300599C.svg?style=for-the-badge&logo=c%2B%2B&logoColor=white)
* ![OpenGL](https://img.shields.io/badge/OpenGL-%23FFFFFF.svg?style=for-the-badge&logo=opengl)
* ![CMake](https://img.shields.io/badge/CMake-%23008FBA.svg?style=for-the-badge&logo=cmake&logoColor=white)



<!-- GETTING STARTED -->
## Getting Started

To be able to use this project you will need some stuff first.

### Prerequisites

* cmake
  [Cmake Installation steps](https://cgold.readthedocs.io/en/latest/first-step/installation.html)
* OpenGL



<!-- ROADMAP -->
## Roadmap

- [x] Make a window where to render stuff
- [x] Drawing the cell grid
- [x] Computation of lighting in fragment shader for dancers and walls
- [x] Using an attenuation factor that limits illumination to a chosen distance
- [x] Compute and send to the shader only the lights that have influence on a drawn object
- [x] Calculating illumination of at least 4 spot light sources, in fragment shader, for dancers, dance floor surface and walls
- [x] Drawing Light Cones
- [x] Random rotation of light source direction (10p)
Disco Globe Lighting 
- [x] Generate the texture that will contain a randomly chosen color for each pixel
- [x] Fragment shader lighting calculation for walls, dancers, dance floor surface, ceiling and disco globe 
- [x] Continuous rotation of the disco ball, achieved by translating the texture coordinates 
- [x] Switch between the 3 types of lighting at the press of a key 
- [x] Random movement of dancers



<!-- ACKNOWLEDGMENTS -->
## Acknowledgments

Some things that helped me while making this project :
* [Learn OpenGL](https://learnopengl.com/)





