NeuralNetwork
=============

To get started with the demo, SDL is needed. In the demo there are 30 squares, each with it's own neural network. One genetic algorithm trains them all. The goal of each square is to collect as many yellow dots as possible. The neural networks get an 4 inputs: a normalized x and y of the closest mine and a normalized x and y of the direction it is facing. The 2 outputs determine determine how the square moves. The more yellow dots a square collects, the higher it's fitness becomes. Heres a picture.

![alt tag](https://raw.github.com/xuset/NeuralNetwork/master/Screenshot.png)

To compile the demo run.
```
g++ -o demo -lSDL src/*.cpp src/Demo/*.cpp src/NNetwork/*.cpp src/NNetwork/GeneticAlg/*.cpp
```
To compile without the demo, run this. You will need to add in your own int main(void).
```
g++ -o notADemo src/NNetwork/*.cpp src/NNetwork/GeneticAlg/*.cpp
```

Using the code below will create a feedforward neural network with 2 input neurons, 2 hidden layers, and 3 output neurons.
```C++
#define LAYER_COUNT 4
using namespace NeuralNetwork;

int layers[LAYER_COUNT] = { 2, 6, 6, 3 };
NNetwork nn(layers, layerCount);
nn.setSigmoidOutput(true);
```

To create a genetic algorithm that trains a neural network, a sample neural network must be created first. This neural network is not trained but just used to make copies. The code below creates a genetic algorithm with 100 neural networks that have the same attributes as the sample.
```C++
#define LAYER_COUNT 4
using namespace NeuralNetwork;

int layers[LAYER_COUNT] = { 2, 6, 6, 3 };
NNetwork nn(layers, layerCount);
nn.setSigmoidOutput(true);
GeneticAlg alg(nn, 100);
```

To train the networks, you can loop through each network. Then apply an input and determine the network's fitness base on it's output. Calling epoch() runs through one generation on the genetic algorithm.
```C++
#define LAYER_COUNT 4
using namespace NeuralNetwork;

int layers[LAYER_COUNT] = { 2, 6, 6, 3};
NNetwork nn(layers, LAYER_COUNT);
nn.setSigmoidOutput(true);
GeneticAlg alg(nn, 100);

while (alg.getGeneration() < 1000) {

	for (int i = 0; i < alg.getPopulationSize(); i++) {
		Chromosome& chromo = alg.getChromo(i);
		
		double inputs[] = { 1, 1}
		double outputs[3];
		chromo.stimulate(inputs, outputs);
		
		chromo.fitness = 1.0;
	}
	
	alg.epoch();
}
```
