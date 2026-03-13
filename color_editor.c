 #define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void convert_to_grayscale(unsigned char *image, int width, int height, int channels) {
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            unsigned char *pixel = image + (y * width + x) * channels;
            unsigned char r = pixel[0];
            unsigned char g = pixel[1];
            unsigned char b = pixel[2]; 

            // Convert to grayscale using the luminance method
            unsigned char gray = (unsigned char)(0.299f * r + 0.587f * g + 0.114f * b);

            // Set all channels to the grayscale value
            pixel[0] = gray;
            pixel[1] = gray;
            pixel[2] = gray;
        }
    }
}

void adjust_brightness(unsigned char *image, int width, int height, int channels, int brightness_value) {
    // Skip processing if brightness value is 0 (no change)
    if (brightness_value == 0) {
        return;
    }
    
    float adjustment_factor;
    if (brightness_value > 0) {
        // Positive values (1 to 50): increase brightness
        // Map 1-50 range to a factor between 1.02 and 2.0
        adjustment_factor = 1.0f + (brightness_value * 0.02f);
    } else {
        // Negative values (-50 to -1): decrease brightness
        // Map -50 to -1 range to a factor between 0.5 and 0.98
        adjustment_factor = 1.0f + (brightness_value * 0.01f);
    }
    
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            unsigned char *pixel = image + (y * width + x) * channels;
            
            for (int c = 0; c < channels; c++) {
                // Apply brightness adjustment to each channel
                int adjusted_value = (int)(pixel[c] * adjustment_factor);
                
                // Clamp the value to 0-255 range
                if (adjusted_value > 255) adjusted_value = 255;
                if (adjusted_value < 0) adjusted_value = 0;
                
                pixel[c] = (unsigned char)adjusted_value;
            }
        }
    }
    
}
// Helper function to get yes/no input
int get_yes_no_input(const char *prompt) {
    char response[10];
    printf("%s (y/n): ", prompt);
    scanf("%9s", response);
    
    // Convert to lowercase for case-insensitive comparison
    for (int i = 0; response[i]; i++) {
        response[i] = tolower(response[i]);
    }
    
        return (strcmp(response, "y") == 0 || strcmp(response, "yes") == 0);
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Use: %s <input_image> <output_image>\n", argv[0]);
        return 1;
    }
                                                      
    const char *input_image  = argv[1];
    const char *output_image = argv[2];
    
    // Load the image
    int width, height, channels;
    unsigned char *image = stbi_load(input_image, &width, &height, &channels, 0);

    if (image == NULL) {
        printf("Error loading image %s\n", input_image);
        return 1;
    }

    printf("Loaded image with %dx%d and %d channels\n", width, height, channels);
    
    // Ask if user wants to convert to black and white
    int convert_to_bw = get_yes_no_input("Do you want to convert the image to black and white");
    
    if (convert_to_bw) {
        printf("Converting image to black and white...\n");
        convert_to_grayscale(image, width, height, channels);
    }
    
    // Ask for brightness adjustment
    int brightness_value;
    printf("Enter brightness adjustment (-50 to -1: decrease, 0: no change, 1 to 50: increase): ");
    scanf("%d", &brightness_value);
    
    // Validate the input
    if (brightness_value < -50 || brightness_value > 50) {
        printf("Warning: Invalid brightness value. Using default (0 - no change)\n");
        brightness_value = 0;
    } else if (brightness_value != 0) {
        printf("Adjusting brightness with value: %d\n", brightness_value);
        adjust_brightness(image, width, height, channels, brightness_value);
    }

    // Save the processed image
    if (stbi_write_png(output_image, width, height, channels, image, width * channels) == 0) {
        printf("Error saving image %s\n", output_image  );
    } else {
        printf("Processed image saved as %s\n", output_image);
    }

    stbi_image_free(image);
    return 0;
}