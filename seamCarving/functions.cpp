#include <iostream>
#include <sstream>
#include <fstream>
#include <cmath>
#include "functions.h"

using std::cout, std::endl, std::string;

void initializeImage(Pixel image[][MAX_HEIGHT])
{
  // iterate through columns
  for (unsigned int col = 0; col < MAX_WIDTH; col++)
  {
    // iterate through rows
    for (unsigned int row = 0; row < MAX_HEIGHT; row++)
    {
      // initialize pixel
      image[col][row] = {0, 0, 0};
    }
  }
}

/**
 * Description: opens and validates a PPM file while populating an array of pixels.
 *  - Should read in the preamble and pixel values (you can use a file stream).
 *  - Should validate values as they are read in.
 *  - Should use stream states to ensure successful input.
 *  - PPM files are in row major order.
 *
 * Exceptions:
 *  - If the file cannot be opened, throw a runtime_error exception with the description "Failed to open <filename>".
 *  - If the file type is not "P3" or "p3", throw a runtime_error exception with the description "Invalid type <type>".
 *  - Both dimensions should be positive integers and less than or equal to the maximum’s defined in functions.h.
 *    - If the dimensions are invalid, throw a runtime_error exception with the description "Invalid dimensions".
 *  - Each pixel should be 3 (red, green, and blue) non-negative integers less than 256.
 *    - If there is an invalid pixel value, throw a runtime_error exception with the description "Invalid color value".
 *    - If there are not enough pixel values, throw a runtime_error exception with the description "Invalid color value".
 *    - If there are too many pixels, throw a runtime_error exception with the description "Too many values".
 */
void loadImage(string filename, Pixel image[][MAX_HEIGHT], unsigned int &width, unsigned int &height)
{
  // Declare/Initialize input filestream
  std::ifstream inputFile;
  inputFile.open(filename);

  // Check that file is open
  if (!inputFile.is_open())
  {
    string err = "Failed to open " + filename;
    throw std::runtime_error(err);
  }

  // Get preamble values
  string type;
  int maxValue;
  inputFile >> type >> width >> height >> maxValue; // Since width and height are passed as pointers, we can directly assign them as such

  // cout << "TYPE: " << type << endl
  //      << "WIDTH: " << width << endl
  //      << "HEIGHT: " << height << endl
  //      << "MAX VALUE: " << maxValue << endl;

  // Validate values
  if (type != "p3" && type != "P3") // Make sure type is either "P3" or "p3"
  {
    string err = "Invalid type " + type;
    throw std::runtime_error(err);
  }
  if (width == 0 || width > MAX_WIDTH || height == 0 || height > MAX_HEIGHT) // Make sure width and height are within accepted values
  {
    string err = "Invalid dimensions";
    throw std::runtime_error(err);
  }
  if (maxValue > 255)
  {
    string err = "Invalid color value";
    throw std::runtime_error(err);
  }

  // begin reading values;
  for (unsigned int i = 0; i < height; i++)
  {
    for (unsigned int j = 0; j < width; j++)
    {
      Pixel currentPixel;
      if (inputFile >> currentPixel.r && currentPixel.r <= 255 && currentPixel.r >= 0 &&
          inputFile >> currentPixel.g && currentPixel.g <= 255 && currentPixel.g >= 0 &&
          inputFile >> currentPixel.b && currentPixel.b <= 255 && currentPixel.b >= 0) // Check that all pixels have valid values
      {
        image[j][i] = currentPixel;
      }
      else // If invalid color values or too few pixels, throw "Invalid color value"
      {
        string err = "Invalid color value";
        throw std::runtime_error(err);
      }
    }
  }

  // Check if there are still any values after the size specified in the preamble
  // If so, throw error
  string check;
  if (inputFile >> check)
  {
    string err = "Too many values";
    throw std::runtime_error(err);
  }
}

/**
 * Description: Outputs an array of pixels to a PPM file.
 *  - Should output the preamble and all the pixel values (separated by spaces / newline characters). You can use a file stream.
 *  - PPM files are in row major order.
 *
 * Exceptions:
 *  - If the output file cannot be opened, throw a runtime_error exception with the description "Failed to open <filename>".
 */
void outputImage(string filename, Pixel image[][MAX_HEIGHT], unsigned int width, unsigned int height)
{
  // Declare/Initialize input filestream
  std::ofstream outputFile;
  outputFile.open(filename);

  // Check that file is open, throw exeption if not
  if (!outputFile.is_open())
  {
    string err = "Failed to open " + filename;
    throw std::runtime_error(err);
  }

  // Create Preamble
  outputFile << "P3" << endl
             << width << " " << height << endl
             << 255 << endl;

  // Read pixel values from pixel array and add to output
  for (unsigned int i = 0; i < height; i++)
  {
    for (unsigned int j = 0; j < width; j++)
    {
      Pixel currentPixel = image[j][i];
      outputFile << currentPixel.r << " "
                 << currentPixel.g << " "
                 << currentPixel.b << " ";
    }
    outputFile << endl;
  }
}

/**
 * Description: Calculates the energy of a specific pixel in an array array.
 *
 * Exceptions: none.
 */
