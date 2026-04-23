*This project has been created as part of the 42 curriculum by yotsurud, tamatsuu.*

## Description

The goal of this project is to 

## Instructions

### Installations

 - `git clone <repository of this project>`<br>
 - `cd project-name`

### Download minilibx

 - `download minilibx files from project page, and put it in the root of this project directory.`

### Compilation

 - `make`<br>
 - `make bonus`

### Run

 - `./miniRT scene/<filename>.rt`<br>
 - `./miniRT_bonus scene/<filename>.rt`

### Close window

 - `ESC button`<br>
 - `-click x mark of the window.`<br>
 - `ctrl-C`

## Resources
 - https://inzkyk.xyz/ray_tracing_in_one_weekend/
 - https://jun-networks.hatenablog.com/entry/2021/04/02/043216
 - https://www.youtube.com/watch?v=RIgc5J_ZGu8&list=PLAqGIYgEAxrUO6ODA0pnLkM2UOijerFPv

## Feature list
 - Mandatory part
	 - Ambient lighting
	 - Camera
	 - Light
	 - Sphere
	 - Plane
	 - Cylinder
 - Bonus part
	 - Specular reflection
	 - color disruption: checkerboard pattern
	 - Colored and multi-spot lights
	 - Another object: cone
	 - Handle bump map texture: earth.xpm

## .rt file sample
```bash
# Ambient light
###     ratio           								rgb
A   	0.1                                       		255,255,255

# Camera
###     xyz             vector          degree
C   	0,0,-30        	0,0,1       	45

# Light
###     xyz             				ratio           rgb
L   	-10,20,-10                  	0.7             255,255,255

# Sphere
###     xyx             				diameter        rgb				tex/mat	filename
sp		0,10,5							15				127,127,127		metal
sp		0,-5,5							8				127,127,127
sp		0,-5,5							8				0,255,0			image	earth.xpm	

# Plane
###     xyz             vector          				rgb				tex/mat
pl		10,-10,10		0,1,0							127,127,127		checker
pl		0,0,200	0,0,1									255,255,255

# Cylinder
###     xyz             vector          diameter        height 
cy 		10.0,4.0,10   	1.0,1.0,0		7.2    21.42   	0,255,0

# Cone
###     xyz             vector          diameter        height 
cn 		0,10,0   		1.0,1.0,1.0 	7.5    15   	0,255,0
cn 		10,10,0   		0,1.0,0			7.5    15   	255,0,0
```

## Examples

### [Mandatory part] ###
- ### Symple Scene
 ![Sphere](./image/r_sphere.png)
 <br>*Sphere*

- ### Ambient Light
 ![Ambient](./image/r_ambient.png)

- ### Light Position
<p>
 <img src="./image/r_light_front.png" width="400">
 <img src="./image/r_light_back.png" width="400"><br>
 <em>Fromt and Back</em>
</p>
<p>
 <img src="./image/r_light_top.png" width="400">
 <img src="./image/r_light_bottom.png" width="400"><br>
 <em>Top and Bottom</em>
</p>
<p>
 <img src="./image/r_light_left.png" width="400">
 <img src="./image/r_light_right.png" width="400"><br>
 <em>Left and Right</em>
</p>
<p>
 <img src="./image/r_light_inside.png" width="400"><br>
 <em>Inside</em>
</p>

- ### Objects
<p>
 <img src="./image/r_sphere.png" width="400">
 <img src="./image/r_plane.png" width="400"><br>
 <em>Sphere and Plane</em>
</p>
<p>
 <img src="./image/r_cylinder.png" width="400">
 <em>Cylinder</em>
</p>

### [Bonus part] ###

- ### Specular refrection

- ### Checker
 ![Sphere](./image/r_checker.png)

- ### Multi spot-lights

- ### Cone
 ![Cone](./image/r_cone.png)

- ### Image bump
 
### Mixed
<p>
 <img src="./image/r_default.png" width="400">
 <img src="./image/r_mix_objs.png" width="400"><br>
</p>
