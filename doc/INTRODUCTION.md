# INTRODUCTION

This document provides an overview of the terminology used in BioMesh.

## Terminology
- **fiber:** A 1D mesh modelled as a set of vertices in the Eucledian space.
- **fiber_grid:** The set of all generated fibers.
- **seed_point:** The point that represents the initial vertex of the fiber.
- **seed_plane:** The seed points are located on a plane. The plane splits the
vector field into two parts. The fibers are then generated in the forward direction and reverse direction. It is modelled using the point-normal formulation. The seed points are computed on this plane.

## Input description
- **Ultrasound Imaging data:** The data is represented as a vector field
embedded onto a VTK structured grid. The vectors represent the flow direction of the
muscle fiber. The file uses the legacy VTK format.

- **Configuration file:** The data represents the parameters that define the
**fiber_grid**. The file uses the XML format. The parameters are as follows:
    - **seed_vertex_count:** The total count of seed vertices required.
    - **vertex_count**: The total count of vertices on a single fiber. The count may be lower if some vertices exceed the bounds of the vector field
    - **vertex_width**: The distance between two vertices.
    - **integration_scheme:** The numeric integration scheme for tracing the fiber path. **Runge-Kutta4** is the default scheme for now.
    - **strategy**: It decides if the time stepping for numeric stepping is static or adaptive.
    - **adaptive_steps_max:** The count of adaptive time steps to be performed.
    - **plane_point:** The point of the **seed_plane**.
    - **plane_normal:** The normal of the **seed_plane**.

### **Sample configuration file**
```bash
<?xml version="1.0" encoding="UTF-8"?>
<fiber_set>
    <seed_vertex_count>100</seed_vertex_count>
    <vertex_count>200</vertex_count>
    <vertex_width>0.14</vertex_width>

    <integration_scheme>runge-kutta4</integration_scheme>
    <adaptive_steps_max>0</adaptive_steps_max>
    <strategy>static</strategy>

    <plane_point>
        <x>0.0</x>
        <y>1.0</y>
        <z>2.0</z>
    </plane_point>

    <plane_normal>
        <x>0.0</x>
        <y>0.0</y>
        <z>1.0</z>
    </plane_normal>
</fiber_set>
```

## Output description
- The fibers are written to JSON and VTK file formats so that they can be read in **OpenDiHu** and visualized in **paraview**.
- For the JSON format all fibers are written to a single JSON file.
- For the VTK format all fibers are written to a separate VTK file because every fiber is a 1D structured grid in the source code.
- The files are written to the results folder in the build directory by default.
### **Sample JSON file for fiber_grid**
```bash
{
   "fiber0" : [
      {
         "x" : 4.4444444444444446,
         "y" : 3.1111111111111112,
         "z" : 18.0
      },
      {
         "x" : 4.4446006859958294,
         "y" : 3.1114018101548044,
         "z" : 18.1399996110089
      },
      {
         "x" : 4.4450702718355455,
         "y" : 3.1122755286940715,
         "z" : 18.279996097054276
      }
   ],
   "fiber1" : [
      {
         "x" : 4.8888888888888893,
         "y" : 3.5555555555555558,
         "z" : 18.0
      },
      {
         "x" : 4.8890513153344806,
         "y" : 3.5559287646126934,
         "z" : 18.13999940832964
      },
      {
         "x" : 4.8895399224164731,
         "y" : 3.5570515252305359,
         "z" : 18.279994053483353
      },
      {
         "x" : 4.8903549839712577,
         "y" : 3.5589247161763193,
         "z" : 18.419979148512581
      }
    ]
}
```

