//
// Created by shernand on 12/11/17.
//

#include "ConfigFileExecuter.h"
ConfigFileExecuter::ConfigFileExecuter(ConfigFileParser pConfigFile) {
    configFile = pConfigFile;
}

ConfigFileExecuter::~ConfigFileExecuter(){}

void ConfigFileExecuter::execute(){
    //Gets the parsed values
    std::vector<std::string> filters = configFile.getFilters();
    std::vector<int> filterSizes = configFile.getFilterSizes();
    std::map<std::string,std::string> data = configFile.getData();
    //Constructs the Signal
    Signal SoundSignal;
    auto it = data.begin();
    auto end = data.end();
    //Type input
    std::string tempKey = "type_input";
    auto iter = data.find(tempKey);
    std::string valueTemp = iter->second;
    //Checks the cases
    if(valueTemp=="audio"){
        tempKey = "filename";
        auto iter_file = data.find(tempKey);
        std::string fName = iter_file->second;
        std::cout<<"Opening = " << fName << std::endl;
        ReadAudioFile Sound(fName);
        SoundSignal = Sound.construct();
    }

    //Apply the filters in order
    if(filterSizes.empty()){
        std::for_each(filters.begin(), filters.end(),
                      [&SoundSignal](std::string filter) {
                          std::cout <<"Applying Filter: "<< filter <<std::endl;
                          if(filter=="mean"){
                              MeanFilter<double> myMean = MeanFilter<double>();
                              SoundSignal = myMean.apply(SoundSignal);
                          }
                          if(filter=="prewitt"){
                              PrewittFilter<double> myEdge = PrewittFilter<double>();
                              SoundSignal = myEdge.apply(SoundSignal);
                          }
                          if(filter=="laplace"){
                              LaplaceFilter<double> myLaplace = LaplaceFilter<double>();
                              SoundSignal = myLaplace.apply(SoundSignal);
                          }
                          //\todo Can insert here new filter types

                      });
    }
    else{
        for(int i=0;i<filters.size();++i){
            std::string filter = filters[i];
            int filterSize = filterSizes[i];
            std::cout <<"Applying Filter: "<< filter <<" with maskSize: "<<filterSize<<std::endl;
            if(filter=="mean"){
                MeanFilter<double> myMean = MeanFilter<double>(filterSize);
                SoundSignal = myMean.apply(SoundSignal);

            }
            if(filter=="prewitt"){
                PrewittFilter<double> myEdge = PrewittFilter<double>(filterSize);
                SoundSignal = myEdge.apply(SoundSignal);
            }
            if(filter=="laplace"){
                LaplaceFilter<double> myLaplace = LaplaceFilter<double>(filterSize);
                SoundSignal = myLaplace.apply(SoundSignal);
            }
            //\todo Can insert here new filter types
        }
    }

    tempKey = "fourierWrite";
    iter = data.find(tempKey);
    valueTemp = iter->second;
    //Checks the cases
    if(valueTemp=="1"){
        std::string fileNameKey = "outputFourierFile";
        std::string fileName;
        auto iter_file = data.find(fileNameKey);
        fileName =(iter->second);
        SoundSignal.FourierTransformCalculator(0,500,fileName);
    }
    tempKey = "fourierCompute";
    iter = data.find(tempKey);
    valueTemp = iter->second;
    //Checks the cases
    if(valueTemp=="1")
        SoundSignal.FourierTransformCalculator(0,500);
    //Type output
    tempKey = "type_output";
    iter = data.find(tempKey);
    valueTemp = iter->second;
    std::string fileNameKey = "outputFile";
    std::string fileName;
    auto iter_file = data.find(fileNameKey);
    fileName =(iter_file->second);
    //Checks the cases
    if(valueTemp=="audio")
        SoundSignal.WriteSound(fileName);
    if(valueTemp=="ampl")
        SoundSignal.SaveSignal(fileName);

}