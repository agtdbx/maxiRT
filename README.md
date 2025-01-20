## rt

### Compilation

```bash
cmake -B build; cmake --build build
```

### Usage

```bash
export LD_LIBRARY_PATH=lib/ffmpeg
./rt <map path>
```

### Controls
Move forward `W/Z`
Move backward `S`
Move left `A/Q`
Move right `D`
Move up `space`
Move down `left shift`
Sprint `left ctrl`

Look up `up arrow`
Look down `down arrow`
Look left `left arrow`
Look right `right arrow`

Menu `tab`
Record `R` (long press)

### Map format
#### Scene unique required components
Camera
```
C <position> <orientation vector> <fov>
```

Ambient Light
```
A <brightness> <color>
```

#### Scene unique non required component
Sky box
```
S <texture path>
```

#### Scene non unique components
Sphere
```
sp <position> <diameter> <color>
sp-ck <position> <diameter>
sp-sn <position> <diameter>
sp-pn <position> <diameter>
sp-t <position> <diameter> <texture path>
sp-tn <position> <diameter> <texture path> <normal map path>
```

Plane
```
pl <position> <orientation vector> <color>
pl-ck <position> <orientation vector>
pl-sn <position> <orientation vector>
pl-pn <position> <orientation vector>
pl-t <position> <orientation vector>
pl-tn <position> <orientation vector>
```

Cylinder
```
cy <position> <orientation vector> <diameter> <height> <color>
cy-ck <position> <orientation vector> <diameter> <height>
cy-sn <position> <orientation vector> <diameter> <height>
cy-pn <position> <orientation vector> <diameter> <height>
cy-t <position> <orientation vector> <diameter> <height>
cy-tn <position> <orientation vector> <diameter> <height>
```

Cone
```
co <position> <orientation vector> <diameter> <height> <color>
co-ck <position> <orientation vector> <diameter> <height>
co-sn <position> <orientation vector> <diameter> <height>
co-pn <position> <orientation vector> <diameter> <height>
co-t <position> <orientation vector> <diameter> <height>
co-tn <position> <orientation vector> <diameter> <height>
```

Cube
```
cu <position> <orientation x vector> <orientation y vector> <widht> <height> <depth> <color>
cu-ck <position> <orientation x vector> <orientation y vector> <widht> <height> <depth>
cu-sn <position> <orientation x vector> <orientation y vector> <widht> <height> <depth>
cu-pn <position> <orientation x vector> <orientation y vector> <widht> <height> <depth>
cu-t <position> <orientation x vector> <orientation y vector> <widht> <height> <depth> <texture path>
cu-tn <position> <orientation x vector> <orientation y vector> <widht> <height> <depth> <texture path> <normal map path>
```

Triangle
```
tr <point> <point> <point> <color>
tr-ck <point> <point> <point>
tr-sn <point> <point> <point>
tr-pn <point> <point> <point>
tr-t <point> <point> <point> <texture path>
tr-tn <point> <point> <point> <texture path> <normal map path>
```

.obj 3D object
```
ob <position> <orientation x vector> <orientation y vector> <size> <obj file path> <color>
ob-ck <position> <orientation x vector> <orientation y vector> <size> <obj file path>
ob-sn <position> <orientation x vector> <orientation y vector> <size> <obj file path>
ob-pn <position> <orientation x vector> <orientation y vector> <size> <obj file path>
ob-t <position> <orientation x vector> <orientation y vector> <size> <obj file path> <texture path>
ob-tn <position> <orientation x vector> <orientation y vector> <size> <obj file path> <texture path> <normal map path>
```

Paraboloid
```
par <position> <orientation vector> <height> <color>
par-ck <position> <orientation vector> <height>
par-sn <position> <orientation vector> <height>
par-pn <position> <orientation vector> <height>
par-t <position> <orientation vector> <height> <texture path>
par-tn <position> <orientation vector> <height> <texture path> <normal map path>"
```

#### Scene specials
add a cartoon effect
```
cartoon
```

comment a line
```
# <what ever you want>
```
