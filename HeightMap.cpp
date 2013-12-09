#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <cassert>
#include <iostream>
#include "Vector3.h"
#include <vector>
using namespace std;
// This function loads a PGM image file
// returns pointer to image if successful, NULL on error
class HeightMap
{
private:
    unsigned char* rawData;
    unsigned char* load(string filename)
    {
        const int BUFSIZE = 128;
        FILE* fp;
        unsigned int read;
        char buf[3][BUFSIZE];
        char* retval_fgets;
        size_t retval_sscanf;

        if ( (fp=fopen(filename.c_str(), "rb")) == NULL)
        {
            return NULL;
        }

        // Read magic number:
        retval_fgets=fgets(buf[0], BUFSIZE, fp);
        if (retval_fgets==NULL)
        {
            fclose(fp);
            return NULL;
        }
        if (strncmp("P5", buf[0], 2) != 0)
        {
            fclose(fp);
            return NULL;
        }

        // Read width and height:
        do
        {
            retval_fgets=fgets(buf[0], BUFSIZE, fp);
            if (retval_fgets==NULL)
            {
                fclose(fp);
                return NULL;
            }
        }
        while (buf[0][0] == '#');
        retval_sscanf=sscanf(buf[0], "%s %s", buf[1], buf[2]);
        if (retval_sscanf!=2)
        {
            fclose(fp);
            return NULL;
        }
        width  = atoi(buf[1]);
        height = atoi(buf[2]);

        // Read maxval:
        do
        {
            retval_fgets=fgets(buf[0], BUFSIZE, fp);
            if (retval_fgets==NULL)
            {
                fclose(fp);
                return NULL;
            }
        }
        while (buf[0][0] == '#');

        // Read image data:
        rawData = new unsigned char[width * height];
        read = fread(rawData, width * height, 1, fp);
        if (read != 1)
        {
            fclose(fp);
            delete[] rawData;
            return NULL;
        }

        fclose(fp);
        return rawData;
    }

    void calcNormals()
    {
        for(int i=0; i<width-1; ++i)
        {
            vector<Vector3> row;
            for(int j=0; j<height-1; ++j)
            {
                Vector3 vec1(0,h[i+1][j]-h[i][j],-1);
                Vector3 vec2(-1,h[i][j+1]-h[i][j],0);
                Vector3 vec3 = vec1*vec2;
                row.push_back(vec3);
            }
            normals.push_back(row);
        }
    }
public:
    int width, height;

    int ** h; //height data
    vector<vector<Vector3> > normals;


    HeightMap()
    {
        load("model/Heightmap.pgm");

        assert(rawData!=NULL);
        h = new int*[height];
        for(int i=0; i<height; ++i)
            h[i] = new int[width];
        for(int i=0; i<height; ++i)
            for(int j=0; j<width; ++j)
                h[i][j] = rawData[width*i+j];

        calcNormals();
    }

};
