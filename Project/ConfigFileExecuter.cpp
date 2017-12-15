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
    std::vector<std::string> filterNames = configFile.getFilterNames();
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
    std::string fileNameKey = "filename";
    iter = data.find(fileNameKey);
    std::string fileName = iter->second;;
    std::cout<<"Opening = " << fileName << std::endl;
    //Checks the cases
    if(valueTemp=="audio"){
        ReadAudioFile reader(fileName);
        SoundSignal = reader.construct();
    }
    else if(valueTemp=="ampl"){
        ReadAmplitudeFile reader(fileName);
        SoundSignal = reader.construct();
    }
    //\todo Implement a Reader class which reads a frequency file and constructs a Signal from it
    else if(valueTemp=="freq"){
        ReadFrequencyFile reader(fileName);
        SoundSignal = reader.construct();
    }
    else
        throw FileParserException();

    //Apply the filters in order
    if(!filterSizes.empty()) {
        //Creates the filters and adds them to the vector
        for(int i=0;i<filterNames.size();++i) {
            std::string filter = filterNames[i];
            int filterSize = filterSizes[i];
            if (filter == "mean") {
                MeanFilter<double> myMean = MeanFilter<double>(filterSize);
                std::cout <<"Applying Filter: "<< myMean.getName()<<" with mask size: "<<myMean.getLength()<<std::endl;
                SoundSignal = myMean.apply(SoundSignal);
            }
            if (filter == "prewitt") {
                PrewittFilter<double> myEdge = PrewittFilter<double>(filterSize);
                std::cout <<"Applying Filter: "<< myEdge.getName()<<" with mask size: "<<myEdge.getLength()<<std::endl;
                SoundSignal = myEdge.apply(SoundSignal);
            }
            if (filter == "laplace") {
                LaplaceFilter<double> myLaplace = LaplaceFilter<double>(filterSize);
                std::cout <<"Applying Filter: "<< myLaplace.getName()<<" with mask size: "<<myLaplace.getLength()<<std::endl;
                SoundSignal = myLaplace.apply(SoundSignal);
            }
            if (filter == "median"){
                MedianFilter myMedian = MedianFilter(filterSize);
                std::cout <<"Applying Filter: "<< myMedian.getName()<<" with mask size: "<<myMedian.getLength()<<std::endl;
                SoundSignal = myMedian.apply(SoundSignal);
            }
            //\todo Can insert here new filter types
        }
    }

    else{   //No sizes are specified
        std::vector<StandardFilter<double>> filters_temp;
        std::for_each(filterNames.begin(), filterNames.end(),
                      [&SoundSignal](std::string filter) {
                          if (filter == "mean") {
                              MeanFilter<double> myMean = MeanFilter<double>();
                              std::cout <<"Applying Filter: "<< myMean.getName()<<" with mask size: "<<myMean.getLength()<<std::endl;
                              SoundSignal = myMean.apply(SoundSignal);
                          }
                          if (filter == "prewitt") {
                              PrewittFilter<double> myEdge = PrewittFilter<double>();
                              std::cout <<"Applying Filter: "<< myEdge.getName()<<" with mask size: "<<myEdge.getLength()<<std::endl;
                              SoundSignal = myEdge.apply(SoundSignal);
                          }
                          if (filter == "laplace") {
                              LaplaceFilter<double> myLaplace = LaplaceFilter<double>();
                              std::cout <<"Applying Filter: "<< myLaplace.getName()<<" with mask size: "<<myLaplace.getLength()<<std::endl;
                              SoundSignal = myLaplace.apply(SoundSignal);
                          }
                          if (filter == "median"){
                              MedianFilter myMedian = MedianFilter();
                              std::cout <<"Applying Filter: "<< myMedian.getName()<<" with mask size: "<<myMedian.getLength()<<std::endl;
                              SoundSignal = myMedian.apply(SoundSignal);
                          }
                          //\todo Can insert here new filter types

                      });
    }
    tempKey = "histogram";
    iter = data.find(tempKey);
    valueTemp = iter->second;
    //Checks the cases
    if(valueTemp=="1"){
        tempKey = "outputHistogramFile";
        std::string fileName;
        auto iter_file = data.find(tempKey);
        fileName =(iter->second);
        tempKey = "histogramBins";
        int binsHistogram;
        iter_file = data.find(tempKey);
        binsHistogram =stoi(iter->second);
        SoundSignal.histogram(binsHistogram,fileName);
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
        SoundSignal.writeFourier(fileName);
    }
    tempKey = "fourierCompute";
    iter = data.find(tempKey);
    valueTemp = iter->second;
    //Checks the cases
    if(valueTemp=="1")
        SoundSignal.fouriertransformCalculator();
    //Type output
    tempKey = "type_output";
    iter = data.find(tempKey);
    valueTemp = iter->second;
    fileNameKey = "outputFile";
    iter = data.find(fileNameKey);
    fileName =(iter->second);
    //Checks the cases
    if(valueTemp=="audio")
        SoundSignal.writeSound(fileName);
    if(valueTemp=="ampl")
        SoundSignal.saveSignal(fileName);

}