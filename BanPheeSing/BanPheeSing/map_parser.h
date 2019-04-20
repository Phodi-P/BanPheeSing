#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include<sstream>
#include<cstdlib>

#include"tilemap.h"

namespace mp {
  void parseMap(std::string path,Level level){
    std::ifstream fr;
    fr.open(path);
    std::string line;
    int mode;
    while(getline(fr,line)){
      //Mode
      if(line == "Object") {mode = 1; continue;}
      else if(line == "Map") {mode = 2; continue;}

      //Read File with format
      if(mode == 1){
        if(line[0] == '*') continue;
        char type[100];
        float x,y,w,h;
        sscanf(line.c_str(),"%[^,],%f,%f,%f,%f",type,&x,&y,&w,&h);
        //print object detail
        // std::cout << type << x<< y << w <<h<< std::endl;
        //
      }else if(mode == 2){
        if(line[0] == '*') continue;
        //layerName,width,hegih
        char layer[100];
        int w,h;
        sscanf(line.c_str(),"%[^,],%d,%d",layer,&w,&h);
        //print layer detail
        // std::cout << layer << w << h << std::endl;
        //

        //map data
        std::vector<int> datas;
        for(int i=0;i<h;i++) {
          getline(fr,line);
          std::stringstream lineStream(line);
          std::string data;
            for(int j=0;j<w;j++) {
              getline(lineStream,data,',');
              datas.push_back(stoi(data));
            }
        }
        //print map data
        // for(int i=0;i<h;i++){
        //   for(int j=0;j<w;j++) std::cout<<datas[(i*w)+j] << " ";
        //   std::cout << "\n";
        //
        // }
        //

        TileMapData *p;
		std::string strLayer = layer;
        if (strLayer == "bot") p = &level.botData;
		if (strLayer == "mid") p = &level.midData;
		if (strLayer == "top") p = &level.topData;

         p->mapData = datas;
         p->layer = layer;
         p->mapWidth = w;
         p->mapHeight = h;
      }
    }
    fr.close();
  }
}
