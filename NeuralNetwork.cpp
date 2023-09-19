#include <NeueralNetwork.h>

void InsertCard(int Pin){
   if(!SD.begin(Pin)){
    Serial.print("No SD card");
    while(1);
    }

  Serial.println("Inserted Sd Card");
}

void sdSave(int HiddenLayerCount, int countW, float Weights[], float Biases[]){
  File neurons = SD.open("neurons.txt", FILE_WRITE);

  

  if(neurons){
    for(int i = 0; i < countW; i++){
      neurons.println(Weights[i]);
    }

    for(int i = 0; i < HiddenLayerCount; i++){
      neurons.println(Biases[i]);
    }

    neurons.close();

    Serial.println("saved");
  }
}

void Generate(int HiddenLayerCount, int NeuronsInHhiddenLayer, int IN, int OUT, int countW, float Weights[], float Inputs[], float Outputs[], float HiddenNeurons[], float Biases[]){
  for(int i = 0; i < IN; i++){
    for (int x = 0; x < NeuronsInHhiddenLayer; x++) {
      countW++;
    }
  }

  for(int i = 0; i < (HiddenLayerCount - 1); i++){
    for (int x = 0; x < NeuronsInHhiddenLayer; x++) {
      countW += NeuronsInHhiddenLayer;
    }
  }

  for(int i = 0; i < OUT; i++){
    for (int x = 0; x < NeuronsInHhiddenLayer; x++) {
      countW++;
    }
  }

  HiddenNeurons[NeuronsInHhiddenLayer * HiddenLayerCount];
  Weights[countW];
  Inputs[IN];
  Outputs[OUT];
  Biases[HiddenLayerCount];

  for(int i = 0; i < countW; i++) {
    Weights[i] = random(-1000, 1000) / 1000.0;
  }

  for(int i = 0; i < HiddenLayerCount; i++) {
    Biases[i] = random(-1000, 1000) / 1000.0;
  }

  Serial.println("weights");
  for(int i = 0; i < countW; i++){
    Serial.println(Weights[i]);
  }
  
  Serial.println("biases");
  for(int i = 0; i < HiddenLayerCount; i++){
    Serial.println(Biases[i]);
  }
}

void callOut(int IN, int NeuronsInhiddenLayer, int OUT, int HiddenLayerCount, float Inputs[], float Weights[], float Outputs[], float Biases[], float HiddenNeurons[]){
  int trackOfweights = 0;
  int countOfNeurons = -1;
  int ongoingnumber = 0;
  Serial.println("In 1");
  for(int i = 0; i < NeuronsInhiddenLayer; i++){
    ongoingnumber = 0;
    for(int x = 0; x < IN; x++){
      ongoingnumber += Inputs[x] * Weights[trackOfweights];
      trackOfweights++;
    }
    HiddenNeurons[i] = max(0.0 , ongoingnumber);
    Serial.println(HiddenNeurons[i]);
    countOfNeurons++;
  }

  Serial.println("H H x");
  for(int i = 0; i < (HiddenLayerCount - 1); i++){
    for(int x = 0; x < NeuronsInhiddenLayer; x++){
      ongoingnumber = 0;
      for(int z = 0; z < NeuronsInhiddenLayer; z++){
        ongoingnumber += HiddenNeurons[countOfNeurons - z] * Weights[trackOfweights];
        trackOfweights++;
      }
      HiddenNeurons[x] = max(0.0, ongoingnumber);
      Serial.println(HiddenNeurons[x]);
    }
    countOfNeurons += NeuronsInhiddenLayer;
  }

  for(int i = 0; i < OUT; i++){
    ongoingnumber = 0;
    for(int x = 0; x < NeuronsInhiddenLayer; x++){
      ongoingnumber += HiddenNeurons[countOfNeurons - x] * Weights[trackOfweights];
      trackOfweights++;  
    }
    Outputs[i] = ongoingnumber;
  }
  
  for(int i = 0; i < OUT; i++){
    Outputs[i] = 1.0 / (1.0 + exp(-Outputs[i]));
  }
}

void sdUpload(int HiddenLayerCount, int NeuronsInHiddenLayer, int IN, int OUT, float Weights[], float Biases[], float Inputs[], float Outputs[], float HiddenNeurons[], int countW){
  for(int i = 0; i < IN; i++){
    for (int x = 0; x < NeuronsInHiddenLayer; x++) {
      countW++;
    }
  }

  for(int i = 0; i < (HiddenLayerCount - 1); i++){
    for (int x = 0; x < NeuronsInHiddenLayer; x++) {
      countW += NeuronsInHiddenLayer;
    }
  }

  for(int i = 0; i < OUT; i++){
    for (int x = 0; x < NeuronsInHiddenLayer; x++) {
      countW++;
    }
  }

  HiddenNeurons[NeuronsInHiddenLayer * HiddenLayerCount];
  Weights[countW];
  Inputs[IN];
  Outputs[OUT];
  Biases[HiddenLayerCount];

  File myFile = SD.open("neurons.txt");

  if(myFile){
    for(int i = 0; i < countW; i++){
      String line = myFile.readStringUntil('\n');
      float weight = atof(line.c_str());
      Weights[i] = weight;
      Serial.println(Weights[i]);
    }

    for(int i = 0; i < HiddenLayerCount; i++){
      String line = myFile.readStringUntil('\n');
      float weight = atof(line.c_str());
      Biases[i] = weight;
      Serial.println(Biases[i]);
    }
  }
}