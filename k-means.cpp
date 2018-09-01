//
//  main.cpp
//  k-means
//
//  Created by Mauricio Matter Donato on 31/08/18.
//  Copyright © 2018 Mauricio Matter Donato. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cmath>
#include <ctime>
#include <cstdlib>

struct DataPoint {
    double x;
    double y;
    int n_cluster;
};
typedef struct DataPoint data_point_t;


struct Centroid {
    double x;
    double y;
};
typedef struct Centroid centroid_t;

 
std::vector<std::string> split(std::string str, char delimitir) {
    std::stringstream stringStream(str);
    std::vector<std::string> stringPlaceholder;
    std::string token;
    
    while(std::getline(stringStream, token, delimitir)) {
        stringPlaceholder.push_back(token);
    }
    
    return stringPlaceholder;
}


std::vector<data_point_t> read_file(std::string filename) {
    std::ifstream inputFile;
    std::vector<data_point_t> dataset;
    
    inputFile.open(filename);
    if(!inputFile.is_open()) {
        std::cout << "Fail to open file: " << filename << std::endl;
        exit(1);
    }
    
    std::string line;
    while(!inputFile.eof()) {
        std::getline(inputFile, line);
        
        std::vector<std::string> str = split(line, ' ');
        if(str.size() > 0) {
            const char* x = str[1].c_str();
            const char* y = str[2].c_str();
            data_point_t point = { std::atof(x), std::atof(y), -1 };
            dataset.push_back(point);
        }
    }
    
    inputFile.close();
    
    return dataset;
}


centroid_t* initialize_centroids(std::vector<data_point_t> *dataset, int kClusters) {
    centroid_t *c = new centroid_t[kClusters];
    int gap = dataset->size() / kClusters;
    int position = 0;
    
    for(auto i = 0; i < kClusters; i++) {
        c[i] = {dataset->at(position).x, dataset->at(position).y};
        position += gap;
    }
    
    return c;
}


double euclidean_distance(data_point_t point, centroid_t centroid) {
    double x = std::pow((point.x - centroid.x), 2) + std::pow((point.y - centroid.y), 2);
    return std::sqrt(x);
}


bool assign_points_in_clusters(std::vector<data_point_t> *dataset, centroid_t *centroids, int kClusters) {
    bool shouldContinue = false;
    int currentCluster = 0;
    
    for(auto i = 0; i < dataset->size(); i++) {
        double minDistance = std::pow(10.0, 10.0);
        
        for(auto j = 0; j < kClusters; j++) {
            double distance = euclidean_distance(dataset->at(i), centroids[j]);
            if(distance < minDistance) {
                currentCluster = j;
                minDistance = distance;
            }
        }
        
        if(dataset->at(i).n_cluster != currentCluster) {
            dataset->at(i).n_cluster = currentCluster;
            shouldContinue = true;
        }
    }
    
    return shouldContinue;
}


void recalculate_clusters_position(std::vector<data_point_t> *dataset, centroid_t *centroids, int kClusters) {
    for(auto i = 0; i < kClusters; i++) {
        int totalPoints = 0;
        long double distanceXAxis = 0.0;
        long double distanceYAxis = 0.0;
        
        for(auto j = 0; j < dataset->size(); j++) {
            if(dataset->at(j).n_cluster == i) {
                distanceXAxis += dataset->at(j).x;
                distanceYAxis += dataset->at(j).y;
                totalPoints++;
            }
        }
        
        centroids[i].x = (double) distanceXAxis / totalPoints;
        centroids[i].y = (double) distanceYAxis / totalPoints;
    }
}


void k_means(std::vector<data_point_t> *dataset, int kClusters) {
    centroid_t *centroids = initialize_centroids(dataset, kClusters);
    bool shouldConinue = false;
    
    do {
        shouldConinue = assign_points_in_clusters(dataset, centroids, kClusters);
        recalculate_clusters_position(dataset, centroids, kClusters);
    } while (shouldConinue);
    
    for(auto i = 0; i < kClusters; i++) {
        std::cout << "Centroid " << i+1 << " position: " << centroids[i].x << ", " << centroids[i].y << std::endl;
    }

    delete[] centroids; 
}


/*
 * Input file format:
 * Label X_Axis_Value Y_Axis_Value without any text
 * 
 * Input example:
 *     312992 28.0 1.5
 *     322583 27.3 2.27
 *     248164 17.0 5.46
 */ 
int main(int argc, const char * argv[]) {
    if(argc < 3) {
        std::cout << "Execution: ./kmeans [dataset_file] [k_clusters]" << std::endl;
        exit(1);
    }
    
    int kClusters = std::atoi(argv[2]);
    if(kClusters <= 0) {
        std::cout << "Error: K must be greater than 0!" << std::endl;
        exit(2);
    }

    std::vector<data_point_t> dataset = read_file(argv[1]);
    if(kClusters > dataset.size()) {
        std::cout << "Error: K must be less or iqual than dataset size!" << std::endl;
        exit(3);
    }
    
    k_means(&dataset, kClusters);
    dataset.clear();


    return 0;
}
