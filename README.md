*This project has been created as part of the 42 curriculum by yotsurud, tamatsuu.*

## Description

The goal of this project is to 

## Instructions

### Installations
```bash
	git clone <repository of this project>
	cd project-name
```
### Download minilibx
```
	download minilibx files from project page, and put it in the root of this project directory.
```
### Compilation
```bash
	make
	make bonus
```
### Run
```bash
	./miniRT scene/<filename>.rt
	./miniRT_bonus scene/<filename>.rt
```
### Close window
```
	ESC button
	click x mark of the window.
	ctrl-C
```

## Resources
 - https://inzkyk.xyz/ray_tracing_in_one_weekend/
 - https://jun-networks.hatenablog.com/entry/2021/04/02/043216
 - https://www.youtube.com/watch?v=RIgc5J_ZGu8&list=PLAqGIYgEAxrUO6ODA0pnLkM2UOijerFPv

## Feature list
 - Ambient Light
 - Camera
 - Light
 - object / Plane, Shpere, Cylinder, Cone
 - Texture / checker, image
 - Materila / non-metal, metal

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
