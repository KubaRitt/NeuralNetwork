#ifndef NeuralNetwork_h
#define NeuralNetwork_h
  #include <Arduino.h>
  #include <math.h>
  #include <SD.h>
  #include <SPI.h>

  void sdSave(int HiddenLayerCount , int countW, float Weights[], float Biases[]);
  void InsertCard(int Pin);
  void Generate(int HiddenLayerCount, int NeuronsInHhiddenLayer, int IN, int OUT, float countW, float Weights[], float Inputs[], float Outputs[], float HiddenNeurons[], float Biases[]);
  void sdUpload(int HLC, int NIHL, int IN, int OUT);
  void callOut(int IN, int NeuronsInhiddenLayer, int OUT, int HiddenLayerCount, float Inputs[], float Weights[], float Outputs[], float Biases[], float HiddenNeurons[]);

#endif