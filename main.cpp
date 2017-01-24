#include <iostream>
#include <fstream>
#include <cstdlib> // for exit()

using namespace std;

int truncate(int value)
{
    if (value < 0) value = 0;

    if (value > 255) value = 255;

    return value;
}

int adjustBrightness(int value, int brightness)
{
    //cout << "adjusting to " << value + brightness;
    return truncate(value + brightness);
}

int main()
{
    string filename;
    string line;

    cout << "Enter the filename" << endl;
    cin >> filename;

    ifstream infile(filename.c_str());

    // If we couldn't open the output file stream for reading
    if (!infile)
    {
        // Print an error and exit
        cerr << "Uh oh " + filename + " could not be opened for reading!" << endl;
        exit(1);
    }

    int brightness;
    cout << "Enter the brightness -255 to 255" << endl;
    cin >> brightness;


    // Ignore first two lines
    getline(infile,line);
    getline(infile,line);

    int width, height, img_size;

    infile >> width;
    infile >> height;

    if (width < 0 || height < 0)
    {
        cerr << "Uh oh  invalid image size" << endl;
        exit(1);
    }

    img_size = width * height * 3;

    cout << "Width " << width << ", Height " << height<< endl;
    cout << "Processing image..." << endl;

    // Δυναμική δέσμευση μνήμης του πίνακα
    int *pixels = new int[img_size]; // use array new.  Note that length does not need to be constant!



    int n;
    int i = 0;
    while (infile >> n)
    {

        pixels[i] = adjustBrightness(n, brightness);
        //cout << i << endl;

        //cout << "Pixel " << pixels[i] << endl;
        i++;

    }


    cout << "Writing Image " << endl;
    // ofstream is used for writing files
    // We'll make a file called Sample.dat
    ofstream outfile("out.ppm");

    // If we couldn't open the output file stream for writing
    if (!outfile)
    {
        // Print an error and exit
        cerr << "Uh oh, Sample.dat could not be opened for writing!" << endl;
        exit(1);
    }



    outfile << "P3" << endl;
    outfile << "# CREATOR: GIMP PNM Filter Version 1.1" << endl;
    outfile << width << " " << height << endl;

    for(int i = 0; i < img_size; i++)
    {
        outfile << pixels[i] << endl;
    }




    return 0;
}
