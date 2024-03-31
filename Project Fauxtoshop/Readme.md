Fauxtoshop is a simple program written in C that allows you to rotate BMP (BitMaP) images by 90 degrees clockwise. This tool is useful for manipulating BMP images without the need for complex image editing software.

## How to run it 

Both on Linux and Windows: 

`gcc fauxtoshop.c -o fauxtoshop`

And then you can run it like so:

`./fauxtoshop < input_image.bmp > rotated_image.bmp`

## Input 

Fauxtoshop accepts BMP images as input. Make sure the input image is in the BMP format and has 24-bit color depth.

## Output
The rotated image will be saved as a new BMP file with the name specified during redirection.

## Example execution with the provided bmp

`./fauxtoshop < ghost.bmp > rotated_ghost.bmp`

## Note
This program only rotates BMP images by 90 degrees clockwise. It does not support other image formats or rotation angles. Additionally, the input image must be properly formatted BMP with 24-bit color depth for accurate results.