#include "helpers.h"
#include <math.h>
#include <stdlib.h>

void swap(int *x, int *y);

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    float color = 0;
    //loops for all pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //average out the color
            color = (image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0;
            int color1 = round(color);
            //set all color to the same amount so that it becomes grayscale
            image[i][j].rgbtRed = color1;
            image[i][j].rgbtGreen = color1;
            image[i][j].rgbtBlue = color1;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    float sepiaRed = 0, originalRed = 0, sepiaGreen = 0, originalGreen = 0, sepiaBlue = 0, originalBlue = 0;
    //loops for all pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //store original color
            originalRed = image[i][j].rgbtRed;
            originalGreen = image[i][j].rgbtGreen;
            originalBlue = image[i][j].rgbtBlue;
            //formula to change original color ro sepia
            sepiaRed = .393 * originalRed + .769 * originalGreen + .189 * originalBlue;
            sepiaGreen = .349 * originalRed + .686 * originalGreen + .168 * originalBlue;
            sepiaBlue = .272 * originalRed + .534 * originalGreen + .131 * originalBlue;
            //rounding numbers
            int Red = round(sepiaRed);
            int Green = round(sepiaGreen);
            int Blue = round(sepiaBlue);
            //stops when the color reaches max amount
            if (Red > 255)
            {
                Red = 255;
            }
            if (Green > 255)
            {
                Green = 255;
            }
            if (Blue > 255)
            {
                Blue = 255;
            }
            //puts the colors into each pixel
            image[i][j].rgbtRed = Red;
            image[i][j].rgbtGreen = Green;
            image[i][j].rgbtBlue = Blue;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    //subtracted width by 1, because width starts from 0
    int swapwidth = width - 1;
    //loops for all pixels
    for (int i = 0; i < height; i++)
    {
        //divide the width by 2, then swaps the pixels by using pointer address
        for (int j = 0; j <= swapwidth / 2; j++)
        {
            RGBTRIPLE temp = image[i][j];
            image[i][j] = image[i][swapwidth - j];
            image[i][swapwidth - j] = temp;

        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    //makes duplicate image
    RGBTRIPLE dupimage[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            dupimage[i][j] = image[i][j];
        }
    }
    //loops for all pixels
    float count = 9, red = 0, blue = 0, green = 0;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //blur for pixles in the middle
            if (i > 0 && i < height - 1 && j > 0 && j < width - 1)
            {
                count = 9;
                red = dupimage[i - 1][j - 1].rgbtRed + dupimage[i - 1][j].rgbtRed + dupimage[i - 1][j + 1].rgbtRed +
                      dupimage[i][j - 1].rgbtRed + dupimage[i][j + 1].rgbtRed  + dupimage[i + 1][j - 1].rgbtRed +
                      dupimage[i + 1][j].rgbtRed + dupimage[i + 1][j + 1].rgbtRed + dupimage[i][j].rgbtRed;
                green = dupimage[i - 1][j - 1].rgbtGreen + dupimage[i - 1][j].rgbtGreen + dupimage[i - 1][j + 1].rgbtGreen +
                        dupimage[i][j - 1].rgbtGreen + dupimage[i][j + 1].rgbtGreen  + dupimage[i + 1][j - 1].rgbtGreen +
                        dupimage[i + 1][j].rgbtGreen + dupimage[i + 1][j + 1].rgbtGreen + dupimage[i][j].rgbtGreen;
                blue = dupimage[i - 1][j - 1].rgbtBlue + dupimage[i - 1][j].rgbtBlue + dupimage[i - 1][j + 1].rgbtBlue +
                       dupimage[i][j - 1].rgbtBlue + dupimage[i][j + 1].rgbtBlue  + dupimage[i + 1][j - 1].rgbtBlue +
                       dupimage[i + 1][j].rgbtBlue + dupimage[i + 1][j + 1].rgbtBlue + dupimage[i][j].rgbtBlue;
                image[i][j].rgbtRed = round(red / count);
                image[i][j].rgbtBlue = round(blue / count);
                image[i][j].rgbtGreen = round(green / count);
            }
            //blur for pixles in the corner
            if (i == 0 && j == 0)
            {
                count = 4;
                red = dupimage[i][j + 1].rgbtRed  + dupimage[i + 1][j].rgbtRed + dupimage[i + 1][j + 1].rgbtRed + dupimage[i][j].rgbtRed;
                green = dupimage[i][j + 1].rgbtGreen  + dupimage[i + 1][j].rgbtGreen + dupimage[i + 1][j + 1].rgbtGreen + dupimage[i][j].rgbtGreen;
                blue = dupimage[i][j + 1].rgbtBlue  + dupimage[i + 1][j].rgbtBlue + dupimage[i + 1][j + 1].rgbtBlue + dupimage[i][j].rgbtBlue;
                image[i][j].rgbtRed = round(red / count);
                image[i][j].rgbtBlue = round(blue / count);
                image[i][j].rgbtGreen = round(green / count);
            }
            //blur for pixles in the corner
            if (i == 0 && j == width - 1)
            {
                count = 4;
                red = dupimage[i][j - 1].rgbtRed + dupimage[i + 1][j - 1].rgbtRed + dupimage[i + 1][j].rgbtRed + dupimage[i][j].rgbtRed;
                green = dupimage[i][j - 1].rgbtGreen + dupimage[i + 1][j - 1].rgbtGreen + dupimage[i + 1][j].rgbtGreen + dupimage[i][j].rgbtGreen;
                blue = dupimage[i][j - 1].rgbtBlue + dupimage[i + 1][j - 1].rgbtBlue + dupimage[i + 1][j].rgbtBlue + dupimage[i][j].rgbtBlue;
                image[i][j].rgbtRed = round(red / count);
                image[i][j].rgbtBlue = round(blue / count);
                image[i][j].rgbtGreen = round(green / count);
            }
            //blur for pixles in the corner
            if (i == height - 1 && j == 0)
            {
                count = 4;
                red = dupimage[i - 1][j].rgbtRed + dupimage[i - 1][j + 1].rgbtRed + dupimage[i][j + 1].rgbtRed + dupimage[i][j].rgbtRed;
                green = dupimage[i - 1][j].rgbtGreen + dupimage[i - 1][j + 1].rgbtGreen + dupimage[i][j + 1].rgbtGreen + dupimage[i][j].rgbtGreen;
                blue = dupimage[i - 1][j].rgbtBlue + dupimage[i - 1][j + 1].rgbtBlue + dupimage[i][j + 1].rgbtBlue + dupimage[i][j].rgbtBlue;
                image[i][j].rgbtRed = round(red / count);
                image[i][j].rgbtBlue = round(blue / count);
                image[i][j].rgbtGreen = round(green / count);
            }
            //blur for pixles in the corner
            if (i == height - 1 && j == width - 1)
            {
                count = 4;
                red = dupimage[i - 1][j - 1].rgbtRed + dupimage[i - 1][j].rgbtRed + dupimage[i][j - 1].rgbtRed + dupimage[i][j].rgbtRed;
                green = dupimage[i - 1][j - 1].rgbtGreen + dupimage[i - 1][j].rgbtGreen + dupimage[i][j - 1].rgbtGreen + dupimage[i][j].rgbtGreen;
                blue = dupimage[i - 1][j - 1].rgbtBlue + dupimage[i - 1][j].rgbtBlue + dupimage[i][j - 1].rgbtBlue + dupimage[i][j].rgbtBlue;
                image[i][j].rgbtRed = round(red / count);
                image[i][j].rgbtBlue = round(blue / count);
                image[i][j].rgbtGreen = round(green / count);
            }
            //blur for pixles at the edge
            if (i == 0 && j > 0 && j < width - 1)
            {
                count = 6;
                red = dupimage[i][j - 1].rgbtRed + dupimage[i][j + 1].rgbtRed  + dupimage[i + 1][j - 1].rgbtRed +
                      dupimage[i + 1][j].rgbtRed + dupimage[i + 1][j + 1].rgbtRed + dupimage[i][j].rgbtRed;
                green = dupimage[i][j - 1].rgbtGreen + dupimage[i][j + 1].rgbtGreen  + dupimage[i + 1][j - 1].rgbtGreen +
                        dupimage[i + 1][j].rgbtGreen + dupimage[i + 1][j + 1].rgbtGreen + dupimage[i][j].rgbtGreen;
                blue = dupimage[i][j - 1].rgbtBlue + dupimage[i][j + 1].rgbtBlue  + dupimage[i + 1][j - 1].rgbtBlue +
                       dupimage[i + 1][j].rgbtBlue + dupimage[i + 1][j + 1].rgbtBlue + dupimage[i][j].rgbtBlue;
                image[i][j].rgbtRed = round(red / count);
                image[i][j].rgbtBlue = round(blue / count);
                image[i][j].rgbtGreen = round(green / count);
            }
            //blur for pixles at the edge
            if (i == height - 1 && j != 0 && j != width - 1)
            {
                count = 6;
                red = dupimage[i - 1][j - 1].rgbtRed + dupimage[i - 1][j].rgbtRed + dupimage[i - 1][j + 1].rgbtRed + dupimage[i][j - 1].rgbtRed
                      + dupimage[i][j + 1].rgbtRed + dupimage[i][j].rgbtRed;
                green = dupimage[i - 1][j - 1].rgbtGreen + dupimage[i - 1][j].rgbtGreen + dupimage[i - 1][j + 1].rgbtGreen + dupimage[i][j - 1].
                        rgbtGreen + dupimage[i][j + 1].rgbtGreen + dupimage[i][j].rgbtGreen;
                blue = dupimage[i - 1][j - 1].rgbtBlue + dupimage[i - 1][j].rgbtBlue + dupimage[i - 1][j + 1].rgbtBlue + dupimage[i][j - 1].rgbtBlue
                       + dupimage[i][j + 1].rgbtBlue + dupimage[i][j].rgbtBlue;
                image[i][j].rgbtRed = round(red / count);
                image[i][j].rgbtBlue = round(blue / count);
                image[i][j].rgbtGreen = round(green / count);
            }
            //blur for pixles at the edge
            if (j == 0 && i != 0 && i != height - 1)
            {
                count = 6;
                red = dupimage[i - 1][j].rgbtRed + dupimage[i - 1][j + 1].rgbtRed + dupimage[i][j + 1].rgbtRed  +
                      dupimage[i + 1][j].rgbtRed + dupimage[i + 1][j + 1].rgbtRed + dupimage[i][j].rgbtRed;
                green = dupimage[i - 1][j].rgbtGreen + dupimage[i - 1][j + 1].rgbtGreen + dupimage[i][j + 1].rgbtGreen  +
                        dupimage[i + 1][j].rgbtGreen + dupimage[i + 1][j + 1].rgbtGreen + dupimage[i][j].rgbtGreen;
                blue = dupimage[i - 1][j].rgbtBlue + dupimage[i - 1][j + 1].rgbtBlue + dupimage[i][j + 1].rgbtBlue  +
                       dupimage[i + 1][j].rgbtBlue + dupimage[i + 1][j + 1].rgbtBlue + dupimage[i][j].rgbtBlue;
                image[i][j].rgbtRed = round(red / count);
                image[i][j].rgbtBlue = round(blue / count);
                image[i][j].rgbtGreen = round(green / count);
            }
            //blur for pixles at the edge
            if (j == width - 1 && i != 0 && i != height - 1)
            {
                count = 6;
                red = dupimage[i - 1][j - 1].rgbtRed + dupimage[i - 1][j].rgbtRed + dupimage[i][j - 1].rgbtRed + dupimage[i + 1][j - 1].rgbtRed +
                      dupimage[i + 1][j].rgbtRed + dupimage[i][j].rgbtRed;
                green = dupimage[i - 1][j - 1].rgbtGreen + dupimage[i - 1][j].rgbtGreen + dupimage[i][j - 1].rgbtGreen + dupimage[i + 1][j -
                        1].rgbtGreen + dupimage[i + 1][j].rgbtGreen + dupimage[i][j].rgbtGreen;
                blue = dupimage[i - 1][j - 1].rgbtBlue + dupimage[i - 1][j].rgbtBlue + dupimage[i][j - 1].rgbtBlue + dupimage[i + 1][j - 1].rgbtBlue
                       + dupimage[i + 1][j].rgbtBlue + dupimage[i][j].rgbtBlue;
                image[i][j].rgbtRed = round(red / count);
                image[i][j].rgbtBlue = round(blue / count);
                image[i][j].rgbtGreen = round(green / count);
            }
        }
    }
    return;
}

