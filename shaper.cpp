#include <vector>
#include <string>

#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image.h"
#include "stb_image_write.h"

// contains pixel coordinates & RGB channels
typedef std::vector < std::vector < std::vector < unsigned char > > > image;

// function prototypes
std::vector < image > produce_subsections(image sec1, image sec2, int m, int w, int h);
image morph(image im1, image im2, int w, int h);
image arr_to_im(unsigned char * arr, int w, int h);
unsigned char * im_to_arr(image im, int w, int h);

int main() {

    int n = 3;
    int m = 10;

    int w, h, bpp;
    int i, j;

    unsigned char * io;
    std::vector < image > sections, subsections;

    // read sections
    for (i = 0; i < n; i++) {
        io = stbi_load((std::to_string(i + 1) + ".png").c_str(), & w, & h, & bpp, 3);
        sections.push_back(arr_to_im(io, w, h));
        stbi_image_free(io);
    }

    // produce & save subsections
    for (i = 0; i < n - 1; i++) {
        subsections = produce_subsections(sections[i], sections[i + 1], m, w, h);
        for (j = 0; j < m; j++) {
            io = im_to_arr(subsections[j], w, h);
            stbi_write_bmp((std::to_string(i + 1) + "_" + std::to_string(j + 1) + ".png").c_str(), w, h, 3, io);
            delete[] io;
        }
    }

}

std::vector < image > produce_subsections(image sec1, image sec2, int m, int w, int h) {

    int i;
    std::vector < image > subsections, subsections_scaled;

    // initialize
    subsections.push_back(sec1);
    subsections.push_back(sec2);

    // iterate
    int ncycles = 0;
    while (pow(2, ncycles) - 1 < m) {
        for (i = 0; i < pow(2, ncycles); i++) {
            subsections.insert(subsections.begin() + (2 * i + 1), morph(subsections[2 * i], subsections[2 * i + 1], w, h));
        }
        ncycles++;
    }

    // rescale
    for (i = 0; i < m + 2; i++) {
        subsections_scaled.push_back(subsections[round(pow(2, ncycles) * (1. * i) / (m + 1))]);
    }

    // return subsections only
    subsections_scaled.erase(subsections_scaled.begin());
    subsections_scaled.erase(subsections_scaled.end());

    return subsections_scaled;

}

image morph(image im1, image im2, int w, int h) {

    int i, j;
    image res = im1;
    std::vector < std::vector < bool > > no_mismatch(h, std::vector < bool > (w, false));
    std::vector < std::vector < bool > > mismatch = no_mismatch;

    // initialize mismatch
    for (i = 0; i < h; i++) {
        for (j = 0; j < w; j++) {
            if (im1[i][j][0] != im2[i][j][0] || im1[i][j][1] != im2[i][j][1] || im1[i][j][2] != im2[i][j][2]) {
                mismatch[i][j] = true;
            }
        }
    }

    while (mismatch != no_mismatch) {

        // right neighbors
        for (i = 0; i < h; i++) {
            for (j = 0; j < w - 1; j++) {
                if (mismatch[i][j] == true && mismatch[i][j + 1] == false) {
                    res[i][j] = res[i][j + 1];
                    mismatch[i][j] = false;
                }
            }
        }

        // top neighbors
        for (i = h - 1; i > 0; i--) {
            for (j = 0; j < w; j++) {
                if (mismatch[i][j] == true && mismatch[i - 1][j] == false) {
                    res[i][j] = res[i - 1][j];
                    mismatch[i][j] = false;
                }
            }
        }

        // left neighbors
        for (i = 0; i < h; i++) {
            for (j = w - 1; j > 0; j--) {
                if (mismatch[i][j] == true && mismatch[i][j - 1] == false) {
                    res[i][j] = res[i][j - 1];
                    mismatch[i][j] = false;
                }
            }
        }

        // bottom neighbors
        for (i = 0; i < h - 1; i++) {
            for (j = 0; j < w; j++) {
                if (mismatch[i][j] == true && mismatch[i + 1][j] == false) {
                    res[i][j] = res[i + 1][j];
                    mismatch[i][j] = false;
                }
            }
        }

    }

    return res;

}

image arr_to_im(unsigned char * arr, int w, int h) {

    int i, j;
    image im(h, std::vector < std::vector < unsigned char > > (w, std::vector < unsigned char > (3, 0)));

    for (i = 0; i < h; i++) {
        for (j = 0; j < w; j++) {
            im[i][j][0] = arr[3 * (i * w + j)];
            im[i][j][1] = arr[3 * (i * w + j) + 1];
            im[i][j][2] = arr[3 * (i * w + j) + 2];
        }
    }

    return im;

}

unsigned char * im_to_arr(image im, int w, int h) {

    int i, j;
    unsigned char * arr = new unsigned char[w * h * 3];

    for (i = 0; i < h; i++) {
        for (j = 0; j < w; j++) {
            arr[3 * (i * w + j)] = im[i][j][0];
            arr[3 * (i * w + j) + 1] = im[i][j][1];
            arr[3 * (i * w + j) + 2] = im[i][j][2];
        }
    }

    return arr;
    
}