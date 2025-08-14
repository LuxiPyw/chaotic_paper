Chaotic paper requires Magick++.
For build you need make and cmake.

# For install
```
git clone https://github.com/LuxiPyw/chaotic_paper
cd chaotic_paper
mkdir build
cd build
cmake ..
make
cd ..
cd bin
./my_app
```

# Config

You can change how image should write, for this you need edit: 
```
bin/config/config.json
```
There are many fields in the config that are responsible for image properties.
Comments are left in the config to help you understand how things work.
```
{
	"general": {
		"height": 3,
		"width": 3,
		"resizeScale": 1, // Final scaling factor for the output image (1 = default)
		"backGroundColor": "#000000" // Background color of the image (hex format)
	},
	"glyphs": {
		"inTiles": true, // If true, height/width are in tiles; if false, they are in pixels
		"antiAliasing": true, // Enables smoother edges for drawn text and shapes
		"glyphSet": "0", // Identifier for the set of glyphs (characters) to be used
		"fontFamilySet": "Hack.ttf", // Font file to use for rendering the glyphs
		"fontSize": 10, // Font size in pixels (before scaling or padding)
		"fontPadding": 2, // Space (in pixels) added around each glyph
		"colorSetSize": 3, // Number of colors in the colorSet array
		"colorSet": [ // Array of colors (hex) for random selection
			"#7123dd",
			"#571ea8",
			"#32096b"
		]
	}
}
```
