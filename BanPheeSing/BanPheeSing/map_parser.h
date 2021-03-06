#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include<sstream>
#include<cstdlib>

#include"tilemap.h"

namespace mp {
  void parseMap(std::string path,Level &level){
    std::ifstream fr;
    fr.open(path.c_str());
    std::string line;
    int mode;
	bool mapReadComplete = false;
    while(getline(fr,line)){
      //Mode
      if(line == "Object") {mode = 1; continue;}
      else if(line == "Map") {mode = 2; continue;}
	  else if (line == "Event") { mode = 3; continue; }
	  else if (line == "Door") { mode = 4; continue; }
	  
      //Read File with format
      if(mode == 1){
        if(line[0] == '*') continue;
		std::stringstream sObj(line);
		std::string curObj;

		getline(sObj, curObj, ',');
		std::string type = curObj;
		//std::cout << curObj << " ";

		getline(sObj, curObj, ',');
		int propertiesCount = std::stoi(curObj);
		//std::cout << curObj << " ";

		//Reading properties
		//std::string event_id, event_type;
		for (int i = 0; i < propertiesCount; i++)
		{
			getline(sObj, curObj, ',');
			//if (i == 0) event_id = curObj;
			//if (i == 1) event_type = curObj;
		}

		getline(sObj, curObj, ',');
		int x = std::stoi(curObj);
		//std::cout << curObj << " ";

		getline(sObj, curObj, ',');
		int y = std::stoi(curObj);
		//std::cout << curObj << " ";

		getline(sObj, curObj, ',');
		int w = std::stoi(curObj);
		//std::cout << curObj << " ";

		getline(sObj, curObj, ',');
		int h = std::stoi(curObj);
		//std::cout << curObj << " ";

		//std::cout << std::endl;

        //sscanf_s(line.c_str(),"%[^,],%f,%f,%f,%f",type,sizeof(type),&x,&y,&w,&h);
		//sscanf_s(line.c_str(), "%[^,],%f,%f,%f,%f", type, &x, &y, &w, &h);
        //print object detail
        // std::cout << type << x<< y << w <<h<< std::endl;
        //

		//Obj data
		level.objData.push_back(ObjSpawnData(type, sf::Vector2f(x, y), sf::Vector2f(w, h)));

      }else if(mode == 2){
        if(line[0] == '*') continue;
        //layerName,width,hegih
        //char layer[100];
		std::stringstream sMap(line);
		std::string curMap;
        
		getline(sMap, curMap, ',');
		std::string layer = curMap;
		//std::cout << curMap << " ";

		getline(sMap, curMap, ',');
		int propertiesCount = std::stoi(curMap);
		//std::cout << curObj << " ";

		//Reading properties
		//std::string event_id, event_type;
		for (int i = 0; i < propertiesCount; i++)
		{
			getline(sMap, curMap, ',');
			//if (i == 0) event_id = curObj;
			//if (i == 1) event_type = curObj;
		}

		getline(sMap, curMap, ',');
		int w = std::stoi(curMap);
		//std::cout << curMap << " ";

		getline(sMap, curMap, ',');
		int h = std::stoi(curMap);
		//std::cout << curMap << " ";

		//std::cout << std::endl;
        //sscanf_s(line.c_str(),"%[^,],%d,%d",layer,sizeof(layer),&w,&h);
		//sscanf_s(line.c_str(), "%[^,],%d,%d", layer, sizeof(layer), &w, &h);
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
              datas.push_back(std::stoi(data));
            }
        }
		mapReadComplete = true;
        //print map data
		/*
         for(int i=0;i<h;i++){
           for(int j=0;j<w;j++) std::cout<<datas[(i*w)+j] << " ";
           std::cout << "\n";
        
        }*/

        //TileMapData *p = NULL;
		//if (layer == "bot") p = &level.botData;
		//if (layer == "mid") p = &level.midData;
		//if (layer == "top") p = &level.topData;
		//p->mapData = datas;

		/*for (int i = 0; i < level.tileData.size(); i++) { 
			std::cout << "This is "<< layer << "\n";
			level.tileData[i].mapData = datas;
			level.tileData[i].layer = layer;
			level.tileData[i].mapWidth = w;
			level.tileData[i].mapHeight = h;
		}*/
		if (mapReadComplete) {
			//std::cout << "This is " << layer << "\n";
			/*
			level.tileData[i].mapData = datas;
			level.tileData[i].layer = layer;
			level.tileData[i].mapWidth = w;
			level.tileData[i].mapHeight = h;
			*/
			/*
			TileMapData td;
			td.mapData = datas;
			td.layer = layer;
			td.mapWidth = w;
			td.mapHeight = h;*/

			//level.tileData.push_back(td);
			level.tileData.push_back(TileMapData(layer, datas, w, h));
		}
		/*
		 if (layer == "bot" && mapReadComplete)
		 {
			 std::cout << "This is bot\n";
			 level.botData.mapData = datas;
			 level.botData.layer = layer;
			 level.botData.mapWidth = w;
			 level.botData.mapHeight = h;
		 }

		 if (layer == "mid" && mapReadComplete)
		 {
			 std::cout << "This is mid\n";
			 level.midData.mapData = datas;
			 level.midData.layer = layer;
			 level.midData.mapWidth = w;
			 level.midData.mapHeight = h;
		 }


		 if (layer == "top" && mapReadComplete)
		 {
			 std::cout << "This is top\n";
			 level.topData.mapData = datas;
			 level.topData.layer = layer;
			 level.topData.mapWidth = w;
			 level.topData.mapHeight = h;
		 }
		 */
      }else if (mode == 3) {
		  if (line[0] == '*') continue;
		  std::stringstream sObj(line);
		  std::string curObj;

		  getline(sObj, curObj, ',');
		  std::string type = curObj;
		  //std::cout << curObj << " ";

		  getline(sObj, curObj, ',');
		  int propertiesCount = std::stoi(curObj);
		  //std::cout << curObj << " ";

		  //Reading properties
		  std::string event_id, event_type;
		  for (int i = 0; i < propertiesCount; i++)
		  {
			  getline(sObj, curObj, ',');
			  if (i == 0) event_id = curObj;
			  if (i == 1) event_type = curObj;
		  }

		  getline(sObj, curObj, ',');
		  int x = std::stoi(curObj);
		  //std::cout << curObj << " ";

		  getline(sObj, curObj, ',');
		  int y = std::stoi(curObj);
		  //std::cout << curObj << " ";

		  getline(sObj, curObj, ',');
		  int w = std::stoi(curObj);
		  //std::cout << curObj << " ";

		  getline(sObj, curObj, ',');
		  int h = std::stoi(curObj);
		  //std::cout << curObj << " ";

		  //std::cout << std::endl;

		  //sscanf_s(line.c_str(),"%[^,],%f,%f,%f,%f",type,sizeof(type),&x,&y,&w,&h);
		  //sscanf_s(line.c_str(), "%[^,],%f,%f,%f,%f", type, &x, &y, &w, &h);
		  //print object detail
		  // std::cout << type << x<< y << w <<h<< std::endl;
		  //

		  //Obj data
		  level.objData.push_back(ObjSpawnData(type, sf::Vector2f(x, y), sf::Vector2f(w, h), event_id, event_type));

	  }
	  else if (mode == 4) {
	  if (line[0] == '*') continue;
	  std::stringstream sObj(line);
	  std::string curObj;

	  getline(sObj, curObj, ',');
	  std::string type = curObj;
	  //std::cout << curObj << " ";

	  getline(sObj, curObj, ',');
	  int propertiesCount = std::stoi(curObj);
	  //std::cout << curObj << " ";

	  //Reading properties
	  std::string door_id;
	  for (int i = 0; i < propertiesCount; i++)
	  {
		  getline(sObj, curObj, ',');
		  if (i == 0) door_id = curObj;
	  }

	  getline(sObj, curObj, ',');
	  int x = std::stoi(curObj);
	  //std::cout << curObj << " ";

	  getline(sObj, curObj, ',');
	  int y = std::stoi(curObj);
	  //std::cout << curObj << " ";

	  getline(sObj, curObj, ',');
	  int w = std::stoi(curObj);
	  //std::cout << curObj << " ";

	  getline(sObj, curObj, ',');
	  int h = std::stoi(curObj);
	  //std::cout << curObj << " ";

	  //std::cout << std::endl;

	  //sscanf_s(line.c_str(),"%[^,],%f,%f,%f,%f",type,sizeof(type),&x,&y,&w,&h);
	  //sscanf_s(line.c_str(), "%[^,],%f,%f,%f,%f", type, &x, &y, &w, &h);
	  //print object detail
	  // std::cout << type << x<< y << w <<h<< std::endl;
	  //

	  //Obj data
	  level.objData.push_back(ObjSpawnData(type, sf::Vector2f(x, y), sf::Vector2f(w, h), door_id));

	  }
    }
    fr.close();
  }
}
