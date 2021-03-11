#include <vector>
#include <string>
#include <cstring>
#include <iostream>
#include <fstream>
#include <jsoncpp/json/json.h>
#include <jsoncpp/json/writer.h>
#include <bits/stdc++.h> 

using namespace std;

#define db "nodesEdgeDatabase.json"


void FindFlavor(string flavor, vector<int> &b, vector<int> &c){
    ifstream ifs(db);
    Json::Reader reader;
    Json::Value root;
    reader.parse(ifs,root);
    int id = root[0]["flavors"][flavor].asInt();

    int j = 0;
    while(j < root[0]["behaviours"].size()){
        if(root[0]["behaviours"][j]["id"].asInt()/10 == id){
            b.push_back(root[0]["behaviours"][j]["id"].asInt());
        }
        j++;
    }

    j = 0;
    while(j < root[1]["conditions"].size()){
        if(root[1]["conditions"][j]["id"].asInt()/10 == id){
            c.push_back(root[1]["conditions"][j]["id"].asInt());
        }
        j++;
    }

}

void GenerateNodes(const vector<int> &b){
    ifstream ifs(db);
    Json::Reader reader;
    Json::Value root;
    reader.parse(ifs,root);
    string output = root[0]["path"].asString();
    ofstream ofs(output);
    Json::Value event(Json::arrayValue);
    Json::Value child;
    
    Json::Value cat(Json::arrayValue);
    Json::Value behaviours[b.size()] = {};
    Json::Value catParam(Json::arrayValue);
    Json::Value empty(Json::arrayValue);
    Json::Value param;
    int j = 0;
    for(size_t i = 0; i < b.size(); i++){
        j=0;
        while(j < root[0]["behaviours"].size() && root[0]["behaviours"][j]["id"].asInt() != b.at(i)){
            j++;
        }
        if(root[0]["behaviours"][j]["id"].asInt() == b.at(i)){
            behaviours[i]["display_name"] = root[0]["IDsuffix"][to_string(b[i]%10)][0].asString() + root[0]["IDprefix"][to_string(b[i]/10)][0].asString();
            behaviours[i]["id"] = b[i];
            behaviours[i]["name"] = root[0]["IDsuffix"][to_string(b[i]%10)][1].asString() + " " + root[0]["IDprefix"][to_string(b[i]/10)][1].asString();
            for(int k = 0; k < root[0]["behaviours"][j]["params"].size(); k++){
                param["id"] = root[0]["behaviours"][j]["params"][k].asString();
                param["name"] = root[0]["params"][root[0]["behaviours"][j]["params"][k].asString()]["name"].asString();
                param["min"] = root[0]["params"][root[0]["behaviours"][j]["params"][k].asString()]["min"].asDouble();
                param["max"] = root[0]["params"][root[0]["behaviours"][j]["params"][k].asString()]["max"].asDouble();
                param["step"] = root[0]["params"][root[0]["behaviours"][j]["params"][k].asString()]["step"].asDouble();
                catParam.append(param);
            }
            behaviours[i]["params"] = catParam;
            catParam = empty;
            cat.append(behaviours[i]);
        }else{
            cerr << "ERROR: unknown behaviour id = " << b.at(i) << endl;
        }
    }

    child["categories"] = cat;
    child["categories_name"] = "Behavior";
    child["categoryid"] = "s";
    child["typeid"] = 0;

    event.append(child);
    ofs << event;
    ofs.close();
}

