#include <stdio.h>
#include <stdlib.h>

#include <fstream>
#include <vector>
#include <map>
#include <string>
#include <sstream>
#include <iostream>

using namespace std;
using std::ifstream;
using std::stringstream;

vector<string> splitLine(string line) {
  stringstream lineStream(line);
  string cell;
  vector<string> result;
  while(getline(lineStream, cell, ','))
  {
      result.push_back(cell);
  }
  return result;
}


double parseDouble(string value) {
  size_t sz;
  double val = stod(value, &sz);
  return val;
}
vector<vector<double>> getData() {
//open file stream that reads this file (already in our replit)
  ifstream str("snod.csv");

  //data will go here
  vector<vector<double>> data;

  string line;

  //loop until we get to the end of the file
  while (true) {
    getline(str,line);

    //line length will be zero when we get to end of file
    if (line.length() == 0) {
      //break exits the loop
      break;
    }

    vector<string> row = splitLine(line);
    vector<double> rowValues;
    for (int i = 0; i < row.size(); i++) {
      rowValues.push_back(parseDouble(row[i]));
    }
    data.push_back(rowValues);
  }
  return data;
}

void writeImage(vector<vector<double>> data) {
  FILE *imageFile;
   int x,y,pixel,height=data.size(),width=data[0].size();

   imageFile=fopen("image.pgm","wb");
   if(imageFile==NULL){
      perror("ERROR: Cannot open output file");
      exit(EXIT_FAILURE);
   }

   fprintf(imageFile,"P5\n");           // P5 filetype
   fprintf(imageFile,"%d %d\n",width,height);   // dimensions
   fprintf(imageFile,"255\n");          // Max pixel

   /* Now write a greyscale ramp */
   for(x=0;x<height;x++){
      for(y=0;y<width;y++){
         pixel=(int)(data[x][y]*100);
         fputc(pixel,imageFile);
      }
   }

   fclose(imageFile);
}

/*
  min lat = 36.69578069273795
  min lon = -110.07023810278962
  max lat = 41.49181240222188
  max lon = -101.27628856757693
*/

/*STUDENT: write a function that will take a lat/lon as the
           input and find the snow depth value for that lat/lon
           and return it
*/
double getSnowDepthValue (double lat, double lon, vector<vector<double>> data) {
  double max_lat = 41.49181240222188;
  double max_lon = -101.27628856757693;
  double min_lat = 36.69578069273795;
  double min_lon = -110.07023810278962;
  double height = data.size();
  double width = data[0].size();
  double delta_y = (max_lat - min_lat) / height;
  double delta_x = (max_lon - min_lon) / width;
  double y = (lat - min_lat) / delta_y;
  double x = (lon - min_lon) / delta_x;
  //int index_x = (int)x;
  //int index_y = (int)y;
  //cout << x <<", " << y << " -- " << index_x << ", " << index_y << endl;
  double value = data[y][x];
  return value;
}

int main(){

  vector<vector<double>> data = getData();
  
  //STUDENT: lookup the lat/lon for coordinates 40.0106, -105.266
  double val1 = getSnowDepthValue(40.0106, -105.266, data);
  cout << "snow depth for first point is " << val1 << endl;

  //STUDENT: lookup the lat/lon for coordinates 40.1383, -105.1287
  double val2 = getSnowDepthValue(40.1383, -105.1287, data);
  cout << "snow depth for second point is " << val2 << endl;

}