unsigned int energy(Pixel image[][MAX_HEIGHT], unsigned int x, unsigned int y, unsigned int width, unsigned int height)
{
  // Find which values to use for x1/x2 and y1/y2
  int x1, x2, y1, y2;
  if (x == 0) // If x value is minimum possible, use width-1 and x+1
  {
    x1 = width - 1;
    x2 = x + 1;
  }
  else if (x == width - 1) // If x value is maximum possible, use x-1 and 0
  {
    x1 = x - 1;
    x2 = 0;
  }
  else // For standard cases use x-1 and x+1
  {
    x1 = x - 1;
    x2 = x + 1;
  }

  if (y == 0) // If x value is minimum possible, use height-1 and y+1
  {
    y1 = height - 1;
    y2 = y + 1;
  }
  else if (y == height - 1) // If x value is maximum possible, use y-1 and 0
  {
    y1 = y - 1;
    y2 = 0;
  }
  else // For standard cases use x-1 and x+1
  {
    y1 = y - 1;
    y2 = y + 1;
  }

  // // DEBUG:
  // cout << endl
  //      << "specified x-value: " << x << endl
  //      << "specified y-value: " << y << endl
  //      << "width/height: " << width << "/" << height << endl
  //      << endl
  //      << "x1/x2: " << x1 << "/" << x2 << endl
  //      << "y1/y2: " << y1 << "/" << y2 << endl
  //      << endl;

  // Get x gradient
  Pixel xpixel1 = image[x1][y], xpixel2 = image[x2][y];
  int rx, gx, bx, gradX;
  rx = xpixel2.r - xpixel1.r;
  gx = xpixel2.g - xpixel1.g;
  bx = xpixel2.b - xpixel1.b;
  gradX = pow(rx, 2) + pow(gx, 2) + pow(bx, 2);

  // // DEBUG:
  // cout << "X-Gradient:" << endl
  //     << "Pixel1: (" << x1 << ", " << y << ") " << xpixel1.r << ", " << xpixel1.g << ", " << xpixel1.b << endl
  //     << "Pixel2: (" << x2 << ", " << y << ") " << xpixel2.r << ", " << xpixel2.g << ", " << xpixel2.b << endl
  //     << endl
  //     << "Rx: " << rx << endl
  //     << "Gx: " << gx << endl
  //     << "Bx: " << bx << endl
  //     << "gradX: " << rx << "^2 + " << gx << "^2 + " << bx << "^2 = " << gradX << endl
  //     << endl;

  // Get y gradient
  Pixel ypixel1 = image[x][y1], ypixel2 = image[x][y2];
  int ry, gy, by, gradY;
  ry = ypixel2.r - ypixel1.r;
  gy = ypixel2.g - ypixel1.g;
  by = ypixel2.b - ypixel1.b;
  gradY = pow(ry, 2) + pow(gy, 2) + pow(by, 2);

  // // DEBUG:
  // cout << "Y-Gradient:" << endl
  //     << "Pixel1: (" << x << ", " << y1 << ") " << ypixel1.r << ", " << ypixel1.g << ", " << ypixel1.b << endl
  //     << "Pixel2: (" << x << ", " << y2 << ") " << ypixel2.r << ", " << ypixel2.g << ", " << ypixel2.b << endl
  //     << endl
  //     << "Ry: " << ry << endl
  //     << "Gy: " << gy << endl
  //     << "By: " << by << endl
  //     << "gradX: " << ry << "^2 + " << gy << "^2 + " << by << "^2 = " << gradY << endl
  //     << endl;

  // Use x/y gradients to get energy, then return
  unsigned int energy = gradX + gradY;

  // // DEBUG:
  // cout << "Energy = " << gradX << " + " << gradY << " = " << energy << endl
  //      << endl;

  return energy;
}

// uncomment functions as you implement them (part 2)

