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
    //std::vector<std::string> filters = configFile.getFilterNames();
    std::vector<StandardFilter<double>> filters = configFile.getFilters();
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
    //else if(valueTemp="freq"){
    //    ReadFrequenciesFile reader(fileName);
    //    SoundSignal = reader.construct();
    //}
    else
        throw FileParserException();

    //Apply the filters in order
    std::for_each(filters.begin(), filters.end(),
                  [&SoundSignal](StandardFilter<double> filter) {
                      std::cout <<"Applying Filter: "<< filter.getName()<<" with mask size: "<<filter.getLength()<<std::endl;
                      SoundSignal = filter.apply(SoundSignal); });
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
        SoundSignal.Histogram(binsHistogram,fileName);
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
    fileNameKey = "outputFile";
    iter = data.find(fileNameKey);
    fileName =(iter->second);
    //Checks the cases
    if(valueTemp=="audio")
        SoundSignal.WriteSound(fileName);
    if(valueTemp=="ampl")
        SoundSignal.SaveSignal(fileName);

}