void GenerateEdges(const vector<int> &b){
    ifstream ifs(db);
    Json::Reader reader;
    Json::Value root;
    reader.parse(ifs,root);
    string output = root[1]["path"].asString();
    ofstream ofs(output);
    Json::Value event(Json::arrayValue);
    Json::Value child;
    
    Json::Value cat(Json::arrayValue);
    Json::Value conditions[b.size()] = {};
    Json::Value catParam(Json::arrayValue);
    Json::Value empty(Json::arrayValue);
    Json::Value param;
    int j = 0;
    for(size_t i = 0; i < b.size(); i++){
        j=0;
        while(j < root[1]["conditions"].size() && root[1]["conditions"][j]["id"].asInt() != b.at(i)){
            j++;
        }
        if(root[1]["conditions"][j]["id"].asInt() == b.at(i)){
            conditions[i]["display_name"] = root[1]["IDsuffix"][to_string(b[i]%10)][0].asString() + root[0]["IDprefix"][to_string(b[i]/10)][0].asString();
            conditions[i]["id"] = b[i];
            conditions[i]["name"] = root[1]["IDsuffix"][to_string(b[i]%10)][1].asString() + " " + root[0]["IDprefix"][to_string(b[i]/10)][1].asString();
            for(int k = 0; k < root[1]["conditions"][j]["params"].size(); k++){
                param["id"] = root[1]["conditions"][j]["params"][k].asString();
                param["name"] = root[1]["params"][root[1]["conditions"][j]["params"][k].asString()]["name"].asString();
                param["min"] = root[1]["params"][root[1]["conditions"][j]["params"][k].asString()]["min"].asDouble();
                param["max"] = root[1]["params"][root[1]["conditions"][j]["params"][k].asString()]["max"].asDouble();
                param["step"] = root[1]["params"][root[1]["conditions"][j]["params"][k].asString()]["step"].asDouble();
                catParam.append(param);
            }
            conditions[i]["params"] = catParam;
            catParam = empty;
            cat.append(conditions[i]);
        }else{
            cerr << "ERROR: unknown condition id = " << b.at(i) << endl;
        }
    }

    child["categories"] = cat;
    child["categories_name"] = "Condition";
    child["categoryid"] = "c";
    child["typeid"] = 0;

    event.append(child);
    ofs << event;
    ofs.close();
}

void CheckNodes(vector<int> &behaviours){
    for (auto i = behaviours.begin(); i != behaviours.end()-1; ++i){
        for (auto j = i+1; j != behaviours.end(); ++j){
            if(*i == *j){
                behaviours.erase(j);
            }
        }
    }
}

void CheckEdges(vector<int> &conditions){
    for (auto i = conditions.begin(); i != conditions.end()-1; ++i){
        for (auto j = i+1; j != conditions.end(); ++j){
            if(*i == *j){
                conditions.erase(j);
            }
        }
    }
}


int main(int argc, char** argv)
{
    bool isFlavor = false;
    //string flavor = "";
    vector<string> flavors;
    bool isBehaviour = false;
    vector<int> behaviours;
    bool isCondition = false;
    vector<int> conditions;

    for(int i =0; i < argc; ++i){
        if(isFlavor && argv[i][0] != '-'){
            flavors.push_back(argv[i]);
        }
        else if(isFlavor && argv[i][0] == '-'){
            isFlavor = false;
        }
        if(isBehaviour && argv[i][0] != '-'){
            behaviours.push_back(atoi(argv[i]));
        }
        else if(isBehaviour && argv[i][0] == '-'){
            isBehaviour = false;
        }
        if(isCondition && argv[i][0] != '-'){
            conditions.push_back(atoi(argv[i]));
        }
        else if(isCondition && argv[i][0] == '-'){
            isCondition = false;
        }
        if(strcmp(argv[i],"-f") == 0){
            isFlavor = true;
        }
        if(strcmp(argv[i],"-b") == 0){
            isBehaviour = true;
        }
        if(strcmp(argv[i],"-c") == 0){
            isCondition = true;
        }
    }


    for(size_t i = 0; i < flavors.size(); i++){
        FindFlavor(flavors[i], behaviours, conditions);
    }


    CheckNodes(behaviours);
    CheckEdges(conditions);

    sort(behaviours.begin(), behaviours.end());
    sort(conditions.begin(), conditions.end());

    GenerateNodes(behaviours);
    GenerateEdges(conditions);

    return 0;

}