### Sample VTK file for a single fiber
```bash
# vtk DataFile Version 5.1
vtk output
ASCII
DATASET STRUCTURED_GRID
DIMENSIONS 107 1 1
POINTS 107 float
4.44444 3.11111 18 4.4446 3.1114 18.14 4.44507 3.11228 18.28 
4.44585 3.11373 18.42 4.44695 3.11577 18.56 4.44836 3.1184 18.6999 
4.45009 3.12162 18.8399 4.45213 3.12542 18.9798 4.45449 3.12981 19.1197 
4.45717 3.1348 19.2596 4.46017 3.14038 19.3995 4.46349 3.14657 19.5393 
4.46713 3.15336 19.6791 4.4711 3.16075 19.8188 4.47539 3.16876 19.9585 
4.47998 3.17733 20.0982 4.4848 3.18637 20.2378 4.48985 3.19589 20.3774 
4.49516 3.2059 20.517 4.50072 3.21644 20.6564 4.50655 3.22754 20.7959 
4.51267 3.23921 20.9353 4.5191 3.25149 21.0746 4.52584 3.2644 21.2138 
4.53292 3.27799 21.353 4.54034 3.29227 21.492 4.54812 3.30727 21.631 
4.55628 3.32303 21.7699 4.56483 3.33958 21.9086 4.57379 3.35693 22.0473 
4.58317 3.37514 22.1858 4.59297 3.39421 22.3241 4.60322 3.41417 22.4623 
4.61392 3.43505 22.6003 4.62509 3.45688 22.7382 4.63672 3.47966 22.8758 
4.64882 3.50342 23.0132 4.66141 3.52817 23.1505 4.67447 3.55393 23.2875 
4.68802 3.5807 23.4242 4.70204 3.6085 23.5607 4.71655 3.63733 23.6969 
4.73152 3.66719 23.8329 4.74697 3.6981 23.9685 4.7628 3.72999 24.1039 
4.77882 3.76269 24.2391 4.795 3.79627 24.3741 4.81137 3.83079 24.5088 
4.82793 3.86629 24.6432 4.84469 3.90284 24.7773 4.86166 3.94051 24.911 
4.87885 3.97934 25.0444 4.89634 4.01939 25.1774 4.91511 4.0608 25.3099 
4.93545 4.10363 25.4416 4.95748 4.14796 25.5725 4.98133 4.19385 25.7026 
5.00713 4.24136 25.8318 5.03497 4.29056 25.9599 5.06499 4.34151 26.0868 
5.09728 4.39428 26.2123 5.13195 4.44892 26.3365 5.16908 4.50552 26.459 
5.20877 4.56413 26.5798 5.2511 4.62485 26.6987 5.29618 4.68776 26.8153 
5.34399 4.75295 26.9296 5.39258 4.82019 27.0424 5.44072 4.88944 27.1541 
5.4881 4.96081 27.2649 5.53446 5.03442 27.3746 5.5795 5.11039 27.4832 
5.62295 5.18885 27.5907 5.66455 5.26992 27.697 5.70405 5.35354 27.8021 
5.74112 5.43453 27.9101 5.77551 5.50965 28.0231 5.80686 5.57811 28.1411 
5.83493 5.63944 28.2638 5.85975 5.69365 28.3905 5.88142 5.74098 28.5205 
5.90014 5.78188 28.653 5.91618 5.81691 28.7876 5.92982 5.8467 28.9237 
5.94135 5.8719 29.061 5.95107 5.89312 29.199 5.95922 5.91093 29.3376 
5.96605 5.92585 29.4767 5.97176 5.93832 29.616 5.97653 5.94872 29.7555 
5.9805 5.9574 29.8952 5.98381 5.96463 30.035 5.98656 5.97065 30.1748 
5.98885 5.97565 30.3147 5.99076 5.97981 30.4546 5.99234 5.98327 30.5946 
5.99365 5.98614 30.7345 5.99474 5.98852 30.8745 5.99565 5.9905 31.0145 
5.9964 5.99214 31.1545 5.99702 5.9935 31.2945 5.99754 5.99462 31.4345 
5.99797 5.99556 31.5745 5.99832 5.99633 31.7145 5.99861 5.99697 31.8545 
5.99886 5.9975 31.9945 5.99906 5.99794 32.1345 
```
