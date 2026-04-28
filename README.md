# Image Processor

A simple C command-line tool for basic image processing.

## Features
- Convert images to grayscale (black & white)
- Adjust image brightness (increase or decrease)

## Dependencies
This project uses the [stb_image](https://github.com/nothings/stb) single-header libraries:
- `stb_image.h`
- `stb_image_write.h`

Download them and place them in the project root before building.

## Build

`make`

## Usage

`./krazy <input_image> <output_image>`

### Example


`./krazy photo.jpg output.png`

You'll be prompted to:
1. Convert to black & white (y/n)
2. Enter a brightness value (-50 to 50, where 0 = no change)

## Supported Formats
Input: JPG, PNG, BMP, TGA (anything stb_image supports)  
Output: PNG