/**
 * Starts at image[start_col][0]
 * Finds pixel in the next row down that has the lowest energy, and adds to seam[]
 *    - formatted as "seam[row] = column"
 * If multiple pixels have same energy, prefer to go forward first, then left, then right
 *    - Forward = col stays same
 *    - Left = col increases (+1)
 *    - Right = col decreases (-1)
*/
unsigned int loadVerticalSeam(Pixel image[][MAX_HEIGHT], unsigned int start_col, unsigned int width, unsigned int height, unsigned int seam[])
{
  // Declare/initialize variables for tracking position an dtotal energy as we iterate through the image
  // totalEnergy = total energy in path
  // currCol = column that path is currently in
  // currRow = row that path is looking at to decide where to move
  unsigned int totalEnergy = energy(image, start_col, 0, width, height);
  unsigned int currCol = start_col, currRow = 0;

  // Start seam[] with initial position data (row = 0, col = start_col)
  seam[currRow] = currCol;

  // Iterate through pixel array to find path
  for (currRow = 1; currRow < height; currRow++) // Starts on row zero, and makes its way down through to the last row of the image
  {
    // Find values for forward, left, and right energies
    // If on an edge, set either left or right energy to negative value so we can know to ignore it
    int fwrdEnergy, leftEnergy, rightEnergy;
    
    fwrdEnergy = energy(image, currCol, currRow, width, height);
    if (currCol == width - 1) // currCol is on rightmost edge --> seam cannot go left --> left = -1
    {
      leftEnergy = -1;
    }
    else // seam can travel left --> left = energy of pixel at [currCol+1, currRow]
    {
      leftEnergy = energy(image, currCol+1, currRow, width, height);
    }
    if (currCol == 0) // currCol is on leftmost edge --> seam cannot go right --> right = -1
    {
      rightEnergy = -1;
    }
    else // seam can travel right --> right = energy of pixel at [currCol-1, currRow]
    {
      rightEnergy = energy(image, currCol-1, currRow, width, height);
    }

    // Figure out which direction seam will go

    // // DEBUG
    // cout << "row " << currRow << ":" << endl
    //      << "fwd   -> " << fwrdEnergy << endl
    //      << "left  -> " << leftEnergy << endl
    //      << "right -> " << rightEnergy << endl;

    // If forward energy is lowest value or tied for lowest value not including invalid energy (-1), then pick forward 
    if ((fwrdEnergy <= leftEnergy || leftEnergy == -1) && (fwrdEnergy <= rightEnergy || rightEnergy == -1))
    {
      // // DEBUG
      // cout << "going forward..." << endl;
      // cout << totalEnergy << " + " << fwrdEnergy << " = ";

      totalEnergy += fwrdEnergy;
    }
    // If left energy is lower than forward energy and right energy or tied with right energy not including invalid energy (-1), then pick left
    else if ((leftEnergy < fwrdEnergy) && (leftEnergy <= rightEnergy || rightEnergy == -1) && (leftEnergy != -1))
    {
      // // DEBUG
      // cout << "going left..." << endl;
      // cout << totalEnergy << " + " << leftEnergy << " = ";

      currCol += 1;
      totalEnergy += leftEnergy;
    }
    // If right energy is lower than forward energy and left energy not including invalid energy (-1), then pick right
    else if ((rightEnergy < fwrdEnergy) && (rightEnergy <= leftEnergy || leftEnergy == -1)  && (rightEnergy != -1))
    {
      // // DEBUG
      // cout << "going right... " << endl;
      // cout << totalEnergy << " + " << rightEnergy << " = ";

      currCol -= 1;
      totalEnergy += rightEnergy;
    }

    // Add path data to seam array
    seam[currRow] = currCol;

    // // DEBUG
    // cout << totalEnergy << endl << endl;
  }

  // Once loop is done, seam[] should contain path of least energy starting at specified column
  // Return total energy in seam as calculated
  return totalEnergy;
}

/**
 * Takes image array of pixels, width, height, and seam array
 * finds column with lowest energy seam
 * updates seam array to contain lowest energy seam
*/
void findMinVerticalSeam(Pixel image[][MAX_HEIGHT], unsigned int width, unsigned int height, unsigned int seam[]) {
  // Declare/initialize variables
  unsigned int minColumn = 0;
  unsigned int minEnergy = loadVerticalSeam(image, 0, width, height, seam);

  // Loop through each column and check for lowest seam energy
  for (unsigned int col = 1; col < width; col++){
    unsigned int seamEnergy = loadVerticalSeam(image, col, width, height, seam);
    if (seamEnergy < minEnergy)
    {
      // Save column with lowest energy and update minEnergy
      minColumn = col;
      minEnergy = seamEnergy;
    }
  }

  // Use minColumn to update seam array to correct values
  loadVerticalSeam(image, minColumn, width, height, seam);
}

/**
 * Takes Pixel array, pointer to width, height, and seam array
 * Updates pixel array to remove all values in seam and move other values to left to fill gap
 * Updates width variable to reflect new width
*/
void removeVerticalSeam(Pixel image[][MAX_HEIGHT], unsigned int& width, unsigned int height, unsigned int verticalSeam[]) {
  // iterate through every row
  for (unsigned int row = 0; row < height; row++)
  {
    // row = row that we are currently on
    // removeCol = column in currRow that is being removed
    unsigned int removeCol = verticalSeam[row];

    // iterate through each column from removeCol to end of image
    for (unsigned int col = removeCol; col < width-1; col++){
      // Will shift every pixel in row that is right of pixel to be removed left by one, 
      // overwriting the removed pixel and decreasing total width by 1
      image[col][row] = image[col + 1][row];
    }
  }

  // after all pixels have been shifted/removed, update width variable
  width -= 1;
}

// EXTRA CREDIT:

// unsigned int loadHorizontalSeam(Pixel image[][MAX_HEIGHT], unsigned int start_row, unsigned int width, unsigned int height, unsigned int seam[]) {
//   // TODO: implement (part 2)
//   return 0;
// }

// void findMinHorizontalSeam(Pixel image[][MAX_HEIGHT], unsigned int width, unsigned int height, unsigned int seam[]) {
//   // TODO: implement (part 2)
// }

// void removeHorizontalSeam(Pixel image[][MAX_HEIGHT], unsigned int width, unsigned int& height, unsigned int horizontalSeam[]) {
//   // TODO: implement (part 2)
// }
